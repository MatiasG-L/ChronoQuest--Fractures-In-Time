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
Player vro(100, 100, {200, 450}, "Vro", 1, 50, {10,10,10,10,10,10,10}, {10,10,10,10,10,10,10}, {10, 10, 10});

std::vector<Wall> walls;

void coll(float distance, char axis);
char plmove;
int main(void)
{
    Wall one(100, 100, {200, 100}, BLUE);
    walls.push_back(one);
    Wall two(300, 100, {-300, 250}, BLUE);
    walls.push_back(two);
    Wall three(100, 300, {450, -300}, BLUE);
    walls.push_back(three);
    Wall four(600, 100, {0, -150},true, GREEN);
    walls.push_back(four);
    Wall five(100, 100, {200, 200}, true, GREEN);
    walls.push_back(five);
    Wall six(100, 100, {300, 0}, true, GREEN);
    walls.push_back(six);
    Wall sv(100,100, {0,300}, true, GREEN);
    walls.push_back(sv);
    
    // Initialization
    //--------------------------------------------------------------------------------------
    //creating variables to set the screen dimentions to
    const int screenWidth = 1600;
    const int screenHeight = 900;
    
    
    
    
    InitWindow(screenWidth, screenHeight, " |ChronoQuest: Fractures In Time| "); //initilisation of the window 

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
    
        camera.target = {vro.position.x + vro.width / 2, vro.position.y + vro.height / 2};
      // Draw, where the scene actually gets rendered and drawn out
        if (IsKeyDown(KEY_W)){
            coll(-10, 'y');
            plmove = 'y';
          }
        if (IsKeyDown(KEY_A)){
            coll(-10, 'x');
            plmove = 'x';
          }
        if (IsKeyDown(KEY_S)){
            coll(10, 'y');
            plmove = 'y';
          }
        if (IsKeyDown(KEY_D)){
            coll(10, 'x');
            plmove = 'x';
          }
        if (IsKeyDown(KEY_UP)){
            coll(-10, 'y');
            plmove = 'y';
          }
        if (IsKeyDown(KEY_LEFT)){
            coll(-10, 'x');
            plmove = 'x';
          }
        if (IsKeyDown(KEY_DOWN)){
            coll(10, 'y');
            plmove = 'y';
          }
        if (IsKeyDown(KEY_RIGHT)){
            coll(10, 'x');
            plmove = 'x';
          }
      
      
    for (int i = 0; i < walls.size(); i++){
        for (int j = 0; j < walls.size(); j++){
            if (walls[i].moveable && j != i && abs(distance(walls[i].position, vro.position)) < abs(distance(walls[j].position, vro.position))){
               if (plmove == 'x'){
                   if (CheckCollisionRecs({walls[i].position.x, walls[i].position.y, walls[i].width, walls[i].height},{walls[j].position.x, walls[j].position.y, walls[j].width, walls[j].height})){
                       if (walls[i].position.x < walls[j].position.x + walls[j].width / 2){
                           walls[i].position.x = walls[j].position.x - walls[i].width;
                           if (CheckCollisionRecs({vro.position.x, vro.position.y, vro.width, vro.height}, {walls[i].position.x, walls[i].position.y,walls[i].width,walls[i].height})){
                           vro.position.x = walls[i].position.x - vro.width;
                           }
                       }else{
                           walls[i].position.x = walls[j].position.x + walls[j].width;
                           if (CheckCollisionRecs({vro.position.x, vro.position.y, vro.width, vro.height}, {walls[i].position.x, walls[i].position.y,walls[i].width,walls[i].height})){
                           vro.position.x = walls[i].position.x + walls[i].width;
                           }
                       }
                   }
               }else if (plmove == 'y'){
                   if (CheckCollisionRecs({walls[i].position.x, walls[i].position.y, walls[i].width, walls[i].height},{walls[j].position.x, walls[j].position.y, walls[j].width, walls[j].height})){
                       if (walls[i].position.y < walls[j].position.y + (float)walls[j].height / 2){
                           walls[i].position.y = walls[j].position.y - walls[i].height;
                           if (CheckCollisionRecs({vro.position.x, vro.position.y, vro.width, vro.height}, {walls[i].position.x, walls[i].position.y,walls[i].width,walls[i].height})){
                           vro.position.y = walls[i].position.y - vro.height;
                           }
                       }else{
                           walls[i].position.y = walls[j].position.y + walls[j].height;
                           if (CheckCollisionRecs({vro.position.x, vro.position.y, vro.width, vro.height}, {walls[i].position.x, walls[i].position.y,walls[i].width,walls[i].height})){
                           vro.position.y = walls[i].position.y + walls[i].height;
                           }
                       }
                   }
               }
            }
        }
    }
      
        BeginDrawing();
            
            
            
            //anything drawn inside of the BeginMode2D() and EndMode2D() are going to be drawn onto the world and wont move with the camera but anything drawn after EndMode2D() is drawn onto the screen and moves with the camera useful for UI
                BeginMode2D(camera);
                
                  
                ClearBackground(WHITE);
                //draws the player
                DrawRectangle(vro.position.x,vro.position.y,vro.width,vro.height,ORANGE);
                for(int i = 0; i < walls.size(); i++){
                    DrawRectangle(walls[i].position.x,walls[i].position.y,walls[i].width, walls[i].height,walls[i].squr);
                }
                

                
                EndMode2D();
                //UI elements past this point
                
           
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
//function for collision handleling that takes paramaters for the distance desired to move and the axis on which to move
void coll(float distance, char axis){
    //boolean to keep trabk of whether a collision was detected in th function
    bool collision = false;
    //collision on x axis
    if (axis == 'x'){
        //loops through a vector of Wall objects to check for collision
        for(int i = 0; i < walls.size(); i++){
            //uses raylibs built in collision detection functino given two Rec objects as paramaters 
            if (CheckCollisionRecs({vro.position.x + distance, vro.position.y, vro.width, vro.height}, {walls[i].position.x, walls[i].position.y,walls[i].width,walls[i].height})){
                
                
                //determines if the players starting position is on the left of the objected collided with
                if(vro.position.x < walls[i].position.x + walls[i].width / 2){
                    if(walls[i].moveable){
                    
                    
                    walls[i].position.x += (vro.position.x + vro.width) - walls[i].position.x + 10;
                }else{
                    vro.position.x = walls[i].position.x - vro.width;
                    collision = true;
                }
                    //sets the players position to the edge of the object hit (left)
                    
                    
                }else{
                    if(walls[i].moveable){
                        walls[i].position.x -= (walls[i].position.x + walls[i].width) - vro.position.x + 10;
                        
                    }else{
                        vro.position.x = walls[i].position.x + walls[i].width;
                        collision = true;
                    }
                    //sets the players position to the edge of the object hit () right
                    
                }
            }
        }
     //collision on y axis
    }else if (axis == 'y'){
        //loops through a vector of Wall objects to check for collision
        for(int i = 0; i < walls.size(); i++){
            //uses raylibs built in collision detection functino given two Rec objects as paramaters 
            if (CheckCollisionRecs({vro.position.x, vro.position.y + distance, vro.width, vro.height}, {walls[i].position.x, walls[i].position.y,walls[i].width, walls[i].height})){
                //determines if the players starting position is above of the objected collided with
                if (vro.position.y < walls[i].position.y + walls[i].height / 2){
                    //checks if the wall is moveable and pushes it
                    if (walls[i].moveable){
                        walls[i].position.y += (vro.position.y + vro.height) - walls[i].position.y + 10;
                        if (CheckCollisionRecs({vro.position.x + distance, vro.position.y, vro.width, vro.height}, {walls[i].position.x, walls[i].position.y,walls[i].width,walls[i].height})){
                        vro.position.y = walls[i].position.y - vro.height;
                        collision = true;
                        }
                    }else{
                        vro.position.y = walls[i].position.y - vro.height;
                        collision = true;
                    }
                    //sets the players position to the edge of the object hit (above)

                }else{
                    if (walls[i].moveable){
                        walls[i].position.y -= (walls[i].position.y + walls[i].height) - vro.position.y + 10;
                        
                    }else{
                        vro.position.y = walls[i].position.y + walls[i].height;
                        collision = true;
                    }
                    //sets the players position to the edge of the object hit (below)
                }
            }   
        }
    
    
    }
    //if no collisin was detected then the player is free to move the desired distance
    if (!collision){
        if (axis == 'x'){
        vro.position.x += distance;
        }else if (axis == 'y'){
            vro.position.y += distance;
        }
    }
}