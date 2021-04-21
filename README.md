# Arduino Remote
A simple gist for controlling an LG TV with infrared remote implemented on an arduino.

This example uses the [Arduino-IRRemote](https://github.com/Arduino-IRremote/Arduino-IRremote) library to handle IR signals.
The library supports more than just LG.
Check it out!

The IR codes for the LG TV were found from [here](https://gist.github.com/francis2110/8f69843dd57ae07dce80).
After a bit of searching, I found out that LG used NEC (up until 2013, not sure on the later versions).

![NEC protocol](https://imgur.com/2yvsPnc.png)

So, I tried to use the NEC protocol ([API](https://github.com/Arduino-IRremote/Arduino-IRremote/blob/48a3249cb810446e3d7b2d05d0c29a25214d5dc5/src/ir_NEC.cpp#L91)) but to avail.
I was able to decode the address and command from the IR codes but it doesn't seem to be working.

More details on my homepage - ( [🇺🇸 en]() / [🇰🇷 ko]() )

## Photos

![cam](https://imgur.com/zHnJXCt.png)

![circuit](https://imgur.com/ZmkBiQp.png)

The circuit editing software is [Circuit.io](https://www.circuito.io/).
