# Five-phase-stepper-driver

I recently obtained a small laboratory spectrophotometer that had been discarded, and was surprised that the diffraction grating was directly driven by a 5-phase, ten wire Vexta motor. The optics were in perfect shape and useful for other projects, but there is little information on the web about how to drive a five phase stepper, and there are no working examples that I could find with Arduino.

Of course, you can buy a five phase driver from Oriental Motor Company (Vexta manufacturer) for about USD $200, but another option is to use an Arduino Pro Mini, and three much less expensive brushed DC motor drivers from Pololu.

The motor specs: Vexta PX33M-A-C6 0.21A, 33 Ohms per phase, 0.36 degrees/step. Ten wires.

The low current rating and moderate winding resistance means that direct drive from 5 to 6V is possible, avoiding the need for a chopper stepper driver. I decided to use three Pololu DRV8835 dual full bridge modules (only five H-bridges are used, leaving one free for other uses), and with dead simple code it is capable of executing 500 steps/sec from dead stop, without skipping a single step. Half step drive is available, for 2000 steps/revolution, capable of better than 500 steps/second.

See it move 1000 steps in real time!

![Stepper in action (1 minute MP4 video)](https://user-images.githubusercontent.com/5509037/108101833-a85dcb80-703c-11eb-8904-4f843a93893b.MP4)

**Vital information in image below**, used as a guide in creating the working example.

![10 Wire Sequence](https://user-images.githubusercontent.com/5509037/108101734-7ea4a480-703c-11eb-8b77-20ec248bf927.png)

There is confusion on the web about motor coil and wiring color code with lead assignment. I started with this diagram, which supposedly reveals the coil and winding start/finish order:

![10wire_pentagon_connection](https://user-images.githubusercontent.com/5509037/108101765-8c5a2a00-703c-11eb-8ffc-eda13e6816d4.png)

But the motor connector had white/yellow and grey/black reversed from the sequence above. The driver works with swapped connections (as long as both pairs of the two connections are reversed) but obeying the connector wire order resulted in the smoothest and presumably correct operation. That is, swap white/yellow and black/gray.

My decision to swap those leads is supported by the alternative assignment of wire colors and winding identifications in the PDF file below. Evidently Oriental Motor is not consistent with wire color codes. 

![5_Phase_Penta_Connection.pdf (44.9 KB)](https://github.com/jremington/Five-phase-stepper-driver/files/5990560/5_Phase_Penta_Connection.pdf)

For the pentagon wiring option, five half bridge drivers are used. Improved step sequences for the pentagon connection are shown in the PDF file below from Oriental Motor.

![10wire_pentagon_connection (pdf)](https://github.com/jremington/Five-phase-stepper-driver/files/5990584/vexta_pentagon_phase_sequence.pdf)

**Stepper Driver Design and Construction**

Wiring diagram for two of the phases, using the Pololu DRV8835 dual H bridge module (micro used was the Pro Mini). The complete pin assignments and subsequent connections are detailed in the code below. Image from Pololu product page: 

![Partial wiring diagram](https://forum.pololu.com/uploads/default/original/2X/2/2d3e2b9c3bdfc6a51cb122b177fbec8df0921917.png)

![Finished 5-phase driver board](https://forum.pololu.com/uploads/default/optimized/2X/a/a757dba4a2396a110fadecf0d8af845cf63d9c08_2_597x500.jpeg)

**Arduino Code** is posted in two files, totally unoptimized and storage-optimized.





