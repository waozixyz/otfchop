# otfchop

`otfchop` is a small build-time tool that scans UTF-8 locale text files, collects the unique codepoints they use, and generates a chopped bitmap font atlas from `unifont-17.0.04.otf`.

It is intended for use in app build pipelines, not as a runtime dependency.

## What it does

- scans locale `.txt` files
- extracts the glyphs actually used by translated text
- rasterizes those glyphs into a compact atlas
- writes:
  - `assets/fonts/<name>.png`
  - `assets/fonts/<name>.dat`

## Build

```bash
make
```

This builds the `otfchop` binary and generates the default font asset set from the locale files in `locales/`.

## Generate font assets manually

```bash
./otfchop unifont-17.0.04.otf locales/*.txt assets/fonts/locales
```

The command format is:

```bash
./otfchop <font.otf> <text1.txt> [more text files...] <output_prefix>
```

Example output:

- `assets/fonts/locales.png`
- `assets/fonts/locales.dat`

## Repository layout

- `otfchop.c` - generator source
- `locales/` - sample locale text files used for font collection
- `assets/fonts/` - generated outputs
- `UNIFONT-LICENSE.txt` - Unifont license notice

## Notes

- The generator scans text files only.
- It does not parse source code, markup, or binary assets.
- The output is meant to be consumed by raylib-based apps that load the chopped atlas at runtime.

## License

This program is licensed under the MIT License. See [LICENSE](LICENSE).

The bundled Unifont font file and generated font assets are covered by the
separate Unifont notice in [UNIFONT-LICENSE.txt](UNIFONT-LICENSE.txt).
