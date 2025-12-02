/**************************************************************************************************************
*
*   COOL LITTLE GAME IN C++, USING: RAYLIB 5.0
*
**************************************************************************************************************/



     //---------------------------------------------------------------------------//
    //  NOTE:                                                                    //            
   //     when subtracting from an objects position on the y axis; it will      //
  //      appear to be moving up and vise versa meaning that, up is a          // 
 //       lower value or negative, while down is a positive or higher number  // 
//---------------------------------------------------------------------------//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <queue>

#include "raylib.h"
#include "Player.h"
#include "Enemy.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
//(int width, int height, Vector2 position, std::string name, int rank, int expRankUp, Stats stats, Suit suit, SuitStats suitStats)
Player player(200, 400, {200, 450}, "Player", 1, 50, {10,10,10,10,10,10,10}, {10,10,10,10,10,10,10});
//(int width, int height, Vector2 position, std::string name, float maxHealth, int threatLevel, Stats stats)
Enemy enemy(150, 300, {1100, 100}, "Enemy01", 100, 2, {10,10,10,10,10});



int main(void)
{
   
    
    // Initialization
    //--------------------------------------------------------------------------------------
    //creating variables to set the screen dimentions to
    const int screenWidth = 1600;
    const int screenHeight = 900;
    
    
    
    
    InitWindow(screenWidth, screenHeight, " |ChronoQuest: Fractures In Time| "); //initilisation of the window 

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    
    
    
    Texture2D IconA = LoadTexture("Assests/UI/Attack Icon.png");
    Texture2D IconB = LoadTexture("Assests/UI/Block Icon.png");
    Texture2D IconI = LoadTexture("Assests/UI/Items Icon.png");
    Texture2D IconR = LoadTexture("Assests/UI/Running Icon.png");
    Texture2D PlayerSprite = LoadTexture("Assests/Player/pixilart-sprite.png");
    Texture2D EnemySprite = LoadTexture("Assests/Enemy/enemy0.png");
    
    Vector2 newTarget = {800,450};
    float zoomTarget = 1;
    //initializes camera values
    Camera2D camera = { 0 };
    camera.offset = {screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    camera.target = {800,450};
    
    
    typedef struct{
        Vector2 pos01 = {1300, 650};
        Vector2 pos02 = {1300, 650};
        Vector2 pos03 = {1300, 650};
        Vector2 pos04 = {1300, 650};
        
        int rad1 = 200;
        int rad2 = 200;
        int rad3 = 200;
        int rad4 = 200;
        
        float HealthWidth = 0;
        float EnergyWidth = 0;
        float StaminaWidth = 0;
        int UIWheel = 0;
    }UI;
    
    UI ui;
   
    
    
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    
    
    while (!WindowShouldClose()){    // Detect window close button or ESC key
    
      if(IsKeyPressed(KEY_LEFT)){
          newTarget = {player.position.x + player.width/2 + 120, player.position.y + player.height/2 -70};
          zoomTarget = 1.2;
      }else if(IsKeyPressed(KEY_RIGHT)){
          zoomTarget = 1.5;
          newTarget = {enemy.position.x + enemy.width/2, enemy.position.y + enemy.height/2};
      }else if(IsKeyPressed(KEY_UP)){
          newTarget = {800,450};
          zoomTarget = 1;
      }
      camera.target = {lerp(camera.target.x, newTarget.x, 0.03), lerp(camera.target.y, newTarget.y, 0.03)};
      
      camera.zoom = lerp(camera.zoom, zoomTarget, 0.03);
      
      
      if(IsKeyDown(KEY_BACKSPACE)){
         player.health -= 10;
      }
      if(IsKeyDown(KEY_L)){
         player.health += 10;
      }
      
      if(IsKeyDown(KEY_T)){
         player.suit.battery -= 10;
      }
      if(IsKeyDown(KEY_Y)){
         player.suit.battery += 10;
      }
      if(IsKeyDown(KEY_G)){
         player.stamina -= 10;
      }
      if(IsKeyDown(KEY_H)){
         player.stamina += 10;
      }
      
      
      if(IsKeyPressed(KEY_ONE)){
          if(ui.UIWheel == 3){
              ui.UIWheel = 0;
          }else{
              ui.UIWheel = 3;
          }
      }
      if(IsKeyPressed(KEY_TWO)){
          if(ui.UIWheel == 1){
              ui.UIWheel = 0;
          }else{
              ui.UIWheel = 1;
          }
      }
      if(IsKeyPressed(KEY_THREE)){
          if(ui.UIWheel == 4){
              ui.UIWheel = 0;
          }else{
              ui.UIWheel = 4;
          }
      }if(IsKeyPressed(KEY_FOUR)){
          if(ui.UIWheel == 2){
             ui.UIWheel = 0;
          }else{
              ui.UIWheel = 2;
          }
      }
      
      
      
      
      // Draw, where the scene actually gets rendered and drawn out
        

        BeginDrawing();
            
            
            
            //anything drawn inside of the BeginMode2D() and EndMode2D() are going to be drawn onto the world and wont move with the camera but anything drawn after EndMode2D() is drawn onto the screen and moves with the camera useful for UI
                BeginMode2D(camera);
                
                ClearBackground(WHITE);
                
                
                //DrawRectangleLines(player.position.x, player.position.y, player.width, player.height, BLACK);
                DrawTextureEx(PlayerSprite, player.position, 0, 6, WHITE);
                //DrawRectangle(enemy.position.x, enemy.position.y, enemy.width, enemy.height, MAROON);
                DrawTextureEx(EnemySprite, vectorAddition(enemy.position, {-300, -150}), 0, 5, WHITE);
                
                
                 
                
                EndMode2D();
                //UI elements past this point
                //DrawRectangleRounded({-100, 0, 1200, 300}, 20, 20, CLEARBASE(BLACK, 100));
                //DrawRectangleRoundedLines(Rectangle rec, float roundness, int segments, Color color);
                
                DrawRectangle(-100, 0, 1200, 225, CLEARBASE(BLACK, 100));
                
                
                //linear interpolates the 'HealthWidth' variable, starting at its current value interpolatated towards the value of the players health scaled to the max width of the bar (1000) by a factor of 0.05 every frame to create a smooth gliding motion.
                ui.HealthWidth = lerp(ui.HealthWidth, lerp(0, 1000, player.health/player.maxHealth), 0.05);  
                //Draws the outline for the bar to make it look a little better
                DrawRectangleRoundedLines({50, 50, 1000, 25}, 20, 20, 10, BLUE);
                //Draws the gray background for the bar when it gets depleted 
                DrawRectangleRounded({50, 50, 1000, 25}, 20, 20, GRAY);
                
                
                //Draws the actual health bar with a width of the value 'HealthWidth' as declared previously.
                DrawRectangleRounded({50, 50, ui.HealthWidth, 25}, 20, 20, GREEN);
                
                
                ui.EnergyWidth = lerp(ui.EnergyWidth, lerp(0, 1000, player.suit.battery/player.suit.maxBattery), 0.05);   
                DrawRectangleRounded({50, 100, 1000, 25}, 20, 20, GRAY);
                DrawRectangleRounded({50, 100, ui.EnergyWidth, 25}, 20, 20, BLUE);
                DrawRectangleRoundedLines({50, 100, 1000, 25}, 20, 20, 2, BLACK);
                
                ui.StaminaWidth = lerp(ui.StaminaWidth, lerp(0, 1000, player.stamina/player.maxStamina), 0.05);   
                DrawRectangleRounded({50, 150, 1000, 25}, 20, 20, GRAY);
                DrawRectangleRounded({50, 150, ui.StaminaWidth, 25}, 20, 20, YELLOW);
                DrawRectangleRoundedLines({50, 150, 1000, 25}, 20, 20, 2, BLACK);
                
                //DrawCircleSector(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color);  
                
                Vector2 pos = {1300, 650};
                
                
                
                Vector2 pos1 = pos;
                Vector2 pos2 = pos;
                Vector2 pos3 = pos;
                Vector2 pos4 = pos;
                
                DrawRectangleRounded({pos.x - 800, pos.y - 200, 1000, 400}, 100, 10, CLEARBASE(BLACK, 100));
                
                if(CheckCollisionPointTriangle({GetMouseX(), GetMouseY()}, pos1, {pos1.x, pos1.y + 200}, {pos1.x + 200, pos1.y})){
                    ui.UIWheel = 4;
                }else if(CheckCollisionPointTriangle({GetMouseX(), GetMouseY()}, pos2, {pos2.x, pos2.y - 200}, {pos2.x + 200, pos2.y})){
                    ui.UIWheel = 2;
                }else if(CheckCollisionPointTriangle({GetMouseX(), GetMouseY()}, pos3, {pos3.x, pos3.y - 200}, {pos3.x - 200, pos3.y})){
                    ui.UIWheel = 1;
                }else if(CheckCollisionPointTriangle({GetMouseX(), GetMouseY()}, pos4, {pos4.x, pos4.y + 200}, {pos4.x - 200, pos4.y})){
                    ui.UIWheel = 3;
                }else{
                    ui.UIWheel = 0;
                }
        
                switch(ui.UIWheel){
                    case 0:
                        pos1 = pos;
                        pos2 = pos;
                        pos3 = pos;
                        pos4 = pos;
                        ui.rad1 = 200;
                        ui.rad2 = 200;
                        ui.rad3 = 200;
                        ui.rad4 = 200;
                        break;
                    
                    case 1:
                        pos3.x -= 40;
                        pos3.y -= 40;
                        ui.rad3 = 250;
                        ui.rad4 = 200;
                        ui.rad1 = 200;
                        ui.rad2 = 200;
                        break;
                        
                    case 2:
                        pos2.x += 40;
                        pos2.y -= 40;
                        ui.rad2 = 250;
                        ui.rad3 = 200;
                        ui.rad4 = 200;
                        ui.rad1 = 200;
                        break;
                        
                    case 3:
                        pos4.x -= 40;
                        pos4.y += 40;
                        ui.rad4 = 250;
                        ui.rad1 = 200;
                        ui.rad2 = 200;
                        ui.rad3 = 200;
                        break;
                        
                    case 4:
                        pos1.x += 40;
                        pos1.y += 40;
                        ui.rad1 = 250;
                        ui.rad2 = 200;
                        ui.rad3 = 200;
                        ui.rad4 = 200;
                        break;
                        
                    default:
                        break;
                }
                
                ui.pos01 = lerpV(ui.pos01, pos1 , 0.3);
                ui.pos02 = lerpV(ui.pos02, pos2, 0.3);
                ui.pos03 = lerpV(ui.pos03, pos3, 0.3);
                ui.pos04 = lerpV(ui.pos04, pos4, 0.3);
                //DrawCircleSectorLines(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color); // Draw circle sector outline   
                DrawCircleSectorLines(ui.pos01, ui.rad1, 0, 90, 50, YELLOW);
                DrawTextureEx(IconR , vectorAddition(ui.pos01, -70, -80), 0, 5, YELLOW);
                DrawCircleSectorLines(ui.pos02, ui.rad2, 270, 360, 50, BLUE);
                DrawTextureEx(IconB , vectorAddition(ui.pos02, 0, -150), 0, 2.5, BLUE);
                DrawCircleSectorLines(ui.pos03, ui.rad3, 180, 270, 50, RED);
                DrawTextureEx(IconA , vectorAddition(ui.pos03, -180, -160), 0, 3, RED);
                DrawCircleSectorLines(ui.pos04, ui.rad4, 90, 180, 50, GREEN);
                DrawTextureEx(IconI , vectorAddition(ui.pos04, -200, -80), 0, 5, GREEN);
           
        //ends the drawing phase of the program     
        EndDrawing();
        //----------------------------------------------------------------------------------
    } 
     
     

    // De-Initialization
    //--------------------------------------------------------------------------------------
      // Texture unloading
      

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
