#define _CRT_SECURE_NO_WARNINGS
#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int32_t value;
    int32_t x, y, w, h;
    int32_t offsetX;
    int32_t offsetY;
    int32_t advanceX;
} ChoppedGlyph;

Font LoadChoppedFont(const char* pngPath, const char* datPath) {
    // Load metadata
    FILE* datFile = fopen(datPath, "rb");
    if (!datFile) {
        fprintf(stderr, "Failed to open %s\n", datPath);
        return (Font){0};
    }

    int32_t glyphCount;
    fread(&glyphCount, sizeof(int32_t), 1, datFile);

    ChoppedGlyph* glyphs = malloc(glyphCount * sizeof(ChoppedGlyph));
    fread(glyphs, sizeof(ChoppedGlyph), glyphCount, datFile);
    fclose(datFile);

    // Allocate raylib arrays
    GlyphInfo* glyphInfos = malloc(glyphCount * sizeof(GlyphInfo));
    Rectangle* recs = malloc(glyphCount * sizeof(Rectangle));

    for (int i = 0; i < glyphCount; i++) {
        glyphInfos[i].value = glyphs[i].value;
        glyphInfos[i].offsetX = glyphs[i].offsetX;
        glyphInfos[i].offsetY = glyphs[i].offsetY;
        glyphInfos[i].advanceX = glyphs[i].advanceX;

        recs[i].x = (float)glyphs[i].x;
        recs[i].y = (float)glyphs[i].y;
        recs[i].width = (float)glyphs[i].w;
        recs[i].height = (float)glyphs[i].h;
    }

    // Load image
    Image img = LoadImage(pngPath);
    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);

    // Create font
    Font font = {0};
    font.texture = texture;
    font.glyphs = glyphInfos;
    font.recs = recs;
    font.glyphCount = glyphCount;
    font.baseSize = 16;
    font.glyphPadding = 0;

    free(glyphs);
    return font;
}

void UnloadChoppedFont(Font font) {
    if (font.glyphs) free(font.glyphs);
    if (font.recs) free(font.recs);
    UnloadTexture(font.texture);
}

int main(void) {
    InitWindow(800, 600, "otfchop Example - Font Loading Demo");
    SetTargetFPS(60);

    // Load fonts
    Font fontEn = LoadChoppedFont("assets/fonts/en.png", "assets/fonts/en.dat");
    Font fontEs = LoadChoppedFont("assets/fonts/es.png", "assets/fonts/es.dat");

    int currentLang = 0; // 0 = English, 1 = Spanish
    const char* texts[] = {
        "otfchop Font Loading Demo\n\nPress SPACE to switch languages\n\nEnglish: The quick brown fox jumps over the lazy dog.\nScore: 1250 | Time: 02:34",
        "otfchop Carga de Fuentes\n\nPresiona ESPACIO para cambiar idioma\n\nEspañol: El rápido zorro marrón salta sobre el perro perezoso.\nPuntos: 1250 | Tiempo: 02:34"
    };

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) {
            currentLang = (currentLang + 1) % 2;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw UI
        Font currentFont = (currentLang == 0) ? fontEn : fontEs;
        DrawTextEx(currentFont, texts[currentLang], (Vector2){50, 50}, 20, 2, BLACK);

        // Draw info
        DrawText(TextFormat("Language: %s", currentLang == 0 ? "English" : "Español"), 10, 10, 20, DARKGRAY);
        DrawText(TextFormat("FPS: %i", GetFPS()), 10, 550, 20, DARKGRAY);

        EndDrawing();
    }

    UnloadChoppedFont(fontEn);
    UnloadChoppedFont(fontEs);

    CloseWindow();
    return 0;
}
