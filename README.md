# voiceActivatedLaserToy
## A laser toy that may be activated remotely or at home using Google Assistant and/or Adafruit I/O.
![The laser toy stands like a sentry waiting for any cat to approach.](https://github.com/boomninjavanish/media/blob/master/voiceActivatedLaserToy/laserToyPhoto.png)

One summer, I decided to vacation in Chile two weeks. After booking a sitter to check on and feed my cat, I realized that I would want to check in on the cat remotely. I setup an Android phone to automatically answer a Skype call so that I may see if the cat is doing well. However, I knew that he would not come to the phone easily. Therefore, with a week before the trip, I designed this toy so that I could play with him remotely while checking in on him. The toy was so successful that I continue to use it to play with the cat to this day!

## Features
* Creates a random play session based on a set of predefined moves. This is to keep the laser game from becoming too predictable.
* Can be activated remotely or on site thanks to Adafruit I/O.
* IFTTT may be used to link with Google Assistant/Home or other services.
* Preoccupied cat...need I say more?

![The laser cat toy in action.](https://github.com/boomninjavanish/media/blob/master/voiceActivatedLaserToy/laserToyGif.gif)

## Required Hardware
The following is a bill of materials needed to complete the project:

QTY | Item | Purchase Link
--- | ---- | --------------
1 | Laser Diode - 5mW 650nm Red | [Link](https://www.adafruit.com/product/1054)
1 | Mini Pan-Tilt Kit - Assembled with Micro Servos | [Link](https://www.adafruit.com/product/1967)
1 | Adafruit Feather HUZZAH with ESP8266 | [Link](https://www.adafruit.com/product/2821)
1 | USB A to Micro-B Cable | [Link](https://www.adafruit.com/product/592)
40 | Grams of 3D Printer Filament | [Link](https://shop.prusa3d.com/en/42-prusament)
2 | M2.26 / 4mm Self-Tapping Screws | [Link](https://www.mcmaster.com/99397A322)
4 | M2.5 / 6mm Screws | [Link](https://www.mcmaster.com/94500A213)
4 | M2.5 Hex Nuts | [Link](https://www.mcmaster.com/90592A006)
1 | M3 / 3mm Set Screw | [Link](https://www.mcmaster.com/92605A097)
2-4 | 3M Command Strips with Velcro Backing | [Link](https://www.amazon.com/command-velcro-strips/s?k=command+velcro+strips)
1 | Bored Cat | [Link](https://www.aspca.org/nyc/aspca-adoption-center/adoptable-cats)

## Software

### Adafruit I/O Setup
In order for this project to work, a [Adafruit I/O account](https://io.adafruit.com) is required. The free account has limitations but should be enough for this project to work.

After creating an account, create the following feeds. Note that the feed names must match and are case-sensitive!

* catLaserInitPlay
* catLaserPitch
* catLaserPoll
* catLaserToggle
* catLaserYaw

Next, create a dashboard with the following blocks. All settings are case-sensitive and do not type the quotation marks.

Type | Feed | Settings
---- | ---- | ---------
Toggle | catLaserInitPlay | Button On Text: "PLAYING"; Button Off Text: "OFF"
Slider | catLaserPitch | Slider Min Value: "0"; Slider Max Value: "180"; Slider Step Size: "1"; Slider Label: "Pitch"
Slider | catLaserYaw | Slider Min Value: "0"; Slider Max Value: "180"; Slider Step Size: "1"; Slider Label: "Yaw"
Toggle | catLaserToggle | Button On Text: "ON"; Button Off Text: "OFF"
Line Chart | catLaserPoll | Show History: "24 Hours"; X-Axis Label: "Time"; Y-Axis Label: "Poll Received"; Y-Axis Minimum: "0"; Y-Axis Maximum: "1"; Stepped Line: Checked


### Compilation
This project may be compiled using the [Arduino IDE](https://www.arduino.cc/en/Main/Software). Simply open the project in Arduino, add your WiFi and Adafruit I/O account information to the project according to the instructions contained within sample_config.h. Be sure to change the file name from "sample_config.h" to "config.h" before compiling.

These libraries will be needed in order to compile the software:
* [ESP8266 Board Library and Drivers](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide)
* [ServoEasing](https://github.com/ArminJo/ServoEasing) Learn how to install libraries found [here](https://www.arduino.cc/en/Guide/Libraries).

Be sure to follow the Arduino setup instructions for the Huzzah Feather that are found [here](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide#setup-esp8266-support-2720750-18). 

## Wiring and Assembly

0. Using the USB cable, compile and upload the Arduino sketch included in the source code (see above).
1. Once the case parts have been printed, feed the laser diode into the laser mount then secure it by tightening the M3 set screw in the hole on the side of the barrel.
2. Feed the laser diode wires through the guides on the laser mount then snap the mount into the top of the Mini Pan-Tilt Kit.
3. Measure the amount of wire from the servos and laser diode needed to travel to the bottom case and be soldered to board. Cut the connectors off of the servos and trim the laser diode cable accordingly. 
4. Then feed the wires from both servos and the laser diode in the round hole in the case bottom. Feel free to add heat shrink between the case bottom and the Mini Pan-Tilt Kit for a cleaner look.
5. Solder the wires to the Feather board according to the following schematic:
![Schematic for the laser cat toy.](https://github.com/boomninjavanish/media/blob/master/voiceActivatedLaserToy/schematic.png)
6. Test the connections on the Feather board: plugin the USB to power and attempt to control various functions using the Adafruit I/O dashboard that was created above.
7. Screw the board into the bottom case using the two M2.26 self-tapping screws.
8. Place the four hex nuts on the underside of the case top. The nuts may be glued into place using super glue if desired.
9. Feed the four M2.5 screws through the Mini Pan-Tilt Kit and fasten into the case top.
10. Snap the case top and bottom together.
11. Apply 3M command strips to bottom of case and surface in which the unit will reside.

## Usage
Once the software and hardware has been setup (see above), the laser and movement may be controlled directly via the Adafruit I/O dashboard. A randomized play session may be initiated by toggling the catLaserInitPlay feed to "PLAYING" within the dashboard. If the dashboard is working correctly, IFFT may be setup to link the Adafruit I/O feeds to almost any other service. I have been using Google Assistant to recognize a custom phrase then post "PLAYING" to the catLaserInitPlay feed. [Adafruit has a nice guide on how to setup I/O on IFTTT.](https://learn.adafruit.com/using-ifttt-with-adafruit-io/ifttt-to-adafruit-io-setup) Also, [here is some information on IFTTT.](https://help.ifttt.com/hc/en-us/articles/115010158167-How-does-IFTTT-work-)

## Contributing
If you wish to contribute to this project, feel free to [reach out to me](https://dunlap.media/contact).

## License
This project is protected by the GNU General Public License v3.0. [More information.](https://github.com/boomninjavanish/voiceActivatedLaserToy/blob/master/LICENSE)


