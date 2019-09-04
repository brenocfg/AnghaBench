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
typedef  int /*<<< orphan*/  GLushort ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int /*<<< orphan*/  GLshort ;
typedef  int GLint ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  int GLenum ;
typedef  int /*<<< orphan*/  GLbyte ;

/* Variables and functions */
#define  GL_BITMAP 135 
#define  GL_BYTE 134 
#define  GL_FLOAT 133 
#define  GL_INT 132 
#define  GL_SHORT 131 
#define  GL_UNSIGNED_BYTE 130 
#define  GL_UNSIGNED_INT 129 
#define  GL_UNSIGNED_SHORT 128 

GLint gl_sizeof_type( GLenum type )
{
   switch (type) {
      case GL_BITMAP:
	 return 0;
      case GL_UNSIGNED_BYTE:
         return sizeof(GLubyte);
      case GL_BYTE:
	 return sizeof(GLbyte);
      case GL_UNSIGNED_SHORT:
	 return sizeof(GLushort);
      case GL_SHORT:
	 return sizeof(GLshort);
      case GL_UNSIGNED_INT:
	 return sizeof(GLuint);
      case GL_INT:
	 return sizeof(GLint);
      case GL_FLOAT:
	 return sizeof(GLfloat);
      default:
         return -1;
   }
}