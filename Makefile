CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11

# Default target: build tool and generate assets
all: otfchop assets

# Build the tool
otfchop: otfchop.c stb_truetype.h stb_image_write.h
	$(CC) $(CFLAGS) otfchop.c -lm -o otfchop

# Generate assets for all locales
assets: otfchop
	@mkdir -p assets/fonts
	./otfchop unifont-17.0.04.otf locales/*.txt assets/fonts/locales

# Build example runtime (requires raylib - use nix-shell in example/ directory)
example:
	@echo "Build the example in the Nix environment:"
	@echo "  cd example && nix-shell"
	@echo "  gcc ../example_runtime.c -lraylib -o demo"

clean:
	rm -f otfchop
	rm -rf assets/fonts/*.png assets/fonts/*.dat

.PHONY: all clean assets example
