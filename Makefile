BUILD_DIR = build

.PHONY: clean build test_library test_all

clean:
	rm -rf $(BUILD_DIR) $(LIBRARY_BUILD_DIR)

build:
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

test:
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)
	cd $(BUILD_DIR)
	ctest --output-on-failure
	cd ..

test_library:
	cd library
	make test