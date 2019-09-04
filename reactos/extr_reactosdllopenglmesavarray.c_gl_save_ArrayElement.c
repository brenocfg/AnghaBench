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
struct TYPE_5__ {int NormalStrideB; int NormalType; int ColorStrideB; int ColorType; int IndexStrideB; int IndexType; int TexCoordStrideB; int TexCoordType; int EdgeFlagStrideB; int VertexStrideB; int VertexType; int /*<<< orphan*/  VertexSize; scalar_t__ VertexPtr; scalar_t__ VertexEnabled; scalar_t__ EdgeFlagPtr; scalar_t__ EdgeFlagEnabled; int /*<<< orphan*/  TexCoordSize; scalar_t__ TexCoordPtr; scalar_t__ TexCoordEnabled; scalar_t__ IndexPtr; scalar_t__ IndexEnabled; int /*<<< orphan*/  ColorSize; scalar_t__ ColorPtr; scalar_t__ ColorEnabled; scalar_t__ NormalPtr; scalar_t__ NormalEnabled; } ;
struct TYPE_6__ {TYPE_1__ Array; } ;
typedef  int /*<<< orphan*/  GLushort ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int /*<<< orphan*/  GLshort ;
typedef  int GLint ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  int /*<<< orphan*/  GLdouble ;
typedef  TYPE_2__ GLcontext ;
typedef  int /*<<< orphan*/  GLbyte ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
#define  GL_BYTE 135 
#define  GL_DOUBLE 134 
#define  GL_FLOAT 133 
#define  GL_INT 132 
#define  GL_SHORT 131 
#define  GL_UNSIGNED_BYTE 130 
#define  GL_UNSIGNED_INT 129 
#define  GL_UNSIGNED_SHORT 128 
 int /*<<< orphan*/  glColor3bv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glColor3dv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glColor3fv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glColor3iv (int*) ; 
 int /*<<< orphan*/  glColor3sv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glColor3ubv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glColor3uiv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glColor3usv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glColor4bv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glColor4dv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glColor4fv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glColor4iv (int*) ; 
 int /*<<< orphan*/  glColor4sv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glColor4ubv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glColor4uiv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glColor4usv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glEdgeFlagv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glIndexdv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glIndexfv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glIndexiv (int*) ; 
 int /*<<< orphan*/  glIndexsv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glNormal3bv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glNormal3dv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glNormal3fv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glNormal3iv (int*) ; 
 int /*<<< orphan*/  glNormal3sv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexCoord1dv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexCoord1fv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexCoord1iv (int*) ; 
 int /*<<< orphan*/  glTexCoord1sv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexCoord2dv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexCoord2fv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexCoord2iv (int*) ; 
 int /*<<< orphan*/  glTexCoord2sv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexCoord3dv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexCoord3fv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexCoord3iv (int*) ; 
 int /*<<< orphan*/  glTexCoord3sv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexCoord4dv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexCoord4fv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexCoord4iv (int*) ; 
 int /*<<< orphan*/  glTexCoord4sv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glVertex2dv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glVertex2fv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glVertex2iv (int*) ; 
 int /*<<< orphan*/  glVertex2sv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glVertex3dv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glVertex3fv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glVertex3iv (int*) ; 
 int /*<<< orphan*/  glVertex3sv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glVertex4dv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glVertex4fv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glVertex4iv (int*) ; 
 int /*<<< orphan*/  glVertex4sv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_problem (TYPE_2__*,char*) ; 

