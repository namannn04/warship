# PROJECT: TIDES OF THE FORSAKEN

## 1. PRIMARY VISION

Build a premium-quality, realistic, cinematic 3D pirate game set in a large open ocean.

The game should make the player feel like they are physically living aboard a pirate ship rather than controlling a ship from a menu.

The player is a pirate captain, but the captain is also a fully playable character.

At any moment, the player should be able to:

- Walk around the ship freely.
- Go below deck.
- Enter storage areas.
- Visit the captain's cabin.
- Climb the rigging.
- Climb to the lookout platform.
- Use a spyglass.
- Talk to crew members.
- Give orders.
- Take direct control of the ship.
- Leave the wheel and let a crew member steer.
- Load and fire cannons.
- Use ranged weapons.
- Fight enemies with melee weapons.
- Board enemy ships.
- Repair the ship.
- Fight sea creatures.
- Explore islands.
- Manage food, ammunition and supplies.

The goal is to make the game feel like the player is inside a cinematic pirate movie.

It should NOT feel like:

- a simple boat simulator,
- a static open-world demo,
- a basic low-poly pirate game,
- an arcade vehicle controller,
- or a game where everything happens through UI buttons.

Most important actions should physically happen in the 3D world.

---

# 2. PLAYER EXPERIENCE

The ideal moment-to-moment experience should look like this:

The player is walking on deck while the ship moves naturally through large ocean waves.

Crew members are working around the ship.

Some are:

- adjusting sails,
- pulling ropes,
- cleaning the deck,
- carrying supplies,
- watching the horizon,
- repairing equipment,
- talking to each other,
- loading cannons.

The player hears:

- wood creaking,
- waves hitting the hull,
- ropes tightening,
- sails reacting to wind,
- crew conversations,
- distant thunder,
- seabirds,
- footsteps on wood.

Suddenly, the lookout shouts:

"SHIP OFF THE STARBOARD SIDE!"

The player can climb the mast and inspect the ship through a spyglass.

The player then decides what to do.

For example:

- Attack.
- Avoid the ship.
- Pursue it.
- Prepare cannons.
- Raise maximum sails.
- Turn into the wind.
- Prepare boarding crew.

The player gives:

"Battle stations!"

The crew dynamically moves to combat positions.

The player can then either:

### Option A
Walk to the helm and personally control the ship.

### Option B
Tell the helmsman:

"Turn starboard and maintain distance."

Then personally run toward a cannon and fight.

This freedom is one of the most important features of the entire game.

---

# 3. CAMERA

Primary perspective:

## Third-Person Character Camera

The player directly controls the captain.

Camera should feel cinematic but responsive.

Requirements:

- Smooth acceleration/deceleration.
- Natural camera lag.
- Collision avoidance.
- Shoulder switching.
- Dynamic FOV.
- Slight camera movement according to ship motion.
- Camera stabilization to prevent seasickness.
- Camera shake during cannon fire.
- Stronger shake during ship impacts.
- Subtle motion during storms.

Optional:

## First-Person Mode

Allow the player to switch between first-person and third-person.

First-person should especially work well for:

- steering,
- aiming firearms,
- using the spyglass,
- inspecting objects,
- exploring interiors.

---

# 4. THE MAIN PIRATE SHIP

The player's ship must be one continuous physical space.

Do NOT teleport the player between decks.

The player should physically walk:

- through doors,
- down stairs,
- through hatchways,
- up ladders,
- through cabins.

Historically informed sailing vessels used several distinct working levels, including quarterdecks, forecastles, gun decks, lower/orlop spaces and holds.

Build the ship around this concept.

---

# 5. SHIP STRUCTURE

The ship should contain approximately the following layout.

## LEVEL 1 — UPPER EXTERIOR

### Bow / Forecastle

Located at the front of the ship.

Include:

- Anchor equipment.
- Rope coils.
- Mooring equipment.
- Small weapon positions.
- Crew working stations.
- Forward observation area.

The bow should visibly rise and fall through waves.

Water spray should sometimes hit this area.

---

## MAIN WEATHER DECK

The central outdoor deck.

This should be one of the busiest areas aboard the ship.

Include:

- Main mast.
- Foremast.
- Mizzenmast.
- Rigging.
- Rope systems.
- Cargo.
- Barrels.
- Deck grates.
- Hatches.
- Cannon access.
- Crates.
- Repair supplies.
- Lanterns.
- Crew stations.

Crew should constantly use this area.

---

# 6. QUARTERDECK

The raised rear section of the ship.

Contains:

### Helm / Ship Wheel

This is a physical interaction point.

When the player approaches:

`[E] Take Helm`

When activated:

the player grabs the wheel physically.

The camera transitions smoothly into steering mode.

Do NOT instantly switch to an external vehicle camera.

The captain should visibly remain at the wheel.

---

# 7. HELM GAMEPLAY

While steering:

W / S:
Adjust sail power or commanded speed.

A / D:
Turn the wheel.

