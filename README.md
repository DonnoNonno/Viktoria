# Wooden Pinball
 
## Description
Pinball game for the physics subject. 

**Original game:** https://www.classicgame.com/game/Pinball+2

**Github Link:** https://github.com/DonnoNonno/Viktoria

## Features
 - Title Scene & Dead Scene.
 - Bumpers do a bounce effect.
 - Death and flippers have Fx.

## Controls

 - Left arrow: Move left flipper
 - Right arrow: Move right flipper
 - Down arrow: Activates kicker

## Debug

 - F1: Show collisions. You can grab the ball with the mouse.

## Developers

 - Iván Bermúdez Sagra
 - Rafael Esquius Pérez
 - Pau Garriga Brotons
 - Joel Romero Botella

## Solved Bugs
 - The ball sometimes went through the flippers.

   Solution --> - Increasing the size of the collider a bit.
              - Adjusting the speed at which the flippers travel so that it does not coincide when the ball goes through the flipper.
 
 - Memory Leak with chains. The chains did not stop creating infinitely.

   Solution --> - Creating a function that prints all chains once.
   
 - When the kicker activates, it activates once more. If it falls back to the kicker zone, the previous impulse is restarted again

## License

This project is licensed under an unmodified MIT license, which is an OSI-certified license that allows static linking with closed source software. Check [LICENSE](LICENSE) for further details.
