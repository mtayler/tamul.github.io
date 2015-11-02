---
layout: post
title: "DIY Bench Power Supply"
date: "2015-11-02"
---
1.2V-21V Variable Voltage Bench Power Supply
============================================
Lacking a bench power supply and in need of a project, I salvaged an old ATX PSU and ordered some components off Digikey to make a fairly bare-bones variable voltage power supply.
<figure>
    <img src="/assets/atx-bench-psu/overview.jpg">
    <figcaption>The mess in all it's glory</figcaption>
</figure>

The design is based off of an LM317 and an old ATX power supply. I chopped the end off the 24-pin connector, and snipped the wires I wasn't using far enough back that they were out of the way (read in the power supply) then hot-glued the ends to prevent shorts. The ground of the 5V rail and the 3.3V rail are actually tied together, as I didn't correctly account for the number of wires and only realized after I purchased the 6-pin connector. Luckily the power supply is only intended for low power applications, but it's definitely something to keep in mind what for keeping one's house slightly less fiery.
<figure>
    <img src="/assets/atx-bench-psu/schematic.png">
    <figcaption>Overview schematic</figcaption>
</figure>

Capacitor C3 was removed after I encountered suggestions that it wouldn't be necessary for such implementations. Testing proved C3 to provide insufficient stability, with an overshoot around 60% on the variable voltage output. The first improvement will likely be install C2, as the sudden load change is likely causing instability on the adjustment pin of the LM317 which in turn creates a large overshoot.

Additional areas of improvement would be with the variable voltage load LED. Since the LED is powered by the voltage of the output, it becomes incredibly dim being in series with a 2.2kΩ resistor. Powering the LED from the 5V rail with the variable voltage output controlling a relay or transistor would provide a more stable interface, with the challenge being finding a transistor that can operate between 1.3V-21V.

The 3.3V and 5V outputs are relatively stable, with the 3.3V output measuring almost exactly 3.3V, and the 5V measuring 4.8 although these values are primarily affected by the PSU rather than what connects it to the binding posts.

The biggest gripe with this implementation is the inability to probe a circuit under test while using the variable voltage output. To acheive 1.3V-20V, ground is instead the -12V rail. Noise filtering at the Mains input causes continuity between the ground and earth, which when accidentally connecting an oscilloscope ground makes a nasty ground loop. There's benefits to leaving the "ground" at a -12V potential and shifting the output on the scope by 12V, and swapping the -12V for actual ground. What path I take will probably be decided by how often I require voltages higher than 5V, because frankly while the oscilloscope survived the first time I'd rather not risk another accident.

All things considered, the project resulted in a handy bench power supply that, while a little questionable, works reasonably well keeping a couple things in mind. The outputs all have current limiting (which is *really* is only effective against a dead short), and the most used 5V output is very stable. While there's some obvious improvements that could be made, the result works quite well.
