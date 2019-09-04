#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_25__ {int Uorder; int Vorder; scalar_t__* Points; void* Retain; scalar_t__ v2; scalar_t__ v1; scalar_t__ u2; scalar_t__ u1; } ;
struct TYPE_24__ {int Uorder; int Vorder; scalar_t__* Points; void* Retain; scalar_t__ v2; scalar_t__ v1; scalar_t__ u2; scalar_t__ u1; } ;
struct TYPE_23__ {int Uorder; int Vorder; scalar_t__* Points; void* Retain; scalar_t__ v2; scalar_t__ v1; scalar_t__ u2; scalar_t__ u1; } ;
struct TYPE_22__ {int Uorder; int Vorder; scalar_t__* Points; void* Retain; scalar_t__ v2; scalar_t__ v1; scalar_t__ u2; scalar_t__ u1; } ;
struct TYPE_21__ {int Uorder; int Vorder; scalar_t__* Points; void* Retain; scalar_t__ v2; scalar_t__ v1; scalar_t__ u2; scalar_t__ u1; } ;
struct TYPE_20__ {int Uorder; int Vorder; scalar_t__* Points; void* Retain; scalar_t__ v2; scalar_t__ v1; scalar_t__ u2; scalar_t__ u1; } ;
struct TYPE_19__ {int Uorder; int Vorder; scalar_t__* Points; void* Retain; scalar_t__ v2; scalar_t__ v1; scalar_t__ u2; scalar_t__ u1; } ;
struct TYPE_18__ {int Uorder; int Vorder; scalar_t__* Points; void* Retain; scalar_t__ v2; scalar_t__ v1; scalar_t__ u2; scalar_t__ u1; } ;
struct TYPE_17__ {int Uorder; int Vorder; scalar_t__* Points; void* Retain; scalar_t__ v2; scalar_t__ v1; scalar_t__ u2; scalar_t__ u1; } ;
struct TYPE_15__ {TYPE_9__ Map2Texture4; TYPE_8__ Map2Texture3; TYPE_7__ Map2Texture2; TYPE_6__ Map2Texture1; TYPE_5__ Map2Normal; TYPE_4__ Map2Color4; TYPE_3__ Map2Index; TYPE_2__ Map2Vertex4; TYPE_1__ Map2Vertex3; } ;
struct TYPE_16__ {TYPE_10__ EvalMap; } ;
typedef  scalar_t__ GLuint ;
typedef  int GLint ;
typedef  scalar_t__ GLfloat ;
typedef  int GLenum ;
typedef  TYPE_11__ GLcontext ;
typedef  void* GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 int /*<<< orphan*/  GL_INVALID_VALUE ; 
#define  GL_MAP2_COLOR_4 136 
#define  GL_MAP2_INDEX 135 
#define  GL_MAP2_NORMAL 134 
#define  GL_MAP2_TEXTURE_COORD_1 133 
#define  GL_MAP2_TEXTURE_COORD_2 132 
#define  GL_MAP2_TEXTURE_COORD_3 131 
#define  GL_MAP2_TEXTURE_COORD_4 130 
#define  GL_MAP2_VERTEX_3 129 
#define  GL_MAP2_VERTEX_4 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_11__*) ; 
 int MAX_EVAL_ORDER ; 
 scalar_t__ components (int) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_11__*,int /*<<< orphan*/ ,char*) ; 

