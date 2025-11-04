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
#include "NPC.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
Player vro(100, 100, {200, 450}, "Vro", 1, 50, {10,10,10,10,10,10,10}, {10,10,10,10,10,10,10});
Npc A(100, 100, {0,0}, "NPC A", "Ultron my goat", '1');
Npc B(100, 100, {500,0}, "NPC A", "Ultron my goat", '1');
Npc C(100, 100, {0,500}, "NPC A", "Ultron my goat", '1');
std::vector<Wall> walls;
std::vector<Npc> npcs; 

template <typename T> void coll(float distance, char axis, std::vector<T> *toCheck);
char plmove;
int main(void)
{
    
    npcs.push_back(A);
    npcs.push_back(B);
    npcs.push_back(C);
    
    Wall one(100, 100, {4500, 100}, BLUE);
    walls.push_back(one);
    Wall two(300, 100, {-300, 250}, BLUE);
    walls.push_back(two);
    Wall three(100, 300, {450, -300}, BLUE);
    walls.push_back(three);
    Wall four(300, 300, {0, -150},true, GREEN);
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
    
        
        camera.target = lerpV(camera.target, {vro.position.x + vro.width / 2, vro.position.y + vro.height / 2}, 0.2);
        
        coll<Wall>(0, 'x', &walls);
        coll<Wall>(0, 'y', &walls);
        
        coll<Npc>(0, 'x', &npcs);
        coll<Npc>(0, 'y', &npcs);
        
         if (IsKeyDown(KEY_W)){
            coll<Wall>(-10, 'y', &walls);
            coll<Npc>(-10, 'y', &npcs);
          }
        else if (IsKeyDown(KEY_A)){
            coll<Wall>(-10, 'x', &walls);
            coll<Npc>(-10, 'x', &npcs);
          }
        else if (IsKeyDown(KEY_S)){
            coll<Wall>(10, 'y', &walls);
            coll<Npc>(10, 'y', &npcs);
          }
        else if (IsKeyDown(KEY_D)){
            coll<Wall>(10, 'x', &walls);
            coll<Npc>(10, 'x', &npcs);
          }
        else if (IsKeyDown(KEY_UP)){
            coll<Wall>(-10, 'y', &walls);
            coll<Npc>(-10, 'y', &npcs);
          }
        else if (IsKeyDown(KEY_LEFT)){
            coll<Wall>(-10, 'x', &walls);
            coll<Npc>(-10, 'x', &npcs);
          }
        else if (IsKeyDown(KEY_DOWN)){
            coll<Wall>(10, 'y', &walls);
            coll<Npc>(10, 'y', &npcs);
          }
        else if (IsKeyDown(KEY_RIGHT)){
            coll<Wall>(10, 'x', &walls);
            coll<Npc>(10, 'x', &npcs);
          }
      
      
     
        // Draw, where the scene actually gets rendered and drawn out
        BeginDrawing();
            
            
            
            //anything drawn inside of the BeginMode2D() and EndMode2D() are going to be drawn onto the world and wont move with the camera but anything drawn after EndMode2D() is drawn onto the screen and moves with the camera useful for UI
                BeginMode2D(camera);
                
                  
                ClearBackground(WHITE);
                //draws the player
                DrawRectangle(vro.position.x,vro.position.y,vro.width,vro.height,ORANGE);
                
                for(int i = 0; i < walls.size(); i++){
                    DrawRectangle(walls[i].position.x,walls[i].position.y,walls[i].width, walls[i].height,walls[i].sqrColor);
                }
                
                for(int i = 0; i < npcs.size(); i++){
                    DrawRectangle(npcs.at(i).position.x,npcs.at(i).position.y,npcs.at(i).width,npcs.at(i).height,RED);
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
template <typename T> void coll(float distance, char axis, std::vector<T> *toCheck){
    //boolean to keep trabk of whether a collision was detected in th function
    bool collision = false;
    //collision on x axis
    if (axis == 'x'){
        //loops through a vector of Wall objects to check for collision
        for(int i = 0; i < toCheck->size(); i++){
            //uses raylibs built in collision detection functino given two Rec objects as paramaters 
            if (CheckCollisionRecs({vro.position.x + distance, vro.position.y, vro.width, vro.height}, {toCheck->at(i).position.x, toCheck->at(i).position.y, toCheck->at(i).width, toCheck->at(i).height})){
                
                
                //determines if the players starting position is on the left of the objected collided with
                if(vro.position.x < toCheck->at(i).position.x + toCheck->at(i).width / 2){
                    if(toCheck->at(i).moveable){
                    
                    
                    //if the wall is movable then the player pushes it along to the left
                        toCheck->at(i).position.x += (vro.position.x + vro.width) - toCheck->at(i).position.x + 10;
                    }else{
                    //sets the players position to the edge of the object hit (left)
                        vro.position.x = toCheck->at(i).position.x - vro.width;
                        collision = true;
                    }
                    //sets the players position to the edge of the object hit (left)
                    
                    
                    
                }else{
                    if(toCheck->at(i).moveable){
                        //if the wall is movable then the player pushes it along to the right
                        toCheck->at(i).position.x -= (toCheck->at(i).position.x + toCheck->at(i).width) - vro.position.x + 10;
                        
                    }else{
                        //sets the players position to the edge of the object hit (right) 
                        vro.position.x = toCheck->at(i).position.x + toCheck->at(i).width;
                        collision = true;
                    }
                    //sets the players position to the edge of the object hit () right
                    
                    
                }
            }
        }
     //collision on y axis
    }else if (axis == 'y'){
        //loops through a vector of Wall objects to check for collision
        for(int i = 0; i < toCheck->size(); i++){
            //uses raylibs built in collision detection functino given two Rec objects as paramaters 
            if (CheckCollisionRecs({vro.position.x, vro.position.y + distance, vro.width, vro.height}, {toCheck->at(i).position.x, toCheck->at(i).position.y,toCheck->at(i).width, toCheck->at(i).height})){
                //determines if the players starting position is above of the objected collided with
                if (vro.position.y < toCheck->at(i).position.y + toCheck->at(i).height / 2){
                    //checks if the wall is moveable and pushes it
                    if (toCheck->at(i).moveable){
                        toCheck->at(i).position.y += (vro.position.y + vro.height) - toCheck->at(i).position.y + 10;
                        if (CheckCollisionRecs({vro.position.x + distance, vro.position.y, vro.width, vro.height}, {toCheck->at(i).position.x, toCheck->at(i).position.y,toCheck->at(i).width,toCheck->at(i).height})){
                        //sets the players position to the edge of the object hit (above)
                        vro.position.y = toCheck->at(i).position.y - vro.height;
                        collision = true;
                        }
                    }else{
                        vro.position.y = toCheck->at(i).position.y - vro.height;
                        collision = true;
                    }
                    //sets the players position to the edge of the object hit (above)
                    

                }else{
                    if (toCheck->at(i).moveable){
                        toCheck->at(i).position.y -= (toCheck->at(i).position.y + toCheck->at(i).height) - vro.position.y + 10;
                        
                    }else{
                        vro.position.y = toCheck->at(i).position.y + toCheck->at(i).height;
                        collision = true;
                    }
                    //sets the players position to the edge of the object hit (below)
                }
            }   
        }
    
    
    }
    
    // code where wall collision is preformed agianst other walls (pushable walls)
    for (int i = 0; i < toCheck->size(); i++){
        for (int j = 0; j < toCheck->size(); j++){
            //only checks collision if the wall at i is a movable wall and, its not the same as wall at j and, if wall at i is closer to the player than wall at j
            if (toCheck->at(i).moveable && j != i && abs(Distance(toCheck->at(i).position, vro.position)) < abs(Distance(toCheck->at(i).position, vro.position))){
                //splits collision between the x and y axis respectivly 
               if (axis == 'x'){
                   //checks for a collision between wall at i and wall at j using raylibs built in CheckCollisionRecs() function
                   if (CheckCollisionRecs({toCheck->at(i).position.x, toCheck->at(i).position.y, toCheck->at(i).width, toCheck->at(i).height},{toCheck->at(i).position.x, toCheck->at(i).position.y, toCheck->at(i).width, toCheck->at(i).height})){
                       //splits the way collision is handled depending if the wall is on the left or right of its collision respectivly
                       if (toCheck->at(i).position.x < toCheck->at(i).position.x + toCheck->at(i).width / 2){
                           toCheck->at(i).position.x = toCheck->at(i).position.x - toCheck->at(i).width;
                           if (CheckCollisionRecs({vro.position.x, vro.position.y, vro.width, vro.height}, {toCheck->at(i).position.x, toCheck->at(i).position.y,toCheck->at(i).width,toCheck->at(i).height})){
                           vro.position.x = toCheck->at(i).position.x - vro.width;
                            vro.position.x = toCheck->at(i).position.x - vro.width;
                           }
                       //splits the way collision is handled depending if the wall is on the left or right of its collision respectivly
                       }else{
                           toCheck->at(i).position.x = toCheck->at(i).position.x + toCheck->at(i).width;
                           if (CheckCollisionRecs({vro.position.x, vro.position.y, vro.width, vro.height}, {toCheck->at(i).position.x, toCheck->at(i).position.y,toCheck->at(i).width,toCheck->at(i).height})){
                           vro.position.x = toCheck->at(i).position.x + toCheck->at(i).width;
                            vro.position.x = toCheck->at(i).position.x + toCheck->at(i).width;
                           }
                       }
                   }
                //splits collision between the x and y axis respectivly 
               }else if (axis == 'y'){
                   //checks for a collision between wall at i and wall at j using raylibs built in CheckCollisionRecs() function
                   if (CheckCollisionRecs({toCheck->at(i).position.x, toCheck->at(i).position.y, toCheck->at(i).width, toCheck->at(i).height},{toCheck->at(i).position.x, toCheck->at(i).position.y, toCheck->at(i).width, toCheck->at(i).height})){
                       //splits the way collision is handled depending if the wall is above or below of its collision respectivly
                       if (toCheck->at(i).position.y < toCheck->at(i).position.y + (float)toCheck->at(i).height / 2){
                           toCheck->at(i).position.y = toCheck->at(i).position.y - toCheck->at(i).height;
                           if (CheckCollisionRecs({vro.position.x, vro.position.y, vro.width, vro.height}, {toCheck->at(i).position.x, toCheck->at(i).position.y,toCheck->at(i).width,toCheck->at(i).height})){
                           vro.position.y = toCheck->at(i).position.y - vro.height;
                           }
                       //splits the way collision is handled depending if the wall is above or below of its collision respectivly
                       }else{
                           toCheck->at(i).position.y = toCheck->at(i).position.y + toCheck->at(i).height;
                           if (CheckCollisionRecs({vro.position.x, vro.position.y, vro.width, vro.height}, {toCheck->at(i).position.x, toCheck->at(i).position.y,toCheck->at(i).width,toCheck->at(i).height})){
                           vro.position.y = toCheck->at(i).position.y + toCheck->at(i).height;
                           }
                       }
                   }
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