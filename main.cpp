#include <raylib.h>
#include <raymath.h>
#include "components/echelon/Echelon.h"
#include "components/weapons/gun/gun.h"
#include <fstream>
//#include <nlohmann/json.hpp>

#define NUM_FRAMES_PER_LINE     5
#define NUM_LINES               5

#define screenWidth 1280
#define screenHeight 720

// GLOBAL VARIABLES
enum GameState {
    MENU,
    PLAYING,
    PLAYER_TURN,
    ENEMY_TURN,
    SHOOTING,
    GAME_OVER,
    EXIT
};

bool isPlayerTurn = true;
float bulletSpeed = 2.0f;

//Texture groundTexture;

Echelon UserEchelon;
Echelon EnemyEchelon;

// BUTTONS
Rectangle startButton = {screenWidth / 2 - 100, 300, 200, 50};
Rectangle exitButton = {screenWidth / 2 - 100, 400, 200, 50};
Rectangle shootButton = {screenWidth / 2 - 100, 600, 200, 50};


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
    Gun gun("gun", 40, 10, 5, 50);
    auto gun1 = std::make_shared<Gun>(gun);
    Fighter f1("F-16", 100, 100, 800, 1, {3, 4}, 10);
    Fighter f2("F-1", 100, 100, 800, 1, {-2, 1}, 5);
    Fighter f3("F-11", 100, 100, 800, 1, {0, -3}, 10);
    Fighter f4("F-23", 100, 100, 800, 1, {5, -1}, 10);
    std::vector<std::shared_ptr<Weapon>> equipment;
    equipment.push_back(gun1);
    auto fighter1 = std::make_shared<Fighter>(f1);
    auto fighter2 = std::make_shared<Fighter>(f2);
    auto fighter3 = std::make_shared<Fighter>(f3);
    auto fighter4 = std::make_shared<Fighter>(f4);
    fighter1->setEquipment(equipment);
    fighter2->setEquipment(equipment);
    fighter3->setEquipment(equipment);
    fighter4->setEquipment(equipment);
    UserEchelon.addFighter(fighter1);
    UserEchelon.addFighter(fighter2);
    EnemyEchelon.addFighter(fighter3);
    EnemyEchelon.addFighter(fighter4);
}

BoundingBox RotateBoundingBox(const BoundingBox &box, float angleDegrees) {
    float angleRadians = DEG2RAD * angleDegrees;
    Matrix rotationMatrix = MatrixRotateX(angleRadians);
    Vector3 rotatedMin = Vector3Transform(box.min, rotationMatrix);
    Vector3 rotatedMax = Vector3Transform(box.max, rotationMatrix);
    BoundingBox rotatedBox;
    rotatedBox.min = Vector3Min(rotatedMin, rotatedMax);
    rotatedBox.max = Vector3Max(rotatedMin, rotatedMax);
    return rotatedBox;
}


