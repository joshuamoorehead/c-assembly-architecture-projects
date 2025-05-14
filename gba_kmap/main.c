//GBA Project 1

//240x160
//ARM7tdmi 16.78MHz

//Thumb Instructions 16 bits
//0bxrrrrrgggggbbbbb (16 bit color word)
//0x00000000 -> 0x00003fff (System ROM, exe but not read)
//0x02000000 -> 0x02020000 (External RAM, 256KB)
//0x03000000 -> 0x03007fff (Internal RAM, 32KB)
//0x04000000 -> 0x04003fff (I/O registers)
//0x05000000 -> 0x05003fff (Color Palette)
//0x06000000 -> 0x06017fff (VRAM 96 KB)
//0x07000000 -> 0x070003ff (OAM RAM)
//0x08000000 -> 0x???????? (Game Cart ROM (Up to 32MBs)
//0x0E000000 -> 0x???????? (Gamepak RAM)
#define REG_DISPLAY_VCOUNT (*(volatile unsigned short *) (0x04000006)) 

void sync()
{
  while(REG_DISPLAY_VCOUNT >= 160); //wait until out of vbuffer
  while(REG_DISPLAY_VCOUNT < 160); //wait until draw cycle is finished
}

int main()
{
  volatile unsigned char *ioram = (unsigned char *) 0x04000000;
  ioram[0] = 0x03; //set to video mode 3
  ioram[1] = 0x04; //enable that video mode
  
  volatile unsigned short *vram = (unsigned short *) 0x06000000;
  
  int inc = 0;
  int clearLine = 0;
  while(1)
  {
    sync();
    
    vram[clearLine * 240 + 110] = 0x0000;
    vram[clearLine * 240 + 120] = 0x0000;
    vram[clearLine * 240 + 130] = 0x0000;

    vram[inc * 240 + 110] = 0x001f;
    vram[inc * 240 + 120] = 0x03e0;
    vram[inc * 240 + 130] = 0x7c00;

    clearLine = inc;
    inc++;
    if(inc >= 160)
    {
      inc = 0;
    }
  }
}