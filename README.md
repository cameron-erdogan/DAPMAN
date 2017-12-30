# DAPMAN
Secret Handshake + Leap Motion + Raspberry Pi 

Unlock a safe using a secret handshake.

### Video Feature Walkthough: https://vimeo.com/193295633


## What is this?
Most people don’t get to have a doorman to watch over their apartment and stuff. Dapman is a digital doorman that only opens what it’s guarding when you correctly “dap” him up. 

## Why did you do this?
Dapman spawned from wanting to find a non-gaming application for my Leap Motion. Even though Leap Motion has experienced a rebirth due to Oculus VR, it seemed like the product came and went without many attempts to do something weird with it. 

## How does it work?
The project has two main parts:
- a laptop with a Leap Motion attached 
- a modified IKEA cabinet with a Raspberry Pi-controlled electric lock 

The laptop does the processing required by Leap Motion and has a GUI shows you some useful things like your hand’s position and how far through the dap process you are. It also acts as a tcp client and sends a message to the Raspberry Pi when you dap up Dapman correctly. 

The Raspberry Pi acts as a server and listens to incoming messages from the laptop. One of the Raspberry Pi’s IO pins is attached to a circuit that locks and unlocks a solenoid lock that was built into the cabinet. 

## What technologies did you use?
The MVP of this project is the Leap Motion, which is powered by my laptop (there are no drivers for the Raspberry Pi’s class of processor, sadly). 

All of the code on the laptop was written in C++. I used Leap’s API to do the hand tracking and OpenFrameworks to draw the GUI and as a wrapper for tcp client stuff. 

The Raspberry Pi runs a very simple python tcp server program and uses the gpiozero library for communicating with the Pi’s GPIO pins. Finally, the actual electric lock is a lock-style solenoid from adafruit, and uses a circuit very similar to the one used in this [adafruit tutorial](https://learn.adafruit.com/secret-knock-activated-drawer-lock/wiring). 

## Some Images:

![circuit](images/circuit.jpg)
the circuit 

![circuit](images/lock.jpg)
the solenoid lock

![circuit](images/sideview.jpg)
a view of the installation
