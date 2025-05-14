//main.c

#include "gba.h"

void sync()
{
  while(REG_DISPLAY_VCOUNT >= 160);
  while(REG_DISPLAY_VCOUNT < 160);
}

uint32 clamp(int value, int min, int max)
{
  return (value < min ? min : (value > max ? max : value));
}

void drawRect(struct Rect r, uint16 color)
{
  for(int i = 0; i < r.h; i++)
  {
    for(int j = 0; j < r.w; j++)
    {
      SCREENBUFFER[SCREEN_WIDTH * (i + r.y) + (j + r.x)] = color;
    }
  }
}

void init7seg()
{
  a.w = 16;
  a.h = 4;
  f.w = 4;
  f.h = 16;
  d2 = g2 = a2 = d = g = a;
  b2 = c2 = e2 = f2 = b = c = e = f;
  
  a.x = d.x = e.x = f.x = g.x = (SCREEN_WIDTH / 2) + 30;
  b.x = c.x = a.x + a.w;

  a2.x = d2.x = e2.x = f2.x = g2.x = (SCREEN_WIDTH / 2) - 30;
  b2.x = c2.x = a2.x + a2.w;
  
  a2.y = b2.y = f2.y = a.y = b.y = f.y = 0;
  c2.y = e2.y = g2.y = c.y = e.y = g.y = b.y + b.h - a.h;
  d2.y = d.y = g.y + b.h - a.h;
}

void clear7seg()
{
  drawRect(a, 0x0000);
  drawRect(b, 0x0000);
  drawRect(c, 0x0000);
  drawRect(d, 0x0000);
  drawRect(e, 0x0000);
  drawRect(f, 0x0000);
  drawRect(g, 0x0000);
}
void clear7seg2()
{
  drawRect(a2, 0x0000);
  drawRect(b2, 0x0000);
  drawRect(c2, 0x0000);
  drawRect(d2, 0x0000);
  drawRect(e2, 0x0000);
  drawRect(f2, 0x0000);
  drawRect(g2, 0x0000);
}

void draw7Seg(uint8 num)
{
  clear7seg();
  uint8 w,x,y,z;
  
  w = num & 8;
  x = num & 4;
  y = num & 2;
  z = num & 1;
  
  if(y || w || (x && z) || (!x && !z))
  {
    drawRect(a, 0x001f);
  }
  if(!x || (!y && !z) || (y && z))
  {
    drawRect(b, 0x001f);
  }
  if(!y|| (!w && x) || (!w && z))
  {
    drawRect(c, 0x001f);
  }
  if((x && !y && z) || (!x && !z) || (!x && y) || (y && !z))
  {
    drawRect(d, 0x001f);
  }
  if((!x && !z) || (y && !z))
  {
    drawRect(e, 0x001f);
  }
  if(w || (!y && !z) || (x && !z) || (x && !y))
  {
    drawRect(f, 0x001f);
  }
  if(w || (y && !z) || (x && !y) || (!x && y))
  {
    drawRect(g, 0x001f);
  }
  //josh mooreheads segments
}
void draw7Seg2(uint8 num)
{
  clear7seg2();
  uint8 w,x,y,z;
  
  w = num & 8;
  x = num & 4;
  y = num & 2;
  z = num & 1;
  
  if(y || w || (x && z) || (!x && !z))
  {
    drawRect(a2, 0x001f);
  }
  if(!x || (!y && !z) || (y && z))
  {
    drawRect(b2, 0x001f);
  }
  if(!y|| (!w && x) || (!w && z))
  {
    drawRect(c2, 0x001f);
  }
  if((x && !y && z) || (!x && !z) || (!x && y) || (y && !z))
  {
    drawRect(d2, 0x001f);
  }
  if((!x && !z) || (y && !z))
  {
    drawRect(e2, 0x001f);
  }
  if(w || (!y && !z) || (x && !z) || (x && !y))
  {
    drawRect(f2, 0x001f);
  }
  if(w || (y && !z) || (x && !y) || (!x && y))
  {
    drawRect(g2, 0x001f);
  }
  //josh mooreheads segments
}

