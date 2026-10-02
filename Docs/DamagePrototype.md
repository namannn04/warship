# Localized hit and flooding prototype

A passive target ship begins off the player's port side. Port gun deck cannons can fire at it. Cannonballs now report impacts to `UShipDamageComponent`, which identifies the hit component and updates the relevant ship condition. Hull hits create breaches; breaches admit water over time; enough water sinks the ship. Mast hits lower sailing efficiency. A damaged rudder would reduce turn authority, and repair and pumping APIs are ready for physical workstations and crew jobs.

The sailing component uses sail, mast, rudder and water condition factors. Water makes a ship sit lower. The movement and damage rules have portable passing tests. The target is a stationary test vessel; enemy combat AI and visible modular destruction are not implemented yet.

In Unreal Editor, fire at the port-side vessel and check the impact status, flooding, and sinking behavior. Test hits to hull and mast separately. This integration cannot be run in the current environment because Unreal Editor is unavailable.
