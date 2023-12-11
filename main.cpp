#include <raylib.h>
#include <raymath.h>

#define screenWidth 1280
#define screenHeight 720


void drawPlaneInfo() {
    DrawRectangle(10, 10, 300, 190, Fade(GRAY, 0.5f));
    DrawRectangleLines(10, 10, 300, 190, BLACK);

    DrawText("Plane 1 Name", 30, 20, 20, BLACK);
    DrawText("HP: 20/100", 40, 50, 18, BLACK);
    DrawText("Speed: 123 km/h", 40, 80, 18, BLACK);
    DrawText("Coordinates: 3, 4", 40, 110, 18, BLACK);
    DrawText("Detection Radius: 5", 40, 140, 18, BLACK);
    DrawText("Max number of equipment: 4", 40, 170, 18, BLACK);

    DrawRectangle(10, 210, 300, 160, Fade(GRAY, 0.5f));
    DrawRectangleLines(10, 210, 300, 160, BLACK);
    DrawText("Equipment:", 30, 220, 20, BLACK);
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

    // Define the camera to look into our 3d world
    Camera3D camera = initCamera();

    // Plane
    Model plane = LoadModel("../resources/models/fighters/fighter1.glb");
    Vector3 position = {0.0f, 3.0f, 0.0f};
    BoundingBox bounds = GetMeshBoundingBox(plane.meshes[0]);
    bool selected = false;
    float Scale = 0.05f;
    bounds.min = Vector3Scale(bounds.min, Scale);
    bounds.max = Vector3Scale(bounds.max, Scale);

    // Background
    Texture background = LoadTexture("../resources/background/sky2.png");
    float scrollingBack = 0.0f;

    DisableCursor();                       // Limit cursor to relative movement inside the window

    SetTargetFPS(120);
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        scrollingBack -= 0.1f;
        UpdateCamera(&camera, CAMERA_FREE);

        if (IsKeyPressed('Z')) camera.target = (Vector3) {0.0f, 0.0f, 0.0f};

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            if (IsCursorHidden()) EnableCursor();
            else DisableCursor();
        }
        // Select model on mouse click
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (GetRayCollisionBox(GetMouseRay(GetMousePosition(), camera), bounds).hit) selected = !selected;
            else selected = false;
        }

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(background, (Vector2) {scrollingBack, 0}, 0.0f, 2.0f, WHITE);
        BeginMode3D(camera);
        DrawModelEx(plane, position, (Vector3) {1.0f, 0.0f, 0.0f}, 90.0f, (Vector3) {0.05f, 0.05f, 0.05f}, WHITE);
        DrawBoundingBox(bounds, RED);
        DrawGrid(10, 1.0f);
        EndMode3D();
        if (selected) drawPlaneInfo();
        DrawFPS(screenWidth - 30, 10);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel(plane);
    UnloadTexture(background);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}