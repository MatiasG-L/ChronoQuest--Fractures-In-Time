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
Player player(200, 400, {200, 450}, "Player", 1, 50, {10,10,10,10,10,10,10}, {10,10,10,10,10,10,10}, {10, 10, 10});
//(int width, int height, Vector2 position, std::string name, float maxHealth, int threatLevel, Stats stats)
Enemy enemy(150, 300, {1100, 100}, "Enemy01", 100, 2, {10,10,10,10,10});

int main(void)
{
   
    
    // Initialization
    //--------------------------------------------------------------------------------------
    //creating variables to set the screen dimentions to
    const int screenWidth = 1600;
    const int screenHeight = 900;
    
    
    
    
    InitWindow(screenWidth, screenHeight, " |Pokemon Purple Version| "); //initilisation of the window 

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
    
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    
    
    while (!WindowShouldClose()){    // Detect window close button or ESC key
    
      if(IsKeyPressed(KEY_UP)){
          newTarget = {player.position.x + player.width/2 + 120, player.position.y + player.height/2 -70};
          zoomTarget = 1.2;
      }else if(IsKeyPressed(KEY_DOWN)){
          zoomTarget = 1.5;
          newTarget = {enemy.position.x + enemy.width/2, enemy.position.y + enemy.height/2};
      }else if(IsKeyPressed(KEY_LEFT)){
          newTarget = {800,450};
          zoomTarget = 1;
      }
      camera.target = {lerp(camera.target.x, newTarget.x, 0.03), lerp(camera.target.y, newTarget.y, 0.03)};
      
      camera.zoom = lerp(camera.zoom, zoomTarget, 0.03);
      
      
      
      
      
      
      
      // Draw, where the scene actually gets rendered and drawn out
        

        BeginDrawing();
            
            
            
            //anything drawn inside of the BeginMode2D() and EndMode2D() are going to be drawn onto the world and wont move with the camera but anything drawn after EndMode2D() is drawn onto the screen and moves with the camera useful for UI
                BeginMode2D(camera);
                
                
                  
                ClearBackground(WHITE);
                
                
                DrawRectangle(player.position.x, player.position.y, player.width, player.height, BLACK);
                DrawRectangle(enemy.position.x, enemy.position.y, enemy.width, enemy.height, RED);
                    
                
                EndMode2D();
                //UI elements past this point
                DrawRectangleRounded({475, 710, 1200, 200}, 4, 4, CLEARBASE(BLACK, 100));
                
                DrawTextureEx(buttonF, {1300,650}, 0, 10, YELLOW);
                DrawTextureEx(buttonF, {1025,650}, 0, 10, GREEN);
                DrawTextureEx(buttonF, {750,650}, 0, 10, BLUE);
                DrawTextureEx(buttonF, {475,650}, 0, 10, WHITE);
           
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
