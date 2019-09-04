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
typedef  int /*<<< orphan*/  GLvoid ;
typedef  int /*<<< orphan*/  GLushort ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  scalar_t__ GLsizei ;
typedef  scalar_t__ GLint ;
typedef  int GLenum ;
typedef  int /*<<< orphan*/  GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 int /*<<< orphan*/  GL_INVALID_VALUE ; 
#define  GL_LINES 140 
#define  GL_LINE_LOOP 139 
#define  GL_LINE_STRIP 138 
#define  GL_POINTS 137 
#define  GL_POLYGON 136 
#define  GL_QUADS 135 
#define  GL_QUAD_STRIP 134 
#define  GL_TRIANGLES 133 
#define  GL_TRIANGLE_FAN 132 
#define  GL_TRIANGLE_STRIP 131 
#define  GL_UNSIGNED_BYTE 130 
#define  GL_UNSIGNED_INT 129 
#define  GL_UNSIGNED_SHORT 128 
 scalar_t__ INSIDE_BEGIN_END (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_ArrayElement (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  gl_Begin (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gl_End (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void gl_DrawElements( GLcontext *ctx,
                      GLenum mode, GLsizei count,
                      GLenum type, const GLvoid *indices )
{
   
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glDrawElements" );
      return;
   }
   if (count<0) {
      gl_error( ctx, GL_INVALID_VALUE, "glDrawElements(count)" );
      return;
   }
   switch (mode) {
      case GL_POINTS:
      case GL_LINES:
      case GL_LINE_STRIP:
      case GL_LINE_LOOP:
      case GL_TRIANGLES:
      case GL_TRIANGLE_STRIP:
      case GL_TRIANGLE_FAN:
      case GL_QUADS:
      case GL_QUAD_STRIP:
      case GL_POLYGON:
         /* OK */
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glDrawArrays(mode)" );
         return;
   }
   switch (type) {
      case GL_UNSIGNED_BYTE:
         {
            GLubyte *ub_indices = (GLubyte *) indices;
            GLint i;
            gl_Begin( ctx, mode );
            for (i=0;i<count;i++) {
               gl_ArrayElement( ctx, (GLint) ub_indices[i] );
            }
            gl_End( ctx );
         }
         break;
      case GL_UNSIGNED_SHORT:
         {
            GLushort *us_indices = (GLushort *) indices;
            GLint i;
            gl_Begin( ctx, mode );
            for (i=0;i<count;i++) {
               gl_ArrayElement( ctx, (GLint) us_indices[i] );
            }
            gl_End( ctx );
         }
         break;
      case GL_UNSIGNED_INT:
         {
            GLuint *ui_indices = (GLuint *) indices;
            GLint i;
            gl_Begin( ctx, mode );
            for (i=0;i<count;i++) {
               gl_ArrayElement( ctx, (GLint) ui_indices[i] );
            }
            gl_End( ctx );
         }
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glDrawElements(type)" );
         return;
   }
}