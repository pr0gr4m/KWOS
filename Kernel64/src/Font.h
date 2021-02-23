#ifndef __FONT_H__
#define __FONT_H__

#define FONT_ENGLISHWIDTH	8
#define FONT_ENGLISHHEIGHT	16

#define FONT_HANGULWIDTH	16
#define FONT_HANGULHEIGHT	16

#define FONT_BAKE_WIDTH 512
#define FONT_BAKE_HEIGHT 512
#include "stb/stb_truetype.h"
typedef struct{
 stbtt_fontinfo*stb_font;
 stbtt_bakedchar*baked;
 int baked_width;
 unsigned char*baked_pixels;
}Font;
extern unsigned char g_vucEnglishFont[];
extern unsigned short g_vusHangulFont[];
extern Font g_fontSystemDefault_0;
extern void kInitializeFont(Font*font,float font_height,char*path);

#endif
