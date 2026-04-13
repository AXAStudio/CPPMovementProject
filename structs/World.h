#ifndef WORLD_H
#define WORLD_H

#include "raylib.h"
#include "rlgl.h"
#include "Box.h"
#include <vector>

struct World {
    std::vector<Box> obstacles;
    Texture2D gridTexture;
    Vector3 startPoint = { 0, 5.0f, 52 };
    Vector3 goalPoint = { 0, 4.85f, -52 };

    World() {
        gridTexture = GenerateGridTexture();
        InitializeObstacles();
    }

    ~World() {
        UnloadTexture(gridTexture);
    }

    void AddBox(Vector3 center, Vector3 half, Color color) {
        obstacles.push_back({ center, half, color });
    }

    void InitializeObstacles() {
        obstacles.clear();

        // =========================================================
        // OUTER MAP WALLS - MUCH BIGGER PLAYSPACE
        // =========================================================
        AddBox({   0, 5, -58 }, { 50, 5, 1 }, DARKGRAY); // north wall
        AddBox({   0, 5,  58 }, { 50, 5, 1 }, DARKGRAY); // south wall
        AddBox({ -50, 5,   0 }, { 1,  5, 58 }, DARKGRAY); // west wall
        AddBox({  50, 5,   0 }, { 1,  5, 58 }, DARKGRAY); // east wall

        // =========================================================
        // MID CORE - THICKER AND LONGER SO ROTATING TAKES TIME
        // =========================================================
        AddBox({  0, 2.2f,   0 }, {  6, 2.2f, 16 }, GRAY);        // main mid block
        AddBox({ -10, 1.2f,  0 }, {  2.5f, 1.2f, 4 }, LIGHTGRAY); // left mid pocket cover
        AddBox({  10, 1.2f,  0 }, {  2.5f, 1.2f, 4 }, LIGHTGRAY); // right mid pocket cover

        AddBox({  0, 1.0f, -20 }, { 8, 1.0f, 2.5f }, BEIGE);      // upper mid low wall
        AddBox({  0, 1.0f,  20 }, { 8, 1.0f, 2.5f }, BEIGE);      // lower mid low wall

        // Bigger side separators so side access is slower
        AddBox({ -19, 3.2f,   0 }, { 2, 3.2f, 18 }, BROWN);
        AddBox({  19, 3.2f,   0 }, { 2, 3.2f, 18 }, BROWN);

        // Further outer separators before lane fully opens up
        AddBox({ -31, 3.2f, -10 }, { 2, 3.2f, 10 }, DARKBROWN);
        AddBox({ -31, 3.2f,  10 }, { 2, 3.2f, 10 }, DARKBROWN);
        AddBox({  31, 3.2f, -10 }, { 2, 3.2f, 10 }, DARKGREEN);
        AddBox({  31, 3.2f,  10 }, { 2, 3.2f, 10 }, DARKGREEN);

        // =========================================================
        // LEFT LANE - PUSHED FARTHER OUT
        // =========================================================
        AddBox({ -39, 2.8f, -34 }, { 7, 2.8f, 1.5f }, MAROON);
        AddBox({ -42, 1.2f, -20 }, { 2.5f, 1.2f, 4 }, ORANGE);
        AddBox({ -42, 1.2f,   0 }, { 2.5f, 1.2f, 4 }, ORANGE);
        AddBox({ -42, 1.2f,  20 }, { 2.5f, 1.2f, 4 }, ORANGE);
        AddBox({ -38, 2.8f,  34 }, { 8, 2.8f, 1.5f }, MAROON);

        // left deep lane blockers / mini choke structure
        AddBox({ -34, 3.0f, -42 }, { 2.5f, 3.0f, 6 }, DARKBROWN);
        AddBox({ -34, 3.0f,  42 }, { 2.5f, 3.0f, 6 }, DARKBROWN);

        // left lane inward cover
        AddBox({ -27, 1.2f, -28 }, { 2.5f, 1.2f, 2.5f }, SKYBLUE);
        AddBox({ -27, 1.2f,  28 }, { 2.5f, 1.2f, 2.5f }, SKYBLUE);

        // left site cover cluster
        AddBox({ -43, 1.4f,  40 }, { 3, 1.4f, 3 }, SKYBLUE);
        AddBox({ -36, 1.4f,  46 }, { 3, 1.4f, 3 }, SKYBLUE);
        AddBox({ -43, 1.4f, -40 }, { 3, 1.4f, 3 }, SKYBLUE);
        AddBox({ -36, 1.4f, -46 }, { 3, 1.4f, 3 }, SKYBLUE);

        // =========================================================
        // RIGHT LANE - PUSHED FARTHER OUT
        // =========================================================
        AddBox({  39, 2.8f, -34 }, { 7, 2.8f, 1.5f }, DARKGREEN);
        AddBox({  42, 1.2f, -20 }, { 2.5f, 1.2f, 4 }, LIME);
        AddBox({  42, 1.2f,   0 }, { 2.5f, 1.2f, 4 }, LIME);
        AddBox({  42, 1.2f,  20 }, { 2.5f, 1.2f, 4 }, LIME);
        AddBox({  38, 2.8f,  34 }, { 8, 2.8f, 1.5f }, DARKGREEN);

        // right deep lane blockers / mini choke structure
        AddBox({  34, 3.0f, -42 }, { 2.5f, 3.0f, 6 }, DARKGREEN);
        AddBox({  34, 3.0f,  42 }, { 2.5f, 3.0f, 6 }, DARKGREEN);

        // right lane inward cover
        AddBox({  27, 1.2f, -28 }, { 2.5f, 1.2f, 2.5f }, PURPLE);
        AddBox({  27, 1.2f,  28 }, { 2.5f, 1.2f, 2.5f }, PURPLE);

        // right site cover cluster
        AddBox({  43, 1.4f,  40 }, { 3, 1.4f, 3 }, PURPLE);
        AddBox({  36, 1.4f,  46 }, { 3, 1.4f, 3 }, PURPLE);
        AddBox({  43, 1.4f, -40 }, { 3, 1.4f, 3 }, PURPLE);
        AddBox({  36, 1.4f, -46 }, { 3, 1.4f, 3 }, PURPLE);

        // =========================================================
        // TOP SIDE / NORTH ZONE
        // =========================================================
        AddBox({ -16, 3.0f, -46 }, { 11, 3.0f, 1.3f }, RED);
        AddBox({  16, 3.0f, -46 }, { 11, 3.0f, 1.3f }, RED);

        AddBox({   0, 2.2f, -52 }, { 4, 2.2f, 3 }, GRAY);
        AddBox({ -10, 1.0f, -38 }, { 2.5f, 1.0f, 2.5f }, GOLD);
        AddBox({  10, 1.0f, -38 }, { 2.5f, 1.0f, 2.5f }, GOLD);

        // towers / strong vertical anchors
        AddBox({ -30, 4.5f, -50 }, { 3, 4.5f, 3 }, DARKBLUE);
        AddBox({  30, 4.5f, -50 }, { 3, 4.5f, 3 }, DARKBLUE);

        // =========================================================
        // BOTTOM SIDE / SOUTH ZONE
        // =========================================================
        AddBox({ -16, 3.0f, 46 }, { 11, 3.0f, 1.3f }, BLUE);
        AddBox({  16, 3.0f, 46 }, { 11, 3.0f, 1.3f }, BLUE);

        AddBox({   0, 2.2f, 52 }, { 4, 2.2f, 3 }, GRAY);
        AddBox({ -10, 1.0f, 38 }, { 2.5f, 1.0f, 2.5f }, YELLOW);
        AddBox({  10, 1.0f, 38 }, { 2.5f, 1.0f, 2.5f }, YELLOW);

        AddBox({ -30, 4.5f, 50 }, { 3, 4.5f, 3 }, DARKPURPLE);
        AddBox({  30, 4.5f, 50 }, { 3, 4.5f, 3 }, DARKPURPLE);

        // =========================================================
        // MID-TO-LANE CONNECTORS - LONGER TRANSITIONS
        // =========================================================
        AddBox({ -13, 2.0f, -14 }, { 2.0f, 2.0f, 5 }, BROWN);
        AddBox({ -13, 2.0f,  14 }, { 2.0f, 2.0f, 5 }, BROWN);
        AddBox({  13, 2.0f, -14 }, { 2.0f, 2.0f, 5 }, BROWN);
        AddBox({  13, 2.0f,  14 }, { 2.0f, 2.0f, 5 }, BROWN);

        AddBox({ -24, 2.4f, -24 }, { 1.8f, 2.4f, 6 }, DARKBROWN);
        AddBox({ -24, 2.4f,  24 }, { 1.8f, 2.4f, 6 }, DARKBROWN);
        AddBox({  24, 2.4f, -24 }, { 1.8f, 2.4f, 6 }, DARKGREEN);
        AddBox({  24, 2.4f,  24 }, { 1.8f, 2.4f, 6 }, DARKGREEN);

        // =========================================================
        // EXTRA MID COVER SO MID ISN'T A STRAIGHT HIGHWAY
        // =========================================================
        AddBox({ -5, 0.9f, -30 }, { 2, 0.9f, 2 }, ORANGE);
        AddBox({  5, 0.9f, -30 }, { 2, 0.9f, 2 }, ORANGE);
        AddBox({ -5, 0.9f,  30 }, { 2, 0.9f, 2 }, SKYBLUE);
        AddBox({  5, 0.9f,  30 }, { 2, 0.9f, 2 }, SKYBLUE);

        AddBox({ -18, 1.0f,  0 }, { 2.0f, 1.0f, 3.0f }, LIGHTGRAY);
        AddBox({  18, 1.0f,  0 }, { 2.0f, 1.0f, 3.0f }, LIGHTGRAY);

        // =========================================================
        // OUTER PERIMETER COVER FOR FLANK ROUTES
        // =========================================================
        AddBox({ -47, 1.2f, -10 }, { 2, 1.2f, 3 }, GRAY);
        AddBox({ -47, 1.2f,  10 }, { 2, 1.2f, 3 }, GRAY);
        AddBox({  47, 1.2f, -10 }, { 2, 1.2f, 3 }, GRAY);
        AddBox({  47, 1.2f,  10 }, { 2, 1.2f, 3 }, GRAY);
    }