Mouse:
Look around independently.

Optional keys:

Q / E:
Look toward port/starboard quickly.

R:
Order sails raised.

F:
Order sails reduced.

X:
Drop anchor where appropriate.

The ship must not behave like a speedboat.

Movement should depend on:

- wind,
- sails,
- ship momentum,
- waves,
- ship mass,
- rudder angle,
- damage,
- cargo weight.

Turning should take time.

Large ships should feel heavy.

---

# 8. NAVIGATION STATION

Near the quarterdeck or captain's area:

Create a physical navigation table.

The player can approach it.

Interaction:

`[E] Inspect Map`

The player looks down toward the table.

The world map appears as a physical nautical chart.

Allow:

- setting destinations,
- viewing discovered islands,
- marking enemy ships,
- checking missions,
- viewing storm systems,
- tracking rumours.

Crew can automatically navigate toward a marked destination if ordered.

---

# 9. CAPTAIN'S CABIN

Located at the stern.

Make it detailed and atmospheric.

Include:

- Large windows.
- Navigation charts.
- Candles/lanterns.
- Captain's desk.
- Compass.
- Books.
- Personal chest.
- Weapons rack.
- Bed.
- Treasure.
- Letters.
- Ship log.

Functions:

### Ship Management

The captain can inspect:

- crew roster,
- provisions,
- ammunition,
- ship condition,
- cargo,
- money,
- missions.

However, do not make everything a floating menu.

Whenever possible, present this information through objects.

Examples:

Crew roster = physical ledger.

Map = physical map.

Ship log = book.

Treasure = visible chest.

---

# 10. LOOKOUT / CROW'S NEST

The player should physically climb ropes or ladders on the mast.

At the top:

provide a lookout platform.

From here:

the player can use a spyglass.

Spyglass should provide:

- realistic zoom,
- slight hand movement,
- lens vignette,
- distant object identification.

Possible discoveries:

- merchant ship,
- naval vessel,
- pirate ship,
- island,
- abandoned ship,
- sea monster,
- floating wreckage,
- storm,
- mysterious lights.

Crew lookout NPCs should also use this location.

---

# 11. GUN DECK

Below the main deck should be the primary cannon deck.

Long rows of cannons should line both sides.

Each cannon should exist physically.

Every cannon should support an interaction cycle:

1. Clean barrel.
2. Insert powder.
3. Insert cannonball.
4. Ram ammunition.
5. Move cannon into position.
6. Aim.
7. Fire.
8. Recoil.
9. Reload.

The complete animation does not always need to be manually performed by the player.

Crew AI can perform these jobs.

The player should still be able to operate a cannon directly.

---

# 12. CANNON GAMEPLAY

Approach cannon:

`[E] Operate Cannon`

Controls:

Mouse:
Aim horizontally/vertically.

Fire:
Fire cannon.

Different ammunition:

### Standard Cannonball
Hull damage.

### Chain Shot
Damages sails, masts and rigging.

### Grapeshot
Effective against exposed enemy crew.

### Heavy Shot
Slow but extremely destructive.

### Fire Shot
Rare ammunition capable of creating fires.

Enemy ships should have modular damage.

Do NOT use only a generic HP bar.

A cannonball can physically damage:

- hull,
- mast,
- sails,
- cannon,
- railing,
- deck,
- rudder.

---

# 13. LOWER DECK / CREW DECK

Under the gun deck, include crew spaces.

Possible rooms:

- Crew sleeping area.
- Hammocks.
- Kitchen/galley.
- Medical area.
- Repair workshop.
- Weapon storage.
- Food storage access.

NPCs should use these areas according to time and circumstances.

---

# 14. GALLEY

A functioning ship kitchen.

Contain:

- cooking pots,
- hanging utensils,
- food barrels,
- water containers,
- meat,
- fish,
- fruit,
- bread.

Food matters.

The ship carries provisions.

Crew morale and effectiveness slowly decline if food supplies run low.

Avoid turning this into an annoying survival meter.

Use it as a strategic resource.

---

# 15. STORAGE HOLD

Lowest major storage area.

Contain:

- food barrels,
- drinking water,
- cannonballs,
- spare wood,
- ropes,
- sails,
- trade goods,
- treasure,
- mission cargo.

Cargo should visually appear inside the ship.

If the player steals 20 crates from another ship, actual crates should appear in the hold where practical.

Cargo affects:

- ship weight,
- acceleration,
- value,
- mission objectives.

---

# 16. POWDER MAGAZINE

Create a protected gunpowder storage room.

This should be important during combat.

If fire reaches the powder magazine:

catastrophic explosion becomes possible.

The player may need to order crew to:

- extinguish fire,
- isolate an area,
- flood part of a compartment.

Enemy ships can suffer the same fate.

---

# 17. BILGE / LOWEST SHIP AREAS

The lowest areas can contain:

- water accumulation,
- pumps,
- structural beams,
- emergency repair locations.

Hull breaches allow water to enter.

