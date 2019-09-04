#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ColorSize; int ColorType; void* ColorPtr; scalar_t__ ColorStride; scalar_t__ ColorStrideB; } ;
struct TYPE_6__ {TYPE_1__ Array; } ;
typedef  int /*<<< orphan*/  GLvoid ;
typedef  int /*<<< orphan*/  GLushort ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  scalar_t__ GLsizei ;
typedef  int /*<<< orphan*/  GLshort ;
typedef  int GLint ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  int GLenum ;
typedef  int /*<<< orphan*/  GLdouble ;
typedef  TYPE_2__ GLcontext ;
typedef  int /*<<< orphan*/  GLbyte ;

/* Variables and functions */
#define  GL_BYTE 135 
#define  GL_DOUBLE 134 
#define  GL_FLOAT 133 
#define  GL_INT 132 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_VALUE ; 
#define  GL_SHORT 131 
#define  GL_UNSIGNED_BYTE 130 
#define  GL_UNSIGNED_INT 129 
#define  GL_UNSIGNED_SHORT 128 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_ColorPointer( GLcontext *ctx,
                      GLint size, GLenum type, GLsizei stride,
                      const GLvoid *ptr )
{
   if (size<3 || size>4) {
      gl_error( ctx, GL_INVALID_VALUE, "glColorPointer(size)" );
      return;
   }
   if (stride<0) {
      gl_error( ctx, GL_INVALID_VALUE, "glColorPointer(stride)" );
      return;
   }
   switch (type) {
      case GL_BYTE:
         ctx->Array.ColorStrideB = stride ? stride : size*sizeof(GLbyte);
         break;
      case GL_UNSIGNED_BYTE:
         ctx->Array.ColorStrideB = stride ? stride : size*sizeof(GLubyte);
         break;
      case GL_SHORT:
         ctx->Array.ColorStrideB = stride ? stride : size*sizeof(GLshort);
         break;
      case GL_UNSIGNED_SHORT:
         ctx->Array.ColorStrideB = stride ? stride : size*sizeof(GLushort);
         break;
      case GL_INT:
         ctx->Array.ColorStrideB = stride ? stride : size*sizeof(GLint);
         break;
      case GL_UNSIGNED_INT:
         ctx->Array.ColorStrideB = stride ? stride : size*sizeof(GLuint);
         break;
      case GL_FLOAT:
         ctx->Array.ColorStrideB = stride ? stride : size*sizeof(GLfloat);
         break;
      case GL_DOUBLE:
         ctx->Array.ColorStrideB = stride ? stride : size*sizeof(GLdouble);
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glColorPointer(type)" );
         return;
   }
   ctx->Array.ColorSize = size;
   ctx->Array.ColorType = type;
   ctx->Array.ColorStride = stride;
   ctx->Array.ColorPtr = (void *) ptr;
}