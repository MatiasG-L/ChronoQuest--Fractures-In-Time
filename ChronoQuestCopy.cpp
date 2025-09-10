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

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
Player vro;


int main(void)
{
   
    
    // Initialization
    //--------------------------------------------------------------------------------------
    //creating variables to set the screen dimentions to
    const int screenWidth = 1600;
    const int screenHeight = 900;
    
    
    
    
    InitWindow(screenWidth, screenHeight, " |Pokemon Purple Version| "); //initilisation of the window 

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    
        
    //initializes camera values
    Camera2D camera = { 0 };
    camera.offset = {screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    camera.target = {800,450};
    
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    
    
    while (!WindowShouldClose()){    // Detect window close button or ESC key
    
        camera.target = {vro.position.x, vro.position.y};
      // Draw, where the scene actually gets rendered and drawn out
        if (IsKeyDown(KEY_W)){
        vro.position.y -= 10;
      }
    if (IsKeyDown(KEY_A)){
        vro.position.x -= 10;
      }
    if (IsKeyDown(KEY_S)){
        vro.position.y += 10;
      }
    if (IsKeyDown(KEY_D)){
        vro.position.x += 10;
      }
    if (IsKeyDown(KEY_UP)){
        vro.position.y -= 10;
      }
    if (IsKeyDown(KEY_LEFT)){
        vro.position.x -= 10;
      }
    if (IsKeyDown(KEY_DOWN)){
        vro.position.y += 10;
      }
    if (IsKeyDown(KEY_RIGHT)){
        vro.position.x += 10;
      }
      
        BeginDrawing();
            
            
            
            //anything drawn inside of the BeginMode2D() and EndMode2D() are going to be drawn onto the world and wont move with the camera but anything drawn after EndMode2D() is drawn onto the screen and moves with the camera useful for UI
                BeginMode2D(camera);
                
                  
                ClearBackground(WHITE);
                //draws the player
                DrawRectangle(vro.position.x,vro.position.y,vro.width,vro.height,ORANGE);
                DrawRectangle(100,300,100,10,BLUE);
                DrawRectangle(200,-100,10,100,BLUE);
                DrawRectangle(-200,100,100,100,BLUE);

                
                EndMode2D();
                
                
           
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
