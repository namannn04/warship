# Tides of the Forsaken

An Unreal Engine 5 pirate game built around one continuous, explorable ship. The full product brief is in [Docs/ProductBrief.md](Docs/ProductBrief.md).

## First milestone

Build a stable movement prototype: the captain walks on a moving ship, approaches a physical helm, takes control, and can hand steering back to a helmsman. This is the foundation for the larger vertical slice in the brief, not a claim that the full game is implemented.

## Development approach

Work in small, complete increments and push each finished increment. Prioritize moving-platform stability and responsive controls before visual polish. Unreal Editor is needed to compile, create the playable level and assets, and validate runtime behavior.

## Repository

- `Source/TidesOfTheForsaken`: runtime C++ module
- `Config`: project and input configuration
- `Docs/ProductBrief.md`: user-provided product specification

## Next playable gate

1. Compile in Unreal Engine 5.
2. Create a test ocean level and collision-ready ship mesh.
3. Place captain, ship, and helm actors and verify walking on deck during sailing.
4. Profile frame time and fix movement or camera issues before adding more systems.
