#include "Font.h"
#include "FileSystem.h"
#include "DynamicMemory.h"
#include "Utility.h"
#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_ifloor(x)   ((int) floor(x))
#define STBTT_iceil(x)    ((int) ceil(x))
#define STBTT_sqrt(x)      sqrt(x)
#define STBTT_pow(x,y)     pow(x,y)
#define STBTT_fmod(x,y)    fmod(x,y)
#define STBTT_cos(x)       cos(x)
#define STBTT_acos(x)      acos(x)
#define STBTT_fabs(x)      fabs(x)
#define STBTT_malloc(x,u)  ((void)(u),kAllocateMemory(x))
#define STBTT_free(x,u)    ((void)(u),kFreeMemory(x))
#define STBTT_assert(x)    ((void)(x))
#define STBTT_strlen    kStrLen
#define STBTT_memcpy    kMemCpy
#define STBTT_memset    kMemSet
#include "stb/stb_truetype.h"
void kInitializeFont(Font*font,float font_height,char*path){
 FILE*fp;
 size_t size;
 BYTE*font_buffer;
 BYTE*pixels;
 kMemSet(font,0,sizeof(*font));
 fp=0;
 font_buffer=0;
 pixels=0;
 if(!font->stb_font){
  if(path){
   fp=fopen(path,"rb");
   if(!fp){
    goto clean;
   }
   fseek(fp,0,SEEK_END);
   size=ftell(fp);
   font_buffer=kAllocateMemory(size);
   fread(font_buffer,size,1,fp);
   fclose(fp);
   fp=0;
   if(!stbtt_InitFont(font->stb_font,font_buffer,0)){
    goto clean;
   }
  }else{
   goto clean;
  }
 }
 font->baked=kAllocateMemory(sizeof(stbtt_bakedchar)*65);
 if(!font->baked){
  goto clean;
 }
 pixels=kAllocateMemory(FONT_BAKE_WIDTH*FONT_BAKE_HEIGHT);
 if(!pixels){
  goto clean;
 }
 stbtt_BakeFontBitmap(font_buffer,0,font_height,pixels,FONT_BAKE_WIDTH,FONT_BAKE_HEIGHT,32,96,font->baked);
 font->baked_pixels=pixels;
 font->baked_width=FONT_BAKE_WIDTH;
clean:
 if(fp){
  fclose(fp);
 }
 if(font_buffer){
  kFreeMemory(font_buffer);
 }
 if(font->baked){
  kFreeMemory(font->baked);
 }
}
