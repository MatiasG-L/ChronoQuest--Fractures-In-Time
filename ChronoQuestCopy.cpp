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
#include "Wall.h"
#include "raylib.h"
#include "Player.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
Player vro;

std::vector<Wall> walls;

void coll(float distance, char axis);

int main(void)
{
    Wall one(100, 100, {450, 100});
    walls.push_back(one);
    Wall two(100, 100, {-300, -200});
    walls.push_back(two);
    Wall three(100, 100, {250, -300});
    walls.push_back(three);
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
        coll(-10, 'x');
      }
    if (IsKeyDown(KEY_S)){
        vro.position.y += 10;
      }
    if (IsKeyDown(KEY_D)){
        coll(10, 'x');
      }
    if (IsKeyDown(KEY_UP)){
        vro.position.y -= 10;
      }
    if (IsKeyDown(KEY_LEFT)){
        coll(-10, 'x');
      }
    if (IsKeyDown(KEY_DOWN)){
        vro.position.y += 10;
      }
    if (IsKeyDown(KEY_RIGHT)){
        coll(10, 'x');
      }
      
        BeginDrawing();
            
            
            
            //anything drawn inside of the BeginMode2D() and EndMode2D() are going to be drawn onto the world and wont move with the camera but anything drawn after EndMode2D() is drawn onto the screen and moves with the camera useful for UI
                BeginMode2D(camera);
                
                  
                ClearBackground(WHITE);
                //draws the player
                DrawRectangle(vro.position.x,vro.position.y,vro.width,vro.height,ORANGE);
                for(int i = 0; i < walls.size(); i++){
                    DrawRectangle(walls[i].width, walls[i].height,walls[i].position.x,walls[i].position.y,BLUE);
                }
                

                
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
void coll(float distance, char axis){
    if (axis == 'x'){
        for(int i = 0; i < walls.size(); i++){
            if (CheckCollisionRecs({vro.position.x + distance, vro.position.y, vro.width, vro.height}, {walls[i].position.x, walls[i].position.y,walls[i].width,walls[i].height})){
                if(vro.position.x < walls[i].position.x){
                    vro.position.x = walls[i].position.x + vro.width;
                    return;
                }else{
                    vro.position.x = walls[i].position.x + walls[i].width;
                    return;
                }
            }else{
                vro.position.x += distance;
                return;
            }
        }
    }else if (axis == 'y'){
        
    }
}