Players should physically see flooding happen.

---

# 18. DYNAMIC SHIP DAMAGE

Use localized damage instead of only health points.

Ship condition consists of:

### Hull

### Sails

### Masts

### Rudder

### Cannons

### Crew

### Flooding

### Fire

Examples:

Hull damaged:
Water enters.

Rudder damaged:
Turning becomes difficult.

Mast broken:
Speed dramatically decreases.

Sails damaged:
Wind efficiency decreases.

Cannons destroyed:
One side loses firepower.

Crew injured:
Tasks become slower.

---

# 19. FLOODING

Hull breaches generate water entry points.

The water level should gradually increase inside the ship.

Crew can:

- patch holes,
- pump water,
- carry repair material.

If ignored:

the ship sinks.

The sinking should be physical and cinematic.

The ship should:

- gradually list,
- sit lower in water,
- become harder to control,
- develop interior flooding,
- eventually capsize or disappear beneath the ocean.

---

# 20. FIRE SYSTEM

Fire can spread across:

- sails,
- ropes,
- wooden deck,
- interior rooms.

Wind affects fire direction.

Rain reduces fire spread.

Crew can form emergency firefighting teams.

Fire creates:

- smoke,
- sparks,
- changing lighting,
- panic,
- structural damage.

---

# 21. CREW SYSTEM

The ship must feel alive even if the player does nothing.

Aim for approximately:

20-40 visible active crew on a large ship.

Additional crew can be simulated at reduced complexity.

Different crew roles:

## Helmsman

Steers when the player does not.

## Navigator

Handles navigation.

## Lookout

Detects threats.

## Gunner

Operates cannons.

## Sailor

Handles rigging and sails.

## Carpenter

Repairs ship damage.

## Surgeon

Treats injuries.

## Cook

Handles provisions.

## Marine/Fighter

Specialized boarding fighter.

## Quartermaster

Helps manage resources.

---

# 22. CREW COMMAND SYSTEM

The captain should be able to issue contextual orders.

Hold command button:

a radial command menu appears.

Categories:

### Navigation

- Full sails.
- Half sails.
- Stop.
- Turn port.
- Turn starboard.
- Hold heading.
- Follow target.
- Flee target.
- Drop anchor.

### Combat

- Battle stations.
- Load port cannons.
- Load starboard cannons.
- Fire at will.
- Hold fire.
- Target sails.
- Target hull.
- Prepare boarding.

### Emergency

- Repair hull.
- Extinguish fire.
- Pump water.
- Repair sails.
- Treat wounded.

### Crew

- Follow me.
- Defend this area.
- Attack target.
- Return to ship.

---

# 23. NATURAL CREW AI

Crew should NOT behave like robots waiting for commands.

They should possess routines.

During calm sailing:

- sailors work ropes,
- people talk,
- someone cleans,
- cook prepares food,
- lookout watches horizon,
- crew rests,
- musicians occasionally play,
- crew carries cargo.

During storms:

- crew secures cargo,
- adjusts sails,
- holds ropes,
- struggles against wind,
- reacts to waves.

During combat:

crew automatically transitions into battle behaviour.

---

# 24. CAPTAIN AUTHORITY

Crew responsiveness should depend on leadership and morale.

High morale:

- quicker commands,
- faster reloads,
- stronger boarding,
- better repairs.

Low morale:

- slower responses,
- arguments,
- fear,
- possible desertion.

Do NOT make morale a constant annoying bar.

It should change because of meaningful events.

Examples:

Winning battles.

Finding treasure.

Running out of food.

Repeated crew deaths.

Successful voyages.

Paying crew shares.

---

# 25. CHARACTER COMBAT

The captain can leave the helm at any time.

Weapons:

## Cutlass

Primary sword.

Support:

- light attack,
- heavy attack,
- block,
- parry,
- dodge,
- execution animations.

## Flintlock Pistol

Powerful short-range firearm.

Slow reload.

## Musket

Longer range.

## Blunderbuss

Close-range spread weapon.

## Throwing Knife

Optional stealth tool.

## Bow

Optional specialized weapon.

Combat should feel weighty and grounded.

Avoid exaggerated fantasy movement unless an ability explicitly requires it.

---

# 26. SHIP BOARDING

One of the flagship features.

If ships are sufficiently close:

the captain can order:

`PREPARE TO BOARD`

Crew throws grappling hooks.

Ships become temporarily connected.

Wooden planks may be placed between them.

Crew members jump between vessels.

The player physically participates.

Combat continues across both ships.

Objectives may include:

- eliminate captain,
- surrender enemy crew,
- capture cargo,
- steal map,
- destroy objective,
- capture entire ship.

---

# 27. SHIP CAPTURE

Enemy ships should sometimes be capturable.

After victory:

Player can:

- loot ship,
- sink ship,
- release ship,
- capture ship.

Captured ships may:

- join fleet,
- be sold,
- replace current ship.

---

# 28. OCEAN SYSTEM

