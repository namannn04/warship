# Weather and day/night prototype

A shared `AWeatherDirector` now advances a twenty-minute in-game day and smoothly cycles between calm and storm conditions. It updates sun rotation and intensity, wind heading, wind speed factor and wave height for every registered ship. Storm transitions take about 45 seconds instead of snapping instantly.

The engine-independent weather model has C++ tests. This pass affects lighting and ship motion; cloud meshes, rain particles, fog, lightning, ocean shader changes and weather audio remain future work. Unreal runtime testing is required to tune the camera and ship movement under stronger waves.
