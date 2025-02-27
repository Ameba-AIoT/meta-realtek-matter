/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include "LightingAppCommandDelegate.h"
#include <AppMain.h>

#include <app-common/zap-generated/ids/Attributes.h>
#include <app-common/zap-generated/ids/Clusters.h>
#include <app/ConcreteAttributePath.h>
#include <app/server/Server.h>
#include <lib/support/logging/CHIPLogging.h>

#if defined(CHIP_IMGUI_ENABLED) && CHIP_IMGUI_ENABLED
#include <imgui_ui/ui.h>
#include <imgui_ui/windows/light.h>
#include <imgui_ui/windows/occupancy_sensing.h>
#include <imgui_ui/windows/qrcode.h>

#endif

#include "MatterPWM.h"
#include "MatterRGBLED.h"

using namespace chip;
using namespace chip::app;
using namespace chip::app::Clusters;

namespace {

constexpr char kChipEventFifoPathPrefix[] = "/tmp/chip_lighting_fifo_";
NamedPipeCommands sChipNamedPipeCommands;
LightingAppCommandDelegate sLightingAppCommandDelegate;
} // namespace

void MatterPostAttributeChangeCallback(const chip::app::ConcreteAttributePath & attributePath, uint8_t type, uint16_t size,
                                       uint8_t * value)
{
    if (attributePath.mClusterId == OnOff::Id && attributePath.mAttributeId == OnOff::Attributes::OnOff::Id)
    {
        switch (*value)
        {
            case 0:
            {
                ChipLogProgress(AppServer, "OnOff Cluster is switched to OFF");
                MatterPWM.Disable();
                MatterRGBLED.Disable();
                break;
            }
            case 1:
            {
                ChipLogProgress(AppServer, "OnOff Cluster is switched to ON");
                MatterPWM.Enable();
                MatterRGBLED.Enable();
                break;
            }
            default:
            {
                ChipLogError(AppServer, "OnOff cluster set value: %d", *value);
                break;
            }
        }
    }
	else if (attributePath.mClusterId == LevelControl::Id && attributePath.mAttributeId == LevelControl::Attributes::CurrentLevel::Id)
	{
		ChipLogProgress(AppServer, "LevelControl::CurrentLevel change to: %d", *value);
        MatterPWM.SetDutyCycle(*value);
        MatterRGBLED.SetVLEDColor(*value);
	}
    else if (attributePath.mClusterId == ColorControl::Id)
    {
        if (attributePath.mAttributeId == ColorControl::Attributes::CurrentHue::Id)
        {
            ChipLogProgress(AppServer, "ColorControl::CurrentHue change to: %u", *value);
            MatterRGBLED.SetHLEDColor(*value);
        }
        else if (attributePath.mAttributeId == ColorControl::Attributes::CurrentSaturation::Id)
        {
            ChipLogProgress(AppServer, "ColorControl::CurrentSaturation change to: %u", *value);
            MatterRGBLED.SetSLEDColor(*value);
        }
        else if (attributePath.mAttributeId == ColorControl::Attributes::CurrentX::Id)
        {
            ChipLogProgress(AppServer, "ColorControl::CurrentX change to: %u", *value);
            MatterRGBLED.SetXLEDColor(*value);
        }
        else if (attributePath.mAttributeId == ColorControl::Attributes::CurrentY::Id)
        {
            ChipLogProgress(AppServer, "ColorControl::CurrentY change to: %u", *value);
            MatterRGBLED.SetYLEDColor(*value);
        }
        else if (attributePath.mAttributeId == ColorControl::Attributes::ColorTemperatureMireds::Id)
        {
            ChipLogProgress(AppServer, "ColorControl::ColorTemperatureMireds change to: %u", *value);
            MatterRGBLED.SetTemperatureLEDColor(*value);
        }
    }
    else
    {
        ChipLogError(AppServer, "Unknown cluster ID: " ChipLogFormatMEI, ChipLogValueMEI(attributePath.mClusterId));
        ChipLogError(AppServer, "Unknown attribute ID: " ChipLogFormatMEI, ChipLogValueMEI(attributePath.mAttributeId));
    }
	
}

/** @brief OnOff Cluster Init
 *
 * This function is called when a specific cluster is initialized. It gives the
 * application an opportunity to take care of cluster initialization procedures.
 * It is called exactly once for each endpoint where cluster is present.
 *
 * @param endpoint   Ver.: always
 *
 * TODO Issue #3841
 * emberAfOnOffClusterInitCallback happens before the stack initialize the cluster
 * attributes to the default value.
 * The logic here expects something similar to the deprecated Plugins callback
 * emberAfPluginOnOffClusterServerPostInitCallback.
 *
 */
void emberAfOnOffClusterInitCallback(EndpointId endpoint)
{
    // TODO: implement any additional Cluster Server init actions
}

void emberAfLevelControlClusterInitCallback(EndpointId endpoint)
{
    MatterPWM.Init(PWM_CHIP, PWM_CHANNEL);
}


void ApplicationInit()
{
    std::string path = kChipEventFifoPathPrefix + std::to_string(getpid());

    if (sChipNamedPipeCommands.Start(path, &sLightingAppCommandDelegate) != CHIP_NO_ERROR)
    {
        ChipLogError(NotSpecified, "Failed to start CHIP NamedPipeCommands");
        sChipNamedPipeCommands.Stop();
    }
}

void ApplicationShutdown()
{
    if (sChipNamedPipeCommands.Stop() != CHIP_NO_ERROR)
    {
        ChipLogError(NotSpecified, "Failed to stop CHIP NamedPipeCommands");
    }

    MatterPWM.Deinit();
}

int main(int argc, char * argv[])
{
    if (ChipLinuxAppInit(argc, argv) != 0)
    {
        return -1;
    }

#if defined(CHIP_IMGUI_ENABLED) && CHIP_IMGUI_ENABLED
    example::Ui::ImguiUi ui;

    ui.AddWindow(std::make_unique<example::Ui::Windows::QRCode>());
    ui.AddWindow(std::make_unique<example::Ui::Windows::OccupancySensing>(chip::EndpointId(1), "Occupancy"));
    ui.AddWindow(std::make_unique<example::Ui::Windows::Light>(chip::EndpointId(1)));

    ChipLinuxAppMainLoop(&ui);
#else
    ChipLinuxAppMainLoop();
#endif

    return 0;
}
