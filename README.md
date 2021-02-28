# PDC_Identifier_Generator
Eurosocpe Plugin that generates real world (e.g. 123A, 456C) PDC Identifier

PDC_identifier Assigner for Euroscope

**Compatible with Euroscope beta r24 or higher (plugin was compiled using VS toolset 2019) https://www.euroscope.hu/wp/2020/04/12/3-2-1-24/

Set-up:
1. Other SET -> Plug-ins -> Load -> Load PDC_identifier.dll
2. Choose Standard ES radar screen from the forbidden
3. Add it to the allowed to draw on types "<<"
4. Hit S on the Departrue list
5. Add Item -> Tag Item type "PDC_identifer/PDC" -> Header name "PDC"
6. Left Button "PDC/Grant PDC" -> Right button "PDC/Reset"
7. Click F on the Departure List and check the PDC box

To Use:
1. Check everything is set on the flight strip
2. Left click on the column under PDC
3. You will notice a preview message flashing in the message area (don't worry this is just a preview)
4. Check everything is correct, simply ctrl+v in the box and hit enter, this actually sends the PDC

Note:
1. Should you require getting rid of the PDC identifier, just right click on the same spot, however this also cleans up the scratchpad
2. As of this version, it is unsure if this custom tag will be passed along to different controller
3. You might counter STACKOVERFLOW and your ES may Crash

Enjoy!
Isaac.
