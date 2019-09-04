#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int GLint ;

/* Variables and functions */
#define  GL_ALPHA 165 
#define  GL_ALPHA12 164 
#define  GL_ALPHA16 163 
#define  GL_ALPHA4 162 
#define  GL_ALPHA8 161 
#define  GL_INTENSITY 160 
#define  GL_INTENSITY12 159 
#define  GL_INTENSITY16 158 
#define  GL_INTENSITY4 157 
#define  GL_INTENSITY8 156 
#define  GL_LUMINANCE 155 
#define  GL_LUMINANCE12 154 
#define  GL_LUMINANCE12_ALPHA12 153 
#define  GL_LUMINANCE12_ALPHA4 152 
#define  GL_LUMINANCE16 151 
#define  GL_LUMINANCE16_ALPHA16 150 
#define  GL_LUMINANCE4 149 
#define  GL_LUMINANCE4_ALPHA4 148 
#define  GL_LUMINANCE6_ALPHA2 147 
#define  GL_LUMINANCE8 146 
#define  GL_LUMINANCE8_ALPHA8 145 
#define  GL_LUMINANCE_ALPHA 144 
#define  GL_R3_G3_B2 143 
#define  GL_RGB 142 
#define  GL_RGB10 141 
#define  GL_RGB10_A2 140 
#define  GL_RGB12 139 
#define  GL_RGB16 138 
#define  GL_RGB4 137 
#define  GL_RGB5 136 
#define  GL_RGB5_A1 135 
#define  GL_RGB8 134 
#define  GL_RGBA 133 
#define  GL_RGBA12 132 
#define  GL_RGBA16 131 
#define  GL_RGBA2 130 
#define  GL_RGBA4 129 
#define  GL_RGBA8 128 

__attribute__((used)) static GLint decode_internal_format( GLint format )
{
   switch (format) {
      case GL_ALPHA:
      case GL_ALPHA4:
      case GL_ALPHA8:
      case GL_ALPHA12:
      case GL_ALPHA16:
         return GL_ALPHA;
      case 1:
      case GL_LUMINANCE:
      case GL_LUMINANCE4:
      case GL_LUMINANCE8:
      case GL_LUMINANCE12:
      case GL_LUMINANCE16:
         return GL_LUMINANCE;
      case 2:
      case GL_LUMINANCE_ALPHA:
      case GL_LUMINANCE4_ALPHA4:
      case GL_LUMINANCE6_ALPHA2:
      case GL_LUMINANCE8_ALPHA8:
      case GL_LUMINANCE12_ALPHA4:
      case GL_LUMINANCE12_ALPHA12:
      case GL_LUMINANCE16_ALPHA16:
         return GL_LUMINANCE_ALPHA;
      case GL_INTENSITY:
      case GL_INTENSITY4:
      case GL_INTENSITY8:
      case GL_INTENSITY12:
      case GL_INTENSITY16:
         return GL_INTENSITY;
      case 3:
      case GL_RGB:
      case GL_R3_G3_B2:
      case GL_RGB4:
      case GL_RGB5:
      case GL_RGB8:
      case GL_RGB10:
      case GL_RGB12:
      case GL_RGB16:
         return GL_RGB;
      case 4:
      case GL_RGBA:
      case GL_RGBA2:
      case GL_RGBA4:
      case GL_RGB5_A1:
      case GL_RGBA8:
      case GL_RGB10_A2:
      case GL_RGBA12:
      case GL_RGBA16:
         return GL_RGBA;
      default:
         return -1;  /* error */
   }
}