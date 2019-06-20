#include <gb/gb.h>
#include "CollissionMap.c"
#include "Globals.c"

typedef struct GameObject
{
    UINT8 numberOfTilesx;
    UINT8 numberOfTilesy;
    UINT8 position[2];
    UINT8 Width;
    UINT8 Height;
    UINT8 baseIndex;
    unsigned char* Tiles;  
    UINT8 moveindex;
    UINT8 NumFrames;
    UINT8 currentFrame;
    UINT8 isJumping;
    UINT8 basePosY;
    UINT8 isFalling;
    UINT8 jumpSpeed;
     

};
UINT8 checkStagecollision(UINT8 nextX, UINT8 nextY)
 {

    
    if(nextX<sizeof(collisionData)/sizeof(char)+35 )
   {
     if(collisionData[nextX-35]==0)
     return 0;
     else
     {
       return 1;
     }
     
   }
   else
   {
     
   
   
   return 1;
   }
 }
void MoveChar(struct GameObject* charK, UINT8 movX, UINT16 movY)
{
  if(checkStagecollision(charK->position[0]+ movX,0)==0)
  {

    charK->position[0]+= movX;
    charK->position[1]+= movY;
    index = charK->baseIndex;
    for(y=0; y<charK->numberOfTilesy; y++)
    {
        for(x=0; x<charK->numberOfTilesx; x++)
      {
        UINT8 X =charK->position[0]+(x*8);
        UINT8 Y =charK->position[1]+(y*8);
        move_sprite(index,X,Y);

          index++;
      }
     
    }
    index=0;
  }
}

UBYTE checkcollision(struct  GameObject* obj1,struct GameObject* obj2) 
{
  if(obj2->position[0]>obj1->position[0]
  /*&&
     (obj2->position[0])<=(obj1->position[0]+obj1->Width)&&
     obj2->position[1]>=obj1->position[1] &&
     (obj2->position[1])<=(obj1->position[1]+obj1->Height) */)
  {
    return 1;
  }
  return 0;
}

void Animate(struct GameObject* charK,UINT8 numFrame)
{
  // charK->currentFrame = (numFrame+1)%charK->NumFrames;
    index = charK->baseIndex;
    charK->currentFrame = numFrame;
  for(y=0; y<charK->numberOfTilesy; y++)
    {
        for(x=0; x<charK->numberOfTilesx; x++)
      {
        move_sprite(index,charK->position[0]+(x*8),charK->position[1]+(y*8));
        set_sprite_tile(index,index + (( numFrame-1)*(charK->numberOfTilesx*charK->numberOfTilesy)));
        
        index++;
      }
    }
    index =0;
}

void setDirection(struct GameObject* charK, UINT8 dir)
{
   UINT8 newindex = charK->currentFrame;
  index = charK->baseIndex;
 
   for(y=0; y<charK->numberOfTilesy; y++)
    {
        for(x=0; x<charK->numberOfTilesx; x++)
      {
        if(x==0 && dir!=0)
         {
           set_sprite_tile(index,(index+2)+((charK->numberOfTilesx*charK->numberOfTilesy)*( newindex-1)));
         } 
         else if(x==1 && dir!=0)
         {
            set_sprite_tile(index,(index)+((charK->numberOfTilesx*charK->numberOfTilesy)*( newindex-1)));

         }
         else if(x==2 && dir!=0)
         {
           set_sprite_tile(index,(index-2)+((charK->numberOfTilesx*charK->numberOfTilesy)*( newindex-1)));
         } 

        set_sprite_prop(index,dir);
        
        index++;
      }
    }
    index =0;
  

}

void Jump(struct GameObject* charK)
{
   MoveChar(charK,0,-charK->jumpSpeed);
        charK->jumpSpeed= charK->jumpSpeed+gravity;
        NR10_REG = 0x16;
        NR11_REG = 0x40;
        NR12_REG = 0xC2;
        NR13_REG = 0x00;
        NR14_REG = 0xFF;
        if(charK->position[1]>=charK->basePosY)
        {
          charK->isJumping=0;
            charK->jumpSpeed = 8;
      
          charK->position[1]=charK->basePosY;
          MoveChar(charK,0,0);


        }
      
  
  

  
}


