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

#define PLAYERSCALE 15

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
//Player(int width, int height, Vector2 position, std::string name, int rank, int expRankUp, Stats stats, Suit suit)
Player player(200, 400, {200, 400}, "Player", 3, 50, {100,100,10,10,10,10,10}, {10,10,10,10,100,100});
//Enemy(int width, int height, Vector2 position, std::string name, float maxHealth, int level, float maxStamina, float maxEnergy, Stats stats)
Enemy enemy(150, 300, {1100, 100}, "Enemy01", 100, 5, 100, 100,{5,5,5,5,5});



int main(void)
{
   
    
    // Initialization
    //--------------------------------------------------------------------------------------
    //creating variables to set the screen dimentions to
    const int screenWidth = 1600;
    const int screenHeight = 900;
    
    
    
    
    InitWindow(screenWidth, screenHeight, " |ChronoQuest: Fractures In Time| "); //initilisation of the window 

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    
    Texture2D PlayerIdleC = LoadTexture("Assests/Player/PlayerIdleCombat.png");
    Texture2D PlayerAttackP = LoadTexture("Assests/Player/PlayerAttackPhysical.png");
    Texture2D PlayerAttackS = LoadTexture("Assests/Player/PlayerAttackSpecial.png");
    
    Texture2D Background = LoadTexture("Assests/UI/BackgroundBattle.png");
    Texture2D BarFrame = LoadTexture("Assests/UI/BarFrame.png");
    Texture2D IconA = LoadTexture("Assests/UI/Attack Icon.png");
    Texture2D IconAS = LoadTexture("Assests/UI/AttackSIcon.png");
    Texture2D IconAP = LoadTexture("Assests/UI/AttackPIcon.png");
    Texture2D IconB = LoadTexture("Assests/UI/Block Icon.png");
    Texture2D BlockP = LoadTexture("Assests/UI/BlockP.png");
    Texture2D BlockS = LoadTexture("Assests/UI/BlockS.png");
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
    camera.zoom = 0.2f;
    camera.target = {800,450};
    
     float spinA = 90;
    bool turn = true;
    
    bool attackANM = false;
    bool enemyView = false;
    float timerATK = 0;
    float timerflick = 0;
    int flickcount = 0;
    int flicktotal = 5;
    int flick = 0;
    
    float timerflickP = 0;
    int flickcountP = 0;
    int flicktotalP = 5;
    int flickP = 0;
    
    float enemyWaitTimer = 0;
    float enemyAttackTimer = 0;
    
    
    typedef struct{
        Vector2 pos01 = {1300, 650};
        Vector2 pos02 = {1300, 650};
        Vector2 pos03 = {1300, 650};
        Vector2 pos04 = {1300, 650};
        
        Vector2 posS1 = {1300, 650};
        Vector2 posS2 = {1300, 650};
        
        int rad1 = 200;
        int rad2 = 200;
        int rad3 = 200;
        int rad4 = 200;
        
        float HealthWidth = 0;
        float HealthWidthE = 0;
        float EnergyWidth = 0;
        float StaminaWidth = 0;
        int UIWheel = 0;
        Vector2 BarPos = {0, 0};
        Vector2 pos = {1300, 650};
        int menu = 0;
        float UIBackW = 400;
    }UI;
    
    UI ui;
    
    Background.width *= 15;
    Background.height *= 15;
    
    PlayerIdleC.width *= PLAYERSCALE;
    PlayerIdleC.height *= PLAYERSCALE;
    PlayerAttackP.width *= PLAYERSCALE;
    PlayerAttackP.height *= PLAYERSCALE;
    PlayerAttackS.width *= PLAYERSCALE;
    PlayerAttackS.height *= PLAYERSCALE;
    
    player.idle = {3, 4, PlayerIdleC.width, PlayerIdleC.height, "Idle", true, PlayerIdleC};
    player.AttackP = {10, 23, PlayerAttackP.width, PlayerAttackP.height, "AttackPhysical", false, PlayerAttackP};
    player.AttackS = {10, 19, PlayerAttackS.width, PlayerAttackS.height, "AttackSpecial", false, PlayerAttackS};
    
    player.changeAnimation("Idle");
    
    std::cout << "\n" <<player.currentAnimation.width << ", " << player.currentAnimation.height;
   
    Vector2 BarPos = {0, 0};
    Vector2 pos = {1300, 650};
    Vector2 PlayerTarget = {200, 400};
    Vector2 EnemyTarget = {1100, 100};
    int attackType = 0;
    
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    
    
    while (!WindowShouldClose()){    // Detect window close button or ESC key
    
    bool clicked = false;
    
    player.animation();
    
      if(IsKeyPressed(KEY_LEFT)){
          newTarget = {player.position.x + player.width/2 + 120, player.position.y + player.height/2 -70};
          zoomTarget = 1.2;
          ui.BarPos = {0, 0};
          ui.pos = {1300, 650};
      }else if(IsKeyPressed(KEY_RIGHT)){
          zoomTarget = 1.5;
          ui.BarPos = {-100, -300};
          ui.pos = {1300, 1100};
          newTarget = {enemy.position.x + enemy.width/2, enemy.position.y + enemy.height/2 -100};
      }else if(IsKeyPressed(KEY_UP)){
          newTarget = {800,450};
          zoomTarget = 1;
          ui.BarPos = {0, 0};
          ui.pos = {1300, 650};
      }
      
      
      
      if(attackANM){
          
          if(timerATK >= 2){  
              flick = 1;
              timerATK = 0;
              attackANM = false;
              switch(attackType){
                  case 1:
                    enemy.health -= enemy.damageCalc(0, player.specialDamageOut());
                    break;
                  case 2:
                    enemy.health -= enemy.damageCalc(1, player.physicalDamageOut());
                    break;
                  default:
                    enemy.health -= 10;
              }
             
              turn = false;
              enemyWaitTimer = 0.1;
              attackType = 0;
          }else{
              
          } timerATK += GetFrameTime();
          
          PlayerTarget = {400, 0};
          zoomTarget = 1.5;
          ui.BarPos = {-100, -300};
          ui.pos = {1300, 1100};
          newTarget = {enemy.position.x + enemy.width/2, enemy.position.y + enemy.height/2 -100};
      }else{
          if(EnemyTarget.x == 500 && EnemyTarget.y == 300){
             
              newTarget = {player.position.x + player.width/2 + 120, player.position.y + player.height/2 -70};
              zoomTarget = 1.2;
          }else if(!enemyView){
              PlayerTarget = {200, 400};
              newTarget = {800,450};
              zoomTarget = 1;
              ui.BarPos = {0, 0};
              ui.pos = {1300, 650};
              
          }else{
              zoomTarget = 1.5;
              ui.BarPos = {-100, -300};
              ui.pos = {1300, 1100};
              newTarget = {enemy.position.x + enemy.width/2, enemy.position.y + enemy.height/2 -100};
          }
      }
      if(!turn) ui.pos = {1300, 1100};
      
      if(!turn){
          if(enemyAttackTimer >= 1.2){
              enemyAttackTimer = 0;
              turn = true;
              EnemyTarget = {1100, 100};
              int temp = (int)GetRandomValue(0,1);
              player.health -= player.damageCalc(temp, enemy.returnDamage(temp));
              flickP = 1;
              player.block = false;
          }else if(enemyAttackTimer > 0.1){
              enemyAttackTimer += GetFrameTime();
          }
          
          if(enemyWaitTimer >= 1.5){
              enemyWaitTimer = 0;
              EnemyTarget = {500, 300};
              newTarget = {player.position.x + player.width/2 + 120, player.position.y + player.height/2 -70};
              zoomTarget = 1.2;
              enemyAttackTimer = 0.1;
          }else if(enemyWaitTimer > 0.1){
              enemyWaitTimer += GetFrameTime();
          }
      }else{
        EnemyTarget = {1100,100};
      }
      
     
      
      camera.target = {lerp(camera.target.x, newTarget.x, 0.03), lerp(camera.target.y, newTarget.y, 0.03)};
      
      camera.zoom = lerp(camera.zoom, zoomTarget, 0.03);
      
      player.position = Tween(player.position, PlayerTarget, 10);
      enemy.position = Tween(enemy.position, EnemyTarget, 10);
      
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
                DrawTextureEx(Background, {-300, -300}, 0, 1, WHITE);
                
                //DrawRectangleLines(player.position.x, player.position.y, player.width, player.height, BLACK);
                //DrawTextureEx(player.textureBack, player.position, 0, 6, WHITE);
                // DrawTextureRec(Texture2D texture, Rectangle source, Vector2 position, Color tint); 

                //DrawTextureRec(player.textureBack, {player.animRec.x, 0, 64 * PLAYERSCALE, 64 * PLAYERSCALE}, {player.position.x - 200, player.position.y}, WHITE);
                //DrawRectangleLines(enemy.position.x, enemy.position.y, enemy.width, enemy.height, MAROON);
                
                
                if(flick != 0){
                    if(timerflick > 0.1){
                        timerflick = 0;
                        if(flick == 1){
                          flick = 2;
                          flickcount++;
                        } 
                        else flick = 1;
                       
                        if(flickcount >= flicktotal){
                          flick = 0;
                           flickcount = 0;                          
                        } 
                    }else{
                        timerflick += GetFrameTime();
                    }
                }
                
                switch(flick){
                    case 0:
                        DrawTextureEx(EnemySprite, vectorAddition(enemy.position, {-300, -100}), 0, 5, WHITE);
                        break;
                    case 1:
                         DrawTextureEx(EnemySprite, vectorAddition(enemy.position, {-300, -100}), 0, 5, WHITE);
                        break;
                    case 2:
                         DrawTextureEx(EnemySprite, vectorAddition(enemy.position, {-300, -100}), 0, 5, SEMICLEAR);
                        break;
                }
                 if(player.block){
                    DrawRectangle(400, 425, 500, 500, BLUE);
                }
                 if(flickP != 0){
                    if(timerflickP > 0.1){
                        timerflickP = 0;
                        if(flickP == 1){
                          flickP = 2;
                          flickcountP++;
                        } 
                        else flickP = 1;
                       
                        if(flickcountP >= flicktotalP){
                          flickP = 0;
                          flickcountP = 0;                          
                        } 
                    }else{
                        timerflickP += GetFrameTime();
                    }
                }
                
                switch(flickP){
                    case 0:
                        DrawTextureRec(player.textureBack, {player.animRec.x, 0, 64 * PLAYERSCALE, 64 * PLAYERSCALE}, {player.position.x - 200, player.position.y}, WHITE);
                        break;
                    case 1:
                         DrawTextureRec(player.textureBack, {player.animRec.x, 0, 64 * PLAYERSCALE, 64 * PLAYERSCALE}, {player.position.x - 200, player.position.y}, WHITE);
                        break;
                    case 2:
                         DrawTextureRec(player.textureBack, {player.animRec.x, 0, 64 * PLAYERSCALE, 64 * PLAYERSCALE}, {player.position.x - 200, player.position.y}, SEMICLEAR);
                        break;
                }
                
                
                ui.HealthWidthE = lerp(ui.HealthWidthE, lerp(0, 500, enemy.health/enemy.maxHealth), 0.2);
                //Draws the gray background for the bar when it gets depleted 
                DrawRectangle(900, -100, 500, 25, GRAY);
                //Draws the actual health bar with a width of the value 'HealthWidth' as declared previously.
                DrawRectangle(900, -100, ui.HealthWidthE, 25, MAROON);
                //Draws the outline for the bar to make it look a little better
                //DrawRectangleRoundedLines({900, -100, 600, 30}, 5, 5, 10, BLACK);
                 
                
                 
                
                EndMode2D();
                //UI elements past this point

                
                
                BarPos = lerpV(BarPos, ui.BarPos, 0.2);
                
                if(IsMouseButtonPressed(0) && CheckCollisionPointRec({GetMouseX(), GetMouseY()}, {enemy.position.x, enemy.position.y, enemy.width, enemy.height})){
                    enemyView = true;
                }
                
                if(IsMouseButtonPressed(1)){
                    enemyView = false;
                }

              
                //linear interpolates the 'HealthWidth' variable, starting at its current value interpolatated towards the value of the players health scaled to the max width of the bar (1000) by a factor of 0.05 every frame to create a smooth gliding motion.
                ui.HealthWidth = lerp(ui.HealthWidth, lerp(0, 648, player.health/player.maxHealth), 0.05);  
                //Draws the outline for the bar to make it look a little better
               // DrawRectangleRoundedLines({BarPos.x + 150, BarPos.y + 50, 1000, 25}, 20, 20, 10, BLUE);
                //Draws the gray background for the bar when it gets depleted 
                DrawRectangle(BarPos.x + 20, BarPos.y + 40, 648, 25, GRAY);
                
                
                //Draws the actual health bar with a width of the value 'HealthWidth' as declared previously.
                DrawRectangle(BarPos.x + 20, BarPos.y + 40, ui.HealthWidth, 25, GREEN);
                
                
                ui.EnergyWidth = lerp(ui.EnergyWidth, lerp(0, 620, player.suit.battery/player.suit.maxBattery), 0.05);   
                DrawRectangle(BarPos.x + 20, BarPos.y + 120, 620, 25, GRAY);
                DrawRectangle(BarPos.x + 20, BarPos.y + 120, ui.EnergyWidth, 25, BLUE);
                
                ui.StaminaWidth = lerp(ui.StaminaWidth, lerp(0, 592, player.stamina/player.maxStamina), 0.05);   
                DrawRectangle(BarPos.x + 20, BarPos.y + 200, 592, 25, GRAY);
                DrawRectangle(BarPos.x + 20, BarPos.y + 200, ui.StaminaWidth, 25, YELLOW);
                
                //bar frame for the bars
                DrawTextureEx(BarFrame , BarPos, 0, 8, WHITE);
                
                pos = lerpV(pos, ui.pos, 0.2);
                
               //DrawRectangleRoundedLines({50, 100, 1000, 25}, 20, 20, 4, BLACK);
                
                Vector2 pos1 = pos; 
                Vector2 pos2 = pos;
                Vector2 pos3 = pos;
                Vector2 pos4 = pos;
                
                Vector2 pos1temp = {pos.x - 10, pos.y};
                Vector2 pos2temp = {pos.x + 10, pos.y};    
                
                 
                  if(spinA > 0){
                    spinA -= 130 * GetFrameTime();
                  }else{
                      spinA = 0;
                  }
                
                
                if(ui.menu == 0){
                    if(CheckCollisionPointTriangle({GetMouseX(), GetMouseY()}, pos, {pos.x, pos.y + 200}, {pos.x + 200, pos.y})){
                        ui.UIWheel = 4;
                        if(IsMouseButtonPressed(0) && ui.UIWheel != 0 && !clicked){
                            ui.menu = 4;
                            clicked = true;
                        }
                    }else if(CheckCollisionPointTriangle({GetMouseX(), GetMouseY()}, pos, {pos.x, pos.y - 200}, {pos.x + 200, pos.y})){
                        ui.UIWheel = 2;
                        if(IsMouseButtonPressed(0) && ui.UIWheel != 0 && !clicked){
                            ui.menu = 2;
                            clicked = true;
                        }
                    }else if(CheckCollisionPointTriangle({GetMouseX(), GetMouseY()}, pos, {pos.x, pos.y - 200}, {pos.x - 200, pos.y})){
                        ui.UIWheel = 1;
                        if(IsMouseButtonPressed(0) && ui.UIWheel != 0 && !clicked){
                            ui.menu = 1;
                            clicked = true;
                        }
                    }else if(CheckCollisionPointTriangle({GetMouseX(), GetMouseY()}, pos, {pos.x, pos.y + 200}, {pos.x - 200, pos.y})){
                        ui.UIWheel = 3;
                        if(IsMouseButtonPressed(0) && ui.UIWheel != 0 && !clicked){
                            ui.menu = 3;
                            clicked = true;
                        }
                    }else{
                        ui.UIWheel = 0;
                    }
                }
                
                /*
                if(IsMouseButtonPressed(0) && ui.UIWheel != 0){
                    ui.menu = 1;
                }
                */
                if(IsMouseButtonPressed(1)){
                    ui.menu = 0;
                }
        
                
                //DrawCircleSectorLines(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color); // Draw circle sector outline   
                switch(ui.menu){
                    
                    case 0:
                        
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
                            DrawCircleSectorLines(ui.pos01, ui.rad1, 0 + spinA, 90 + spinA, 50, YELLOW);                           
                            DrawCircleSectorLines(ui.pos02, ui.rad2, 270 + spinA, 360 + spinA, 50, BLUE);                           
                            DrawCircleSectorLines(ui.pos03, ui.rad3, 180 + spinA, 270 + spinA, 50, RED);                           
                            DrawCircleSectorLines(ui.pos04, ui.rad4, 90 + spinA, 180 + spinA, 50, GREEN);
                            DrawTextureEx(IconI , vectorAddition(ui.pos04, -200, -80), 0, 5, GREEN);
                            DrawTextureEx(IconR , vectorAddition(ui.pos01, -70, -80), 0, 5, YELLOW);
                            DrawTextureEx(IconB , vectorAddition(ui.pos02, 0, -150), 0, 2.5, BLUE);
                            DrawTextureEx(IconA , vectorAddition(ui.pos03, -180, -160), 0, 3, RED);
                            break;
                        
                        case 1:
                            pos3.x -= 40;
                            pos3.y -= 40;
                            ui.rad3 = 250;
                            ui.rad4 = 200;
                            ui.rad1 = 200;
                            ui.rad2 = 200;
                            DrawCircleSectorLines(ui.pos01, ui.rad1, 0, 90, 50, YELLOW);
                            DrawTextureEx(IconR , vectorAddition(ui.pos01, -70, -80), 0, 5, YELLOW);
                            DrawCircleSectorLines(ui.pos02, ui.rad2, 270, 360, 50, BLUE);
                            DrawTextureEx(IconB , vectorAddition(ui.pos02, 0, -150), 0, 2.5, BLUE);
                            DrawCircleSector(ui.pos03, ui.rad3, 180, 270, 50, RED);
                            DrawTextureEx(IconA , vectorAddition(ui.pos03, -200, -180), 0, 3, WHITE);
                            DrawTextureEx(IconA , vectorAddition(ui.pos03, -180, -160), 0, 3, SEMICLEAR);
                            DrawCircleSectorLines(ui.pos04, ui.rad4, 90, 180, 50, GREEN);
                            DrawTextureEx(IconI , vectorAddition(ui.pos04, -200, -80), 0, 5, GREEN);
                            break;
                            
                        case 2:
                            pos2.x += 40;
                            pos2.y -= 40;
                            ui.rad2 = 250;
                            ui.rad3 = 200;
                            ui.rad4 = 200;
                            ui.rad1 = 200;
                            DrawCircleSectorLines(ui.pos01, ui.rad1, 0, 90, 50, YELLOW);
                            DrawTextureEx(IconR , vectorAddition(ui.pos01, -70, -80), 0, 5, YELLOW);
                            DrawCircleSector(ui.pos02, ui.rad2, 270, 360, 50, BLUE);
                            DrawTextureEx(IconB , vectorAddition(ui.pos02, 20, -160), 0, 2.5, BLUE);
                            DrawTextureEx(IconB , vectorAddition(ui.pos02, -0, -140), 0, 2.5, SEMICLEAR);
                            DrawCircleSectorLines(ui.pos03, ui.rad3, 180, 270, 50, RED);
                            DrawTextureEx(IconA , vectorAddition(ui.pos03, -180, -160), 0, 3, RED);
                            DrawCircleSectorLines(ui.pos04, ui.rad4, 90, 180, 50, GREEN);
                            DrawTextureEx(IconI , vectorAddition(ui.pos04, -200, -80), 0, 5, GREEN);
                            break;
                            
                        case 3:
                            pos4.x -= 40;
                            pos4.y += 40;
                            ui.rad4 = 250;
                            ui.rad1 = 200;
                            ui.rad2 = 200;
                            ui.rad3 = 200;
                            DrawCircleSectorLines(ui.pos01, ui.rad1, 0, 90, 50, YELLOW);
                            DrawTextureEx(IconR , vectorAddition(ui.pos01, -70, -80), 0, 5, YELLOW);
                            DrawCircleSectorLines(ui.pos02, ui.rad2, 270, 360, 50, BLUE);
                            DrawTextureEx(IconB , vectorAddition(ui.pos02, 0, -150), 0, 2.5, BLUE);
                            DrawCircleSectorLines(ui.pos03, ui.rad3, 180, 270, 50, RED);
                            DrawTextureEx(IconA , vectorAddition(ui.pos03, -180, -160), 0, 3, RED);
                            DrawCircleSector(ui.pos04, ui.rad4, 90, 180, 50, GREEN);
                            DrawTextureEx(IconI , vectorAddition(ui.pos04, -230, -50), 0, 5, GREEN);
                            DrawTextureEx(IconI , vectorAddition(ui.pos04, -210, -80), 0, 5, SEMICLEAR);
                            break;
                            
                        case 4:
                            pos1.x += 40;
                            pos1.y += 40;
                            ui.rad1 = 250;
                            ui.rad2 = 200;
                            ui.rad3 = 200;
                            ui.rad4 = 200;
                            
                          
                            DrawCircleSector(ui.pos01, ui.rad1, 0, 90, 50, YELLOW);
                            DrawTextureEx(IconR , vectorAddition(ui.pos01, -50, -60), 0, 5, YELLOW);
                            DrawTextureEx(IconR , vectorAddition(ui.pos01, -80, -80), 0, 5, SEMICLEAR);
                            DrawCircleSectorLines(ui.pos02, ui.rad2, 270, 360, 50, BLUE);
                            DrawTextureEx(IconB , vectorAddition(ui.pos02, 0, -150), 0, 2.5, BLUE);
                            DrawCircleSectorLines(ui.pos03, ui.rad3, 180, 270, 50, RED);
                            DrawTextureEx(IconA , vectorAddition(ui.pos03, -180, -160), 0, 3, RED);
                            DrawCircleSectorLines(ui.pos04, ui.rad4, 90, 180, 50, GREEN);
                            DrawTextureEx(IconI , vectorAddition(ui.pos04, -200, -80), 0, 5, GREEN);
                            break;
                            
                            default:
                            break;
                        }
                        
                        break;
                        
                    // sub menu attack
                    case 1:
                  
                        if(CheckCollisionPointTriangle({GetMouseX(), GetMouseY()}, {pos1temp.x - 200, pos1temp.y + 200}, {pos1temp.x - 200, pos1temp.y - 200}, pos1temp)){
                            pos1temp.x -= 40;
                            DrawCircleSector(ui.posS1, 225, 90, 270, 50, BLUE);
                            DrawTextureEx(IconAS , vectorAddition(ui.posS1, -140, -30), 0, 6, WHITE);
                            if(IsMouseButtonPressed(0) && !clicked && player.suit.battery >= 15 && player.stamina >= 5){
                                player.stamina -= 5;
                                player.suit.battery -= 15;
                                if(player.stamina < 0) player.stamina = 0;
                                if(player.suit.battery < 0) player.suit.battery = 0;
                                ui.menu = 0;
                                clicked = true;
                                attackType = 1;
                                player.changeAnimation("Special");
                                attackANM = true;
                            }
                        }else{
                            DrawCircleSectorLines(ui.posS1, 200, 90, 270, 50, BLUE);
                            DrawTextureEx(IconAS , vectorAddition(ui.posS1, -110, -30), 0, 5.5, WHITE);
                        }
                        if(CheckCollisionPointTriangle({GetMouseX(), GetMouseY()}, {pos1temp.x + 200, pos1temp.y + 200}, {pos1temp.x + 200, pos1temp.y - 200}, pos1temp)){
                            pos2temp.x += 40;
                            DrawCircleSector(ui.posS2, 225, 450, 270, 50, RED);
                            DrawTextureEx(IconAP , vectorAddition(ui.posS2, 60, -40), 0, 7, WHITE);
                            if(IsMouseButtonPressed(0) && !clicked && player.stamina >= 15 && player.suit.battery >= 5){
                                player.stamina -= 15;
                                player.suit.battery -= 5;
                                if(player.stamina < 0) player.stamina = 0;
                                if(player.suit.battery < 0) player.suit.battery = 0;
                                ui.menu = 0;
                                clicked = true;
                                attackType = 2;
                                player.changeAnimation("Physical");
                                attackANM = true;
                            }

                        }else{
                            DrawCircleSectorLines(ui.posS2, 200, 450, 270, 50, RED);
                            DrawTextureEx(IconAP , vectorAddition(ui.posS2, 40, -40), 0, 6, WHITE);
                        }
                        
                        break;
                        
                      //sub menu block  
                      case 2:
                        
                            if(CheckCollisionPointTriangle({GetMouseX(), GetMouseY()}, {pos1temp.x - 200, pos1temp.y + 200}, {pos1temp.x - 200, pos1temp.y - 200}, pos1temp)){
                                pos1temp.x -= 40;
                                DrawCircleSector(ui.posS1, 225, 90, 270, 50, BLUE);
                                DrawTextureEx(BlockS , vectorAddition(ui.posS1, -180, -50), 0, 4.5, WHITE);
                                if(IsMouseButtonPressed(0) && !clicked){
                                    player.stamina += player.maxStamina/4;
                                    player.suit.battery += player.suit.maxBattery/2;
                                    if(player.stamina > player.maxStamina) player.stamina = player.maxStamina;
                                    if(player.suit.battery > player.suit.maxBattery) player.suit.battery = player.suit.maxBattery;
                                    ui.menu = 0;
                                    clicked = true;
                                    player.block = true;
                                    player.blockT = 0;
                                    enemyWaitTimer = 0.1;
                                    turn = false;
                                }
                            }else{
                                DrawCircleSectorLines(ui.posS1, 200, 90, 270, 50, BLUE);
                                DrawTextureEx(BlockS , vectorAddition(ui.posS1, -140, -50), 0, 4, WHITE);
                            }
                            if(CheckCollisionPointTriangle({GetMouseX(), GetMouseY()}, {pos1temp.x + 200, pos1temp.y + 200}, {pos1temp.x + 200, pos1temp.y - 200}, pos1temp)){
                                pos2temp.x += 40;
                                DrawCircleSector(ui.posS2, 225, 450, 270, 50, RED);
                                DrawTextureEx(BlockP , vectorAddition(ui.posS2, 50, -70), 0, 5, WHITE);
                                if(IsMouseButtonPressed(0) && !clicked){
                                    player.stamina += player.maxStamina/2;
                                    player.suit.battery += player.suit.maxBattery/4;
                                    if(player.stamina > player.maxStamina) player.stamina = player.maxStamina;
                                    if(player.suit.battery > player.suit.maxBattery) player.suit.battery = player.suit.maxBattery;
                                    clicked = true;
                                    ui.menu = 0;
                                    clicked = true;
                                    player.block = true;
                                    player.blockT = 1;
                                    enemyWaitTimer = 0.1;
                                    turn = false;
                                }
                            }else{
                                DrawCircleSectorLines(ui.posS2, 200, 450, 270, 50, RED);
                                DrawTextureEx(BlockP , vectorAddition(ui.posS2, 20, -70), 0, 4.5, WHITE);
                            }
                        
                            break;
                    
                    default:
                        break;
                    
                }   
                  
                
                
                ui.posS1 = lerpV(ui.posS1, pos1temp , 0.3);
                ui.posS2 = lerpV(ui.posS2, pos2temp, 0.3);
                
                ui.pos01 = lerpV(ui.pos01, pos1 , 0.3);
                ui.pos02 = lerpV(ui.pos02, pos2, 0.3);
                ui.pos03 = lerpV(ui.pos03, pos3, 0.3);
                ui.pos04 = lerpV(ui.pos04, pos4, 0.3);
                
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
