#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * Buffer; } ;
struct TYPE_7__ {int /*<<< orphan*/ * EdgeFlagPtr; int /*<<< orphan*/ * TexCoordPtr; int /*<<< orphan*/ * IndexPtr; int /*<<< orphan*/ * ColorPtr; int /*<<< orphan*/ * NormalPtr; int /*<<< orphan*/ * VertexPtr; } ;
struct TYPE_8__ {TYPE_1__ Feedback; TYPE_2__ Array; } ;
typedef  int /*<<< orphan*/  GLvoid ;
typedef  int GLenum ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
#define  GL_COLOR_ARRAY_POINTER 134 
#define  GL_EDGE_FLAG_ARRAY_POINTER 133 
#define  GL_FEEDBACK_BUFFER_POINTER 132 
#define  GL_INDEX_ARRAY_POINTER 131 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
#define  GL_NORMAL_ARRAY_POINTER 130 
#define  GL_TEXTURE_COORD_ARRAY_POINTER 129 
#define  GL_VERTEX_ARRAY_POINTER 128 
 int /*<<< orphan*/  gl_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 

void gl_GetPointerv( GLcontext *ctx, GLenum pname, GLvoid **params )
{
   switch (pname) {
      case GL_VERTEX_ARRAY_POINTER:
         *params = ctx->Array.VertexPtr;
         break;
      case GL_NORMAL_ARRAY_POINTER:
         *params = ctx->Array.NormalPtr;
         break;
      case GL_COLOR_ARRAY_POINTER:
         *params = ctx->Array.ColorPtr;
         break;
      case GL_INDEX_ARRAY_POINTER:
         *params = ctx->Array.IndexPtr;
         break;
      case GL_TEXTURE_COORD_ARRAY_POINTER:
         *params = ctx->Array.TexCoordPtr;
         break;
      case GL_EDGE_FLAG_ARRAY_POINTER:
         *params = ctx->Array.EdgeFlagPtr;
         break;
      case GL_FEEDBACK_BUFFER_POINTER:
         *params = ctx->Feedback.Buffer;
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glGetPointerv" );
         return;
   }
}