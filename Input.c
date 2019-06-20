#include <gb/gb.h>
#include "GameObject.c"

 void Input(struct GameObject* objecto)
{
 if(joypad() & J_B)
  {
    //DISPLAY_OFF;
  }
  if(joypad() &J_A)
  {
     //DISPLAY_ON;
      if( objecto->isJumping==0&& objecto->isFalling==0)
    {
      objecto->basePosY= objecto->position[1];
      objecto->isJumping =1;
    }
  }
  if(joypad() & J_LEFT)
  {
    scroll_bkg(-5,0);
    MoveChar(objecto,-1,0);
    objecto->currentFrame++;
    if(objecto->currentFrame>objecto->NumFrames)
      objecto->currentFrame=1;
    setDirection(objecto,S_FLIPX); 

   // Animate(objecto,objecto->currentFrame);
  }
  if(joypad() & J_RIGHT)
  {
    NR10_REG = 0x16;
    NR11_REG = 0x40;
    NR12_REG = 0xC2;
    NR13_REG = 0x00;
    NR14_REG = 0xFF;
    scroll_bkg(5,0);
    MoveChar(objecto,1,0);
    objecto->currentFrame++;
    if(objecto->currentFrame>objecto->NumFrames)
    {
        objecto->currentFrame=1;
    }

    Animate(objecto,objecto->currentFrame);
    setDirection(objecto,0);
  }

   if(objecto->isJumping==1)
    {
      Jump(objecto);
    }
}