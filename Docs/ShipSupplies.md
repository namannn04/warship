# Ship supplies

Each ship owns `UShipInventoryComponent`. Loading a cannon consumes one powder charge and one cannonball at their physical loading steps. Hull repair consumes planks before restoring structure. Cargo crates reduce the ship's effective sailing speed through a bounded weight factor.

The prototype begins with 30 planks, 60 powder charges, 60 cannonballs and 120 food rations. These amounts are code defaults for the blockout, not final balance. A physical supply ledger, cargo crates in the hold, food use, looting and resupply are later work.