void drawEchelon(Model plane, BoundingBox bounds, Camera3D camera, std::shared_ptr<Fighter> &selectedFighter,
                 Echelon echelon, Color color) {
//    DrawPlane((Vector3) {0.0f, 0.0f, 0.0f}, (Vector2) {15.0f, 15.0f}, WHITE);
    for (const auto &fighter: echelon.getFighters()) {
        int x = fighter->getCoordinates().first;
        int y = fighter->getCoordinates().second;
        Vector3 position = {static_cast<float>(x), 3.0f, static_cast<float>(y)};
        Matrix transformation = MatrixTranslate(position.x, 3.0f, position.z);
        BoundingBox transformedBounds = bounds;
        transformedBounds = RotateBoundingBox(transformedBounds, 90.0f);
        transformedBounds.min = Vector3Transform(transformedBounds.min, transformation);
        transformedBounds.max = Vector3Transform(transformedBounds.max, transformation);
        Vector3 shadowPosition = {position.x, 0.1f, position.z};
        DrawModelEx(plane, shadowPosition, (Vector3) {1.0f, 0.0f, 0.0f}, 90.0f, (Vector3) {0.05f, 0.05f, 0.0f},
                    Fade(BLACK, 0.5f));
        DrawModelEx(plane, position, (Vector3) {1.0f, 0.0f, 0.0f},
                    90.0f, (Vector3) {0.05f, 0.05f, 0.05f}, WHITE);
        DrawBoundingBox(transformedBounds, color);
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
    GameState gameState = MENU;

    // Load Plane Model
    Model plane = LoadModel("../resources/models/fighters/fighter1.glb");
    BoundingBox bounds = GetMeshBoundingBox(plane.meshes[0]);
    std::shared_ptr<Fighter> selectedFighter;
    bounds.min = Vector3Scale(bounds.min, 0.05f);
    bounds.max = Vector3Scale(bounds.max, 0.05f);

    // Load Background
    Texture background = LoadTexture("../resources/background/sky2.png");
    float scrollingBack = 0.0f;
//    groundTexture = LoadTexture("../resources/ground_texture.jpg");

    Texture menuBackground = LoadTexture("../resources/background/menu.png");
    SetTargetFPS(120);

    std::vector<Bullet> bullets;
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(background, (Vector2) {scrollingBack, 0}, 0.0f, 2.0f, WHITE);
        switch (gameState) {
            case MENU:
                DrawTextureV(menuBackground, (Vector2) {0.0f, 0.0f}, WHITE);
                DrawText("Squadron Battle", screenWidth / 2 - MeasureText("Squadron Battle", 50) / 2, 140, 50, WHITE);
                DrawRectangleRec(startButton, WHITE);
                DrawText("Start Game", startButton.x + 40, startButton.y + 15, 20, BLACK);
                DrawRectangleRec(exitButton, WHITE);
                DrawText("Exit", exitButton.x + 80, exitButton.y + 15, 20, BLACK);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (CheckCollisionPointRec(GetMousePosition(), startButton)) {
                        gameState = PLAYING;
                    }
                    if (CheckCollisionPointRec(GetMousePosition(), exitButton)) {
                        break;
                    }
                }
                break;

            case PLAYING:
                if (isPlayerTurn) {
                    gameState = PLAYER_TURN;
                } else {
                    gameState = ENEMY_TURN;
                }
                break;

            case PLAYER_TURN:
                scrollingBack -= 0.1f;
                if (IsKeyPressed('Z')) camera.target = (Vector3) {0.0f, 0.0f, 0.0f};
                if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                    if (IsCursorHidden()) EnableCursor();
                    else DisableCursor();
                }
                if (!selectedFighter) {
                    UpdateCamera(&camera, CAMERA_FREE);
                }
                BeginMode3D(camera);
                drawEchelon(plane, bounds, camera, selectedFighter, UserEchelon, LIME);
                drawEchelon(plane, bounds, camera, selectedFighter, EnemyEchelon, RED);
                DrawGrid(10, 2.0f);
                EndMode3D();
                DrawRectangleRec(shootButton, SKYBLUE);
                DrawText("Shoot", shootButton.x + 75, shootButton.y + 15, 20, BLACK);
                if (selectedFighter) {
                    drawPlaneInfo(selectedFighter);
                }
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (CheckCollisionPointRec(GetMousePosition(), shootButton)) {
                        gameState = SHOOTING;
                        UserEchelon.simulateAirRaid(EnemyEchelon, bullets);
                        isPlayerTurn = false;
                    }
                }
                break;

            case ENEMY_TURN:
                scrollingBack -= 0.1f;
                if (IsKeyPressed('Z')) camera.target = (Vector3) {0.0f, 0.0f, 0.0f};
                if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                    if (IsCursorHidden()) EnableCursor();
                    else DisableCursor();
                }
                if (!selectedFighter) {
                    UpdateCamera(&camera, CAMERA_FREE);
                }
                BeginMode3D(camera);
                drawEchelon(plane, bounds, camera, selectedFighter, UserEchelon, LIME);
                drawEchelon(plane, bounds, camera, selectedFighter, EnemyEchelon, RED);
                DrawGrid(10, 2.0f);
                EndMode3D();
                std::cout << "меня атакают" << std::endl;
                EnemyEchelon.simulateAirRaid(UserEchelon, bullets);
                isPlayerTurn = true;
                gameState = SHOOTING;
                break;

            case SHOOTING:
                BeginMode3D(camera);
                drawEchelon(plane, bounds, camera, selectedFighter, UserEchelon, LIME);
                drawEchelon(plane, bounds, camera, selectedFighter, EnemyEchelon, RED);
                DrawGrid(10, 2.0f);
                EndMode3D();
                if (!isPlayerTurn) {
                    DrawText("Your turn", shootButton.x + 75, shootButton.y + 15, 20, BLACK);
                } else {
                    DrawText("Enemy turn", shootButton.x + 75, shootButton.y + 15, 20, BLACK);
                }
                for (auto &bullet: bullets) {
                    std::cout << bullet.success << std::endl;
                    if (bullet.isActive) {
                        Vector3 direction = Vector3Normalize(Vector3Subtract(bullet.target, bullet.position));
                        bullet.position = Vector3Add(bullet.position,
                                                     Vector3Scale(direction, bulletSpeed * GetFrameTime()));
                        if (Vector3Distance(bullet.position, bullet.target) < 0.1f) {
                            bullet.isActive = false;
                        }
                        BeginMode3D(camera);
                        DrawSphere(bullet.position, .1f, RED);
                        EndMode3D();
                    }
                }
                if (std::all_of(bullets.begin(), bullets.end(), [](const Bullet &b) { return !b.isActive; })) {
                    if (!isPlayerTurn) {
                        gameState = ENEMY_TURN;
                    } else {
                        gameState = PLAYER_TURN;
                    }
                }
                break;

//            case GAME_OVER:
//
//                // If restart conditions met, change to MENU state
//                break;
        }

        EndDrawing();
    }

// De-Initialization
//--------------------------------------------------------------------------------------
    UnloadTexture(background);
    UnloadModel(plane);
    UnloadTexture(menuBackground);

//--------------------------------------------------------------------------------------
    return 0;
}