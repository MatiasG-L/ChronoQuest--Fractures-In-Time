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
    
    Texture2D buttonF = LoadTexture("Assests/UI/FButton.png");
    
    Vector2 newTarget = {800,450};
    float zoomTarget = 1;
    //initializes camera values
    Camera2D camera = { 0 };
    camera.offset = {screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    camera.target = {800,450};
    
    Vector2 pos01 = {1300, 650};
    Vector2 pos02 = {1300, 650};
    Vector2 pos03 = {1300, 650};
    Vector2 pos04 = {1300, 650};
    float HealthWidth = 0;
    float EnergyWidth = 0;
    int UIWheel = 0;
    
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
      
      
      if(IsKeyPressed(KEY_ONE)){
          if(UIWheel == 3){
              UIWheel = 0;
          }else{
              UIWheel = 3;
          }
      }
      if(IsKeyPressed(KEY_TWO)){
          if(UIWheel == 1){
              UIWheel = 0;
          }else{
              UIWheel = 1;
          }
      }
      if(IsKeyPressed(KEY_THREE)){
          if(UIWheel == 4){
              UIWheel = 0;
          }else{
              UIWheel = 4;
          }
      }if(IsKeyPressed(KEY_FOUR)){
          if(UIWheel == 2){
              UIWheel = 0;
          }else{
              UIWheel = 2;
          }
      }
      
      
      
      
      // Draw, where the scene actually gets rendered and drawn out
        

        BeginDrawing();
            
            
            
            //anything drawn inside of the BeginMode2D() and EndMode2D() are going to be drawn onto the world and wont move with the camera but anything drawn after EndMode2D() is drawn onto the screen and moves with the camera useful for UI
                BeginMode2D(camera);
                
                
                  
                ClearBackground(WHITE);
                
                
                DrawRectangle(player.position.x, player.position.y, player.width, player.height, BLACK);
                DrawRectangle(enemy.position.x, enemy.position.y, enemy.width, enemy.height, MAROON);
                
                
                 
                
                EndMode2D();
                //UI elements past this point
                //DrawRectangleRounded({-100, 0, 1200, 300}, 20, 20, CLEARBASE(BLACK, 100));
                //DrawRectangleRoundedLines(Rectangle rec, float roundness, int segments, Color color);
                
                DrawRectangle(-100, 0, 1200, 300, CLEARBASE(BLACK, 100));
                
                
                //linear interpolates the 'HealthWidth' variable, starting at its current value interpolatated towards the value of the players health scaled to the max width of the bar (1000) by a factor of 0.05 every frame to create a smooth gliding motion.
                HealthWidth = lerp(HealthWidth, lerp(0, 1000, player.health/player.maxHealth), 0.05);  
                //Draws the outline for the bar to make it look a little better
                DrawRectangleRoundedLines({50, 50, 1000, 25}, 20, 20, 10, BLUE);
                //Draws the gray background for the bar when it gets depleted 
                DrawRectangleRounded({50, 50, 1000, 25}, 20, 20, GRAY);
                
                
                //Draws the actual health bar with a width of the value 'HealthWidth' as declared previously.
                DrawRectangleRounded({50, 50, HealthWidth, 25}, 20, 20, GREEN);
                
                
                EnergyWidth = lerp(EnergyWidth, lerp(0, 1000, player.suit.battery/player.suit.maxBattery), 0.05);   
                DrawRectangleRounded({50, 120, 1000, 25}, 20, 20, GRAY);
                DrawRectangleRounded({50, 120, EnergyWidth, 25}, 20, 20, BLUE);
                DrawRectangleRoundedLines({50, 120, 1000, 25}, 20, 20, 2, BLACK);
                
                //DrawCircleSector(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color);  
                
                Vector2 pos = {1300, 650};
                
                
                
                Vector2 pos1 = pos;
                Vector2 pos2 = pos;
                Vector2 pos3 = pos;
                Vector2 pos4 = pos;
                
                
        
        
                switch(UIWheel){
                    case 0:
                        pos1 = pos;
                        pos2 = pos;
                        pos3 = pos;
                        pos4 = pos;
                        break;
                    
                    case 1:
                        pos3.x -= 40;
                        pos3.y -= 40;
                        break;
                        
                    case 2:
                        pos2.x += 40;
                        pos2.y -= 40;
                        break;
                        
                    case 3:
                        pos4.x -= 40;
                        pos4.y += 40;
                        break;
                        
                    case 4:
                        pos1.x += 40;
                        pos1.y += 40;
                        break;
                        
                    default:
                        break;
                }
                
                pos01 = lerpV(pos01, pos1 , 0.3);
                pos02 = lerpV(pos02, pos2, 0.3);
                pos03 = lerpV(pos03, pos3, 0.3);
                pos04 = lerpV(pos04, pos4, 0.3);
                //DrawCircleSectorLines(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color); // Draw circle sector outline   
                DrawCircleSectorLines(pos01, 200, 0, 90, 50, YELLOW);
                DrawCircleSectorLines(pos02, 200, 270, 360, 50, BLUE);
                DrawCircleSectorLines(pos03, 200, 180, 270, 50, RED);
                DrawCircleSectorLines(pos04, 200, 90, 180, 50, GREEN);
           
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
