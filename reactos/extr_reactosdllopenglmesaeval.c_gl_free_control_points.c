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
struct gl_2d_map {void* Retain; int /*<<< orphan*/ * Points; } ;
struct gl_1d_map {void* Retain; int /*<<< orphan*/ * Points; } ;
struct TYPE_5__ {struct gl_2d_map Map2Texture4; struct gl_2d_map Map2Texture3; struct gl_2d_map Map2Texture2; struct gl_2d_map Map2Texture1; struct gl_2d_map Map2Normal; struct gl_2d_map Map2Color4; struct gl_2d_map Map2Index; struct gl_2d_map Map2Vertex4; struct gl_2d_map Map2Vertex3; struct gl_1d_map Map1Texture4; struct gl_1d_map Map1Texture3; struct gl_1d_map Map1Texture2; struct gl_1d_map Map1Texture1; struct gl_1d_map Map1Normal; struct gl_1d_map Map1Color4; struct gl_1d_map Map1Index; struct gl_1d_map Map1Vertex4; struct gl_1d_map Map1Vertex3; } ;
struct TYPE_6__ {TYPE_1__ EvalMap; } ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  int GLenum ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 void* GL_FALSE ; 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
#define  GL_MAP1_COLOR_4 145 
#define  GL_MAP1_INDEX 144 
#define  GL_MAP1_NORMAL 143 
#define  GL_MAP1_TEXTURE_COORD_1 142 
#define  GL_MAP1_TEXTURE_COORD_2 141 
#define  GL_MAP1_TEXTURE_COORD_3 140 
#define  GL_MAP1_TEXTURE_COORD_4 139 
#define  GL_MAP1_VERTEX_3 138 
#define  GL_MAP1_VERTEX_4 137 
#define  GL_MAP2_COLOR_4 136 
#define  GL_MAP2_INDEX 135 
#define  GL_MAP2_NORMAL 134 
#define  GL_MAP2_TEXTURE_COORD_1 133 
#define  GL_MAP2_TEXTURE_COORD_2 132 
#define  GL_MAP2_TEXTURE_COORD_3 131 
#define  GL_MAP2_TEXTURE_COORD_4 130 
#define  GL_MAP2_VERTEX_3 129 
#define  GL_MAP2_VERTEX_4 128 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_free_control_points( GLcontext* ctx, GLenum target, GLfloat *data )
{
   struct gl_1d_map *map1 = NULL;
   struct gl_2d_map *map2 = NULL;

   switch (target) {
      case GL_MAP1_VERTEX_3:
         map1 = &ctx->EvalMap.Map1Vertex3;
         break;
      case GL_MAP1_VERTEX_4:
         map1 = &ctx->EvalMap.Map1Vertex4;
	 break;
      case GL_MAP1_INDEX:
         map1 = &ctx->EvalMap.Map1Index;
         break;
      case GL_MAP1_COLOR_4:
         map1 = &ctx->EvalMap.Map1Color4;
         break;
      case GL_MAP1_NORMAL:
         map1 = &ctx->EvalMap.Map1Normal;
	 break;
      case GL_MAP1_TEXTURE_COORD_1:
         map1 = &ctx->EvalMap.Map1Texture1;
	 break;
      case GL_MAP1_TEXTURE_COORD_2:
         map1 = &ctx->EvalMap.Map1Texture2;
	 break;
      case GL_MAP1_TEXTURE_COORD_3:
         map1 = &ctx->EvalMap.Map1Texture3;
	 break;
      case GL_MAP1_TEXTURE_COORD_4:
         map1 = &ctx->EvalMap.Map1Texture4;
	 break;
      case GL_MAP2_VERTEX_3:
         map2 = &ctx->EvalMap.Map2Vertex3;
	 break;
      case GL_MAP2_VERTEX_4:
         map2 = &ctx->EvalMap.Map2Vertex4;
	 break;
      case GL_MAP2_INDEX:
         map2 = &ctx->EvalMap.Map2Index;
	 break;
      case GL_MAP2_COLOR_4:
         map2 = &ctx->EvalMap.Map2Color4;
         break;
      case GL_MAP2_NORMAL:
         map2 = &ctx->EvalMap.Map2Normal;
	 break;
      case GL_MAP2_TEXTURE_COORD_1:
         map2 = &ctx->EvalMap.Map2Texture1;
	 break;
      case GL_MAP2_TEXTURE_COORD_2:
         map2 = &ctx->EvalMap.Map2Texture2;
	 break;
      case GL_MAP2_TEXTURE_COORD_3:
         map2 = &ctx->EvalMap.Map2Texture3;
	 break;
      case GL_MAP2_TEXTURE_COORD_4:
         map2 = &ctx->EvalMap.Map2Texture4;
	 break;
      default:
	 gl_error( ctx, GL_INVALID_ENUM, "gl_free_control_points" );
         return;
   }

   if (map1) {
      if (data==map1->Points) {
         /* The control points in the display list are currently */
         /* being used so we can mark them as discard-able. */
         map1->Retain = GL_FALSE;
      }
      else {
         /* The control points in the display list are not currently */
         /* being used. */
         free( data );
      }
   }
   if (map2) {
      if (data==map2->Points) {
         /* The control points in the display list are currently */
         /* being used so we can mark them as discard-able. */
         map2->Retain = GL_FALSE;
      }
      else {
         /* The control points in the display list are not currently */
         /* being used. */
         free( data );
      }
   }

}