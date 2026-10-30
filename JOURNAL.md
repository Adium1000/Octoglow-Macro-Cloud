---
title: "Octoglow Macro Cloud"
github: ""
description: "Octoglow Macro Duo is a compact macro pad designed for on-the-go devices; it can connect via Bluetooth and USB and offers 10 hours of continuous battery life while on the go. It features an OLED display, three buttons, and one programmable button, as well as backlighting. "
created_at: "2026-10-24"
total_time: "13h 12m"
---

# October 25, 2026: My ideea for the macro

Okay, so compared to my old macro pads, I’d like to create a fairly compact one ,the idea is for it to be tiny:
I’m thinking of using something like this:
ESP32 S3—for USB HID or maybe, if I can manage it, Bluetooth LE + battery, but we’ll see
3 MX switches—for macros
An encoder—for volume, scroll wheel, arrow keys, mute, click, etc.
and a 128x32 display under which I’ll hide a touch sensor to switch between tabs

![](https://fabricate.hackclub-assets.com/d2d02281f37951e692e1031e064f51538acd6157cb945075e7febbd421e76372/image-jpeg/WhatsApp%20Image%202026-10-25%20at%201.11.24%20AM.jpeg)

**Total time spent: 1h**

# October 26, 2026: Expanded my iddea 

So I thought I'd make two Macropad prototypes, and I'd like to build both of them: 
The first one, shown in the schematic, would be an RP2040-based version that would support only USB HID, and a slightly more complex version that would use the ESP32 S3, offering both Bluetooth and USB HID capabilities; the idea is that this would be the simplest schematic for both versions

I’m not yet sure if I’ll be able to build a macropad small enough to fit a buzzer inside

One thing I should test first is the implementation of the touch sensor, which would be placed under the OLED screen; the idea is to run a quick test to see if the screen blocks the touch sensor’s detection.
So, in short, I’ll build two versions that will look the same, except one will be more cost-effective—
supporting only USB while the other will also have BLE capabilities.

![](https://fabricate.hackclub-assets.com/7a3309c0bfc003e866e77a38faa8d321f3fca646494ad9a5e619100e28ac57c4/image-jpeg/WhatsApp%20Image%202026-10-25%20at%209.49.42%20PM.jpeg)

**Total time spent: 2h**

# October 26, 2026: Finnished Schematics (for now)

I've finnished  the schematics for both Macropad models; for now, all that's left is to create a BOM and some 3D files for the case. I also have a few components that could help me build this, so to reduce the building cost cost of two similar products, I'm going to buy only what's necessary. 

I also tested the touchscreen under the OLED, and it's unstable, so I won't be including it anymore.

A few more things I'm undecided about on the ESP model are what battery capacity to use: I was thinking of 250 mAh or 500 mAh.

For charging and estimating the battery percentage, I'm going to use the ESP32 S3 Plus from XIAO; this is the only board that seems to significantly reduce the size while offering a lot of built-in features, so that's a pretty big plus.
![](https://fabricate.hackclub-assets.com/10d3671332a99e64b5591a97686b65b628fe7fe9d911f949dfb847b51e4fb014/image-jpeg/WhatsApp%20Image%202026-10-26%20at%202.02.02%20AM.jpeg)

**Total time spent: 1h**

# October 26, 2026: Created a BOM for both versions

I created BOMs for both the ESP32 S3 and RP2040 versions, and the RP2040 version is twice as cheap as the ESP32 S3 of course, because it uses USB-HID and doesn’t include a battery. 

I started looking at what components I have and what else I’d need to build two macro pads, and right now I have the following:
1x White 0.9" 128x32 OLED
A set of various 5mm LEDs
A few MX Yellow switches 
A few M3 screws

So this will save me some of the money set aside for building the macro pads, and I won’t include the cost of printing the case either, since I’ll be using my own filament

Right now I’m not sure if the battery will fit, even though I tried to choose a compact one-though even with that in mind, the battery life will probably be pretty bad for the first prototype, but everything has to start somewhere… I guess  xD

![](https://fabricate.hackclub-assets.com/a90b18c6387b0db72844766854619535a0832d71fdd1ca4d59bea3850aeedb53/image-png/image.png)

In the original design concept, I wanted to use a battery larger than 250 or 500 mAh, but I gave up on the idea because it probably wouldn't fit.


Here are the BOMs

### ESP32-S3 Plus

| Component | Quantity | Unit Price (USD) | Total Price (USD) |
|---|---:|---:|---:|
| [Seeed Studio XIAO ESP32-S3 Plus](https://www.seeedstudio.com/Seeed-Studio-XIAO-ESP32S3-Plus-p-6361.html) | 1 | $7.900000 | $7.9000 |
| [Li-Pol battery - 160 mAh, 3.7 V, 401040](https://ampul.eu/ro/baterii/6783-baterie-li-pol-160mah-37v-401040) | 1 | $4.622709 | $4.6227 |
| [Encoder - EC11 rotary with click, 20 mm](https://sigmanortec.ro/Encoder-rotativ-cu-click-20mm-EC11-p128736611) | 1 | $0.918591 | $0.9186 |
| [OLED display - I2C, 0.91 inch, 128x32](https://sigmanortec.ro/Display-OLED-IIC-I2C-0-91-128x32-p126091015) | 1 | $3.802004 | $3.8020 |
| [Passive buzzer - 5 V](https://sigmanortec.ro/Buzzer-pasiv-5v-p172425809) | 1 | $0.303407 | $0.3034 |
| [Dupont wires - 40 pack, 10 cm, male to male](https://sigmanortec.ro/40-fire-Dupont-10cm-Tata-Tata-p210856288) | 1 | $1.617473 | $1.6175 |
| [Outemu Blue switches - 10 pack](https://qwertykey.ro/products/switchuri-outemu-blue) | 1 | $1.883216 | $1.8832 |
| [Red LED - 5 mm](https://sigmanortec.ro/led-5mm-rosu) | 3 | $0.062774 | $0.1883 |
| QwertyKey shipping | 1 | $3.138694 | $3.1387 |
| Sigmanortec shipping | 1 | $3.138694 | $3.1387 |
| Seeed Studio shipping | 1 | $12.300000 | $12.3000 |
| AMPUL shipping | 1 | $6.100185 | $6.1002 |
| **GRAND TOTAL** |  |  | **$45.9133** |

### RP2040

| Component | Quantity | Unit Price (USD) | Total Price (USD) |
|---|---:|---:|---:|
| [RP2040 development board - 2 MB flash](https://sigmanortec.ro/placa-dezvoltare-compatibila-rp2040-cortex-m0-2mb-flash) | 1 | $4.289548 | $4.2895 |
| [Encoder - EC11 rotary with click, 20 mm](https://sigmanortec.ro/Encoder-rotativ-cu-click-20mm-EC11-p128736611) | 1 | $0.918591 | $0.9186 |
| [OLED display - I2C, 0.91 inch, 128x32](https://sigmanortec.ro/Display-OLED-IIC-I2C-0-91-128x32-p126091015) | 1 | $3.802004 | $3.8020 |
| [Passive buzzer - 5 V](https://sigmanortec.ro/Buzzer-pasiv-5v-p172425809) | 1 | $0.303407 | $0.3034 |
| [Dupont wires - 40 pack, 10 cm, male to male](https://sigmanortec.ro/40-fire-Dupont-10cm-Tata-Tata-p210856288) | 1 | $1.617473 | $1.6175 |
| [Outemu Blue switches - 10 pack](https://qwertykey.ro/products/switchuri-outemu-blue) | 1 | $1.883216 | $1.8832 |
| [Red LED - 5 mm](https://sigmanortec.ro/led-5mm-rosu) | 3 | $0.062774 | $0.1883 |
| QwertyKey shipping | 1 | $3.138694 | $3.1387 |
| Sigmanortec shipping | 1 | $3.138694 | $3.1387 |
| **GRAND TOTAL** |  |  | **$19.2799** |

**Total time spent: 2h**

# October 27, 2026: Did the 3d enclosure 

I created the 3D case for the Macropad in Fusion. it’s super tiny. I tried to make it as minimalist and as small as possible, because my initial plan was to make it portable so I could use it with my iPad, but of course the first prototype wasn’t exactly a success 
![](https://fabricate.hackclub-assets.com/f468c9e518c191b77c4ff154063ae0ef67a9f728a6a241a57532c3fce6fb672a/image-png/image.png)

![](https://fabricate.hackclub-assets.com/1cc75bdb3fa238fa6320f9e4dad4eb0577252ef855ec3b0cb2e18d6c779093a6/image-png/image.png)


In the initial design, I decided to leave a little more space for components so everything would be organized, but that resulted in my Macropad having a slightly narrower viewing angle. I also added a screw hole to prevent the microcontroller from falling out.

In the second design, I tried to improve the viewing angle while keeping all aspects of the board exactly the same but reducing the height very slightly; unfortunately, the result was still the same 

In the final design, I reduced the size and viewing angle to make it very user-friendly. I also removed the screw hole for securing the microcontroller because it wasn’t strong enough and gave way quite easily, so I chose to remove it from the design; instead, the board will be secured with hot glue

The initial design for the inner cover turned out well on the first try; for now, I’ve mounted the OLED display and the buttons I have on hand onto it, and I can say it looks pretty good. 
![](https://fabricate.hackclub-assets.com/2cef6f50672f5327daf1d22edfeec2cd72f5a864de56a6cc3d108898c6589bb4/image-png/image.png)

I also tested the microcontroller mounting rails with some burned-out microcontrollers, and they work pretty well with the RP2040 WS and Seeed.
![](https://fabricate.hackclub-assets.com/631e042982f4e69b8adb3b3117e5c2d799f1dfbc2a4dbed6ca60f3a5ed1ce76a/image-png/image.png)

Here are a few photos of the current finish

![](https://fabricate.hackclub-assets.com/fa0f76eaa8af53eb595903af3189c64920a01e63d070a4ca85eb4b495936c43a/image-png/image.png)
![](https://fabricate.hackclub-assets.com/f14cdb666d67110cb35f71bd500af8889fc724add7c7257c8c75205cd796dde0/image-png/image.png)

**Total time spent: 5h**

# October 29, 2026: Firmware!

Created the minimal firmware for both versions of the macro pad, and this runs only a test configuration for both versions that allows the user to check whether the OLED display, buttons, encoder, and Bluetooth (if applicable) are working properly. 

Once I have all the necessary hardware, I’ll continue development on a larger scale and add software support for Octoglow Connect, just like with the Octoglow Macro Basic moddel

![](https://fabricate.hackclub-assets.com/d40b15650e27ce7f3209705eb4dfdabcd6a13a4220d9a83098382978ff927751/image-png/image.png)
![](https://fabricate.hackclub-assets.com/c90481e76525998a6966d4d11e697357daa86f6cd5bb9b26470758371bc1b28a/image-png/image.png)

**Total time spent: 1h 12m**

# October 30, 2026: Finnished readme.md

I finished the README for my project, making sure it met all the criteria it should include, and I also tried to make it as polished as possible so that it would be easy to read

![](https://fabricate.hackclub-assets.com/64663bc3db5491672dc5716b198a5f458b8883a29285f23c88171ab9943a3f77/image-png/Screenshot%202026-10-30%20184038.png)

**Total time spent: 1h**
