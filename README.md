4 Port high power USB hub 
=====================
  
![Prototype version of USB hub](https://raw.githubusercontent.com/dilshan/usb2-power-hub/master/resource/usb-power-hub-prototype.jpg)

This project is about a high current USB 2.0 hub that is specifically designed to drive USB powered development boards and experimental peripherals.

The core element of this USB hub is the *FE1.1s* USB 2.0 hub controller. *FE1.1s* is a low cost, 4-port, high-speed USB hub controller, and this chip can easily order by *eBay* or *AliExpress*.

Apart from *FE1.1s* features, this USB hub has the following additional features:

 - Switches to on/off and reset individual USB ports.
 - Capability to provide a maximum of 3A of current from each USB port.
 - Power using 9V to 15V DC voltage source.

This USB hub uses *PIC16F630* MCU and four units of *LM2596-5.0* switching regulators to achieve the above-listed features. 

This project is an open-source hardware project. All the documentation, design files, firmware source codes, and binaries are available at this github repository.
