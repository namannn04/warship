# Tides of the Forsaken

An Unreal Engine 5 pirate game being built around one continuous, explorable ship. The full user specification is preserved in [Docs/ProductBrief.md](Docs/ProductBrief.md).

## Current prototype source

- A third-person captain starts in an aft cabin and can walk through a three-level blockout ship, use two physical stairwells, take the helm and hand steering back to automatic heading control.
- Press `V` to toggle a zoomed spyglass view; pointing at the enemy reveals its range and heading.
- Sailing accounts for wind alignment, sail setting, acceleration, rudder authority, cargo, damage, and wave motion.
- Six physical gun deck cannons have a manual loading cycle, aim controls, recoil and cannonball projectiles.
- An enemy ship maneuvers for broadside shots and fires physical cannons at the player. Both ships take localized damage: hull breaches cause flooding, water lowers a ship, and a sunk hull continues descending and listing. A sunk ship ends the encounter with a victory or defeat message. Cannon impacts can also ignite fires, which spread between deck, sails and hold, damage the ship and respond to storm rain.
- A gun-deck repair station lets the captain patch the hull and pump water. Cannons and repairs consume supplies shown at a physical hold ledger.
- Visible blockout crew move toward role-aware jobs for gun loading, repair, pumping and firefighting.
- A shared day/night and storm cycle drives sun light, wind, waves and fire weather.

This is a **source prototype**, not the finished game or a verified playable build. The ship and crew use Unreal's basic shapes. Boarding, islands, sea monsters, cinematic assets, audio, and most of the product brief remain to be built.

## Test status

Run `Tests/run.sh` to compile and execute the engine-independent C++ rules for sailing, cannon loading, ship damage, sinking, inventory, crew job assignment, weather, fire and enemy broadside decisions. GitHub Actions runs these checks on every push.

Until Unreal Editor is installed, only the portable tests can run. Once an official Linux engine build is available, `Scripts/build-linux.sh /path/to/UnrealEngine` builds the editor target. The project still needs Play-in-Editor checks for compile errors, moving-platform behavior, physical interactions, projectiles and performance. The focused manual checks are in `Docs/`.

## Repository layout

- `Source/TidesOfTheForsaken`: Unreal runtime C++ module and portable game rules
- `Config`: project and input configuration
- `Tests`: portable C++ tests and runner
- `Docs`: brief, feature notes and manual verification steps

## Next validation gate

Open `TidesOfTheForsaken.uproject` in Unreal Engine 5, build the C++ module, then test walking and stairs while sailing, helm handoff, cannon operation, target impacts, and emergency repair. Fix any build or runtime issues before visual polish or large-world expansion.
