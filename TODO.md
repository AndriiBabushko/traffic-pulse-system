# TODO

> **Legend**
> - `( + )` = highest priority (immediate)
> - `( ++ )` = medium priority (short‐term)
> - `( +++ )` = lower priority (long‐term)

---

## Research

**Tasks**
- [X] ( + ) Find a way to publish the library
- [X] ( + ) Find a way to test the project
- [X] ( + ) Find a way to document the project
- [X] ( + ) Find a way to structure the project

---

## Library

### Preparation

**Requirements**
- CMake
- Conan
- GoogleTest
- CTest
- Doxygen
- SUMO library

**Tasks**
- [X] ( + ) Set up CTest and GoogleTest
- [X] ( + ) Set up SUMO simulation references (headers, classes, etc.)
- [ ] ( + ) Prepare scripts for:
  - [X] Build
  - [X] Run
  - [ ] ( ++ ) Debug
  - [X] ( ++ ) Test
- [X] ( ++ ) Provide a basic usage example for the library

### Implementation

**Requirements**
- Observer & Singleton patterns
- SOLID, KISS, DRY
- SUMO simulation integration
- Data storage & processing (PulseDataManager)
- Console or minimal UI output

**Tasks**
- [X] ( + ) Implement basic simulation with SUMO; gather sample data
- [ ] ( + ) Refactor core classes (PulseLoader, PulseTrafficAlgo, etc.) for clarity / maintainability
- [ ] ( + ) **Implement PulseStatsCollector** – a new class that collects real‐time stats (vehicle counts, average queue lengths, etc.)
  - [ ] ( + ) Integrate PulseStatsCollector into TrafficSystem’s run loop (or as an Observer)
  - [ ] ( ++ ) Provide a simple query or data structure to display these stats externally
- [ ] ( + ) Display simulation data in the console (minimal text output or logs)
- [ ] ( + ) Use the Observer pattern to notify subscribers of changes (already started, might need final touches)
  - [ ] ( + ) Ensure Observer notifications use typed PulseEvent (with `std::any` where needed)
- [ ] ( + ) Expand or refine **green‐wave logic** in PulseTrafficAlgo
  - [ ] ( ++ ) Possibly add multi‐corridor or advanced offset strategies
  - [ ] ( ++ ) Support different “modes” (normal, night, emergency, etc.)

### Testing

**Requirements**
- Unit tests for all library modules

**Tasks**
- [X] ( + ) Set up the testing environment with GoogleTest
- [X] ( + ) Write initial test cases (PulseLoader, PulseDataManager, TrafficSystem, etc.)
- [X] ( + ) Integrate GitHub Actions for continuous testing on PR
- [ ] ( ++ ) Add more coverage: edge cases in PulseTrafficAlgo, PulseStatsCollector, etc.

### Documentation

**Requirements**
- Doxygen, README, possible GitHub Pages

**Tasks**
- [X] ( + ) Set up Doxygen generation
- [X] ( + ) Generate docs for classes/functions
- [ ] ( ++ ) Update `README.md`, `CHANGELOG.md`, `CONTRIBUTING.md`
- [X] ( ++ ) Use GitHub Pages to host documentation

### Library Publishing

**Requirements**
- Artifactory Pro or personal Conan server (optional)
- GitHub Actions or alternative CI/CD

**Tasks**
- [ ] ( +++ ) Publish the library to a package manager (Conan/Artifactory)
- [ ] ( +++ ) Automate the publishing process

### Future Improvements

**Tasks**
- [ ] ( ++ ) **Strict vs. Lenient** loading modes (throw on missing traffic lights, or auto‐create them with a warning)
- [ ] ( ++ ) Add an **AnomalyDetector** to detect jams or suspicious flow patterns
- [ ] ( +++ ) More traffic light “modes” (rush hour, weekend, night) beyond standard green wave
- [ ] ( +++ ) Role‐based access (operator, admin, analyst)

---

## Traffic Pulse System (Application)

### Preparation

**Requirements**
- CMake
- Qt (for UI)
- MySQL
- Docker
- Traffic Pulse Library

**Tasks**
- [ ] ( + ) Set up project structure
- [ ] ( + ) Configure a database to store traffic data & stats
- [ ] ( + ) Write basic UI or console to test library usage

### Features & Implementation

**Tasks**
- [ ] ( + ) **Interactive display** of intersections & traffic lights
  - [ ] Draw a dynamic map with color-coded lights
  - [ ] Show current phases (red/green/yellow) in real time
- [ ] ( + ) **Display statistics** (graphs & tables) – hooking into PulseStatsCollector data
- [ ] ( + ) **Automatic phase adjustments** (Green Wave) – refine or expand current logic
- [ ] ( + ) **Priority for emergency vehicles**
  - [ ] Detect emergency signals, override normal schedule
- [ ] ( ++ ) **Change traffic light modes automatically**
  - [ ] E.g., night mode, rush hour mode, etc.
- [ ] ( ++ ) **Identify the most congested intersections** in real time
- [ ] ( ++ ) **Detect traffic jams & anomalies**
- [ ] ( ++ ) **Role‐based access** (operator / admin / analyst)

### Testing

**Tasks**
- [ ] ( + ) Test “Green Wave” logic with known scenarios
- [ ] ( + ) Stress test with many roads & intersections
- [ ] ( ++ ) Validate emergency vehicle priority

### Documentation

**Tasks**
- [ ] ( + ) Document the core logic (architectural overview)
- [ ] ( ++ ) Add UML diagrams for intersection flow, jam detection, etc.
- [ ] ( ++ ) Possibly add screenshots or short UI screencast

### Deployment & Maintenance

**Tasks**
- [ ] ( ++ ) Docker for DB + Traffic Pulse service
- [ ] ( ++ ) Cross‐platform testing (Linux, macOS)
- [ ] ( +++ ) Automated SUMO file generation for varied test scenarios

---

## Implementation Order

1. **Refactor & Basic Observers** (Library) - DONE ✅
2. **PulseStatsCollector** (+)
3. **Green‐Wave Enhancements**
4. **Emergency Priority**
5. **UI & Visualization**
6. **Congestion & Anomaly Detection** (++)
7. **Role‐Based Access** (++)
8. **Strict vs. Lenient Loading** (++)
9. **Publish** (+++)  
