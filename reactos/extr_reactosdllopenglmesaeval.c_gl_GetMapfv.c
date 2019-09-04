#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_9__ ;
typedef  struct TYPE_41__   TYPE_8__ ;
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_20__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_19__ ;
typedef  struct TYPE_31__   TYPE_18__ ;
typedef  struct TYPE_30__   TYPE_17__ ;
typedef  struct TYPE_29__   TYPE_16__ ;
typedef  struct TYPE_28__   TYPE_15__ ;
typedef  struct TYPE_27__   TYPE_14__ ;
typedef  struct TYPE_26__   TYPE_13__ ;
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
struct TYPE_42__ {int* Points; int Order; int u1; int u2; } ;
struct TYPE_41__ {int* Points; int Order; int u1; int u2; } ;
struct TYPE_40__ {int* Points; int Order; int u1; int u2; } ;
struct TYPE_39__ {int* Points; int Order; int u1; int u2; } ;
struct TYPE_38__ {int* Points; int Order; int u1; int u2; } ;
struct TYPE_37__ {int* Points; int Order; int u1; int u2; } ;
struct TYPE_36__ {int* Points; int Order; int u1; int u2; } ;
struct TYPE_35__ {int* Points; size_t Order; int u1; int u2; } ;
struct TYPE_31__ {int* Points; int Uorder; int Vorder; int u1; int u2; int v1; int v2; } ;
struct TYPE_30__ {int* Points; int Uorder; int Vorder; int u1; int u2; int v1; int v2; } ;
struct TYPE_29__ {int* Points; int Uorder; int Vorder; int u1; int u2; int v1; int v2; } ;
struct TYPE_28__ {int* Points; int Uorder; int Vorder; int u1; int u2; int v1; int v2; } ;
struct TYPE_27__ {int* Points; int Uorder; int Vorder; int u1; int u2; int v1; int v2; } ;
struct TYPE_26__ {int* Points; int Uorder; int Vorder; int u1; int u2; int v1; int v2; } ;
struct TYPE_25__ {int* Points; int Uorder; int Vorder; int u1; int u2; int v1; int v2; } ;
struct TYPE_24__ {int* Points; size_t Uorder; size_t Vorder; int u1; int u2; int v1; int v2; } ;
struct TYPE_23__ {int* Points; int Uorder; int Vorder; int u1; int u2; int v1; int v2; } ;
struct TYPE_33__ {int* Points; int Order; int u1; int u2; } ;
struct TYPE_32__ {TYPE_18__ Map2Vertex4; TYPE_17__ Map2Vertex3; TYPE_16__ Map2Texture4; TYPE_15__ Map2Texture3; TYPE_14__ Map2Texture2; TYPE_13__ Map2Texture1; TYPE_12__ Map2Normal; TYPE_11__ Map2Index; TYPE_10__ Map2Color4; TYPE_9__ Map1Vertex4; TYPE_8__ Map1Vertex3; TYPE_7__ Map1Texture4; TYPE_6__ Map1Texture3; TYPE_5__ Map1Texture2; TYPE_4__ Map1Texture1; TYPE_3__ Map1Normal; TYPE_2__ Map1Index; TYPE_1__ Map1Color4; } ;
struct TYPE_34__ {TYPE_19__ EvalMap; } ;
typedef  size_t GLuint ;
typedef  int GLfloat ;
typedef  int GLenum ;
typedef  TYPE_20__ GLcontext ;

/* Variables and functions */
#define  GL_COEFF 148 
#define  GL_DOMAIN 147 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
#define  GL_MAP1_COLOR_4 146 
#define  GL_MAP1_INDEX 145 
#define  GL_MAP1_NORMAL 144 
#define  GL_MAP1_TEXTURE_COORD_1 143 
#define  GL_MAP1_TEXTURE_COORD_2 142 
#define  GL_MAP1_TEXTURE_COORD_3 141 
#define  GL_MAP1_TEXTURE_COORD_4 140 
#define  GL_MAP1_VERTEX_3 139 
#define  GL_MAP1_VERTEX_4 138 
#define  GL_MAP2_COLOR_4 137 
#define  GL_MAP2_INDEX 136 
#define  GL_MAP2_NORMAL 135 
#define  GL_MAP2_TEXTURE_COORD_1 134 
#define  GL_MAP2_TEXTURE_COORD_2 133 
#define  GL_MAP2_TEXTURE_COORD_3 132 
#define  GL_MAP2_TEXTURE_COORD_4 131 
#define  GL_MAP2_VERTEX_3 130 
#define  GL_MAP2_VERTEX_4 129 
#define  GL_ORDER 128 
 int /*<<< orphan*/  gl_error (TYPE_20__*,int /*<<< orphan*/ ,char*) ; 

