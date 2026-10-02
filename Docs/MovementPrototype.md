# Movement prototype

The first runnable gate uses an empty Unreal Engine 5 level. `ATidesGameMode` spawns a prototype ship, ocean plane and captain. The ship uses a kinematic movement component with sail acceleration, wind alignment, rudder lag, and small pitch, roll and heave. Its deck is a moving collision base for the captain's `CharacterMovementComponent`.

Controls: **WASD** walks, **mouse** looks, **E** takes the helm when close to its stern position. At the helm **W/S** changes sail power, **A/D** steers, and **E** returns control to the helmsman. The crew handoff currently holds the last heading with a simple proportional controller; visible crew are a later increment.

## Verification in Unreal Editor

1. Open `TidesOfTheForsaken.uproject` in Unreal Engine 5 and build the C++ module.
2. Run Play in Editor on the default empty map.
3. Verify the captain stays on the moving deck while walking in every direction and during turns.
4. Look at the stern helm until `[E] Take Helm` appears, press E, steer, then press E again. Check that the ship keeps its heading and the captain resumes walking.
5. Observe movement base behavior during low frame rates and large waves before creating art assets.

This environment does not have Unreal Engine installed, so these runtime checks remain pending.

The helm now implements `IShipInteractable`. The captain traces from the camera through the visible wheel and checks the interaction distance; future stations can implement the same interface.
