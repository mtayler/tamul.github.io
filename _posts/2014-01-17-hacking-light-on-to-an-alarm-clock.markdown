---
layout: post
title: Hacking a Light on to an Alarm Clock
---
<div style="background:#F78181; border: 2px solid red;">
    <p>February 26, 2016</p>
    <p>This project was done waaaay before I had really any idea what I was doing. Frankly I'm just glad I didn't kill myself on the 120V AC</p>
</div>
{: .disclaimer}

<div>
    <p>I am in no way responsible if you break your <em>anything</em> trying this.</p>
</div>
{: .disclaimer}
<p></p>

What's the point?
=================

I plug my phone in before I go to sleep every night. Except, as nights are, it's dark, and I have end up scratching a new port into the bottom of my phone. So I hacked a light on to the alarm-clock/dock combo that lights up when the dimmable display is below the highest level. This works because when the alarm is turned off in the morning, the display switches to the brightest setting, but I usually turn it down before I go to sleep. Plus it was cool having it work in the end.

Interfacing
===========

The display brightness is toggled between 4 settings (high, medium, low, and off) by a button attached to two push buttons on the outer sides of the button. I tried interfacing with these buttons, but couldn't find out how the damn things worked. I don't have the benefit of an oscilloscope, and messing around with a multimeter around the two terminals, while clicking the button, I didn't see any change. I kept searching on the PCB around the buttons, probing with the multimeter, but couldn't find out a damn thing.

<figure>
    <img src="/assets/alarm-clock-hack/display-pcb.jpg">
    <figcaption>Alarm clock display and PCB overview -- LED comes in later</figcaption>
</figure>

Wishing I had a better camera handy, I started probing around, and found out that when the brightness of the display changes, it's done through the voltage supplied. However, there's a catch: the power is supplied through either AC or DC using PWM. Even with the drawbacks, it seemed this was the best way to go, as if a button press was missed, or the assembly became out of sync, the light would be turning on when it should be off, and vice versa.

Utilizing the interface
=======================

The true difficulty behind this method was using the voltage readings from whatever method of power the display used. Initially, using an Arduino, I saved 100 readings from the positive terminal (from the molex connector the LED is in above) to an array, then took the average. However, the average still jumped too much, and it was near impossible to perfectly sync the reading times with the power waveform. So instead I tried increasing the size of the array, but that lead to problems with memory in the Arduino.

To keep the array index small, I saved the averages of the 100 readings to another array of the same size. Rather than a linear scale of readings by increasing array size, this lead to exponential increase, while keeping the memory usage just over 1000kB including the bootloader. This worked much better, and the readings were more consistent. However, they still weren't _quite_ consistent enough to base the LED's state off of.

<figure>
    <img src="/assets/alarm-clock-hack/variable-averages.png">
    <figcaption>The averages still jumped around quite a bit</figcaption>
</figure>

I added one more array, again of 100, and saved the averaged averages to this array. After averaging the averaged average readings (diagram below might provide some clarification), the value was constant enough to use as a trigger (and somehow dropped two place values, making the max value 600 become 6).

<figure>
    <img src="/assets/alarm-clock-hack/array-model.jpg">
    <figcaption>The array model</figcaption>
</figure>

Utilizing the equivalent of one million readings averaged, a simple function sets the LED's digital pin on the Arduino if the value is above a certain number (in this case, 4). You can get the source code "here":/assets/alarm-clock-hack/alarm_clock_led.ino.

Putting it all together
=======================

Needing a power supply for the Arduino, I tapped into the +5V wire going to one of the clock's iPhone/iPad docks.

<figure>
    <img src="/assets/alarm-clock-hack/wiring-overview.jpg">
    <figcaption>+5V, ground, and wire for reading voltage</figcaption>
</figure>

After setting a common ground, I realized I had a problem. For some reason the display wouldn't change brightness under a common ground when I was reading from the positive terminal going to the display. I honestly have no idea why this was happening, and messed around trying to find a solution.

I tried reading from the negative terminal, which fixed the problem. I have no idea how this worked, as I wasn't (theoretically) supplying power, only reading the power already supplied - I suspect it may have been from the lack of common ground between the display and the Arduino. The only side effect this had was inverting the reading - when the display was at full brightness, the reading was now 0, and with the back light off, 6 - a quick flip of the inequality sign and all was corrected.

<figure>
    <img src="/assets/alarm-clock-hack/led-placement.jpg">
    <figcaption>LED placement on a lamp above the clock</figcaption>
</figure>

After closing everything back up, and attaching the light: it worked! I had a convenient light to find the charging port at night. All in all, it took about six hours, and the LED/resistor were soldered to some wire to stop the annoying flickering my tape-work caused. I plan to add a photoresistor to only turn the LED on when it's dark, and possibly add a real-time clock, or figure out how the RTC in the alarm clock works, so the LED only comes on past a certain time. If I'm feeling really bored, I might also add some sort of sensor, to keep it off unless I'm trying to plug my phone in.

For now, however, I'm going to leave it be. No plans for another project yet, however I don't usually plan these things. Hope you found this at least a little bit interesting, and in no way useful (seriously, don't use this as a guide).
