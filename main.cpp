#include <raylib.h>
#include <raymath.h>
#include "components/echelon/Echelon.h"

#define screenWidth 1280
#define screenHeight 720

// как сделать в зависимости от типа истребители отображать его поля ??.....

Echelon echelon;

void drawPlaneInfo(const std::shared_ptr<Fighter> &fighter) {
    DrawRectangle(10, 10, 300, 190, Fade(GRAY, 0.5f));
    DrawRectangleLines(10, 10, 300, 190, BLACK);
    DrawText(fighter->getModel().c_str(), 30, 20, 20, BLACK);
    DrawText(TextFormat("HP: %02i/100", fighter->getHP()), 40, 50, 18, BLACK);
    DrawText(TextFormat("Speed: %i km/h", fighter->getSpeed()), 40, 80, 18, BLACK);
    DrawText(TextFormat("Coordinates: %i, %i", fighter->getCoordinates().first, fighter->getCoordinates().second), 40,
             110, 18, BLACK);
    DrawText(TextFormat("Detection Radius: %i", fighter->getDetectionRadius()), 40, 140, 18, BLACK);
    DrawText(TextFormat("Max number of equipment: %i", fighter->getMaxNumEquipment()), 40, 170, 18, BLACK);

    DrawRectangle(10, 210, 300, 160, Fade(GRAY, 0.5f));
    DrawRectangleLines(10, 210, 300, 160, BLACK);
    DrawText("Equipment:", 30, 220, 20, BLACK);
}

void initializeEchelons() {
    Fighter f1("F-16", 100, 100, 800, 1, {3, 4}, 10);
    Fighter f2("F-1", 90, 100, 800, 1, {-2, 1}, 5);
    auto fighter1 = std::make_shared<Fighter>(f1);
    auto fighter2 = std::make_shared<Fighter>(f2);
    echelon.addFighter(fighter1);
    echelon.addFighter(fighter2);
}

void drawEchelons(Model plane, BoundingBox bounds, Camera3D camera, std::shared_ptr<Fighter> &selectedFighter) {
    for (const auto &fighter: echelon.getFighters()) {
        int x = fighter->getCoordinates().first;
        int y = fighter->getCoordinates().second;
        Vector3 position = {static_cast<float>(x), 3.0f, static_cast<float>(y)};
        Matrix transformation = MatrixTranslate(position.x, 3.0f, position.z);
        BoundingBox transformedBounds = bounds;
        transformedBounds.min = Vector3Transform(transformedBounds.min, transformation);
        transformedBounds.max = Vector3Transform(transformedBounds.max, transformation);
        DrawModelEx(plane, position, (Vector3) {1.0f, 0.0f, 0.0f},
                    90.0f, (Vector3) {0.05f, 0.05f, 0.05f}, WHITE);
        DrawBoundingBox(transformedBounds, RED);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            GetRayCollisionBox(GetMouseRay(GetMousePosition(), camera), transformedBounds).hit) {
            selectedFighter = fighter;
        }
    }
}

Camera3D initCamera() {
    Camera3D camera = {0};
    camera.position = (Vector3) {0.0f, 10.0f, 10.0f};  // Camera position
    camera.target = (Vector3) {0.0f, 0.0f, 0.0f};      // Camera looking at point
    camera.up = (Vector3) {0.0f, 1.0f, 0.0f};          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                         // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                      // Camera mode type
    return camera;
}

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "MyGame");
    initializeEchelons();
    Camera3D camera = initCamera();

    // Load Plane Model
    Model plane = LoadModel("../resources/models/fighters/fighter1.glb");
    BoundingBox bounds = GetMeshBoundingBox(plane.meshes[0]);
    std::shared_ptr<Fighter> selectedFighter;
    bounds.min = Vector3Scale(bounds.min, 0.05f);
    bounds.max = Vector3Scale(bounds.max, 0.05f);

    // Load Background
    Texture background = LoadTexture("../resources/background/sky2.png");
    float scrollingBack = 0.0f;

    DisableCursor();
    SetTargetFPS(120);
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        scrollingBack -= 0.1f;
        UpdateCamera(&camera, CAMERA_PERSPECTIVE);

        if (IsKeyPressed('Z')) camera.target = (Vector3) {0.0f, 0.0f, 0.0f};

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            if (IsCursorHidden()) EnableCursor();
            else DisableCursor();
        }

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(background, (Vector2) {scrollingBack, 0}, 0.0f, 2.0f, WHITE);
        BeginMode3D(camera);
        drawEchelons(plane, bounds, camera, selectedFighter);
        DrawGrid(10, 1.0f);
        EndMode3D();
        if (selectedFighter) {
            drawPlaneInfo(selectedFighter);
        }
        DrawFPS(screenWidth - 30, 10);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(background);
    UnloadModel(plane);
    CloseWindow();
    //--------------------------------------------------------------------------------------
    return 0;
}