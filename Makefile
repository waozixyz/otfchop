CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11
STB_SRC = /mnt/storage/src/waozi/vendor/raylib/src/external

# Default target: build tool and generate assets
all: otfchop assets

# Copy stb headers (one-time setup)
stb_headers:
	@cp $(STB_SRC)/stb_truetype.h .
	@cp $(STB_SRC)/stb_image_write.h .
	@echo "STB headers copied"

# Build the tool
otfchop: stb_headers otfchop.c
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
	rm -f otfchop stb_*.h
	rm -rf assets/fonts/*.png assets/fonts/*.dat

.PHONY: all clean assets stb_headers example
