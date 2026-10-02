# Tides of the Forsaken

An Unreal Engine 5 pirate game being built around one continuous, explorable ship. The full user specification is preserved in [Docs/ProductBrief.md](Docs/ProductBrief.md).

## Current prototype source

- A third-person captain can walk on a moving two-deck ship, use a physical stairwell, take the helm and hand steering back to automatic heading control.
- Sailing accounts for wind alignment, sail setting, acceleration, rudder authority, cargo, damage, and wave motion.
- Six physical gun deck cannons have a manual loading cycle, aim controls, recoil and cannonball projectiles.
- A passive target ship accepts hull and mast impacts. Hull breaches cause flooding; water lowers the ship and can sink it.
- A lower-deck repair station lets the captain patch the hull and pump water. Cannons and repairs consume ship supplies.
- A role-aware crew job board drives low-frequency gunner reload and carpenter emergency work simulation.

This is a **source prototype**, not the finished game or a verified playable build. The crew are not yet visible characters, and the blockout uses Unreal's basic shapes. Combat AI, boarding, islands, sea monsters, cinematic assets, audio, and most of the product brief remain to be built.

## Test status

Run `Tests/run.sh` to compile and execute the engine-independent C++ rules for sailing, cannon loading, ship damage, inventory and crew job assignment. GitHub Actions runs these checks on every push.

Unreal Editor is not installed in the current development environment. The project still needs an Unreal build and Play-in-Editor checks for compile errors, moving-platform behavior, physical interactions, projectiles and performance. The focused manual checks are in `Docs/`.

## Repository layout

- `Source/TidesOfTheForsaken`: Unreal runtime C++ module and portable game rules
- `Config`: project and input configuration
- `Tests`: portable C++ tests and runner
- `Docs`: brief, feature notes and manual verification steps

## Next validation gate

Open `TidesOfTheForsaken.uproject` in Unreal Engine 5, build the C++ module, then test walking and stairs while sailing, helm handoff, cannon operation, target impacts, and emergency repair. Fix any build or runtime issues before visual polish or large-world expansion.
