#include "raylib.h"
#include <raymath.h>
#include "object.h"
#include "components.h"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "Window title"

USING_COMPONENT(TransformComp);
USING_COMPONENT(Model);
USING_COMPONENT(Camera);

typedef struct Controls {
    int forward;
    int backward;
    int left;
    int right;
} Controls;

Controls control = {KEY_W, KEY_S, KEY_A, KEY_D};

void MoveObject(Object *object, float deltaTime) {
    TransformComp *transform = GET_COMPONENT(object, TransformComp);


    if (IsKeyDown(control.forward)) {
        transform->position.y += 1.0f * deltaTime;
    }
    if (IsKeyDown(control.backward)) {
        transform->position.y -= 1.0f * deltaTime;
    }
    if (IsKeyDown(control.left)) {
        transform->position.z -= 1.0f * deltaTime;
    }
    if (IsKeyDown(control.right)) {
        transform->position.z += 1.0f * deltaTime;
    }
}

void DrawObject(Object *object) {
    Model model = *GET_COMPONENT(object, Model);
    TransformComp *transform = GET_COMPONENT(object, TransformComp);
    Camera *camera = GET_COMPONENT(object, Camera);

    model.transform = QuaternionToMatrix(transform->rotation);

    // Draw model with rotation and scale apply
    DrawModelEx(model, transform->position, camera->up, 0.0f, transform->scale, WHITE);
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    Object obj = Create_Object();

    TransformComp *transform = ADD_COMPONENT_INIT(&obj, TransformComp, .position = {7.0f, 0.0f, 0.0f}, .rotation = QuaternionIdentity(), .scale = {1.0f, 1.0f, 1.0f});
    Model existingModel = LoadModel("assets/teapot.obj");
    ADD_COMPONENT_PTR(&obj, Model, &existingModel);

    ADD_COMPONENT_INIT(&obj, Camera,
        .position = (Vector3){ 0.0f, 0.0f, 0.0f },
        .target = transform->position,
        .up = (Vector3){ 0.0f, 1.0f, 0.0f },
        .fovy = 45.0f,
        .projection = CAMERA_PERSPECTIVE
    );


    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        Camera camera = *GET_COMPONENT(&obj, Camera);
        //UpdateCamera(&camera, CAMERA_PERSPECTIVE);
        BeginMode3D(camera);

        MoveObject(&obj, GetFrameTime());
        DrawObject(&obj);

        EndMode3D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}