The ocean is essentially a major character.

It must look premium.

Requirements:

- large-scale waves,
- small surface waves,
- foam,
- wake,
- reflections,
- translucency,
- underwater appearance,
- dynamic interaction with ship.

Ship movement must respond naturally to waves.

---

# 29. WEATHER

Dynamic weather states:

- clear skies,
- cloudy,
- fog,
- rain,
- heavy rain,
- thunderstorms,
- tropical storms.

Cloud movement should be visible.

Weather should gradually transition instead of instantly changing.

---

# 30. STORM GAMEPLAY

Storms must be dangerous.

Features:

- giant waves,
- strong wind,
- lightning,
- low visibility,
- heavy rain,
- deck flooding,
- ship rolling,
- cargo movement,
- crew struggling.

Lightning can occasionally strike:

- mast,
- sea,
- nearby ship.

Players may need to reduce sail to avoid mast damage.

---

# 31. DAY/NIGHT CYCLE

Implement a smooth cycle.

Sunrise.

Morning.

Afternoon.

Sunset.

Night.

Moonlight.

Storm lighting.

Night ships should use lanterns.

Distant ships may first become visible because of lights.

Moonlight reflecting over ocean should be cinematic.

---

# 32. SEA MONSTERS

Do not constantly spawn monsters.

They should be rare enough that encountering one feels special.

Possible monsters:

## Kraken

Tentacles rise around ship.

Tentacles can:

- strike deck,
- grab crew,
- wrap around mast,
- pull ship.

Players must:

- fire cannons,
- attack tentacles,
- protect crew,
- prevent hull destruction.

---

## Giant Serpent

Moves through water around vessel.

Can:

- ram ship,
- bite hull,
- surface suddenly,
- circle vessel.

---

## Megalodon-like Predator

Can attack smaller ships.

---

## Ghost Leviathan

Very rare supernatural encounter during specific conditions.

---

# 33. MONSTER CINEMATIC SYSTEM

Monster encounters should begin naturally.

Example:

Water becomes unusually calm.

Birds disappear.

Crew becomes nervous.

Lookout notices something.

Large shadow moves under ship.

The ocean surface changes.

Then:

a huge tentacle emerges beside ship.

Do not cut instantly into a traditional cutscene.

Keep the player inside gameplay.

Use cinematic camera effects without stealing control unnecessarily.

---

# 34. ENEMY SHIP TYPES

Different factions should behave differently.

## Merchant Ships

Avoid battle.

Carry valuable cargo.

May surrender quickly.

## Pirate Ships

Aggressive.

May attempt boarding.

## Naval Ships

Organized.

Powerful cannons.

Use formations.

## Bounty Hunters

Specifically hunt the player.

## Smugglers

Fast ships.

Avoid confrontation.

## Ghost Ships

Rare supernatural encounters.

---

# 35. NAVAL COMBAT AI

Enemies should make tactical decisions.

They can:

- position broadside,
- target sails,
- chase player,
- retreat,
- board,
- protect allied ships,
- exploit damaged rudder,
- use wind direction.

Difficulty should come from better decisions rather than simply giving enemies huge health.

---

# 36. CREW COMPANIONS

Create several named major companions.

For example:

### First Mate

Provides tactical advice.

### Navigator

Comments on routes/weather.

### Gunner

Improves cannons.

### Carpenter

Improves repairs.

### Surgeon

Reduces crew losses.

They should react dynamically.

Example:

Navigator:

"Captain, storm ahead. We can go around, but we lose half a day."

First Mate:

"That frigate has twice our guns. I would not fight her head-on."

The player decides.

---

# 37. COMPANION DECISION MEMORY

Important decisions should affect relationships.

Examples:

- abandoning injured crew,
- sharing treasure fairly,
- attacking civilians,
- rescuing shipwreck survivors,
- keeping promises.

Different companions have different personalities.

They may:

- approve,
- disagree,
- confront captain,
- eventually leave.

---

# 38. ISLAND EXPLORATION

The ship should not be the entire world.

Allow landing on:

- tropical islands,
- pirate settlements,
- forts,
- abandoned islands,
- caves,
- shipwreck beaches.

Use smaller dense locations instead of creating thousands of kilometres of empty procedural land.

---

# 39. PORTS

Ports should contain:

- tavern,
- shipyard,
- weapon merchant,
- general store,
- harbour master,
- crew recruitment,
- black market,
- mission boards.

The player can physically walk through ports.

---

# 40. SHIPYARD

Upgrade the ship.

Categories:

### Hull

Stronger wood.

### Cannons

Damage/reload improvements.

### Sails

Speed.

### Rudder

Turning.

### Storage

Cargo capacity.

### Crew Quarters

Crew capacity.

### Appearance

Figurehead.

Sail designs.

Colours.

Decorations.

---

# 41. ECONOMY

Player earns money through:

- contracts,
- trading,
- treasure,
- piracy,
- bounties,
- exploration,
- captured ships.

