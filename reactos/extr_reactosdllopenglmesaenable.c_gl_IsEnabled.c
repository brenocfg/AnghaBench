#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_15__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_32__ {int /*<<< orphan*/  SmoothFlag; } ;
struct TYPE_31__ {int /*<<< orphan*/  Normalize; int /*<<< orphan*/ * ClipEnabled; } ;
struct TYPE_30__ {int /*<<< orphan*/  Map2Vertex4; int /*<<< orphan*/  Map2Vertex3; int /*<<< orphan*/  Map2TextureCoord4; int /*<<< orphan*/  Map2TextureCoord3; int /*<<< orphan*/  Map2TextureCoord2; int /*<<< orphan*/  Map2TextureCoord1; int /*<<< orphan*/  Map2Normal; int /*<<< orphan*/  Map2Index; int /*<<< orphan*/  Map2Color4; int /*<<< orphan*/  Map1Vertex4; int /*<<< orphan*/  Map1Vertex3; int /*<<< orphan*/  Map1TextureCoord4; int /*<<< orphan*/  Map1TextureCoord3; int /*<<< orphan*/  Map1TextureCoord2; int /*<<< orphan*/  Map1TextureCoord1; int /*<<< orphan*/  Map1Normal; int /*<<< orphan*/  Map1Index; int /*<<< orphan*/  Map1Color4; int /*<<< orphan*/  AutoNormal; } ;
struct TYPE_29__ {int /*<<< orphan*/  ColorLogicOpEnabled; int /*<<< orphan*/  IndexLogicOpEnabled; int /*<<< orphan*/  DitherFlag; int /*<<< orphan*/  BlendEnabled; int /*<<< orphan*/  AlphaEnabled; } ;
struct TYPE_28__ {int /*<<< orphan*/  StippleFlag; int /*<<< orphan*/  SmoothFlag; } ;
struct TYPE_27__ {TYPE_3__* Light; int /*<<< orphan*/  Enabled; int /*<<< orphan*/  ColorMaterialEnabled; } ;
struct TYPE_26__ {int /*<<< orphan*/  Enabled; } ;
struct TYPE_25__ {int /*<<< orphan*/  Enabled; } ;
struct TYPE_24__ {int /*<<< orphan*/  Test; } ;
struct TYPE_22__ {int /*<<< orphan*/  EdgeFlagEnabled; int /*<<< orphan*/  TexCoordEnabled; int /*<<< orphan*/  IndexEnabled; int /*<<< orphan*/  ColorEnabled; int /*<<< orphan*/  NormalEnabled; int /*<<< orphan*/  VertexEnabled; } ;
struct TYPE_21__ {int Enabled; int TexGenEnabled; } ;
struct TYPE_20__ {int /*<<< orphan*/  Enabled; } ;
struct TYPE_19__ {int /*<<< orphan*/  Enabled; } ;
struct TYPE_18__ {int /*<<< orphan*/  OffsetFill; int /*<<< orphan*/  OffsetLine; int /*<<< orphan*/  OffsetPoint; int /*<<< orphan*/  StippleFlag; int /*<<< orphan*/  SmoothFlag; int /*<<< orphan*/  CullFlag; } ;
struct TYPE_23__ {TYPE_14__ Array; TYPE_13__ Texture; TYPE_12__ Stencil; TYPE_11__ Scissor; TYPE_10__ Polygon; TYPE_9__ Point; TYPE_8__ Transform; TYPE_7__ Eval; TYPE_6__ Color; TYPE_5__ Line; TYPE_4__ Light; TYPE_2__ Fog; TYPE_1__ Depth; } ;
typedef  int GLenum ;
typedef  TYPE_15__ GLcontext ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
#define  GL_ALPHA_TEST 193 
#define  GL_AUTO_NORMAL 192 
#define  GL_BLEND 191 
#define  GL_CLIP_PLANE0 190 
#define  GL_CLIP_PLANE1 189 
#define  GL_CLIP_PLANE2 188 
#define  GL_CLIP_PLANE3 187 
#define  GL_CLIP_PLANE4 186 
#define  GL_CLIP_PLANE5 185 
#define  GL_COLOR_ARRAY 184 
#define  GL_COLOR_LOGIC_OP 183 
#define  GL_COLOR_MATERIAL 182 
#define  GL_CULL_FACE 181 
#define  GL_DEPTH_TEST 180 
#define  GL_DITHER 179 
#define  GL_EDGE_FLAG_ARRAY 178 
 int /*<<< orphan*/  GL_FALSE ; 
