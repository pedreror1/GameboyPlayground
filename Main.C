#include "Input.C"
#include "guy2.c"
#include "backmap1_data.c"
#include "backmap1_map.c"
 
#include "FontTiles.c"
#include <stdio.h>
#include <gb/font.h>
#include "bea.c"
#include "tiot.c"
#include "bullet.c"
#include "Onigiri.c"
#include "splashscreen3_data.c"
#include "splashscreen3_map.c"
#include "radianlogo_data.c"
#include "radianlogo_map.c"
#include "salaryman.c"

UINT8 maxJumpHeight =-45;
UINT8 jumpHeight = -0;
UINT8 base_Posy=96;
UINT8 originalY =0;
BYTE isJumping =0;
BYTE isFalling;
UINT8 i=0;
UINT8 j=0;
UINT8 tile =0;  

UINT8 speed =18;
UINT8 currentSpriteIndex=0;
font_t min_font;

struct GameObject mrGuy;
struct GameObject beachan;
struct GameObject bullet;
struct GameObject onigiri[5];
struct GameObject salaryGuy;
 //bool canMove = true;

void PlaySound()
{
   NR10_REG = 0x07;
   NR11_REG = 0x40;
   NR12_REG = 0x73;
   NR13_REG = 0x00;
   NR14_REG = 0xC3;
}
void setupCharacter(struct GameObject* charK, int tilesX, int tilesY, const unsigned char* tiles, UINT8 posx,UINT8 posy, UINT8 currentIndex,UINT8 numframes)
{
  charK->numberOfTilesx = tilesX;
  charK->numberOfTilesx = tilesX;
  charK->numberOfTilesy = tilesY;
  charK->currentFrame=1;
  charK->Tiles = tiles;
  charK->position[0] =posx;
  charK->position[1] =posy;
  charK->Width = tilesX*8;
  charK->Height = tilesY*8;
  charK->baseIndex = currentIndex;
  charK->NumFrames = numframes;
  charK->isJumping =0;
  charK->isFalling =0;
  charK->basePosY = posy;
  charK->jumpSpeed =8;
  set_sprite_data(currentIndex,charK->numberOfTilesx*charK->numberOfTilesy*numframes,charK->Tiles);
  index = charK->baseIndex;
  for(y=0; y<charK->numberOfTilesy; y++)
    {
        for(x=0; x<charK->numberOfTilesx; x++)
      {
        move_sprite(index,charK->position[0]+(x*8),charK->position[1]+(y*8));
        set_sprite_tile(index,index);
        
        index++;
      }
    }
    index =0;
    
    currentSpriteIndex=currentIndex+(tilesX*tilesY);
}


 


void playSong()
{
    NR10_REG = 0x1E;
    NR11_REG = 0x40;
    NR12_REG = 0x73;
    NR13_REG = 0x00;
    NR14_REG = 0xC3;
    delay(10);
    NR10_REG = 0x09;
    NR11_REG = 0x40;
    NR12_REG = 0x73;
    NR13_REG = 0x00;
    NR14_REG = 0xC3;
        delay(10);
    NR10_REG = 0xA;
    NR11_REG = 0x40;
    NR12_REG = 0x73;
    NR13_REG = 0x00;
    NR14_REG = 0xC3;
        delay(10);
    NR10_REG = 0x1B;
    NR11_REG = 0x40;
    NR12_REG = 0x73;
    NR13_REG = 0x00;
    NR14_REG = 0xC3;
        delay(10);
    NR10_REG = 0x08;
    NR11_REG = 0x40;
    NR12_REG = 0x73;
    NR13_REG = 0x00;
    NR14_REG = 0xC3;
        delay(10);
    NR10_REG = 0x16;
    NR11_REG = 0x40;
    NR12_REG = 0x73;
    NR13_REG = 0x00;
    NR14_REG = 0xC3;
}



 
void main()
{
  //fonts
 font_init();
 min_font= font_load(font_min);// 36 tile 
 font_set(min_font);

 set_bkg_data(0,237,splashscreen3_data);
 set_bkg_tiles(0,0,20,18,splashscreen3_map);
 SHOW_BKG;
 DISPLAY_ON; 
  
  delay(650);
  set_bkg_data(0,139,radianlogo_data);
 set_bkg_tiles(0,0,20,18,radianlogo_map);
  //Backs

 waitpad(J_START);
  set_bkg_data(0,172,backmap1_data);
 set_bkg_tiles(0,0,80,18,backmap1_map);
  // setupCharacter();
 //Sprites

 setupCharacter(&mrGuy,2,4,tiosprite,108,106, currentSpriteIndex,1);
 setupCharacter(&beachan, 4,4,beasprite,45,196,currentSpriteIndex,1);
 setupCharacter(&bullet,1,1,bulletSprite,25,25,24,1); 
 
  for(onigiriIndex=0; onigiriIndex<numberOfOnigiris; onigiriIndex++)
  {
    setupCharacter(&onigiri[onigiriIndex],1,1,bulletSprite2,65+(15*onigiriIndex),105,25+onigiriIndex,1);
  }// setupCharacter(&onigiri[1],1,1,bulletSprite2,80,105,26,1);
   


 setupCharacter(&salaryGuy,3,4,salaryGuyTiles,35,116,28,2);



 



 



  

//Window
  //set_win_tiles(0,0,5,1,fontTiles);
  move_win(7,136);
  SHOW_WIN;
  DISPLAY_ON;
      
  SHOW_SPRITES;

  //Audio
  NR52_REG = 0x80;
  NR51_REG = 0xFF;
  NR50_REG = 0x77;

 //GameLoop
    
  while (1)
  {
  //
    playSong();
    Input(&salaryGuy);
    for(onigiriIndex=0; onigiriIndex<numberOfOnigiris; onigiriIndex++)
    {
       if(checkcollision(&onigiri[onigiriIndex],&salaryGuy)==1)
       {
         MoveChar(&onigiri[onigiriIndex],200,180);
       }
    }
    delay(50);
          
  }
    
}