void gl_save_ArrayElement( GLcontext *ctx, GLint i )
{
   if (ctx->Array.NormalEnabled) {
      GLbyte *p = (GLbyte*) ctx->Array.NormalPtr
                  + i * ctx->Array.NormalStrideB;
      switch (ctx->Array.NormalType) {
         case GL_BYTE:
            glNormal3bv( (GLbyte*) p );
            break;
         case GL_SHORT:
            glNormal3sv( (GLshort*) p );
            break;
         case GL_INT:
            glNormal3iv( (GLint*) p );
            break;
         case GL_FLOAT:
            glNormal3fv( (GLfloat*) p );
            break;
         case GL_DOUBLE:
            glNormal3dv( (GLdouble*) p );
            break;
         default:
            gl_problem(ctx, "Bad normal type in gl_save_ArrayElement");
            return;
      }
   }

   if (ctx->Array.ColorEnabled) {
      GLbyte *p = (GLbyte*) ctx->Array.ColorPtr + i * ctx->Array.ColorStrideB;
      switch (ctx->Array.ColorType) {
         case GL_BYTE:
            switch (ctx->Array.ColorSize) {
               case 3:   glColor3bv( (GLbyte*) p );   break;
               case 4:   glColor4bv( (GLbyte*) p );   break;
            }
            break;
         case GL_UNSIGNED_BYTE:
            switch (ctx->Array.ColorSize) {
               case 3:   glColor3ubv( (GLubyte*) p );   break;
               case 4:   glColor4ubv( (GLubyte*) p );   break;
            }
            break;
         case GL_SHORT:
            switch (ctx->Array.ColorSize) {
               case 3:   glColor3sv( (GLshort*) p );   break;
               case 4:   glColor4sv( (GLshort*) p );   break;
            }
            break;
         case GL_UNSIGNED_SHORT:
            switch (ctx->Array.ColorSize) {
               case 3:   glColor3usv( (GLushort*) p );   break;
               case 4:   glColor4usv( (GLushort*) p );   break;
            }
            break;
         case GL_INT:
            switch (ctx->Array.ColorSize) {
               case 3:   glColor3iv( (GLint*) p );   break;
               case 4:   glColor4iv( (GLint*) p );   break;
            }
            break;
         case GL_UNSIGNED_INT:
            switch (ctx->Array.ColorSize) {
               case 3:   glColor3uiv( (GLuint*) p );   break;
               case 4:   glColor4uiv( (GLuint*) p );   break;
            }
            break;
         case GL_FLOAT:
            switch (ctx->Array.ColorSize) {
               case 3:   glColor3fv( (GLfloat*) p );   break;
               case 4:   glColor4fv( (GLfloat*) p );   break;
            }
            break;
         case GL_DOUBLE:
            switch (ctx->Array.ColorSize) {
               case 3:   glColor3dv( (GLdouble*) p );   break;
               case 4:   glColor4dv( (GLdouble*) p );   break;
            }
            break;
         default:
            gl_problem(ctx, "Bad color type in gl_save_ArrayElement");
            return;
      }
   }

   if (ctx->Array.IndexEnabled) {
      GLbyte *p = (GLbyte*) ctx->Array.IndexPtr + i * ctx->Array.IndexStrideB;
      switch (ctx->Array.IndexType) {
         case GL_SHORT:
            glIndexsv( (GLshort*) p );
            break;
         case GL_INT:
            glIndexiv( (GLint*) p );
            break;
         case GL_FLOAT:
            glIndexfv( (GLfloat*) p );
            break;
         case GL_DOUBLE:
            glIndexdv( (GLdouble*) p );
            break;
         default:
            gl_problem(ctx, "Bad index type in gl_save_ArrayElement");
            return;
      }
   }

   if (ctx->Array.TexCoordEnabled) {
      GLbyte *p = (GLbyte*) ctx->Array.TexCoordPtr
                  + i * ctx->Array.TexCoordStrideB;
      switch (ctx->Array.TexCoordType) {
         case GL_SHORT:
            switch (ctx->Array.TexCoordSize) {
               case 1:   glTexCoord1sv( (GLshort*) p );   break;
               case 2:   glTexCoord2sv( (GLshort*) p );   break;
               case 3:   glTexCoord3sv( (GLshort*) p );   break;
               case 4:   glTexCoord4sv( (GLshort*) p );   break;
            }
            break;
         case GL_INT:
            switch (ctx->Array.TexCoordSize) {
               case 1:   glTexCoord1iv( (GLint*) p );   break;
               case 2:   glTexCoord2iv( (GLint*) p );   break;
               case 3:   glTexCoord3iv( (GLint*) p );   break;
               case 4:   glTexCoord4iv( (GLint*) p );   break;
            }
            break;
         case GL_FLOAT:
            switch (ctx->Array.TexCoordSize) {
               case 1:   glTexCoord1fv( (GLfloat*) p );   break;
               case 2:   glTexCoord2fv( (GLfloat*) p );   break;
               case 3:   glTexCoord3fv( (GLfloat*) p );   break;
               case 4:   glTexCoord4fv( (GLfloat*) p );   break;
            }
            break;
         case GL_DOUBLE:
            switch (ctx->Array.TexCoordSize) {
               case 1:   glTexCoord1dv( (GLdouble*) p );   break;
               case 2:   glTexCoord2dv( (GLdouble*) p );   break;
               case 3:   glTexCoord3dv( (GLdouble*) p );   break;
               case 4:   glTexCoord4dv( (GLdouble*) p );   break;
            }
            break;
         default:
            gl_problem(ctx, "Bad texcoord type in gl_save_ArrayElement");
            return;
      }
   }

   if (ctx->Array.EdgeFlagEnabled) {
      GLbyte *b = (GLbyte*) ctx->Array.EdgeFlagPtr + i * ctx->Array.EdgeFlagStrideB;
      glEdgeFlagv( (GLboolean*) b );
   }

   if (ctx->Array.VertexEnabled) {
      GLbyte *b = (GLbyte*) ctx->Array.VertexPtr
                  + i * ctx->Array.VertexStrideB;
      switch (ctx->Array.VertexType) {
         case GL_SHORT:
            switch (ctx->Array.VertexSize) {
               case 2:   glVertex2sv( (GLshort*) b );   break;
               case 3:   glVertex3sv( (GLshort*) b );   break;
               case 4:   glVertex4sv( (GLshort*) b );   break;
            }
            break;
         case GL_INT:
            switch (ctx->Array.VertexSize) {
               case 2:   glVertex2iv( (GLint*) b );   break;
               case 3:   glVertex3iv( (GLint*) b );   break;
               case 4:   glVertex4iv( (GLint*) b );   break;
            }
            break;
         case GL_FLOAT:
            switch (ctx->Array.VertexSize) {
               case 2:   glVertex2fv( (GLfloat*) b );   break;
               case 3:   glVertex3fv( (GLfloat*) b );   break;
               case 4:   glVertex4fv( (GLfloat*) b );   break;
            }
            break;
         case GL_DOUBLE:
            switch (ctx->Array.VertexSize) {
               case 2:   glVertex2dv( (GLdouble*) b );   break;
               case 3:   glVertex3dv( (GLdouble*) b );   break;
               case 4:   glVertex4dv( (GLdouble*) b );   break;
            }
            break;
         default:
            gl_problem(ctx, "Bad vertex type in gl_save_ArrayElement");
            return;
      }
   }
}