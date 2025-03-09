# Particle Filter Localization

This repository contains the Ray Marching accelerator to be used in 2D Particle Filters. Tested on Kria KR260.

![Particle Filter](./media/scheme.png)

### Repository structure

In the `hls/` folder you can find the file sources for the accelerator and the `rmds.tcl` script to generate and export the RTL accelerator.
In the `hw/kria` folder you can find
- `rmds.tcl` - the hardware block design for the RMDS system design on Kria.
- `pl.dtsi` - pre-cooked devicetree bindings for the PF and its reserved shared memory spaces
- `shell.json` - a pre-cooked shell file to be used in xmutils
- `design_1_wrapper.xsa` - a ready-to-use bitstream archive 

### Usage
Run `hls/build_rm.tcl` to build the hardware accelerator, source the `rmds.tcl` design into Vivado and generate the corresponding bitstream. We also package our pre-generated `xsa` in the `hw/kria` folder.

Compile the `hw/kria/pl.dtsi` file into a device-tree blob overlay with `dtc -I dts -O dtbo -i hw/kria/pl.dtsi`.

Finally package the `design_1_wrapper.bit.bin`, `shell.json` and `pl.dtbo` files into a single folder named `rmds` and copy it into the KR260 in the `/lib/firmware/xilinx/` folder.

Finally, use `xmutil loadapp rmds` to flash the hardware design in the programmable logic.

### Kria Utilization

| Resource | Utilization | Available | Utilization % |
| :--- | ---: | ---: | ---: |
| LUT | 24953 | 117120 | 21.305498 |
| LUTRAM | 847 | 57600 | 1.470486 |
| FF | 28257 | 234240 | 12.063269 |
| BRAM | 15.50 | 144 | 10.763888 |
| URAM | 48 | 64 | 75.0 |
| DPS | 58 | 1248 | 4.647436 |
| BUFG | 3 | 352 | 0.85227275 |

### Authors
* **Andrea Bernardi** - [andreabernard](https://github.com/andreabernard)
* **Michele Guzzinati** - [mguzzinati](https://github.com/mguzzina)
* **Federico Gavioli** - [fgavioli](https://github.com/fgavioli) - _(Maintainer)_