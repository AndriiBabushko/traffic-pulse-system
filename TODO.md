# TODO

## Research

Tasks:

- [X] The way to publish the library
- [X] The way to test the project
- [X] The way to document the project
- [X] The way to structure the project
- [ ] The best libraries and tools to develop the library
- [ ] The best libraries and tools to develop the simulation

## Library

### Preparation

Requirements:

- CMake
- Conan
- GoogleTest
- CTest
- Doxygen
- SUMO library

Tasks:

- [X] Setup CTest and GoogleTest
- [ ] Setup SUMO simulation and describe header files, classes, etc
- [ ] Prepare scripts to run, build and debug

### Implementation

Requirements:

- Observer & Singleton patterns
- SOLID, KISS, DRY principles
- SUMO simulation
- Data storing and processing
- Data visualization(console)

Tasks:

- [ ] Run SUMO simulation and collect some dummy data
- [ ] Rewrite basic classes and functions to work with the data 
- [ ] Use Observer | Singleton patterns to notify the subscribers

### Testing

Requirements:

- Unit tests

Tasks:

- [X] Setup testing environment
- [X] Write simple case tests and run them locally 
- [X] Add integration on GitHub to run tests on PR automatically
- [ ] Add more test cases to cover all possible scenarios

### Documentation

Requirements:

- Doxygen
- GitHub Pages

Tasks:

- [ ] Setup Doxygen to generate documentation
- [ ] Generate documentation for classes, functions, etc
- [ ] Update README.md
- [ ] Update CHANGELOG.md
- [ ] Update CONTRIBUTING.md
- [ ] Setup GitHub Pages to show the documentation
- [ ] Setup GitHub repo to see these information in beautiful way

### Library Publishing

Requirements:

- Artifactory Pro/Personal Conan Server/**[Conan Center Index](https://github.com/conan-io/conan-center-index)**
- GitHub Actions

Tasks:

- [ ] Add examples
- [ ] Add tests 
- [ ] Publish
- [ ] Automate the process of publishing


## Traffic Pulse System

### Preparation

Requirements:

- CMake
- QT
- MySQL
- Docker
- Traffic Pulse Library

- [ ] Set up the project structure
- [ ] Setup database to store the traffic data and statistics.
- [ ] Write basic tests to cover the main functionality