Money is spent on:

- food,
- ammunition,
- repairs,
- crew,
- ship upgrades,
- weapons,
- information.

---

# 42. TREASURE HUNTS

Treasure maps should require interpretation.

Instead of:

"Go to map marker."

Provide clues.

Example:

"Where the twin stones watch the drowned sailor, walk toward the setting sun."

Players use landmarks and maps.

---

# 43. RANDOM OCEAN EVENTS

Possible events:

- floating survivor,
- shipwreck,
- abandoned ship,
- merchant convoy,
- distress signal,
- storm,
- pirate ambush,
- whale sighting,
- naval patrol,
- floating cargo,
- sea monster evidence,
- mysterious island,
- mutiny on another ship.

---

# 44. REPUTATION

Track reputation with:

- pirates,
- navy,
- merchants,
- settlements,
- smugglers.

Actions should affect how the world reacts.

---

# 45. BOUNTY SYSTEM

Committing piracy increases bounty.

Low bounty:

occasional patrols.

High bounty:

larger naval ships hunt the player.

Extremely high bounty:

elite bounty hunters appear.

---

# 46. DEATH / DEFEAT

Avoid frustrating instant game-over wherever possible.

Possible defeat situations:

### Player knocked out during boarding

Crew may rescue player.

### Ship badly defeated

Enemy may capture player.

### Ship sinks near island

Player may wash ashore.

These can generate new gameplay instead of simply showing:

GAME OVER.

---

# 47. IMMERSION PRINCIPLE

Whenever possible:

DO NOT OPEN A MENU.

Example:

Instead of pressing menu > cannon:

Walk to cannon.

Instead of menu > steer:

Walk to wheel.

Instead of menu > lookout:

Climb mast.

Instead of menu > supplies:

Walk into storage.

This principle defines the game.

---

# 48. WORLD INTERACTION

Objects should react naturally.

Examples:

Lantern swings because of ship motion.

Barrels move slightly during violent storms.

Ropes sway.

Sails react to wind.

Doors move with ship tilt.

Crew adjusts stance when deck tilts.

Water comes over railing during giant waves.

---

# 49. PHYSICS

Prioritize believable physics over completely accurate simulation.

Simulate:

- buoyancy,
- ship roll,
- pitch,
- yaw,
- wave interaction,
- cannon recoil,
- destructible components,
- falling objects,
- ragdolls.

Do NOT simulate every rope physically.

Use hybrid systems to maintain performance.

---

# 50. GRAPHICS TARGET

Visual direction:

Photorealistic cinematic realism.

Reference quality:

modern AAA pirate movie aesthetic.

Focus especially on:

### Water

### Lighting

### Ship materials

### Characters

### Weather

### Fire

### Smoke

### Cloth sails

### Wet surfaces

### Wood damage

Ship materials should show:

- scratches,
- dirt,
- salt,
- wetness,
- age,
- rope fibers,
- damaged paint.

---

# 51. CHARACTER VISUALS

Crew cannot look duplicated.

Use modular characters.

Vary:

- faces,
- hair,
- beard,
- clothing,
- hats,
- body shape,
- scars,
- accessories.

Create several visual combinations using reusable assets.

---

# 52. ANIMATION QUALITY

High-priority animations:

- walking on moving deck,
- ship steering,
- cannon operation,
- climbing,
- sword combat,
- firearm reload,
- carrying cargo,
- pulling ropes,
- repairing,
- falling,
- swimming,
- boarding.

Use inverse kinematics for:

- hands,
- feet,
- ship controls,
- stairs,
- uneven decks.

---

# 53. SOUND DESIGN

Sound quality is critical.

Layer ocean audio.

Examples:

Near hull:

deep water movement.

Deck:

waves + wood.

Storm:

wind + rain + thunder.

Below deck:

muffled waves + wood creaks.

Cannons:

extremely powerful bass-heavy report.

Interior cannon firing should sound different from exterior firing.

---

# 54. DYNAMIC MUSIC

Music should react to gameplay.

Calm sailing:

minimal orchestral music.

Exploration:

adventurous themes.

Enemy spotted:

tension rises.

Combat:

full orchestral percussion.

Kraken:

unique monster theme.

Victory:

music resolves gradually.

Do not abruptly start/stop tracks.

---

# 55. UI PHILOSOPHY

Keep HUD minimal.

Default:

- health,
- equipped weapon,
- small interaction prompts.

During steering:

show:

- heading,
- wind,
- sail state,
- speed,
- major ship damage.

During combat:

show enemy information only when relevant.

Do not fill screen with dozens of indicators.

---

# 56. INTERACTION SYSTEM

Create one universal interaction framework.

Every interactable implements something equivalent to:

Interactable

Functions:

Interact()

GetInteractionText()

CanInteract()

Examples:

Helm:
"Take Helm"

Cannon:
"Operate Cannon"

Door:
"Open Door"

Storage:
"Inspect Supplies"

Crew:
"Talk"

