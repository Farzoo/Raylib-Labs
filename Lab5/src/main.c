#include "raylib.h"
#include <raymath.h>
#include "object.h"
#include "components.h"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "Title"

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

    transform->rotation = QuaternionMultiply(transform->rotation, QuaternionFromEuler(0.0f, DEG2RAD * 30.0f * deltaTime, 0.0f));

}

void Draw3DObject(Object* object, Camera camera, Shader shader) {
    TransformComp *transform = GET_COMPONENT(object, TransformComp);
    Model *model = GET_COMPONENT(object, Model);

    model->transform = QuaternionToMatrix(transform->rotation);

    SetShaderValueMatrix(shader, GetShaderLocation(shader, "matModel"), model->transform);
    SetShaderValueMatrix(shader, GetShaderLocation(shader, "matView"), GetCameraMatrix(camera));
    SetShaderValueMatrix(shader, GetShaderLocation(shader, "matProjection"), GetCameraMatrix(camera));
    Vector3 pos = Vector3Add(camera.position, (Vector3){0, 0.0f, -2});

SetShaderValue(shader, GetShaderLocation(shader, "viewPos"), &pos, SHADER_UNIFORM_VEC3);

Vector3 lightDirection = Vector3Negate(Vector3Subtract(transform->position, pos));
SetShaderValue(shader, GetShaderLocation(shader, "light.direction"), &lightDirection, SHADER_UNIFORM_VEC3);

SetShaderValue(shader, GetShaderLocation(shader, "light.ambient"), &(Vector3){0.3f, 0.3f, 0.3f}, SHADER_UNIFORM_VEC3);
SetShaderValue(shader, GetShaderLocation(shader, "light.diffuse"), &(Vector3){0.7f, 0.7f, 0.7f}, SHADER_UNIFORM_VEC3);
SetShaderValue(shader, GetShaderLocation(shader, "light.specular"), &(Vector3){1.0f, 1.0f, 1.0f}, SHADER_UNIFORM_VEC3);

Vector4 color = ColorNormalize(model->materials[0].maps[MATERIAL_MAP_DIFFUSE].color);
SetShaderValue(shader, GetShaderLocation(shader, "objectColor"), &color, SHADER_UNIFORM_VEC4);

    model->materials[0].shader = shader;

    DrawModelEx(*model, transform->position, (Vector3){0, 1, 0}, 0.0f, transform->scale, WHITE);
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 5.0f, 2.0f, 0.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Object obj = Create_Object();
    ADD_COMPONENT_INIT(&obj, TransformComp, .position = {0, 0, 0}, .rotation = QuaternionIdentity(), .scale = {1.0f, 1.0f, 1.0f});
    Model objModel;
    objModel = LoadModelFromMesh(GenMeshCube(1, 1, 1));
    objModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = YELLOW;
    ADD_COMPONENT_PTR(&obj, Model, &objModel);

    Shader shader = LoadShader("assets/lighting.vs", "assets/lighting.fs");

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        MoveObject(&obj, deltaTime);


        BeginDrawing();
        ClearBackground(WHITE);

        BeginMode3D(camera);

        BeginShaderMode(shader);

        Draw3DObject(&obj, camera, shader);

        EndShaderMode();

        EndMode3D();

        EndDrawing();
    }

    UnloadShader(shader);
    CloseWindow();
    return 0;
}