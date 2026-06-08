{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    gcc
    raylib
    pkg-config
  ];

  shellHook = ''
    echo "otfchop example environment ready"
    echo "raylib: $(pkg-config --modversion raylib)"
    echo ""
    echo "Build and run:"
    echo "  gcc ../example_runtime.c -lraylib -o demo"
    echo "  ./demo"
  '';
}
