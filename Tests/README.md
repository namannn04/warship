# Portable sailing checks

Run from the repository root:

```sh
g++ -std=c++17 -Wall -Wextra -Werror -I Source/TidesOfTheForsaken/Public Tests/SailingModelTests.cpp -o /tmp/tides-sailing-tests
/tmp/tides-sailing-tests
```

These tests cover acceleration, rudder authority, anchor deceleration, frame substeps, and wind alignment. They verify the sailing rules only. Unreal Editor is still required to check moving deck collisions, camera behavior, and actual gameplay.