void gl_GetMapfv( GLcontext* ctx, GLenum target, GLenum query, GLfloat *v )
{
   GLuint i, n;
   GLfloat *data;

   switch (query) {
      case GL_COEFF:
	 switch (target) {
	    case GL_MAP1_COLOR_4:
	       data = ctx->EvalMap.Map1Color4.Points;
	       n = ctx->EvalMap.Map1Color4.Order * 4;
	       break;
	    case GL_MAP1_INDEX:
	       data = ctx->EvalMap.Map1Index.Points;
	       n = ctx->EvalMap.Map1Index.Order;
	       break;
	    case GL_MAP1_NORMAL:
	       data = ctx->EvalMap.Map1Normal.Points;
	       n = ctx->EvalMap.Map1Normal.Order * 3;
	       break;
	    case GL_MAP1_TEXTURE_COORD_1:
	       data = ctx->EvalMap.Map1Texture1.Points;
	       n = ctx->EvalMap.Map1Texture1.Order * 1;
	       break;
	    case GL_MAP1_TEXTURE_COORD_2:
	       data = ctx->EvalMap.Map1Texture2.Points;
	       n = ctx->EvalMap.Map1Texture2.Order * 2;
	       break;
	    case GL_MAP1_TEXTURE_COORD_3:
	       data = ctx->EvalMap.Map1Texture3.Points;
	       n = ctx->EvalMap.Map1Texture3.Order * 3;
	       break;
	    case GL_MAP1_TEXTURE_COORD_4:
	       data = ctx->EvalMap.Map1Texture4.Points;
	       n = ctx->EvalMap.Map1Texture4.Order * 4;
	       break;
	    case GL_MAP1_VERTEX_3:
	       data = ctx->EvalMap.Map1Vertex3.Points;
	       n = ctx->EvalMap.Map1Vertex3.Order * 3;
	       break;
	    case GL_MAP1_VERTEX_4:
	       data = ctx->EvalMap.Map1Vertex4.Points;
	       n = ctx->EvalMap.Map1Vertex4.Order * 4;
	       break;
	    case GL_MAP2_COLOR_4:
	       data = ctx->EvalMap.Map2Color4.Points;
	       n = ctx->EvalMap.Map2Color4.Uorder
                 * ctx->EvalMap.Map2Color4.Vorder * 4;
	       break;
	    case GL_MAP2_INDEX:
	       data = ctx->EvalMap.Map2Index.Points;
	       n = ctx->EvalMap.Map2Index.Uorder
                 * ctx->EvalMap.Map2Index.Vorder;
	       break;
	    case GL_MAP2_NORMAL:
	       data = ctx->EvalMap.Map2Normal.Points;
	       n = ctx->EvalMap.Map2Normal.Uorder
                 * ctx->EvalMap.Map2Normal.Vorder * 3;
	       break;
	    case GL_MAP2_TEXTURE_COORD_1:
	       data = ctx->EvalMap.Map2Texture1.Points;
	       n = ctx->EvalMap.Map2Texture1.Uorder
                 * ctx->EvalMap.Map2Texture1.Vorder * 1;
	       break;
	    case GL_MAP2_TEXTURE_COORD_2:
	       data = ctx->EvalMap.Map2Texture2.Points;
	       n = ctx->EvalMap.Map2Texture2.Uorder
                 * ctx->EvalMap.Map2Texture2.Vorder * 2;
	       break;
	    case GL_MAP2_TEXTURE_COORD_3:
	       data = ctx->EvalMap.Map2Texture3.Points;
	       n = ctx->EvalMap.Map2Texture3.Uorder
                 * ctx->EvalMap.Map2Texture3.Vorder * 3;
	       break;
	    case GL_MAP2_TEXTURE_COORD_4:
	       data = ctx->EvalMap.Map2Texture4.Points;
	       n = ctx->EvalMap.Map2Texture4.Uorder
                 * ctx->EvalMap.Map2Texture4.Vorder * 4;
	       break;
	    case GL_MAP2_VERTEX_3:
	       data = ctx->EvalMap.Map2Vertex3.Points;
	       n = ctx->EvalMap.Map2Vertex3.Uorder
                 * ctx->EvalMap.Map2Vertex3.Vorder * 3;
	       break;
	    case GL_MAP2_VERTEX_4:
	       data = ctx->EvalMap.Map2Vertex4.Points;
	       n = ctx->EvalMap.Map2Vertex4.Uorder
                 * ctx->EvalMap.Map2Vertex4.Vorder * 4;
	       break;
	    default:
	       gl_error( ctx, GL_INVALID_ENUM, "glGetMapfv(target)" );
	 }
	 if (data) {
	    for (i=0;i<n;i++) {
	       v[i] = data[i];
	    }
	 }
         break;
      case GL_ORDER:
	 switch (target) {
	    case GL_MAP1_COLOR_4:
	       *v = ctx->EvalMap.Map1Color4.Order;
	       break;
	    case GL_MAP1_INDEX:
	       *v = ctx->EvalMap.Map1Index.Order;
	       break;
	    case GL_MAP1_NORMAL:
	       *v = ctx->EvalMap.Map1Normal.Order;
	       break;
	    case GL_MAP1_TEXTURE_COORD_1:
	       *v = ctx->EvalMap.Map1Texture1.Order;
	       break;
	    case GL_MAP1_TEXTURE_COORD_2:
	       *v = ctx->EvalMap.Map1Texture2.Order;
	       break;
	    case GL_MAP1_TEXTURE_COORD_3:
	       *v = ctx->EvalMap.Map1Texture3.Order;
	       break;
	    case GL_MAP1_TEXTURE_COORD_4:
	       *v = ctx->EvalMap.Map1Texture4.Order;
	       break;
	    case GL_MAP1_VERTEX_3:
	       *v = ctx->EvalMap.Map1Vertex3.Order;
	       break;
	    case GL_MAP1_VERTEX_4:
	       *v = ctx->EvalMap.Map1Vertex4.Order;
	       break;
	    case GL_MAP2_COLOR_4:
	       v[0] = ctx->EvalMap.Map2Color4.Uorder;
	       v[1] = ctx->EvalMap.Map2Color4.Vorder;
	       break;
	    case GL_MAP2_INDEX:
	       v[0] = ctx->EvalMap.Map2Index.Uorder;
	       v[1] = ctx->EvalMap.Map2Index.Vorder;
	       break;
	    case GL_MAP2_NORMAL:
	       v[0] = ctx->EvalMap.Map2Normal.Uorder;
	       v[1] = ctx->EvalMap.Map2Normal.Vorder;
	       break;
	    case GL_MAP2_TEXTURE_COORD_1:
	       v[0] = ctx->EvalMap.Map2Texture1.Uorder;
	       v[1] = ctx->EvalMap.Map2Texture1.Vorder;
	       break;
	    case GL_MAP2_TEXTURE_COORD_2:
	       v[0] = ctx->EvalMap.Map2Texture2.Uorder;
	       v[1] = ctx->EvalMap.Map2Texture2.Vorder;
	       break;
	    case GL_MAP2_TEXTURE_COORD_3:
	       v[0] = ctx->EvalMap.Map2Texture3.Uorder;
	       v[1] = ctx->EvalMap.Map2Texture3.Vorder;
	       break;
	    case GL_MAP2_TEXTURE_COORD_4:
	       v[0] = ctx->EvalMap.Map2Texture4.Uorder;
	       v[1] = ctx->EvalMap.Map2Texture4.Vorder;
	       break;
	    case GL_MAP2_VERTEX_3:
	       v[0] = ctx->EvalMap.Map2Vertex3.Uorder;
	       v[1] = ctx->EvalMap.Map2Vertex3.Vorder;
	       break;
	    case GL_MAP2_VERTEX_4:
	       v[0] = ctx->EvalMap.Map2Vertex4.Uorder;
	       v[1] = ctx->EvalMap.Map2Vertex4.Vorder;
	       break;
	    default:
	       gl_error( ctx, GL_INVALID_ENUM, "glGetMapfv(target)" );
	 }
         break;
      case GL_DOMAIN:
	 switch (target) {
	    case GL_MAP1_COLOR_4:
	       v[0] = ctx->EvalMap.Map1Color4.u1;
	       v[1] = ctx->EvalMap.Map1Color4.u2;
	       break;
	    case GL_MAP1_INDEX:
	       v[0] = ctx->EvalMap.Map1Index.u1;
	       v[1] = ctx->EvalMap.Map1Index.u2;
	       break;
	    case GL_MAP1_NORMAL:
	       v[0] = ctx->EvalMap.Map1Normal.u1;
	       v[1] = ctx->EvalMap.Map1Normal.u2;
	       break;
	    case GL_MAP1_TEXTURE_COORD_1:
	       v[0] = ctx->EvalMap.Map1Texture1.u1;
	       v[1] = ctx->EvalMap.Map1Texture1.u2;
	       break;
	    case GL_MAP1_TEXTURE_COORD_2:
	       v[0] = ctx->EvalMap.Map1Texture2.u1;
	       v[1] = ctx->EvalMap.Map1Texture2.u2;
	       break;
	    case GL_MAP1_TEXTURE_COORD_3:
	       v[0] = ctx->EvalMap.Map1Texture3.u1;
	       v[1] = ctx->EvalMap.Map1Texture3.u2;
	       break;
	    case GL_MAP1_TEXTURE_COORD_4:
	       v[0] = ctx->EvalMap.Map1Texture4.u1;
	       v[1] = ctx->EvalMap.Map1Texture4.u2;
	       break;
	    case GL_MAP1_VERTEX_3:
	       v[0] = ctx->EvalMap.Map1Vertex3.u1;
	       v[1] = ctx->EvalMap.Map1Vertex3.u2;
	       break;
	    case GL_MAP1_VERTEX_4:
	       v[0] = ctx->EvalMap.Map1Vertex4.u1;
	       v[1] = ctx->EvalMap.Map1Vertex4.u2;
	       break;
	    case GL_MAP2_COLOR_4:
	       v[0] = ctx->EvalMap.Map2Color4.u1;
	       v[1] = ctx->EvalMap.Map2Color4.u2;
	       v[2] = ctx->EvalMap.Map2Color4.v1;
	       v[3] = ctx->EvalMap.Map2Color4.v2;
	       break;
	    case GL_MAP2_INDEX:
	       v[0] = ctx->EvalMap.Map2Index.u1;
	       v[1] = ctx->EvalMap.Map2Index.u2;
	       v[2] = ctx->EvalMap.Map2Index.v1;
	       v[3] = ctx->EvalMap.Map2Index.v2;
	       break;
	    case GL_MAP2_NORMAL:
	       v[0] = ctx->EvalMap.Map2Normal.u1;
	       v[1] = ctx->EvalMap.Map2Normal.u2;
	       v[2] = ctx->EvalMap.Map2Normal.v1;
	       v[3] = ctx->EvalMap.Map2Normal.v2;
	       break;
	    case GL_MAP2_TEXTURE_COORD_1:
	       v[0] = ctx->EvalMap.Map2Texture1.u1;
	       v[1] = ctx->EvalMap.Map2Texture1.u2;
	       v[2] = ctx->EvalMap.Map2Texture1.v1;
	       v[3] = ctx->EvalMap.Map2Texture1.v2;
	       break;
	    case GL_MAP2_TEXTURE_COORD_2:
	       v[0] = ctx->EvalMap.Map2Texture2.u1;
	       v[1] = ctx->EvalMap.Map2Texture2.u2;
	       v[2] = ctx->EvalMap.Map2Texture2.v1;
	       v[3] = ctx->EvalMap.Map2Texture2.v2;
	       break;
	    case GL_MAP2_TEXTURE_COORD_3:
	       v[0] = ctx->EvalMap.Map2Texture3.u1;
	       v[1] = ctx->EvalMap.Map2Texture3.u2;
	       v[2] = ctx->EvalMap.Map2Texture3.v1;
	       v[3] = ctx->EvalMap.Map2Texture3.v2;
	       break;
	    case GL_MAP2_TEXTURE_COORD_4:
	       v[0] = ctx->EvalMap.Map2Texture4.u1;
	       v[1] = ctx->EvalMap.Map2Texture4.u2;
	       v[2] = ctx->EvalMap.Map2Texture4.v1;
	       v[3] = ctx->EvalMap.Map2Texture4.v2;
	       break;
	    case GL_MAP2_VERTEX_3:
	       v[0] = ctx->EvalMap.Map2Vertex3.u1;
	       v[1] = ctx->EvalMap.Map2Vertex3.u2;
	       v[2] = ctx->EvalMap.Map2Vertex3.v1;
	       v[3] = ctx->EvalMap.Map2Vertex3.v2;
	       break;
	    case GL_MAP2_VERTEX_4:
	       v[0] = ctx->EvalMap.Map2Vertex4.u1;
	       v[1] = ctx->EvalMap.Map2Vertex4.u2;
	       v[2] = ctx->EvalMap.Map2Vertex4.v1;
	       v[3] = ctx->EvalMap.Map2Vertex4.v2;
	       break;
	    default:
	       gl_error( ctx, GL_INVALID_ENUM, "glGetMapfv(target)" );
	 }
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glGetMapfv(query)" );
   }
}