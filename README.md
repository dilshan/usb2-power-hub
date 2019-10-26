4 Port high power USB hub 
=========================
  
![Prototype version of USB hub](https://raw.githubusercontent.com/dilshan/usb2-power-hub/master/resource/usb-power-hub-prototype.jpg)

This project is about a high current USB 2.0 hub that is specifically designed to drive USB powered development boards and experimental peripherals.

The core element of this USB hub is the *FE1.1s* USB 2.0 hub controller. *FE1.1s* is a low cost, 4-port, high-speed USB hub controller, and this chip can easily order by *eBay* or *AliExpress*.

Apart from *FE1.1s* features, this USB hub has the following additional features:

 - Switches to on/off and reset individual USB ports.
 - Capability to provide a maximum of 3A of current from each USB port.
 - Power using 9V to 15V DC voltage source.

This USB hub uses *PIC16F630* MCU and four units of *LM2596-5.0* switching regulators to achieve the above-listed features. 

[All the details related to this project are available at project documentation.](https://github.com/dilshan/usb2-power-hub/wiki)


Licenses
--------

This is an open hardware project and all it's design files, firmware source codes, documentation, and other resource files are available at this project source repository. All the content of this project are distributed under the terms of the following license:

 - Hardware License: [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/)
 - Software License: [MIT](https://github.com/dilshan/usb-morse-keyer/blob/master/LICENSE)
 - Documentation License: [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/)

