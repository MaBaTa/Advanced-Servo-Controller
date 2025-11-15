# ASC as Inverter for (Schego) Air Pump

This is a subproject of the usage of the ASC as a inverter for a membrane compressor.

### Prestory:

Since I have been looking for a small compressor that is quiet and high quality for a long time, I was very happy when I came across the company [Schego](https://schego.de/de/hobby-freizeit/aquarientechnik/membranpumpen/).They produce a small range of aquarium / industrial membrane pumps. Since I also intend to use them in the area of air-brush & 3D printers, I was very happy to have finally found a quieter and more robust version that also is Made in Germany, after all the China compressors. The only catch is of course the price, whereas the 230V variants are perfectly appropriate priced. But since I need 12V for most applications, these were not really an option for me. So I came up with the idea of simply buying a 230V version, and operating it with the help of the ASC. For this to work, however, the electromagnet must also be adapted, more on this later.

### The Schego M2K3:

![](pictures/Schego%20M2K3%20Topview.jpg)

I've bougt a M2K3 since it is the biggest Model and i got it used a bit less expensive. The cool thing about this (and probaply all Schego models), is that you can easily disassemble it. You even get replacements like the membranes from the manufacturer.

![](pictures/Schego%20M2K3%20Teilzerlegt.jpg)

And you can pretty easily change it from vacuum to compressor and vice versa by just rotanting both these valve plates.

![](pictures/Schego%20M2K3%20Ventile.jpg)

So alltogother, this pump seems to be exactly what I was looking for. Now it only needs to be converted to low voltage.

### Converting for high voltage to low voltage coil

Since the pump will later be operated with about 12V, the configuration of the coil of the electromagnetic drive has to be reconfigured. In my case, it had previously 1.2KΩ, which is obviously far too much for 12V operation, as I had no good alternative, I decided to unwind the coil and rewind it with several wires in parallel. On my coil there was a little over 840m of wire, which I initially wound by 2, 20m apart rods. This turned out to be a problem in retrospect, because with the resulting 40 parallel wires with a length of 20m I achieved a resistance of 1Ω. Which unfortunately was a bit too little to drive this with the ASC. So I had to rebuild the whole thing again to 10 parallel wires, each 80m. With which I achieved a resistance of 13Ωs. This is also very suitable for 12-24V, for 5-12V I would rather recommend 20 parallel wires, each 40m which would then have to end up at slightly below 4Ω. Finally, the new winding must of course be rewinded, and the paint at the new ends has to be burned off.

### Configuration of the ASC

In general there is not that much to do to the ASC. Its has a [DRV8231A](https://www.ti.com/de/lit/gpn/drv8231a) brushed motor driver, witch is perfectly capabil of driving a Coil and even has overtemp and overcurrent protection. So the coil gets connected to the motor pins of th ASC, the pot pins stay unused at this state of the project. *(could be used for pressure feedback in the future)* Next the given Software is flashed to the ASC. In my case the pump was more effective at 45Hz than the original 50Hz, so you mayby wanna try out a bit as well. And now all that's left to do is close the case, and the pump can be used.

![](pictures/Schego%20M2K3%20mit%20ASC.jpg)