#define  GL_FOG 177 
#define  GL_INDEX_ARRAY 176 
#define  GL_INDEX_LOGIC_OP 175 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
#define  GL_LIGHT0 174 
#define  GL_LIGHT1 173 
#define  GL_LIGHT2 172 
#define  GL_LIGHT3 171 
#define  GL_LIGHT4 170 
#define  GL_LIGHT5 169 
#define  GL_LIGHT6 168 
#define  GL_LIGHT7 167 
#define  GL_LIGHTING 166 
#define  GL_LINE_SMOOTH 165 
#define  GL_LINE_STIPPLE 164 
#define  GL_MAP1_COLOR_4 163 
#define  GL_MAP1_INDEX 162 
#define  GL_MAP1_NORMAL 161 
#define  GL_MAP1_TEXTURE_COORD_1 160 
#define  GL_MAP1_TEXTURE_COORD_2 159 
#define  GL_MAP1_TEXTURE_COORD_3 158 
#define  GL_MAP1_TEXTURE_COORD_4 157 
#define  GL_MAP1_VERTEX_3 156 
#define  GL_MAP1_VERTEX_4 155 
#define  GL_MAP2_COLOR_4 154 
#define  GL_MAP2_INDEX 153 
#define  GL_MAP2_NORMAL 152 
#define  GL_MAP2_TEXTURE_COORD_1 151 
#define  GL_MAP2_TEXTURE_COORD_2 150 
#define  GL_MAP2_TEXTURE_COORD_3 149 
#define  GL_MAP2_TEXTURE_COORD_4 148 
#define  GL_MAP2_VERTEX_3 147 
#define  GL_MAP2_VERTEX_4 146 
#define  GL_NORMALIZE 145 
#define  GL_NORMAL_ARRAY 144 
#define  GL_POINT_SMOOTH 143 
#define  GL_POLYGON_OFFSET_FILL 142 
#define  GL_POLYGON_OFFSET_LINE 141 
#define  GL_POLYGON_OFFSET_POINT 140 
#define  GL_POLYGON_SMOOTH 139 
#define  GL_POLYGON_STIPPLE 138 
#define  GL_SCISSOR_TEST 137 
#define  GL_STENCIL_TEST 136 
#define  GL_TEXTURE_1D 135 
#define  GL_TEXTURE_2D 134 
#define  GL_TEXTURE_COORD_ARRAY 133 
#define  GL_TEXTURE_GEN_Q 132 
#define  GL_TEXTURE_GEN_R 131 
#define  GL_TEXTURE_GEN_S 130 
#define  GL_TEXTURE_GEN_T 129 
 int /*<<< orphan*/  GL_TRUE ; 
#define  GL_VERTEX_ARRAY 128 
 int Q_BIT ; 
 int R_BIT ; 
 int S_BIT ; 
 int TEXTURE_1D ; 
 int TEXTURE_2D ; 
 int T_BIT ; 
 int /*<<< orphan*/  gl_error (TYPE_15__*,int /*<<< orphan*/ ,char*) ; 

