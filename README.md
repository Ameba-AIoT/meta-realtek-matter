# Introduction
This is a layer that builds Matter applications using [connectedhomeip](https://github.com/project-chip/connectedhomeip). 
This layer depends and builds on top of [Realtek's Yocto BSP layer](https://github.com/Ameba-AIoT/ameba-linux-manifest/tree/ameba-3.1).

# Usage
To build and use this layer, refer to [AmebaSmart Yocto Matter Guide](<doc/AmebaSmart Yocto Matter Guide.md>)

# Matter Layer Structure

| Directory                                          | Description                                                                                                                                                              |
| -------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| conf                                               | Contains the matter layer configuration file “layer.conf”, which contains configuration settings for the matter layer.                                                   |
| doc                                                | Contains markdown formatted documentations for using the matter layer.                                                                                                   |
| examples                                           | Contains the source code for ported matter application examples. Follow the included README.md within each example subdirectory to use the examples.                     |
| recipes-devtools                                   | Contains development tool recipes required to build matter recipes.                                                                                                      |
| recipes-matter                                     | Contains matter recipes to build matter example applications.                                                                                                            |
| recipes-matter/matter-app-examples                 | Contains recipes that will add the Linux example matter applications from connectedhomeip/examples/*/linux/.                                                             |
| recipes-matter/matter-app-port-examples            | Contains recipes that will add ported example matter applications from sources/matter/examples/.                                                                         |
| recipes-matter/matter-app-port-custom-dac-examples | Contains recipes that will add ported example matter applications from sources/matter/examples/ that uses custom Device Attestation Certificate (DAC) for commissioning. |
| recipes-matter/matter-service-example              | Contains recipes that will add the Matter service script from sources/matter/examples/ to start Matter Application as a service/daemon.                                  |
| recipes-matter/packagegroups                       | Contains package group recipes, which combines multiple recipes into one group.                                                                                          |