void gl_Map2f( GLcontext* ctx, GLenum target,
	      GLfloat u1, GLfloat u2, GLint ustride, GLint uorder,
	      GLfloat v1, GLfloat v2, GLint vstride, GLint vorder,
	      const GLfloat *points, GLboolean retain )
{
   GLuint k;

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glMap2" );
      return;
   }

   if (u1==u2) {
      gl_error( ctx, GL_INVALID_VALUE, "glMap2(u1,u2)" );
      return;
   }

   if (v1==v2) {
      gl_error( ctx, GL_INVALID_VALUE, "glMap2(v1,v2)" );
      return;
   }

   if (uorder<1 || uorder>MAX_EVAL_ORDER) {
      gl_error( ctx, GL_INVALID_VALUE, "glMap2(uorder)" );
      return;
   }

   if (vorder<1 || vorder>MAX_EVAL_ORDER) {
      gl_error( ctx, GL_INVALID_VALUE, "glMap2(vorder)" );
      return;
   }

   k = components( target );
   if (k==0) {
      gl_error( ctx, GL_INVALID_ENUM, "glMap2(target)" );
   }

   if (ustride < k) {
      gl_error( ctx, GL_INVALID_VALUE, "glMap2(ustride)" );
      return;
   }
   if (vstride < k) {
      gl_error( ctx, GL_INVALID_VALUE, "glMap2(vstride)" );
      return;
   }

   switch (target) {
      case GL_MAP2_VERTEX_3:
         ctx->EvalMap.Map2Vertex3.Uorder = uorder;
	 ctx->EvalMap.Map2Vertex3.u1 = u1;
	 ctx->EvalMap.Map2Vertex3.u2 = u2;
         ctx->EvalMap.Map2Vertex3.Vorder = vorder;
	 ctx->EvalMap.Map2Vertex3.v1 = v1;
	 ctx->EvalMap.Map2Vertex3.v2 = v2;
	 if (ctx->EvalMap.Map2Vertex3.Points
             && !ctx->EvalMap.Map2Vertex3.Retain) {
	    free( ctx->EvalMap.Map2Vertex3.Points );
	 }
	 ctx->EvalMap.Map2Vertex3.Retain = retain;
	 ctx->EvalMap.Map2Vertex3.Points = (GLfloat *) points;
	 break;
      case GL_MAP2_VERTEX_4:
         ctx->EvalMap.Map2Vertex4.Uorder = uorder;
	 ctx->EvalMap.Map2Vertex4.u1 = u1;
	 ctx->EvalMap.Map2Vertex4.u2 = u2;
         ctx->EvalMap.Map2Vertex4.Vorder = vorder;
	 ctx->EvalMap.Map2Vertex4.v1 = v1;
	 ctx->EvalMap.Map2Vertex4.v2 = v2;
	 if (ctx->EvalMap.Map2Vertex4.Points
             && !ctx->EvalMap.Map2Vertex4.Retain) {
	    free( ctx->EvalMap.Map2Vertex4.Points );
	 }
	 ctx->EvalMap.Map2Vertex4.Points = (GLfloat *) points;
	 ctx->EvalMap.Map2Vertex4.Retain = retain;
	 break;
      case GL_MAP2_INDEX:
         ctx->EvalMap.Map2Index.Uorder = uorder;
	 ctx->EvalMap.Map2Index.u1 = u1;
	 ctx->EvalMap.Map2Index.u2 = u2;
         ctx->EvalMap.Map2Index.Vorder = vorder;
	 ctx->EvalMap.Map2Index.v1 = v1;
	 ctx->EvalMap.Map2Index.v2 = v2;
	 if (ctx->EvalMap.Map2Index.Points
             && !ctx->EvalMap.Map2Index.Retain) {
	    free( ctx->EvalMap.Map2Index.Points );
	 }
	 ctx->EvalMap.Map2Index.Retain = retain;
	 ctx->EvalMap.Map2Index.Points = (GLfloat *) points;
	 break;
      case GL_MAP2_COLOR_4:
         ctx->EvalMap.Map2Color4.Uorder = uorder;
	 ctx->EvalMap.Map2Color4.u1 = u1;
	 ctx->EvalMap.Map2Color4.u2 = u2;
         ctx->EvalMap.Map2Color4.Vorder = vorder;
	 ctx->EvalMap.Map2Color4.v1 = v1;
	 ctx->EvalMap.Map2Color4.v2 = v2;
	 if (ctx->EvalMap.Map2Color4.Points
             && !ctx->EvalMap.Map2Color4.Retain) {
	    free( ctx->EvalMap.Map2Color4.Points );
	 }
	 ctx->EvalMap.Map2Color4.Retain = retain;
	 ctx->EvalMap.Map2Color4.Points = (GLfloat *) points;
	 break;
      case GL_MAP2_NORMAL:
         ctx->EvalMap.Map2Normal.Uorder = uorder;
	 ctx->EvalMap.Map2Normal.u1 = u1;
	 ctx->EvalMap.Map2Normal.u2 = u2;
         ctx->EvalMap.Map2Normal.Vorder = vorder;
	 ctx->EvalMap.Map2Normal.v1 = v1;
	 ctx->EvalMap.Map2Normal.v2 = v2;
	 if (ctx->EvalMap.Map2Normal.Points
             && !ctx->EvalMap.Map2Normal.Retain) {
	    free( ctx->EvalMap.Map2Normal.Points );
	 }
	 ctx->EvalMap.Map2Normal.Retain = retain;
	 ctx->EvalMap.Map2Normal.Points = (GLfloat *) points;
	 break;
      case GL_MAP2_TEXTURE_COORD_1:
         ctx->EvalMap.Map2Texture1.Uorder = uorder;
	 ctx->EvalMap.Map2Texture1.u1 = u1;
	 ctx->EvalMap.Map2Texture1.u2 = u2;
         ctx->EvalMap.Map2Texture1.Vorder = vorder;
	 ctx->EvalMap.Map2Texture1.v1 = v1;
	 ctx->EvalMap.Map2Texture1.v2 = v2;
	 if (ctx->EvalMap.Map2Texture1.Points
             && !ctx->EvalMap.Map2Texture1.Retain) {
	    free( ctx->EvalMap.Map2Texture1.Points );
	 }
	 ctx->EvalMap.Map2Texture1.Retain = retain;
	 ctx->EvalMap.Map2Texture1.Points = (GLfloat *) points;
	 break;
      case GL_MAP2_TEXTURE_COORD_2:
         ctx->EvalMap.Map2Texture2.Uorder = uorder;
	 ctx->EvalMap.Map2Texture2.u1 = u1;
	 ctx->EvalMap.Map2Texture2.u2 = u2;
         ctx->EvalMap.Map2Texture2.Vorder = vorder;
	 ctx->EvalMap.Map2Texture2.v1 = v1;
	 ctx->EvalMap.Map2Texture2.v2 = v2;
	 if (ctx->EvalMap.Map2Texture2.Points
             && !ctx->EvalMap.Map2Texture2.Retain) {
	    free( ctx->EvalMap.Map2Texture2.Points );
	 }
	 ctx->EvalMap.Map2Texture2.Retain = retain;
	 ctx->EvalMap.Map2Texture2.Points = (GLfloat *) points;
	 break;
      case GL_MAP2_TEXTURE_COORD_3:
         ctx->EvalMap.Map2Texture3.Uorder = uorder;
	 ctx->EvalMap.Map2Texture3.u1 = u1;
	 ctx->EvalMap.Map2Texture3.u2 = u2;
         ctx->EvalMap.Map2Texture3.Vorder = vorder;
	 ctx->EvalMap.Map2Texture3.v1 = v1;
	 ctx->EvalMap.Map2Texture3.v2 = v2;
	 if (ctx->EvalMap.Map2Texture3.Points
             && !ctx->EvalMap.Map2Texture3.Retain) {
	    free( ctx->EvalMap.Map2Texture3.Points );
	 }
	 ctx->EvalMap.Map2Texture3.Retain = retain;
	 ctx->EvalMap.Map2Texture3.Points = (GLfloat *) points;
	 break;
      case GL_MAP2_TEXTURE_COORD_4:
         ctx->EvalMap.Map2Texture4.Uorder = uorder;
	 ctx->EvalMap.Map2Texture4.u1 = u1;
	 ctx->EvalMap.Map2Texture4.u2 = u2;
         ctx->EvalMap.Map2Texture4.Vorder = vorder;
	 ctx->EvalMap.Map2Texture4.v1 = v1;
	 ctx->EvalMap.Map2Texture4.v2 = v2;
	 if (ctx->EvalMap.Map2Texture4.Points
             && !ctx->EvalMap.Map2Texture4.Retain) {
	    free( ctx->EvalMap.Map2Texture4.Points );
	 }
	 ctx->EvalMap.Map2Texture4.Retain = retain;
	 ctx->EvalMap.Map2Texture4.Points = (GLfloat *) points;
	 break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glMap2(target)" );
   }
}