Ladder:
"Climb"

This allows expansion without rewriting character logic.

---

# 57. GAME STATES

Player should transition seamlessly between:

CharacterExploration

HelmControl

CannonControl

Combat

Climbing

Swimming

Interaction

Spyglass

Boarding

Avoid loading screens between these states.

---

# 58. TECHNICAL ENGINE RECOMMENDATION

Use Unreal Engine for the high-fidelity implementation.

The project needs:

- large environments,
- realistic lighting,
- cinematic rendering,
- character animation,
- physics,
- AI,
- water,
- scalable LOD systems.

Use C++ for important underlying systems.

Blueprints may be used for:

- configuration,
- level events,
- designers' workflows,
- mission scripting.

Do not build the entire project as one giant Blueprint graph.

---

# 59. CODE ARCHITECTURE

Separate systems carefully.

Suggested structure:

Game/
    Character/
    Ship/
    Ocean/
    Combat/
    Weapons/
    Crew/
    AI/
    Navigation/
    Weather/
    World/
    Missions/
    Inventory/
    Interaction/
    Audio/
    UI/
    Save/
    Optimization/

---

# 60. SHIP CLASS ARCHITECTURE

Example:

ShipActor

Components:

ShipMovementComponent

ShipBuoyancyComponent

ShipDamageComponent

ShipSailComponent

ShipRudderComponent

ShipWeaponComponent

ShipCrewComponent

ShipInventoryComponent

ShipFireComponent

ShipFloodingComponent

ShipAudioComponent

Keep them modular.

---

# 61. CHARACTER ARCHITECTURE

CaptainCharacter

Components:

Movement

Combat

Inventory

Interaction

Command

Climbing

Swimming

Health

Animation

Camera

---

# 62. CREW AI ARCHITECTURE

CrewMember

Properties:

Role

CurrentTask

Morale

Health

CombatAbility

RepairAbility

NavigationAbility

Personality

AI states:

Idle

RoutineTask

FollowingOrder

Combat

Repair

FireEmergency

FloodEmergency

Boarding

Fleeing

Injured

---

# 63. SHARED TASK SYSTEM

Do not individually script every sailor.

Create a ship job system.

Example:

Ship generates:

`ReloadCannon_07`

Nearest qualified free gunner claims task.

Hull gets damaged:

`RepairBreach_03`

Available carpenter automatically takes task.

Fire:

`ExtinguishFire_02`

Crew prioritizes emergency.

This makes crew behaviour scalable.

---

# 64. NAVIGATION AI

Crew-controlled ship AI should receive high-level commands.

Example:

MaintainHeading(125 degrees)

FollowTarget(enemyShip)

KeepDistance(80m)

PresentBroadside(PORT)

FleeFrom(target)

Navigation system calculates rudder/sail behaviour.

---

# 65. NPC OPTIMIZATION

Do NOT fully simulate 40 characters at maximum quality all the time.

Use AI significance levels.

Nearby NPC:

Full AI + detailed animation.

Medium distance:

Reduced decision frequency.

Far away:

Simplified state simulation.

Inside hidden lower deck:

possibly background simulation unless relevant.

---

# 66. OCEAN OPTIMIZATION

The ocean can destroy performance if implemented badly.

Use:

GPU-driven wave rendering.

Simplified collision representation.

Limited buoyancy sample points.

Do not run expensive full water physics against every object.

---

# 67. LOD SYSTEM

Every major asset needs LOD management.

Ships:

LOD0:
Near player.

LOD1:
Medium.

LOD2:
Far.

Impostor / simplified mesh:
Extreme distance.

Characters should also reduce animation and simulation quality by distance.

---

# 68. OCCLUSION

Interior ship decks provide excellent opportunities for optimization.

When player is below deck:

do not render expensive exterior details that cannot be seen.

When player is outside:

deep interior rooms can be culled.

---

# 69. PERFORMANCE TARGET

Performance is not optional.

Target:

1080p / 60 FPS on reasonable gaming hardware using appropriate quality settings.

Provide:

Low

Medium

High

Ultra

settings.

The game should remain playable without requiring maximum graphics hardware.

---

# 70. GPU PERFORMANCE PRIORITIES

Use expensive effects where the player notices them.

Spend performance on:

- nearby ocean,
- nearby ship,
- characters,
- combat effects,
- lighting.

Reduce detail for:

- distant ships,
- distant islands,
- invisible interiors,
- distant ocean geometry.

---

# 71. PARTICLE EFFECTS

Use Niagara or equivalent scalable particle effects for:

- cannon smoke,
- fire,
- sparks,
- rain,
- ocean spray,
- splinters,
- dust,
- fog.

Effects must have scalability settings.

---

# 72. DESTRUCTION

Avoid full procedural destruction of the entire ship.

Use modular destruction.

Sections can have:

Intact mesh.

Damaged mesh.

Destroyed mesh.

Add:

- wood splinter particles,
- decals,
- broken railing,
- holes.

