# Ship traversal blockout

The prototype ship now has a weather deck with a real central opening, ten physical stair steps, and a gun deck below it. Each surface uses collision on a component attached to the same moving ship root. This keeps traversal continuous as the vessel translates, pitches, and rolls.

The ship remains a blockout: its cube surfaces, mast, and walls establish dimensions and access paths for later art. They are not the final vessel or materials. The stair risers are 30 cm, below the captain movement component's normal step height. In Unreal Editor, walk down and back up while the ship is moving and turning; check that the character stays based on each step and deck surface.
