BUILD_DIR   = build
VERSION  ?= 1.0.0

.PHONY: clean build test_library test_root test_all

clean:
	rm -rf $(BUILD_DIR)

build:
	@echo "Building the simulation, version $(VERSION)..."
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DPROJECT_VERSION=$(VERSION)
	cmake --build build

test_all:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. && make
	cd $(BUILD_DIR) && ctest --output-on-failure

test_root:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. && make
	cd $(BUILD_DIR) && ctest -L root --output-on-failure

test_library:
	cd library
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. && make
	cd $(BUILD_DIR) && ctest -L library --output-on-failure
	cd ../..