This looks realistic without destroying performance.

---

# 73. SHIP MOVEMENT MODEL

Do not attach every player and NPC rigidly without considering ship motion.

Characters should inherit ship velocity appropriately.

Movement aboard ship should remain stable even when the vessel moves.

The player should not slide randomly across the deck.

However, extremely violent impacts may physically stagger characters.

---

# 74. SAVE SYSTEM

Save:

Player position.

Ship position.

Ship damage.

Crew.

Inventory.

Cargo.

Missions.

World events.

Reputation.

Captured ships.

Upgrades.

Companion relationships.

---

# 75. FIRST PLAYABLE SCENARIO

Do NOT begin development by creating the entire world.

Build one extremely polished vertical slice.

Scenario:

Player wakes inside captain's cabin.

Walks outside.

Ocean is calm.

Crew is working.

Player climbs mast.

Lookout notices merchant ship.

Player comes down.

Player takes helm.

Player approaches merchant ship.

Enemy pirate ship suddenly appears.

Player gives:

"Battle stations."

Crew loads cannons.

Player hands steering to helmsman.

Player operates cannon.

Ships exchange fire.

Enemy closes distance.

Boarding begins.

Player sword fights.

Enemy ship catches fire.

Storm starts approaching.

After battle, player returns to own ship.

Damaged hull starts flooding.

Player orders crew to repair.

Then a giant shadow moves underneath the ship.

END DEMO.

If this experience looks and feels excellent, the foundation is working.

---

# 76. DEVELOPMENT PHASE 1 — MOVEMENT PROTOTYPE

Build:

- ocean,
- basic ship,
- buoyancy,
- third-person character,
- moving ship traversal,
- camera,
- helm.

Success condition:

Player can walk naturally around a moving ship and take control of it without physics glitches.

---

# 77. DEVELOPMENT PHASE 2 — FULL SHIP

Add:

- decks,
- cabins,
- hold,
- gun deck,
- mast,
- crow's nest,
- ladders,
- interactions.

Success condition:

Entire ship can be explored seamlessly.

---

# 78. DEVELOPMENT PHASE 3 — CREW

Add:

10-20 crew.

Implement:

- routines,
- task system,
- commands,
- helm AI,
- cannon AI.

---

# 79. DEVELOPMENT PHASE 4 — NAVAL COMBAT

Add:

enemy ship.

Implement:

- cannons,
- damage,
- sails,
- hull damage,
- flooding,
- repair,
- fire.

---

# 80. DEVELOPMENT PHASE 5 — CHARACTER COMBAT

Add:

- cutlass,
- flintlock,
- enemy pirates,
- blocking,
- parrying,
- boarding.

---

# 81. DEVELOPMENT PHASE 6 — CINEMATIC ENVIRONMENT

Add:

- advanced ocean,
- sky,
- clouds,
- rain,
- storms,
- day/night,
- high-quality lighting,
- audio.

---

# 82. DEVELOPMENT PHASE 7 — SEA MONSTER

Implement one exceptionally polished Kraken encounter.

Do not create five mediocre monsters initially.

One excellent monster is more valuable.

---

# 83. DEVELOPMENT PHASE 8 — WORLD

Only after the ship experience works:

add:

- islands,
- ports,
- quests,
- treasure,
- economy,
- factions.

---

# 84. VISUAL QUALITY RULE

Never substitute visual quality with excessive effects.

Realism comes from:

good lighting,

good materials,

correct scale,

animation,

physics,

sound,

environmental reactions.

Not just:

bloom,

motion blur,

particles.

---

# 85. SCALE

Everything must have believable physical proportions.

Ship doors.

Stairs.

Cannons.

Cabins.

Masts.

Ropes.

Furniture.

Characters.

Incorrect scale instantly destroys realism.

---

# 86. DETAILS THAT MAKE THE GAME FEEL AAA

Add small environmental reactions.

When cannon fires:

- crew covers ears,
- deck vibrates,
- smoke expands,
- rope moves,
- nearby birds fly away.

When giant wave hits:

- characters brace,
- water runs across deck,
- loose objects shift,
- sails shake,
- ship creaks.

When enemy cannonball hits:

- wood explodes into splinters,
- nearby crew reacts,
- hole appears,
- dust fills air,
- alarms begin.

These details matter more than simply increasing polygon counts.

---

# 87. CINEMATIC RULE

The game should frequently create scenes that LOOK scripted even though they are emerging naturally from systems.

Example:

Sunset.

Enemy ship beside player.

Cannons firing.

Smoke moving with wind.

Crew fighting.

Lightning in background.

Water crashing onto deck.

Mast collapses between ships.

Captain jumps over debris and boards enemy vessel.

This should happen through interacting systems, not only pre-rendered sequences.

---

# 88. NO-FAKE-SHIP RULE

The player's ship is not merely a controllable vehicle.

It is simultaneously:

- the player's home,
- combat platform,
- moving level,
- inventory,
- command centre,
- social hub,
- survival system,
- progression system.

