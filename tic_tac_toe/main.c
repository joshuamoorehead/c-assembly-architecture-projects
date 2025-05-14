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
  
  a.x = d.x = e.x = f.x = g.x = SCREEN_WIDTH - 40;
  b.x = c.x = a.x + a.w;

  a2.x = d2.x = e2.x = f2.x = g2.x = SCREEN_WIDTH - 40;
  b2.x = c2.x = a2.x + a2.w;
  
  a2.y = b2.y = f2.y = 94.6;
  a.y = b.y = f.y = 41.3;
  c2.y = e2.y = g2.y = b2.y + b2.h - a2.h;
  c.y = e.y = g.y = b.y + b.h - a.h;
  d2.y = g2.y + b2.h - a2.h;
  d.y = g.y + b.h - a.h;
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
int checkWin(int arr[])
{
    if((arr[0] & arr[1] & arr[2]) || (arr[0] & arr[3] & arr[6]) || 
    (arr[0] & arr[4] & arr[8]) || (arr[1] & arr[4] & arr[7]) || 
    (arr[2] & arr[5] & arr[8]) || (arr[2] & arr[4] & arr[6]) ||
    (arr[3] & arr[4] & arr[5]) || (arr[6] & arr[7] & arr[8]))
    {
      return 1;
    }
    else
    {
      return 0;
    }
}



