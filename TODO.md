# TODO

> **Note on priorities**
> - `( + )` = first priority
> - `( ++ )` = second priority
> - `( +++ )` = third priority

---

## Research

**Tasks:**
- [X] ( + ) Find a way to publish the library
- [X] ( + ) Find a way to test the project
- [X] ( + ) Find a way to document the project
- [X] ( + ) Find a way to structure the project
- [ ] ( ++ ) Identify the best libraries/tools to develop the library
- [ ] ( ++ ) Identify the best libraries/tools to develop the simulation

---

## Library

### Preparation

**Requirements:**
- CMake
- Conan
- GoogleTest
- CTest
- Doxygen
- SUMO library

**Tasks:**
- [X] ( + ) Set up CTest and GoogleTest
- [ ] ( + ) Set up SUMO simulation and describe headers, classes, etc.
- [ ] ( ++ ) Prepare scripts to run, build, and debug

### Implementation

**Requirements:**
- Observer & Singleton patterns
- SOLID, KISS, DRY principles
- SUMO simulation
- Data storing and processing
- Data visualization (console)

**Tasks:**
- [ ] ( + ) Run SUMO simulation and collect some sample data
- [ ] ( + ) Refactor basic classes and functions to handle simulation data
- [ ] ( ++ ) Implement Observer | Singleton to notify subscribers of changes

### Testing

**Requirements:**
- Unit tests

**Tasks:**
- [X] ( + ) Set up the testing environment
- [X] ( + ) Write simple test cases and run them locally
- [X] ( + ) Integrate GitHub actions to run tests on each pull request
- [ ] ( ++ ) Add more test cases to cover all possible scenarios

### Documentation

**Requirements:**
- Doxygen
- GitHub Pages

**Tasks:**
- [ ] ( + ) Set up Doxygen to generate documentation
- [ ] ( + ) Generate documentation for classes, functions, etc.
- [ ] ( ++ ) Update `README.md`
- [ ] ( ++ ) Update `CHANGELOG.md`
- [ ] ( ++ ) Update `CONTRIBUTING.md`
- [ ] ( ++ ) Set up GitHub Pages to display documentation
- [ ] ( ++ ) Make the documentation easily accessible in the GitHub repo

### Library Publishing

**Requirements:**
- Artifactory Pro / Personal Conan Server
- [Conan Center Index](https://github.com/conan-io/conan-center-index)
- GitHub Actions

**Tasks:**
- [ ] ( + ) Add usage examples
- [ ] ( + ) Add tests
- [ ] ( ++ ) Publish the library
- [ ] ( ++ ) Automate the publishing process

---

## Traffic Pulse System

### Preparation

**Requirements:**
- CMake
- Qt
- MySQL
- Docker
- Traffic Pulse Library

**Tasks:**
- [ ] ( + ) Set up the project structure
- [ ] ( + ) Set up a database to store traffic data and statistics
- [ ] ( ++ ) Write basic tests to cover main functionality

### Features & Implementation

**Tasks:**
- [ ] ( + ) **Interactive display of intersections and traffic lights**
    - [ ] Draw a dynamic map with highlighted traffic lights
    - [ ] Show current phases (red/green/yellow) in real time
- [ ] ( + ) **Display statistical data as graphs and tables**
    - [ ] Plot histograms/line charts for traffic intensity
    - [ ] Show detailed tables with sorting capabilities
- [ ] ( + ) **Automatic traffic light phase adjustments based on an algorithm**
    - [ ] Integrate the “Green Wave” logic as a graph model
    - [ ] Configure switching times while considering priority lanes
- [ ] ( + ) **Support priority for emergency vehicles**
    - [ ] Define a protocol for signals (ambulance, fire trucks, etc.)
    - [ ] Trigger “Green Wave” automatically when an emergency signal is detected

- [ ] ( ++ ) **Change traffic light modes without operator intervention**
    - [ ] Dynamically recalculate cycles based on time of day/season
    - [ ] Log all automatic adjustments
- [ ] ( ++ ) **Identify the most congested intersections in real time**
    - [ ] Compare traffic volumes among different intersections
    - [ ] Automatically mark high-problem areas
- [ ] ( ++ ) **Detect traffic jams and anomalies in the flow**
    - [ ] Analyze flow speed to detect bottlenecks
    - [ ] Send alerts about critical congestion levels
- [ ] ( ++ ) **Role-based access control (operators, admins, analysts)**
    - [ ] Develop a system of user roles and access rights
    - [ ] Log and audit user actions

- [ ] ( +++ ) **View the history of changes in the traffic light system**
    - [ ] Store historical data of traffic light configurations
    - [ ] Provide tools to see who changed configurations and when

### Testing

**Requirements:**
- Testing framework (GoogleTest / Catch2 / QTest)
- Docker-based Continuous Integration

**Tasks:**
- [ ] ( + ) Verify “Green Wave” logic correctness
- [ ] ( + ) Test system behavior under maximum load
- [ ] ( ++ ) Cover emergency vehicle priority scenarios

### Documentation

**Requirements:**
- Doxygen (for core C++ logic)
- UI documentation for Qt/QML

**Tasks:**
- [ ] ( + ) Document key classes and algorithms of the Traffic Pulse Library
- [ ] ( ++ ) Add sequence/UML diagrams for main components
- [ ] ( ++ ) Include screenshots or short videos for UI demonstration

### Deployment & Maintenance

**Tasks:**
- [ ] ( + ) Set up Docker containers for the database and the Traffic Pulse service
- [ ] ( ++ ) Test cross-platform compatibility (Linux, macOS)
- [ ] ( ++ ) Configure backups and monitoring for reliable operations  