Almost every major gameplay system should somehow connect back to the ship.

---

# 89. PROCEDURAL VS HANDCRAFTED CONTENT

Use procedural systems for:

- ocean encounters,
- weather,
- ambient traffic,
- loot variation,
- crew routines.

Use handcrafted content for:

- major islands,
- story missions,
- boss encounters,
- important ports,
- companion stories.

This produces scale without making the world feel generic.

---

# 90. PLAYER FREEDOM

Do not force players into one role.

During combat, the captain can:

### Command

Stay near quarterdeck and issue orders.

### Steer

Personally maneuver ship.

### Gunner

Operate cannon.

### Marksman

Shoot enemy crew.

### Fighter

Prepare boarding party.

### Repair

Go below deck and help save ship.

This is one of the most important design pillars.

---

# 91. EXAMPLE FULL BATTLE

The player spots an enemy frigate.

Spyglass identifies it.

Captain orders:

"Prepare port cannons."

Crew starts loading.

Captain takes helm.

Player turns ship.

Wind fills sails.

Enemy fires first.

Cannonball destroys railing.

Another penetrates hull.

Carpenter reports damage.

Captain orders:

"Repair lower deck!"

Crew runs downstairs.

Player brings ship parallel to enemy.

Captain leaves helm.

Helmsman immediately takes over.

Player runs downstairs.

Cannons are ready.

Player manually aims one.

Fire.

Whole broadside fires.

Enemy mast takes damage.

Captain orders:

"Load chain shot!"

Crew reloads.

Enemy begins turning.

Captain runs to bow.

Enemy pirates prepare boarding.

Player fires pistol.

Ships collide.

Grappling hooks attach.

Crew screams:

"BOARD THEM!"

Music rises.

Player draws cutlass.

Pirates cross between ships.

During combat:

storm begins.

Heavy rain extinguishes part of enemy fire.

A wave separates the vessels partially.

Enemy mast collapses.

Player defeats enemy captain.

The surviving enemy crew surrender.

Player chooses:

Take cargo.

Recruit survivors.

Capture ship.

Sink vessel.

That is the desired gameplay fantasy.

---

# 92. FINAL EXPERIENCE TARGET

The player should occasionally be able to stop moving and simply look around because the game world itself looks impressive.

Standing on the quarterdeck at sunset should already feel rewarding.

Walking below deck during a storm should feel dramatically different from standing outside.

Firing a full broadside should feel powerful.

Seeing a sea monster emerge should feel frightening.

Climbing the mast should provide a sense of height.

Losing a mast should feel catastrophic.

Capturing another ship should feel meaningful.

The player should feel like:

"I am actually the captain of this vessel."

Not:

"I am controlling a pirate-themed vehicle."

---

# 93. NON-NEGOTIABLE REQUIREMENTS

The final implementation MUST prioritize all of these:

1. Seamless third-person exploration.

2. Fully explorable multi-deck pirate ship.

3. Physical helm interaction.

4. Ability to leave helm while crew continues steering.

5. Crew command system.

6. Autonomous crew AI.

7. Physical cannons.

8. Naval combat.

9. Character combat.

10. Boarding.

11. Localized ship destruction.

12. Flooding.

13. Fire.

14. Repair mechanics.

15. Realistic ocean.

16. Dynamic weather.

17. Day/night system.

18. Sea monsters.

19. Climbable mast/lookout.

20. Spyglass.

21. Storage/cargo.

22. Food/provisions.

23. Ship upgrades.

24. Companions.

25. Islands and ports.

26. Cinematic audio.

27. Strong environmental animation.

28. High graphical fidelity.

29. Scalable performance.

30. Stable gameplay without noticeable lag.

---

# 94. MOST IMPORTANT ENGINEERING RULE

Never implement visual realism at the cost of a broken game.

The priority order is:

1. Stable player movement.
2. Stable ship movement.
3. Stable moving-platform interactions.
4. Responsive controls.
5. Reliable crew AI.
6. Combat.
7. Physics.
8. Graphics polish.

A beautiful game running poorly or constantly glitching is not acceptable.

---

# 95. AGENT EXECUTION INSTRUCTION

Treat this document as the product specification.

Do not attempt to implement the entire game in one pass.

First establish a clean modular architecture and build the vertical slice.

For every phase:

1. Define the architecture.
2. Implement the core system.
3. Test it in isolation.
4. Integrate it with existing systems.
5. Profile performance.
6. Fix bugs.
7. Polish visuals.
8. Move to the next system.

Do not create placeholder architecture that will need to be completely rewritten later.

Design every major system so the game can gradually scale from:

one ship

to

multiple ships,

full crew,

combat,

storms,

monsters,

islands,

and eventually the complete open world.

The first milestone is not "create an open world."

The first milestone is:

**Create one pirate ship that feels so believable, alive, cinematic and interactive that simply spending ten minutes aboard it is already entertaining.**

Everything else should grow from that foundation.