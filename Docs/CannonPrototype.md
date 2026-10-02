# Gun deck cannon prototype

Six physical cannons are spawned on the gun deck, three on each side. Each stays attached to the moving ship and implements `IShipInteractable`. Approach and look at one for `[E] Operate Cannon`. While operating, move the mouse to aim, press **R** through the five loading stages, **left click** to fire a physical cannonball, and **E** to return to walking. A shot enters recoil and must be cleaned before another loading cycle.

The ball currently collides and disappears on impact. Localized damage, ammunition types, crew reloads, audio, smoke, and enemy ships are separate future systems. The portable cannon state machine has a passing C++ test; firing and moving-platform interaction still require Unreal Editor verification.