int main()
{
  REG_DISPLAY = VIDEOMODE | BGMODE;
  
  init7seg();
  
  uint8 counter = 0;
  uint8 counter2 = 0;
  uint8 down = 0;
  
  ball.w = 8;
  ball.h = 8;
  
  ball.x = 120 - ball.w/2;
  ball.y = 80 - ball.h/2;
  
  prevBall = ball;
  
  player.w = 8;
  player.h = 32;
  
  player.x = 0;
  player.y = 0;
  
  player2.w = 8;
  player2.h = 32;
  
  player2.x = SCREEN_WIDTH - player2.w;
  player2.y = 0;
  
  prevPlayer = player;
  
  int ballSpeedX = 1;
  int ballSpeedY = 1;
  
  int playerSpeedY = 2;
  
  while(1)
  {
    sync();
    
    drawRect(prevBall, 0x0000);
    drawRect(prevPlayer, 0x0000);
    drawRect(prevPlayer2, 0x0000);
    
    if(!(REG_DISPLAY_INPUT & A) && !down)
    {
      counter2 ++;  
      if(counter2 > 9)
        counter2 = 0;
      counter++;
      if(counter > 9)
        counter = 0;
      down = 1;
    }
    else if((REG_DISPLAY_INPUT & A))
    {
      down = 0;
    }
    draw7Seg2(counter2);
    draw7Seg(counter);
    drawRect(ball, 0x1111);
    drawRect(player, 0x2222);
    drawRect(player2, 0x2222);
    
    prevBall = ball;
    prevPlayer = player;
    prevPlayer2 = player2;
    
    ball.x += ballSpeedX;
    ball.y += ballSpeedY;
    
    int newPlayerY = player.y;
    int newPlayer2Y = player2.y;
    
    if(!(REG_DISPLAY_INPUT & DOWN))
    {
      newPlayerY += playerSpeedY;
    }
    
    if(!(REG_DISPLAY_INPUT & UP))
    {
      newPlayerY -= playerSpeedY;
    }
    
    if(!(REG_DISPLAY_INPUT & LEFT))
    {
      newPlayer2Y += playerSpeedY;
    }
    
    if(!(REG_DISPLAY_INPUT & RIGHT))
    {
      newPlayer2Y -= playerSpeedY;
    }
    
    player.y = clamp(newPlayerY, 0, SCREEN_HEIGHT - player.h);
    player2.y = clamp(newPlayer2Y, 0, SCREEN_HEIGHT - player2.h);
    
    if(ball.y + ball.h >= SCREEN_HEIGHT || ball.y <= 0)
    {
      ballSpeedY = -ballSpeedY;
    }
    if(ball.x <= 0)
    {
        counter ++;
        if(counter > 9)
            counter = 0;
        draw7Seg(counter);
        //ball.x = 120 - ball.w/2;
        //ball.y = 80 - ball.h/2;

        //give player 2 a point
        //then reset ball
        ball.x = 130;
        ball.y = 80;
    }
    else if(ball.x + ball.w >= SCREEN_WIDTH)
    {
    
        counter2 ++;
        if(counter2 > 9)
            counter2 = 0;
        draw7Seg2(counter2);
        //ball.x = 120 - ball.w/2;
        //ball.y = 80 - ball.h/2;
        //give player 1 a point
        //then reset ball
        ball.x = 130;
        ball.y = 80;
    }
    if(ball.x == player.x + player.w)
    {
      if(ball.y <= player.y + player.h && ball.y + ball.h >= player.y)
      {
        ballSpeedX = -ballSpeedX;
      }
    }
    if(ball.x + ball.w == player2.x)
    {
      if(ball.y <= player2.y + player2.h && ball.y + ball.h >= player2.y)
      {
        ballSpeedX = -ballSpeedX;
      }
    }
  }
}