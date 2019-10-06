# Reversing radar for motorcycle

## Purpose

This Arduino project is performed to create a reversing radar for a motorcycle.
You will avoid breaking the back of the bike.

![Assembly](https://raw.githubusercontent.com/turbo-xav/arduino-radar-recul-moto/master/assembly/radar-recul-moto.png =250x250)

## Concents of project

You can find on this repository
- [Photos](https://github.com/turbo-xav/arduino-radar-recul-moto/tree/master/photos) of project on a motorcycle
- [Gerber file](https://github.com/turbo-xav/arduino-radar-recul-moto/blob/master/gerbers/Gerber_pcb%20complet%20radar%20%2B%20barre%20led_20190922212650.zip) to create a printed circuit board
- [radar-recul-moto.ino](https://github.com/turbo-xav/arduino-radar-recul-moto/blob/master/radar-recul-moto.ino) : ARDUINO program
- [Electronic Assembly](https://github.com/turbo-xav/arduino-radar-recul-moto/blob/master/assembly/radar-recul-moto.png) : Assembly on Tinker cad (photo)

## Links
- [Tinkercad project](https://www.tinkercad.com/things/4okGJGsEwJa-radar-recul-moto) : My project on TinkerCad
- [Grove bar Led Library and Help](http://wiki.seeedstudio.com/Grove-LED_Bar/) : If you want to use a Grove bar led

## Required Equipment
- [Ultrasonic Sensor](https://fr.aliexpress.com/item/32911119661.html?spm=a2g0s.9042311.0.0.27426c37yo3OsX) : PWM Version required
- [Bargraphe](https://fr.aliexpress.com/item/32943633774.html?spm=a2g0s.9042311.0.0.27426c37K34Ko4) : A simple Bar Graphe with 10 LEDs
- [Arduino Nano](https://fr.aliexpress.com/item/32347096044.html?spm=a2g0o.productlist.0.0.113d5d4c7O3TPN&s=p&algo_pvid=2ff3e413-5c3a-41cd-9ec4-0ca23e98efe0&algo_expid=2ff3e413-5c3a-41cd-9ec4-0ca23e98efe0-0&btsid=b37b3c35-563c-467f-a736-f89b7695e36a&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_53) : Nano version is more compact
- [Shift Register 74HC595N](https://fr.aliexpress.com/item/32845387091.html?spm=a2g0o.productlist.0.0.2e0a4cdfpXrM8y&s=p&algo_pvid=4943cd8e-e6f6-41f6-a35a-165473f085a8&algo_expid=4943cd8e-e6f6-41f6-a35a-165473f085a8-0&btsid=6fade25c-36c7-42c9-bf49-ee2eb86bc270&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_53) : A simple Shift register to minimize arduino pin use
- [Resistances](https://fr.aliexpress.com/item/32827694849.html?spm=a2g0o.productlist.0.0.7dc967418z8N4F&s=p&algo_pvid=2d6df408-94ed-40ac-978f-4c477930dac0&algo_expid=2d6df408-94ed-40ac-978f-4c477930dac0-0&btsid=921dec18-9966-404e-b2f8-a3ffe87d7363&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_53) : Use resistors of 220 ohms minimum

## Useful site :
- [JLCPPB](https://jlcpcb.com/) : Very useful site to développ PCB from Gerber File.