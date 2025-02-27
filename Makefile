BUILD_DIR = build
LIBRARY_BUILD_DIR = library/build

.PHONY: clean build test_library test_all

clean:
	rm -rf $(BUILD_DIR) $(LIBRARY_BUILD_DIR)

build:
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

test_all:
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)
	cd $(BUILD_DIR) && ctest --output-on-failure

test_library:
	cmake -S library -B $(LIBRARY_BUILD_DIR)
	cmake --build $(LIBRARY_BUILD_DIR)
	cd $(LIBRARY_BUILD_DIR) && ctest --output-on-failure