4 Port high power USB hub 
=========================

![Platform](https://img.shields.io/badge/platform-PIC16-blue) ![License](https://img.shields.io/github/license/dilshan/usb2-power-hub) ![Release Version](https://img.shields.io/github/v/release/dilshan/usb2-power-hub) ![Release Date](https://img.shields.io/github/release-date/dilshan/usb2-power-hub)
  
![Prototype version of USB hub](https://raw.githubusercontent.com/dilshan/usb2-power-hub/master/resource/usb-power-hub-prototype.jpg)

This project is about a high current USB 2.0 hub that is specifically designed to drive USB powered development boards and experimental peripherals.

The core element of this USB hub is the *FE1.1s* USB 2.0 hub controller. The *FE1.1s* is a low cost, 4-port, high-speed USB hub controller you should be able to find on *eBay* or AliExpress.

This USB hub adds the following additional features to those offered by the *FE1.1s*:

 - Switches to on/off and reset individual USB ports.
 - Capability to provide a maximum of 3A of current from each USB port.
 - Power using 9V to 15V DC voltage source.

This USB hub uses a *PIC16F630* MCU and four *LM2596-5.0* switching regulators. 

[You can find everything about how to build and use this project on our wiki.](https://github.com/dilshan/usb2-power-hub/wiki)


Licenses
--------

This is a [certified open hardware project](https://certification.oshwa.org/lk000005.html) and all its design files, firmware source code, documentation, and other resource files are available at this project source repository. The content of this project is distributed under the terms of the following licenses:

 - Hardware License: [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/)
 - Software License: [MIT](https://github.com/dilshan/usb-morse-keyer/blob/master/LICENSE)
 - Documentation License: [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/)

[![OSHW-LK000005](https://raw.githubusercontent.com/wiki/dilshan/usb2-power-hub/images/OSHW_LK000005.png)](https://certification.oshwa.org/lk000005.html)
