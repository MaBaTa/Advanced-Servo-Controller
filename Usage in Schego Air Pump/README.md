# ASC as Inverter for (Schego) Air Pump

@Tristan Wieczorek    15.11.2025

This is a subproject within the overall initiative to use the [ASC](https://github.com/MaBaTa/Advanced-Servo-Controller) as an inverter for a membrane compressor.

### Motivatiom:

For a long time, I have been looking for a small compressor that is quiet and made of high quality. I was excited when I came across the company [Schego](https://schego.de/de/hobby-freizeit/aquarientechnik/membranpumpen/).They produce a small range of aquarium and industrial membrane pumps. Since I also intend to use them in airbrushing and 3D printing, I was thrilled to have finally found a quieter and more robust version that is also made in Germany, after using poor quality compressors from China. The only catch, of course, are the prices. The 230V variants are appropriately priced, but since I need 12 V for most applications, these were not really an option for me. So I came up with the idea of simply buying a 230V version and operating it with the help of the ASC. For this to work, however, the electromagnet must also be adapted, more on this later.

### The Schego M2K3:

![](pictures/Schego%20M2K3%20Topview.jpg)

I bought an M2K3 since it is the largest model and I got it used and therefore cheaper. The cool thing about this (and probably all Schego models) is that you can easily disassemble it. You can even get replacements like membranes directly from the manufacturer.

![](pictures/Schego%20M2K3%20Teilzerlegt.jpg)

You can also easily change it from vacuum to compressor and vice versa by simply rotating both valve plates.

![](pictures/Schego%20M2K3%20Ventile.jpg)

So altogether, this pump seems to be exactly what I was looking for. Now it only needs to be converted to low voltage.

### Converting from high-voltage to low-voltage coil

Since the pump will later be operated at about 12V, the configuration of the electromagnetic drive’s coil must be reconfigured. In my case, it previously had 1.2kΩ, which is obviously far too much for 12V operation. As I had no good alternative, I decided to unwind the coil and rewind it with several wires in parallel. On my coil, there was a little over 840m of wire, which I initially wound around two rods placed 20m apart. This turned out to be a problem in retrospect because the resulting 40 parallel wires, each 20m long, resulted in a resistance of 1Ω. Unfortunately, this was a bit to low to drive in combination with the ASC. So I had to rebuild the whole thing again with 10 parallel wires, each 80m long, through which I achieved a resistance of 13Ω. This is also suitable for 12–24V, however, for 5–12V operation, I would recommend 20 parallel wires, each 40m long, which should end up slightly below 4Ω. Finally, the new winding must, of course, be rewound, and the enamel at the new ends must be burned off.

### Configuration of the ASC

In general, there is not much to do with the ASC. It has a [DRV8231A](https://www.ti.com/de/lit/gpn/drv8231a) brushed motor driver, which is perfectly capable of driving a coil and even has build in overtemp and overcurrent protection. The coil is connected to the motor pins of the ASC, the pot pins stay unused at this stage of the project *(though they could be used for pressure feedback in the future)*. Next, the given software is flashed to the ASC. In my case, the pump was more effective at 45Hz than the original 50Hz; however, you may want to test this yourself. And now, all that’s left to do is close the case, and the pump can be used.

![](pictures/Schego%20M2K3%20mit%20ASC.jpg)
