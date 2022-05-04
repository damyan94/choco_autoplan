Avtoplanovik-300 (R)
by Damyan Damyanov 2022

Open source and free for use, just remember to give credit to the original autor.
In case of questions, do not hesitate to contact me on my e-mail: damyandamyanov_94@yahoo.com

----------------------------------------------------------------------------------------------------

README:

This program is aimed at automating the planning of production of chocolate masses on the mass
making line of a chocolate plant. Doing this task manually can be quite time-consuming. The program
generates a rough weekly production plan for the chocolate masses on the line based on demands for
masses from the moulding lines.

Chocolate mass making 101: Cocoa liquor, fats, sugar, SMP and whey powder are dosed and mixed in the
mixer to form a homogenous coarse paste. This paste is then refined from 1 mm to about 150-250 mm,
which is then finely refined to about 25-35 microns. During this time the conche is filled with this
refined mass and once it is fully loaded, conching can start and take place. For the duration of the
conching process the conche is occupied and once done it can be used again for a new batch. The
ready chocolate is then stored in buffer tanks before being distributed to the moulding lines.

The inputs to this program are the configuration files for the types and volumes of conches and the
types and conching characteristics for each chocolate mass.

In a nutshell, the program has a list of conches and masses and then populates a given mass on the
first free conche on the list. The conche is then occupied for the duration of the production of
the mass. What type of mass is chosen depends on its priority - a number that takes into account
the planned consumption of this mass for the next three shifts and its current volume at storage.
The mass with the highest priority is then chosen.

The program can generate plans in three modes:
1. Match demand and produce at max
2. Match demand and fill up buffers to maximum capacity
3. Match demand and do not fill buffers

Below is a table with a comparison between the different modes:

No | Matches demand | Buffer capacity at end of week
---|----------------|--------------------------------
 1 | Yes            | Overflowing
 2 | Yes            | Full just to the brim
 3 | Yes            | Same as starting volume

----------------------------------------------------------------------------------------------------

CHANGELOG:

v.1.01 - 02.2022
	1. Code changes in order to make the program more flexible with changes in line setup and
	   assortments of masses:
	   - All configuration settings are now accessible in the cfg folder instead of being fixed
	     as enums.
	   - This way the program can be configured without the support of the programmer.
	2. Added three modes for generation of the plan: produce at max, fill up buffers and do not
	   fill buffers.