int main()
{
  REG_DISPLAY = VIDEOMODE | BGMODE;
  
  init7seg();
  
  uint8 counter = 0;
  uint8 counter2 = 0;
  uint8 stop = 0;
  uint8 stopLeft = 0;
  uint8 stopLeft2 = 0;
  uint8 stopRight = 0;
  uint8 stopRight2 = 0;
  uint8 stopB1 = 0;
  uint8 stopB2 = 0;
  uint8 sum = 0;
  uint8 playerSpecifier = 0;
  uint8 playerTracker = 0;
  uint8 BIG_INCREMENT = (SCREEN_HEIGHT/3)*2;
  uint8 SMALL_INCREMENT = (SCREEN_HEIGHT/3);
  
  int availableSquares[9] = {1,1,1,1,1,1,1,1,1};
  int player1Squares[9] = {0,0,0,0,0,0,0,0,0};
  int player2Squares[9] = {0,0,0,0,0,0,0,0,0};
  
  border1.w = border2.w = border3.w = 1;
  borderY1.w = borderY2.w = 160;
  border1.h = border2.h = border3.h = 160;
  borderY1.h = borderY2.h = 1;
  border1.x = 53.3;
  border2.x = 106.6;
  border3.x = 160;
  border1.y = border2.y = border3.y = 0;
  borderY1.x = borderY2.x = 0;
  borderY1.y = 53.3;
  borderY2.y = 106.6;
  player1Score.x = player2Score.x = 180;
  player1Score.y = 53.3;
  player2Score.y = 102.6;
  player1Score.w = player2Score.w = 8;
  player1Score.h = player2Score.h = 8;
  square0.w = square0.h = square1.w = square1.h = square2.w = square2.h = square3.w = square3.h = square4.w = square4.h = 
  square5.w = square5.h = square6.w = square6.h = square7.w = square7.h = square8.w = square8.h = playerSquare.w = playerSquare.h =  20;
  square0.x = square3.x = square6.x = playerSquare.x = 16.65;
  square1.x = square4.x = square7.x = 69.95;
  square2.x = square5.x = square8.x = 123.25;
  square0.y = square1.y = square2.y = playerSquare.y = 16.65;
  square3.y = square4.y = square5.y = 69.95;
  square6.y = square7.y = square8.y = 123.25;

  drawRect(border1, 0x001f);
  drawRect(border2, 0x001f);
  drawRect(border3, 0x001f);
  drawRect(borderY1, 0x001f);
  drawRect(borderY2, 0x001f);
  drawRect(player1Score, 0xABCD);
  drawRect(player2Score, 0x7000);
  draw7Seg2(0);
  draw7Seg(0);
  drawRect(square1, 0x0ABC);
  drawRect(square2, 0x0ABC);
  drawRect(square3, 0x0ABC);
  drawRect(square0, 0x0ABC);
  drawRect(square4, 0x0ABC);
  drawRect(square5, 0x0ABC);
  drawRect(square6, 0x0ABC);
  drawRect(square7, 0x0ABC);
  drawRect(square8, 0x0ABC);
  drawRect(playerSquare, 0xABCD);
  

  
  
  while(1)
  {
    
    sync();
    if(!(REG_DISPLAY_INPUT & A) && !stop)//pressing A once changes player
    {
      if(playerSpecifier == 1)
      {
        if(availableSquares[playerTracker])
          drawRect(playerSquare, 0xABCD);
        playerSpecifier = 0;
      }
      else if(playerSpecifier == 0)
      {
        if(availableSquares[playerTracker])
          drawRect(playerSquare, 0x7000);
        playerSpecifier = 1;
      }
      stop = 1;
    }
    else if((REG_DISPLAY_INPUT & A))
    {
      stop = 0;
    }
    
    if(!(REG_DISPLAY_INPUT & B) && playerSpecifier && !stopB1)//selecting square as player2
    {
      if(availableSquares[playerTracker] == 1)
      {
        if(playerTracker == 0)
        {
          drawRect(square0, 0x7000);
          player2Squares[0] = 1;
          availableSquares[0] = 0;
        }
        else if(playerTracker == 1)
        {
          drawRect(square1, 0x7000);
          player2Squares[1] = 1;
          availableSquares[1] = 0;
        }
        else if(playerTracker == 2)
        {
          drawRect(square2, 0x7000);
          player2Squares[2] = 1;
          availableSquares[2] = 0;
        }
        else if(playerTracker == 3)
        {
          drawRect(square3, 0x7000);
          player2Squares[3] = 1;
          availableSquares[3] = 0;
        }
        else if(playerTracker == 4)
        {
          drawRect(square4, 0x7000);
          player2Squares[4] = 1;
          availableSquares[4] = 0;
        }
        else if(playerTracker == 5)
        {
          drawRect(square5, 0x7000);
          player2Squares[5] = 1;
          availableSquares[5] = 0;
        }
        else if(playerTracker == 6)
        {
          drawRect(square6, 0x7000);
          player2Squares[6] = 1;
          availableSquares[6] = 0;
        }
        else if(playerTracker == 7)
        {
          drawRect(square7, 0x7000);
          player2Squares[7] = 1;
          availableSquares[7] = 0;
        }
        else if(playerTracker == 8)
        {
          drawRect(square8, 0x7000);
          player2Squares[8] = 1;
          availableSquares[8] = 0;
        }
        if(checkWin(player2Squares))
        {
          counter ++;
          if(counter > 9)
              counter = 0;
          draw7Seg2(counter);
          //resetting board and square arrays
          for(int i = 0; i<9; i++)
          {
            availableSquares[i] = 1;
            player1Squares[i] = player2Squares[i] = 0;
          }
          drawRect(square1, 0x0ABC);
          drawRect(square2, 0x0ABC);
          drawRect(square3, 0x0ABC);
          drawRect(square0, 0x0ABC);
          drawRect(square4, 0x0ABC);
          drawRect(square5, 0x0ABC);
          drawRect(square6, 0x0ABC);
          drawRect(square7, 0x0ABC);
          drawRect(square8, 0x0ABC);
          
          

        }
      }
      stopB1 = 1;
    }
    else if((REG_DISPLAY_INPUT & B))
    {
      stopB1 = 0;
    }
    if(!(REG_DISPLAY_INPUT & B) && !playerSpecifier && !stopB2)//selecting square as player1
    {
      if(availableSquares[playerTracker] == 1)
      {
        if(playerTracker == 0)
        {
          drawRect(square0, 0xABCD);
          player1Squares[0] = 1;
          availableSquares[0] = 0;
        }
        else if(playerTracker == 1)
        {
          drawRect(square1, 0xABCD);
          player1Squares[1] = 1;
          availableSquares[1] = 0;
        }
        else if(playerTracker == 2)
        {
          drawRect(square2, 0xABCD);
          player1Squares[2] = 1;
          availableSquares[2] = 0;
        }
        else if(playerTracker == 3)
        {
          drawRect(square3, 0xABCD);
          player1Squares[3] = 1;
          availableSquares[3] = 0;
        }
        else if(playerTracker == 4)
        {
          drawRect(square4, 0xABCD);
          player1Squares[4] = 1;
          availableSquares[4] = 0;
        }
        else if(playerTracker == 5)
        {
          drawRect(square5, 0xABCD);
          player1Squares[5] = 1;
          availableSquares[5] = 0;
        }
        else if(playerTracker == 6)
        {
          drawRect(square6, 0xABCD);
          player1Squares[6] = 1;
          availableSquares[6] = 0;
        }
        else if(playerTracker == 7)
        {
          drawRect(square7, 0xABCD);
          player1Squares[7] = 1;
          availableSquares[7] = 0;
        }
        else if(playerTracker == 8)
        {
          drawRect(square8, 0xABCD);
          player1Squares[8] = 1;
          availableSquares[8] = 0;
        }
        if(checkWin(player1Squares))
        {
          counter2 ++;
          if(counter2 > 9)
              counter2 = 0;
          draw7Seg(counter2);
          //resetting board and square arrays
          for(int i = 0; i<9; i++)
          {
            availableSquares[i] = 1;
            player1Squares[i] = player2Squares[i] = 0;
          }
          drawRect(square1, 0x0ABC);
          drawRect(square2, 0x0ABC);
          drawRect(square3, 0x0ABC);
          drawRect(square0, 0x0ABC);
          drawRect(square4, 0x0ABC);
          drawRect(square5, 0x0ABC);
          drawRect(square6, 0x0ABC);
          drawRect(square7, 0x0ABC);
          drawRect(square8, 0x0ABC);
          

        }
      }
      stopB2 = 1;
    }
    else if((REG_DISPLAY_INPUT & B))
    {
      stopB2 = 0;
    }
    
      
    
    
    if(!(REG_DISPLAY_INPUT & LEFT) && playerSpecifier && !stopLeft)//moving left for player 2
    {
      if(playerTracker != 0)
      {
        
        if(playerTracker == 1 || playerTracker == 2 || playerTracker == 4 || playerTracker == 5 || playerTracker == 7 || playerTracker == 8)
        {
          if(availableSquares[playerTracker])
            drawRect(playerSquare, 0x0ABC);
          playerSquare.x -= SMALL_INCREMENT;
          if(!player1Squares[playerTracker-1])
            drawRect(playerSquare, 0x7000);
        }
        else if(playerTracker == 3 || playerTracker == 6)
        {
          if(availableSquares[playerTracker])
            drawRect(playerSquare, 0x0ABC);
          playerSquare.x += BIG_INCREMENT;
          playerSquare.y -= SMALL_INCREMENT;
          if(!player1Squares[playerTracker-1])
            drawRect(playerSquare, 0x7000);
        }
        
        playerTracker --;
        stopLeft = 1;
      }
    }
    else if((REG_DISPLAY_INPUT & LEFT))
    {
      stopLeft = 0;
    }



    if(!(REG_DISPLAY_INPUT & LEFT) && !playerSpecifier && !stopLeft2)//moving left for player 1
    {
      if(playerTracker != 0)
      {
        
        if(playerTracker == 1 || playerTracker == 2 || playerTracker == 4 || playerTracker == 5 || playerTracker == 7 || playerTracker == 8)
        {
          if(availableSquares[playerTracker])
            drawRect(playerSquare, 0x0ABC);
          playerSquare.x -= SMALL_INCREMENT;
          if(!player2Squares[playerTracker-1])
            drawRect(playerSquare, 0xABCD);
        }
        else if(playerTracker == 3 || playerTracker == 6)
        {
          if(availableSquares[playerTracker])
            drawRect(playerSquare, 0x0ABC);
          playerSquare.x += BIG_INCREMENT;
          playerSquare.y -= SMALL_INCREMENT;
          if(!player2Squares[playerTracker-1])
            drawRect(playerSquare, 0xABCD);
        }
        
        playerTracker --;
        stopLeft2 = 1;
      }
    }
    else if((REG_DISPLAY_INPUT & LEFT))
    {
      stopLeft2 = 0;
    }



    
    if(!(REG_DISPLAY_INPUT & RIGHT) && playerSpecifier && !stopRight)//moving right for player 2
    {
      if(playerTracker != 8)
      {
        
        if(playerTracker == 1 || playerTracker == 3 || playerTracker == 4 || playerTracker == 6 || playerTracker == 7 || playerTracker == 0)
        {
          if(availableSquares[playerTracker])
            drawRect(playerSquare, 0x0ABC);
          playerSquare.x += SMALL_INCREMENT;
          if(!player1Squares[playerTracker+1])
            drawRect(playerSquare, 0x7000);
        }
        else if(playerTracker == 2 || playerTracker == 5)
        {
          if(availableSquares[playerTracker])
            drawRect(playerSquare, 0x0ABC);
          playerSquare.x -= BIG_INCREMENT;
          playerSquare.y += SMALL_INCREMENT;
          if(!player1Squares[playerTracker+1])
            drawRect(playerSquare, 0x7000);
        }
        
        playerTracker ++;
        stopRight = 1;
      }
    }
    else if((REG_DISPLAY_INPUT & RIGHT))
    {
      stopRight = 0;
    }
    if(!(REG_DISPLAY_INPUT & RIGHT) && !playerSpecifier && !stopRight2)//moving right for player 1
    {
      if(playerTracker != 8)
      {
        
        if(playerTracker == 1 || playerTracker == 3 || playerTracker == 4 || playerTracker == 6 || playerTracker == 7 || playerTracker == 0)
        {
          if(availableSquares[playerTracker])
            drawRect(playerSquare, 0x0ABC);
          playerSquare.x += SMALL_INCREMENT;
          if(!player2Squares[playerTracker+1])
            drawRect(playerSquare, 0xABCD);
        }
        else if(playerTracker == 2 || playerTracker == 5)
        {
          if(availableSquares[playerTracker])
            drawRect(playerSquare, 0x0ABC);
          playerSquare.x -= BIG_INCREMENT;
          playerSquare.y += SMALL_INCREMENT;
          if(!player2Squares[playerTracker+1])
            drawRect(playerSquare, 0xABCD);
        }
        
        playerTracker ++;
        stopRight2 = 1;
      }
    }
    else if((REG_DISPLAY_INPUT & RIGHT))
    {
      stopRight2 = 0;
    }
    for(int i = 0; i<9; i++)
    {
      sum += availableSquares[i];
    }
    if(sum == 0)
    {
      for(int i = 0; i<9; i++)
        {
          availableSquares[i] = 1;
          player1Squares[i] = player2Squares[i] = 0;
        }
        drawRect(square1, 0x0ABC);
        drawRect(square2, 0x0ABC);
        drawRect(square3, 0x0ABC);
        drawRect(square0, 0x0ABC);
        drawRect(square4, 0x0ABC);
        drawRect(square5, 0x0ABC);
        drawRect(square6, 0x0ABC);
        drawRect(square7, 0x0ABC);
        drawRect(square8, 0x0ABC);
          
    }
    sum = 0;
    
  }
}