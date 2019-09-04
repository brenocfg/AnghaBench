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
typedef  int GLenum ;

/* Variables and functions */
#define  GL_ALPHA 140 
#define  GL_BGRA_EXT 139 
#define  GL_BGR_EXT 138 
#define  GL_BLUE 137 
#define  GL_COLOR_INDEX 136 
#define  GL_DEPTH_COMPONENT 135 
#define  GL_GREEN 134 
#define  GL_LUMINANCE 133 
#define  GL_LUMINANCE_ALPHA 132 
#define  GL_RED 131 
#define  GL_RGB 130 
#define  GL_RGBA 129 
#define  GL_STENCIL_INDEX 128 

GLint gl_components_in_format( GLenum format )
{
   switch (format) {
      case GL_COLOR_INDEX:
      case GL_STENCIL_INDEX:
      case GL_DEPTH_COMPONENT:
      case GL_RED:
      case GL_GREEN:
      case GL_BLUE:
      case GL_ALPHA:
      case GL_LUMINANCE:
         return 1;
      case GL_LUMINANCE_ALPHA:
	 return 2;
      case GL_RGB:
      case GL_BGR_EXT:
	 return 3;
      case GL_RGBA:
      case GL_BGRA_EXT:
	 return 4;
      default:
         return -1;
   }
}