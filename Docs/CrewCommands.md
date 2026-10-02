# First navigation orders

The ship has a `UShipCommandComponent` that holds the ordered heading and steers toward it whenever the captain is away from the wheel. Taking the helm suspends automatic rudder control; leaving it records the current heading for the helmsman. Component tick ordering makes the command update run before the sailing movement update.

Prototype controls anywhere aboard: **R** raise sails by 20%, **F** reduce sails by 20%, and **X** toggle anchor. Away from the wheel, **Z** orders a 20° port turn and **C** orders a 20° starboard turn. At the helm, **W/S** also trim sail and **A/D** directly steer. A compact status line shows heading, speed, sail setting, and anchor state.

These are input bindings for the first playable prototype. A visible crew member, spoken acknowledgement, and radial command interface remain to be built and tested in Unreal.
