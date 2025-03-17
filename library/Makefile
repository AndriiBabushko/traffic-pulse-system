VERSION  ?= 1.0.0
USER     ?= root
CHANNEL  ?= stable
REMOTE   ?= myserver
LIBRARY_BUILD_DIR = build

.PHONY: help build package create publish test clean

help:
	@echo "Makefile for building, packaging, and publishing the library"
	@echo "Usage: make [target] [parameters]"
	@echo ""
	@echo "Targets:"
	@echo "  build      - Builds the project using CMake"
	@echo "  package    - Packages (installs) the library using CMake install target"
	@echo "  create     - Creates the Conan package"
	@echo "  publish    - Builds, packages, and publishes the package"
	@echo "  clean      - Removes the build directory"
	@echo ""
	@echo "Parameters (can be overridden):"
	@echo "  VERSION    - Library version (default: $(VERSION))"
	@echo "  USER       - Conan user (default: $(USER))"
	@echo "  CHANNEL    - Conan channel (default: $(CHANNEL))"

build:
	@echo "Building the project, version $(VERSION)..."
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DPROJECT_VERSION=$(VERSION)
	cmake --build build

package: build
	@echo "Packaging (installing) the library..."
	cmake --build build --target install

create: package
	@echo "Creating Conan package for the library version $(VERSION)..."
	$(CONAN) create . --user=$(USER) --channel=$(CHANNEL)

publish: create
	@echo "Uploading Conan package to remote '$(REMOTE)'..."
	conan remote add myserver http://localhost:9300
	conan remote login myserver admin -p admin
	conan upload traffic-pulse-library/$(VERSION)@$(USER)/$(CHANNEL) -r=$(REMOTE)
	@echo "Library version $(VERSION) has been uploaded to '$(REMOTE) as $(USER)/$(CHANNEL)'!"

test:
	rm -rf $(LIBRARY_BUILD_DIR)
	make build
	cd $(LIBRARY_BUILD_DIR) && ctest --output-on-failure
	cd ..

clean:
	@echo "Removing the build directory..."
	rm -rf build