GLboolean gl_IsEnabled( GLcontext* ctx, GLenum cap )
{
   switch (cap) {
      case GL_ALPHA_TEST:
         return ctx->Color.AlphaEnabled;
      case GL_AUTO_NORMAL:
	 return ctx->Eval.AutoNormal;
      case GL_BLEND:
         return ctx->Color.BlendEnabled;
      case GL_CLIP_PLANE0:
      case GL_CLIP_PLANE1:
      case GL_CLIP_PLANE2:
      case GL_CLIP_PLANE3:
      case GL_CLIP_PLANE4:
      case GL_CLIP_PLANE5:
	 return ctx->Transform.ClipEnabled[cap-GL_CLIP_PLANE0];
      case GL_COLOR_MATERIAL:
	 return ctx->Light.ColorMaterialEnabled;
      case GL_CULL_FACE:
         return ctx->Polygon.CullFlag;
      case GL_DEPTH_TEST:
         return ctx->Depth.Test;
      case GL_DITHER:
	 return ctx->Color.DitherFlag;
      case GL_FOG:
	 return ctx->Fog.Enabled;
      case GL_LIGHTING:
         return ctx->Light.Enabled;
      case GL_LIGHT0:
      case GL_LIGHT1:
      case GL_LIGHT2:
      case GL_LIGHT3:
      case GL_LIGHT4:
      case GL_LIGHT5:
      case GL_LIGHT6:
      case GL_LIGHT7:
         return ctx->Light.Light[cap-GL_LIGHT0].Enabled;
      case GL_LINE_SMOOTH:
	 return ctx->Line.SmoothFlag;
      case GL_LINE_STIPPLE:
	 return ctx->Line.StippleFlag;
      case GL_INDEX_LOGIC_OP:
	 return ctx->Color.IndexLogicOpEnabled;
      case GL_COLOR_LOGIC_OP:
	 return ctx->Color.ColorLogicOpEnabled;
      case GL_MAP1_COLOR_4:
	 return ctx->Eval.Map1Color4;
      case GL_MAP1_INDEX:
	 return ctx->Eval.Map1Index;
      case GL_MAP1_NORMAL:
	 return ctx->Eval.Map1Normal;
      case GL_MAP1_TEXTURE_COORD_1:
	 return ctx->Eval.Map1TextureCoord1;
      case GL_MAP1_TEXTURE_COORD_2:
	 return ctx->Eval.Map1TextureCoord2;
      case GL_MAP1_TEXTURE_COORD_3:
	 return ctx->Eval.Map1TextureCoord3;
      case GL_MAP1_TEXTURE_COORD_4:
	 return ctx->Eval.Map1TextureCoord4;
      case GL_MAP1_VERTEX_3:
	 return ctx->Eval.Map1Vertex3;
      case GL_MAP1_VERTEX_4:
	 return ctx->Eval.Map1Vertex4;
      case GL_MAP2_COLOR_4:
	 return ctx->Eval.Map2Color4;
      case GL_MAP2_INDEX:
	 return ctx->Eval.Map2Index;
      case GL_MAP2_NORMAL:
	 return ctx->Eval.Map2Normal;
      case GL_MAP2_TEXTURE_COORD_1: 
	 return ctx->Eval.Map2TextureCoord1;
      case GL_MAP2_TEXTURE_COORD_2:
	 return ctx->Eval.Map2TextureCoord2;
      case GL_MAP2_TEXTURE_COORD_3:
	 return ctx->Eval.Map2TextureCoord3;
      case GL_MAP2_TEXTURE_COORD_4:
	 return ctx->Eval.Map2TextureCoord4;
      case GL_MAP2_VERTEX_3:
	 return ctx->Eval.Map2Vertex3;
      case GL_MAP2_VERTEX_4:
	 return ctx->Eval.Map2Vertex4;
      case GL_NORMALIZE:
	 return ctx->Transform.Normalize;
      case GL_POINT_SMOOTH:
	 return ctx->Point.SmoothFlag;
      case GL_POLYGON_SMOOTH:
	 return ctx->Polygon.SmoothFlag;
      case GL_POLYGON_STIPPLE:
	 return ctx->Polygon.StippleFlag;
      case GL_POLYGON_OFFSET_POINT:
	 return ctx->Polygon.OffsetPoint;
      case GL_POLYGON_OFFSET_LINE:
	 return ctx->Polygon.OffsetLine;
      case GL_POLYGON_OFFSET_FILL:
      /*case GL_POLYGON_OFFSET_EXT:*/
	 return ctx->Polygon.OffsetFill;
      case GL_SCISSOR_TEST:
	 return ctx->Scissor.Enabled;
      case GL_STENCIL_TEST:
	 return ctx->Stencil.Enabled;
      case GL_TEXTURE_1D:
	 return (ctx->Texture.Enabled & TEXTURE_1D) ? GL_TRUE : GL_FALSE;
      case GL_TEXTURE_2D:
	 return (ctx->Texture.Enabled & TEXTURE_2D) ? GL_TRUE : GL_FALSE;
      case GL_TEXTURE_GEN_Q:
	 return (ctx->Texture.TexGenEnabled & Q_BIT) ? GL_TRUE : GL_FALSE;
      case GL_TEXTURE_GEN_R:
	 return (ctx->Texture.TexGenEnabled & R_BIT) ? GL_TRUE : GL_FALSE;
      case GL_TEXTURE_GEN_S:
	 return (ctx->Texture.TexGenEnabled & S_BIT) ? GL_TRUE : GL_FALSE;
      case GL_TEXTURE_GEN_T:
	 return (ctx->Texture.TexGenEnabled & T_BIT) ? GL_TRUE : GL_FALSE;

      /*
       * CLIENT STATE!!!
       */
      case GL_VERTEX_ARRAY:
         return ctx->Array.VertexEnabled;
      case GL_NORMAL_ARRAY:
         return ctx->Array.NormalEnabled;
      case GL_COLOR_ARRAY:
         return ctx->Array.ColorEnabled;
      case GL_INDEX_ARRAY:
         return ctx->Array.IndexEnabled;
      case GL_TEXTURE_COORD_ARRAY:
         return ctx->Array.TexCoordEnabled;
      case GL_EDGE_FLAG_ARRAY:
         return ctx->Array.EdgeFlagEnabled;
      default:
	 gl_error( ctx, GL_INVALID_ENUM, "glIsEnabled" );
	 return GL_FALSE;
   }
}