    void Draw(const Camera3D& camera) {
        // Main floor
        DrawPlane({0, 0, 0}, {320, 320}, (Color){38, 38, 42, 255});

        // lane floor strips - much wider spacing
        DrawCube({   0, -0.05f,  0 }, 18, 0.1f, 116, (Color){50, 50, 58, 255}); // mid
        DrawCube({ -39, -0.05f,  0 }, 14, 0.1f, 116, (Color){44, 44, 52, 255}); // left lane
        DrawCube({  39, -0.05f,  0 }, 14, 0.1f, 116, (Color){44, 44, 52, 255}); // right lane

        // site-like zones
        DrawCube({  0, -0.04f, -46 }, 30, 0.08f, 18, (Color){58, 42, 42, 255});
        DrawCube({  0, -0.04f,  46 }, 30, 0.08f, 18, (Color){42, 42, 58, 255});

        // outer lane accents
        DrawCube({ -39, -0.04f, -42 }, 18, 0.08f, 18, (Color){52, 38, 38, 255});
        DrawCube({ -39, -0.04f,  42 }, 18, 0.08f, 18, (Color){52, 38, 38, 255});
        DrawCube({  39, -0.04f, -42 }, 18, 0.08f, 18, (Color){38, 52, 38, 255});
        DrawCube({  39, -0.04f,  42 }, 18, 0.08f, 18, (Color){38, 52, 38, 255});

        for (const auto& b : obstacles) {
            DrawCubeWithTexture(
                gridTexture,
                b.center,
                b.half.x * 2.0f,
                b.half.y * 2.0f,
                b.half.z * 2.0f,
                b.color
            );

            DrawCubeWires(
                b.center,
                b.half.x * 2.0f,
                b.half.y * 2.0f,
                b.half.z * 2.0f,
                (Color){0, 0, 0, 120}
            );
        }

        DrawSphere(goalPoint, 1.2f, YELLOW);
        DrawSphereWires(goalPoint, 1.2f, 16, 16, GOLD);
    }

    static Texture2D GenerateGridTexture() {
        Image img = GenImageChecked(
            512, 512,
            48, 48,
            (Color){55, 55, 60, 255},
            (Color){75, 75, 82, 255}
        );
        Texture2D tex = LoadTextureFromImage(img);
        UnloadImage(img);
        return tex;
    }

    static void DrawCubeWithTexture(Texture2D tex, Vector3 center, float w, float h, float d, Color tint) {
        rlSetTexture(tex.id);
        DrawCube(center, w, h, d, tint);
        rlSetTexture(0);
    }
};

#endif // WORLD_H