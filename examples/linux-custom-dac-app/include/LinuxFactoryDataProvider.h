/*
 *
 *    Copyright (c) 2022 Project CHIP Authors
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

#pragma once

#include <credentials/DeviceAttestationCredsProvider.h>
#include <platform/CommissionableDataProvider.h>
#include <platform/DeviceInstanceInfoProvider.h>
#include <vector>
#include <string>

typedef struct
{
    std::string dac_cert_filepath;
    std::string dac_key_filepath;
    std::string pai_cert_filepath;
    std::string cd_filepath;
} DeviceAttestationCredentialsFilepath;

namespace chip {
namespace DeviceLayer {

class FactoryDataProvider : public chip::Credentials::DeviceAttestationCredentialsProvider
                            // public CommissionableDataProvider,
                            // public DeviceInstanceInfoProvider
{
public:
    // ===== Members functions that implement the DeviceAttestationCredentialsProvider
    CHIP_ERROR Init(DeviceAttestationCredentialsFilepath DacFilepath);
    CHIP_ERROR GetCertificationDeclaration(MutableByteSpan & outBuffer) override;
    CHIP_ERROR GetFirmwareInformation(MutableByteSpan & out_firmware_info_buffer) override;
    CHIP_ERROR GetDeviceAttestationCert(MutableByteSpan & outBuffer) override;
    CHIP_ERROR GetProductAttestationIntermediateCert(MutableByteSpan & outBuffer) override;
    CHIP_ERROR SignWithDeviceAttestationKey(const ByteSpan & messageToSign, MutableByteSpan & outSignBuffer) override;

    // ===== Members functions that implement the CommissionableDataProvider
    // CHIP_ERROR GetSetupDiscriminator(uint16_t & setupDiscriminator) override;
    // CHIP_ERROR SetSetupDiscriminator(uint16_t setupDiscriminator) override;
    // CHIP_ERROR GetSpake2pIterationCount(uint32_t & iterationCount) override;
    // CHIP_ERROR GetSpake2pSalt(MutableByteSpan & saltBuf) override;
    // CHIP_ERROR GetSpake2pVerifier(MutableByteSpan & verifierBuf, size_t & verifierLen) override;
    // CHIP_ERROR GetSetupPasscode(uint32_t & setupPasscode) override;
    // CHIP_ERROR SetSetupPasscode(uint32_t setupPasscode) override;

    // ===== Members functions that implement the DeviceInstanceInfoProvider
    // CHIP_ERROR GetVendorName(char * buf, size_t bufSize) override;
    // CHIP_ERROR GetVendorId(uint16_t & vendorId) override;
    // CHIP_ERROR GetProductName(char * buf, size_t bufSize) override;
    // CHIP_ERROR GetProductId(uint16_t & productId) override;
    // CHIP_ERROR GetPartNumber(char * buf, size_t bufSize) override;
    // CHIP_ERROR GetProductURL(char * buf, size_t bufSize) override;
    // CHIP_ERROR GetProductLabel(char * buf, size_t bufSize) override;
    // CHIP_ERROR GetSerialNumber(char * buf, size_t bufSize) override;
    // CHIP_ERROR GetManufacturingDate(uint16_t & year, uint8_t & month, uint8_t & day) override;
    // CHIP_ERROR GetHardwareVersion(uint16_t & hardwareVersion) override;
    // CHIP_ERROR GetHardwareVersionString(char * buf, size_t bufSize) override;
    // CHIP_ERROR GetRotatingDeviceIdUniqueId(MutableByteSpan & uniqueIdSpan) override;
    // CHIP_ERROR GetProductFinish(app::Clusters::BasicInformation::ProductFinishEnum * finish) override;
    // CHIP_ERROR GetProductPrimaryColor(app::Clusters::BasicInformation::ColorEnum * primaryColor) override;

    bool kReadFromFlash = false;

private:
    CHIP_ERROR ReadFileBytes(std::vector<uint8_t> &outBuffer, const std::string &filepath);

    typedef struct
    {
        std::vector<uint8_t> value;
        size_t len;
    } FactoryDataString;

    typedef struct
    {
        std::vector<uint8_t> value;
        size_t len;
    } CertDataString;

    typedef struct
    {
        std::vector<uint8_t> value;
        size_t len;
    } VerifierDataString;

    typedef struct  
    {
        uint32_t passcode;
        uint16_t discriminator;
        uint32_t spake2_it;
        FactoryDataString spake2_salt;
        VerifierDataString spake2_verifier;
    } CommissionableData;

    typedef struct 
    {
        CertDataString dac_cert;
        FactoryDataString dac_key;
        CertDataString pai_cert;
        CertDataString cd;
    } DeviceAttestationCredentials;

    typedef struct 
    {
        uint16_t vendor_id;
        FactoryDataString vendor_name;
        uint16_t product_id;
        FactoryDataString product_name;
        uint16_t hw_ver;
        FactoryDataString hw_ver_string; 
        FactoryDataString mfg_date;
        FactoryDataString serial_num;
        FactoryDataString rd_id_uid;
    } DeviceInstanceInfo;

    typedef struct
    {
        CommissionableData cdata;
        DeviceAttestationCredentials dac;
        DeviceInstanceInfo dii;
    } FactoryData;

    FactoryData mFactoryData = { 0 };
};

} // namespace DeviceLayer
} // namespace chip