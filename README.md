<div align="center">

[![Gaggiuino](/images/GAGGIUINO_LOGO_transp.png)](https://gaggiuino.github.io/#/)
  
[![Compile Sketch](https://github.com/Zer0-bit/gaggiuino/actions/workflows/compile-sketch.yml/badge.svg)](https://github.com/Zer0-bit/gaggiuino/actions/workflows/compile-sketch.yml)
[![Discord Chat](https://img.shields.io/discord/890339612441063494)](https://discord.gg/eJTDJA3xfh "Join Discord Help Chat")
</div>



## Intro
**Gaggiuino started as an idea to improve an already capable coffee machine while keeping the machine appearance and button functionality as close as possible to the original. An important part is that no internal cables/connectors were modified; all the connections were made by creating splitters using the purchased spade connectors.**
***
**For install instructions head to the project [documentation](https://gaggiuino.github.io/#/) section.**

*For project related help join us on [discord](https://discord.gg/eJTDJA3xfh).*

## For Milesto EM19M3 ONLY

### 免责声明

本项目目的在于记录并保存 **我自己** 的咖啡机改装过程，仅适用于 **迈拓EM19-M3** ，本项目中的 *指南、代码等内容* 仅在 **我自己** 的设备上通过测试，对于因应用本项目中任何内容而产生的一切后果，由应用者本人负责。

### 安全提示

咖啡机改装涉及 **加热组件** 、 **高压组件** 、 **机械组件** 、 **玻纤导线** 、 **高压流体** 等危害源。

改装过程中须做好对应安全防护，避免 **烫伤** 、 **触电** 、 **机械伤害** 、 **割伤** 、 **溅射** 、 **吸入** 、 **接触** 等伤害，做自己的安全负责人！


### 改装提示

改装后，咖啡机将失去保修，改装后的咖啡机未经权威机构安全检测，不排除有未知的安全风险，使用时应时刻监控设备运行状态。

### BOM表

TBD

### 所需工具

TBD

### 控制组件组装

TBD

### 线束制作

TBD

### 机械组件改装

TBD

### 组装

TBD

### 编译配置

1.迈拓EM19-M3拥有独立蒸汽系统，因此，使用蒸汽时无需开启主水泵。

2.EM19-M3热水系统通过独立继电器控制，因此需要激活


本项目已针对EM19-M3完成对应代码修改，为保障与原Repository的兼容性，需对项目文件进行配置以启用对应特性，使用时只需在根目录添加“extra_defines.ini”文件并粘贴如下内容：

```
[extra]
build_flags =
	;placeholder values, create a untracked extra_defines.ini file
	;in the project root directory(same level as platformio.ini)
	;so you can keep your custom setup defined by default on every pull
	-DDREAM_STEAM_DISABLED      ; Milesto EM19M3 has standalone steam boiler and pumps.
    -DSTANDALONE_WATER_VALVE    ; Milesto EM19M3 has standalone water valve.
	; -DSINGLE_HX711_BOARD
```


### 固件编译与刷写

TBD

### Enjoy your Espresso！




</div>