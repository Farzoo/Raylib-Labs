#include "raylib.h"
#include <raymath.h>
#include <malloc.h>

typedef struct Mesh3D {
    Vector3 *vertices;
    int *triangles;
} Mesh3D;

typedef struct Cube {
    Mesh3D mesh;
} Cube;


/*typedef struct Mesh3D {
    Vector3 vertices[24];
    int triangles[36];
} Mesh3D;

typedef struct Cube {
    Mesh3D mesh;
} Cube;
*/


#define NUM_VERTICES 8
#define NUM_TRIANGLES 24
Cube *CreateCube() {

    Vector3 vertices[NUM_VERTICES] = {
            {0.5, -0.5, 0.5}, {-0.5, -0.5, 0.5}, {0.5, 0.5, 0.5}, {-0.5, 0.5, 0.5},
            {0.5, 0.5, -0.5}, {-0.5, 0.5, -0.5}, {0.5, -0.5, -0.5}, {-0.5, -0.5, -0.5}
    };

    int edges[NUM_TRIANGLES] = {
            0, 1, 1, 3, 3, 2, 2, 0,   // Front face
            4, 5, 5, 7, 7, 6, 6, 4,   // Back face
            0, 6, 1, 7, 3, 5, 2, 4    // Connecting edges
    };

    Cube *cube = malloc(sizeof(Cube));

    cube->mesh.vertices = malloc(sizeof(Vector3) * NUM_VERTICES);
    cube->mesh.triangles = malloc(sizeof(int) * NUM_TRIANGLES);

    for (int i = 0; i < 8; i++) cube->mesh.vertices[i] = vertices[i];
    for (int i = 0; i < 24; i++) cube->mesh.triangles[i] = edges[i];

    return cube;
}

void DestroyCube(Cube *cube) {
    if (cube == NULL) return;
    if (cube->mesh.vertices != NULL) free(cube->mesh.vertices);
    if (cube->mesh.triangles != NULL) free(cube->mesh.triangles);
    free(cube);
}

void DrawCubeOutline(Cube *cube) {
    for (int t = 0; t < 24; t += 2) {
        Vector3 v1 = cube->mesh.vertices[cube->mesh.triangles[t]];
        Vector3 v2 = cube->mesh.vertices[cube->mesh.triangles[t + 1]];
        DrawLine3D(v1, v2, DARKGRAY);
    }
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Raylib 3D Cube Outline Example");

    Camera camera = { 0 };
    camera.position = (Vector3){ 4.0f, 4.0f, 4.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 1.0f, 0.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Cube *cube = CreateCube();
    float rotationAngle = 1.0f;

    Matrix rotation = MatrixRotateXYZ((Vector3){ DEG2RAD * rotationAngle,0.0f, 0.0f });

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        camera.position = Vector3Transform(camera.position, rotation);
        UpdateCamera(&camera, CAMERA_PERSPECTIVE);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawCubeOutline(cube);

        DrawGrid(10, 1.0f);

        EndMode3D();

        DrawText("3D Cube Outline with Raylib", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    DestroyCube(cube);

    CloseWindow();

    return 0;
}
