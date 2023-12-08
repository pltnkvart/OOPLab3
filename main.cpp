#include <raylib.h>
#include <rlgl.h>

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "MyGame");

    // Define the camera to look into our 3d world
    Camera3D camera = {0};
    camera.position = (Vector3) {0.0f, 10.0f, 10.0f};  // Camera position
    camera.target = (Vector3) {0.0f, 0.0f, 0.0f};      // Camera looking at point
    camera.up = (Vector3) {0.0f, 1.0f, 0.0f};          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type


    // Model
    Model model = LoadModel("../resources/models/fighters/fighter.glb");
    Vector3 position = {0.0f, 3.0f, 0.0f};
    BoundingBox bounds = GetMeshBoundingBox(model.meshes[0]);
    bool selected = false;

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
        DrawModelEx(model, position, (Vector3) {1.0f, 0.0f, 0.0f}, 90.0f, (Vector3) {0.005f, 0.005f, 0.005f}, WHITE);
        DrawBoundingBox(bounds, GREEN);
        DrawGrid(10, 1.0f);
        EndMode3D();
        DrawText("Enemy: 100 / 100", 0, 5.0f, 20, BLACK);
        // SMALL MENU
        DrawFPS(10, 10);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel(model);
    UnloadTexture(background);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}