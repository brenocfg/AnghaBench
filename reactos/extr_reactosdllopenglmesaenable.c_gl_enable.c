#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_17__ ;
typedef  struct TYPE_30__   TYPE_16__ ;
typedef  struct TYPE_29__   TYPE_15__ ;
typedef  struct TYPE_28__   TYPE_14__ ;
typedef  struct TYPE_27__   TYPE_13__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
struct TYPE_40__ {void* Normalize; void* AnyClip; void** ClipEnabled; } ;
struct TYPE_39__ {void* Map2Vertex4; void* Map2Vertex3; void* Map2TextureCoord4; void* Map2TextureCoord3; void* Map2TextureCoord2; void* Map2TextureCoord1; void* Map2Normal; void* Map2Index; void* Map2Color4; void* Map1Vertex4; void* Map1Vertex3; void* Map1TextureCoord4; void* Map1TextureCoord3; void* Map1TextureCoord2; void* Map1TextureCoord1; void* Map1Normal; void* Map1Index; void* Map1Color4; void* AutoNormal; } ;
struct TYPE_38__ {void* AlphaEnabled; void* BlendEnabled; void* ColorLogicOpEnabled; void* DitherFlag; void* IndexLogicOpEnabled; } ;
struct TYPE_37__ {void* SmoothFlag; void* StippleFlag; } ;
struct TYPE_36__ {void* ColorMaterialEnabled; void* Enabled; TYPE_4__* Light; int /*<<< orphan*/  ColorMaterialBitmask; } ;
struct TYPE_35__ {void* Enabled; } ;
struct TYPE_34__ {void* Enabled; } ;
struct TYPE_33__ {void* Test; } ;
struct TYPE_32__ {int* ByteColor; } ;
struct TYPE_30__ {void* EdgeFlagEnabled; void* TexCoordEnabled; void* IndexEnabled; void* ColorEnabled; void* NormalEnabled; void* VertexEnabled; } ;
struct TYPE_29__ {int /*<<< orphan*/  TexGenEnabled; int /*<<< orphan*/  Enabled; } ;
struct TYPE_27__ {void* Enabled; } ;
struct TYPE_26__ {void* Enabled; } ;
struct TYPE_25__ {void* CullFlag; void* SmoothFlag; void* StippleFlag; void* OffsetPoint; void* OffsetLine; void* OffsetFill; } ;
struct TYPE_24__ {void* SmoothFlag; } ;
struct TYPE_31__ {int NewState; TYPE_16__ Array; TYPE_15__ Texture; TYPE_14__* Visual; TYPE_13__ Stencil; TYPE_12__ Scissor; TYPE_11__ Polygon; TYPE_10__ Point; TYPE_9__ Transform; TYPE_8__ Eval; TYPE_7__ Color; TYPE_6__ Line; TYPE_5__ Light; TYPE_3__ Fog; int /*<<< orphan*/  NoDither; TYPE_2__ Depth; TYPE_1__ Current; } ;
struct TYPE_28__ {int InvRedScale; int InvGreenScale; int InvBlueScale; int InvAlphaScale; int /*<<< orphan*/  RGBAflag; int /*<<< orphan*/  StencilBits; int /*<<< orphan*/  DepthBits; } ;
typedef  size_t GLuint ;
typedef  int GLfloat ;
typedef  int GLenum ;
typedef  TYPE_17__ GLcontext ;
typedef  void* GLboolean ;

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
 void* GL_FALSE ; 
#define  GL_FOG 177 
#define  GL_INDEX_ARRAY 176 
#define  GL_INDEX_LOGIC_OP 175 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
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
 void* GL_TRUE ; 
#define  GL_VERTEX_ARRAY 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_17__*) ; 
 size_t MAX_CLIP_PLANES ; 
 int NEW_LIGHTING ; 
 int NEW_POLYGON ; 
 int NEW_RASTER_OPS ; 
 int NEW_TEXTURING ; 
 int /*<<< orphan*/  Q_BIT ; 
 int /*<<< orphan*/  R_BIT ; 
 int /*<<< orphan*/  S_BIT ; 
 int /*<<< orphan*/  TEXTURE_1D ; 
 int /*<<< orphan*/  TEXTURE_2D ; 
 int /*<<< orphan*/  T_BIT ; 
 int /*<<< orphan*/  gl_error (TYPE_17__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_set_color_function (TYPE_17__*) ; 
 int /*<<< orphan*/  gl_set_material (TYPE_17__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  gl_warning (TYPE_17__*,char*) ; 

__attribute__((used)) static void gl_enable( GLcontext* ctx, GLenum cap, GLboolean state )
{
   GLuint p;

   if (INSIDE_BEGIN_END(ctx)) {
      if (state) {
	 gl_error( ctx, GL_INVALID_OPERATION, "glEnable" );
      }
      else {
	 gl_error( ctx, GL_INVALID_OPERATION, "glDisable" );
      }
      return;
   }

   switch (cap) {
      case GL_ALPHA_TEST:
         if (ctx->Color.AlphaEnabled!=state) {
            ctx->Color.AlphaEnabled = state;
            ctx->NewState |= NEW_RASTER_OPS;
         }
	 break;
      case GL_AUTO_NORMAL:
	 ctx->Eval.AutoNormal = state;
	 break;
      case GL_BLEND:
         if (ctx->Color.BlendEnabled!=state) {
            ctx->Color.BlendEnabled = state;
            /* The following needed to accomodate 1.0 RGB logic op blending */
            ctx->Color.ColorLogicOpEnabled = GL_FALSE;
            ctx->NewState |= NEW_RASTER_OPS;
         }
	 break;
      case GL_CLIP_PLANE0:
      case GL_CLIP_PLANE1:
      case GL_CLIP_PLANE2:
      case GL_CLIP_PLANE3:
      case GL_CLIP_PLANE4:
      case GL_CLIP_PLANE5:
	 ctx->Transform.ClipEnabled[cap-GL_CLIP_PLANE0] = state;
	 /* Check if any clip planes enabled */
         ctx->Transform.AnyClip = GL_FALSE;
         for (p=0;p<MAX_CLIP_PLANES;p++) {
            if (ctx->Transform.ClipEnabled[p]) {
               ctx->Transform.AnyClip = GL_TRUE;
               break;
            }
         }
	 break;
      case GL_COLOR_MATERIAL:
         if (ctx->Light.ColorMaterialEnabled!=state) {
            ctx->Light.ColorMaterialEnabled = state;
            if (state) {
               GLfloat color[4];
               color[0] = ctx->Current.ByteColor[0] * ctx->Visual->InvRedScale;
               color[1] = ctx->Current.ByteColor[1] * ctx->Visual->InvGreenScale;
               color[2] = ctx->Current.ByteColor[2] * ctx->Visual->InvBlueScale;
               color[3] = ctx->Current.ByteColor[3] * ctx->Visual->InvAlphaScale;
               /* update material with current color */
               gl_set_material( ctx, ctx->Light.ColorMaterialBitmask, color );
            }
            gl_set_color_function(ctx);
            ctx->NewState |= NEW_LIGHTING;
         }
	 break;
      case GL_CULL_FACE:
         if (ctx->Polygon.CullFlag!=state) {
            ctx->Polygon.CullFlag = state;
            ctx->NewState |= NEW_POLYGON;
         }
	 break;
      case GL_DEPTH_TEST:
         if (state && ctx->Visual->DepthBits==0) {
            gl_warning(ctx,"glEnable(GL_DEPTH_TEST) but no depth buffer");
            return;
         }
	 if (ctx->Depth.Test!=state) {
            ctx->Depth.Test = state;
            ctx->NewState |= NEW_RASTER_OPS;
         }
         break;
      case GL_DITHER:
         if (ctx->NoDither) {
            /* MESA_NO_DITHER env var */
            state = GL_FALSE;
         }
         if (ctx->Color.DitherFlag!=state) {
            ctx->Color.DitherFlag = state;
            ctx->NewState |= NEW_RASTER_OPS;
         }
	 break;
      case GL_FOG:
	 if (ctx->Fog.Enabled!=state) {
            ctx->Fog.Enabled = state;
            ctx->NewState |= NEW_RASTER_OPS;
         }
	 break;
      case GL_LIGHT0:
      case GL_LIGHT1:
      case GL_LIGHT2:
      case GL_LIGHT3:
      case GL_LIGHT4:
      case GL_LIGHT5:
      case GL_LIGHT6:
      case GL_LIGHT7:
         ctx->Light.Light[cap-GL_LIGHT0].Enabled = state;
         ctx->NewState |= NEW_LIGHTING;
         break;
      case GL_LIGHTING:
         if (ctx->Light.Enabled!=state) {
            ctx->Light.Enabled = state;
            ctx->NewState |= NEW_LIGHTING;
         }
         break;
      case GL_LINE_SMOOTH:
	 if (ctx->Line.SmoothFlag!=state) {
            ctx->Line.SmoothFlag = state;
            ctx->NewState |= NEW_RASTER_OPS;
         }
	 break;
      case GL_LINE_STIPPLE:
	 if (ctx->Line.StippleFlag!=state) {
            ctx->Line.StippleFlag = state;
            ctx->NewState |= NEW_RASTER_OPS;
         }
	 break;
      case GL_INDEX_LOGIC_OP:
         if (ctx->Color.IndexLogicOpEnabled!=state) {
            ctx->NewState |= NEW_RASTER_OPS;
         }
	 ctx->Color.IndexLogicOpEnabled = state;
	 break;
      case GL_COLOR_LOGIC_OP:
         if (ctx->Color.ColorLogicOpEnabled!=state) {
            ctx->NewState |= NEW_RASTER_OPS;
         }
	 ctx->Color.ColorLogicOpEnabled = state;
	 break;
      case GL_MAP1_COLOR_4:
	 ctx->Eval.Map1Color4 = state;
	 break;
      case GL_MAP1_INDEX:
	 ctx->Eval.Map1Index = state;
	 break;
      case GL_MAP1_NORMAL:
	 ctx->Eval.Map1Normal = state;
	 break;
      case GL_MAP1_TEXTURE_COORD_1:
	 ctx->Eval.Map1TextureCoord1 = state;
	 break;
      case GL_MAP1_TEXTURE_COORD_2:
	 ctx->Eval.Map1TextureCoord2 = state;
	 break;
      case GL_MAP1_TEXTURE_COORD_3:
	 ctx->Eval.Map1TextureCoord3 = state;
	 break;
      case GL_MAP1_TEXTURE_COORD_4:
	 ctx->Eval.Map1TextureCoord4 = state;
	 break;
      case GL_MAP1_VERTEX_3:
	 ctx->Eval.Map1Vertex3 = state;
	 break;
      case GL_MAP1_VERTEX_4:
	 ctx->Eval.Map1Vertex4 = state;
	 break;
      case GL_MAP2_COLOR_4:
	 ctx->Eval.Map2Color4 = state;
	 break;
      case GL_MAP2_INDEX:
	 ctx->Eval.Map2Index = state;
	 break;
      case GL_MAP2_NORMAL:
	 ctx->Eval.Map2Normal = state;
	 break;
      case GL_MAP2_TEXTURE_COORD_1: 
	 ctx->Eval.Map2TextureCoord1 = state;
	 break;
      case GL_MAP2_TEXTURE_COORD_2:
	 ctx->Eval.Map2TextureCoord2 = state;
	 break;
      case GL_MAP2_TEXTURE_COORD_3:
	 ctx->Eval.Map2TextureCoord3 = state;
	 break;
      case GL_MAP2_TEXTURE_COORD_4:
	 ctx->Eval.Map2TextureCoord4 = state;
	 break;
      case GL_MAP2_VERTEX_3:
	 ctx->Eval.Map2Vertex3 = state;
	 break;
      case GL_MAP2_VERTEX_4:
	 ctx->Eval.Map2Vertex4 = state;
	 break;
      case GL_NORMALIZE:
	 ctx->Transform.Normalize = state;
	 break;
      case GL_POINT_SMOOTH:
	 if (ctx->Point.SmoothFlag!=state) {
            ctx->Point.SmoothFlag = state;
            ctx->NewState |= NEW_RASTER_OPS;
         }
	 break;
      case GL_POLYGON_SMOOTH:
	 if (ctx->Polygon.SmoothFlag!=state) {
            ctx->Polygon.SmoothFlag = state;
            ctx->NewState |= NEW_RASTER_OPS;
         }
	 break;
      case GL_POLYGON_STIPPLE:
	 if (ctx->Polygon.StippleFlag!=state) {
            ctx->Polygon.StippleFlag = state;
            ctx->NewState |= NEW_RASTER_OPS;
         }
	 break;
      case GL_POLYGON_OFFSET_POINT:
         if (ctx->Polygon.OffsetPoint!=state) {
            ctx->Polygon.OffsetPoint = state;
            ctx->NewState |= NEW_POLYGON;
         }
         break;
      case GL_POLYGON_OFFSET_LINE:
         if (ctx->Polygon.OffsetLine!=state) {
            ctx->Polygon.OffsetLine = state;
            ctx->NewState |= NEW_POLYGON;
         }
         break;
      case GL_POLYGON_OFFSET_FILL:
      /*case GL_POLYGON_OFFSET_EXT:*/
         if (ctx->Polygon.OffsetFill!=state) {
            ctx->Polygon.OffsetFill = state;
            ctx->NewState |= NEW_POLYGON;
         }
         break;
      case GL_SCISSOR_TEST:
         if (ctx->Scissor.Enabled!=state) {
            ctx->Scissor.Enabled = state;
            ctx->NewState |= NEW_RASTER_OPS;
         }
	 break;
      case GL_STENCIL_TEST:
	 if (state && ctx->Visual->StencilBits==0) {
            gl_warning(ctx, "glEnable(GL_STENCIL_TEST) but no stencil buffer");
            return;
	 }
	 if (ctx->Stencil.Enabled!=state) {
            ctx->Stencil.Enabled = state;
            ctx->NewState |= NEW_RASTER_OPS;
         }
	 break;
      case GL_TEXTURE_1D:
         if (ctx->Visual->RGBAflag) {
            /* texturing only works in RGB mode */
            if (state) {
               ctx->Texture.Enabled |= TEXTURE_1D;
            }
            else {
               ctx->Texture.Enabled &= (~TEXTURE_1D);
            }
            ctx->NewState |= (NEW_RASTER_OPS | NEW_TEXTURING);
         }
	 break;
      case GL_TEXTURE_2D:
         if (ctx->Visual->RGBAflag) {
            /* texturing only works in RGB mode */
            if (state) {
               ctx->Texture.Enabled |= TEXTURE_2D;
            }
            else {
               ctx->Texture.Enabled &= (~TEXTURE_2D);
            }
            ctx->NewState |= (NEW_RASTER_OPS | NEW_TEXTURING);
         }
	 break;
      case GL_TEXTURE_GEN_Q:
         if (state) {
            ctx->Texture.TexGenEnabled |= Q_BIT;
         }
         else {
            ctx->Texture.TexGenEnabled &= ~Q_BIT;
         }
         ctx->NewState |= NEW_TEXTURING;
	 break;
      case GL_TEXTURE_GEN_R:
         if (state) {
            ctx->Texture.TexGenEnabled |= R_BIT;
         }
         else {
            ctx->Texture.TexGenEnabled &= ~R_BIT;
         }
         ctx->NewState |= NEW_TEXTURING;
	 break;
      case GL_TEXTURE_GEN_S:
	 if (state) {
            ctx->Texture.TexGenEnabled |= S_BIT;
         }
         else {
            ctx->Texture.TexGenEnabled &= ~S_BIT;
         }
         ctx->NewState |= NEW_TEXTURING;
	 break;
      case GL_TEXTURE_GEN_T:
         if (state) {
            ctx->Texture.TexGenEnabled |= T_BIT;
         }
         else {
            ctx->Texture.TexGenEnabled &= ~T_BIT;
         }
         ctx->NewState |= NEW_TEXTURING;
	 break;

      /*
       * CLIENT STATE!!!
       */
      case GL_VERTEX_ARRAY:
         ctx->Array.VertexEnabled = state;
         break;
      case GL_NORMAL_ARRAY:
         ctx->Array.NormalEnabled = state;
         break;
      case GL_COLOR_ARRAY:
         ctx->Array.ColorEnabled = state;
         break;
      case GL_INDEX_ARRAY:
         ctx->Array.IndexEnabled = state;
         break;
      case GL_TEXTURE_COORD_ARRAY:
         ctx->Array.TexCoordEnabled = state;
         break;
      case GL_EDGE_FLAG_ARRAY:
         ctx->Array.EdgeFlagEnabled = state;
         break;

      default:
	 if (state) {
	    gl_error( ctx, GL_INVALID_ENUM, "glEnable" );
	 }
	 else {
	    gl_error( ctx, GL_INVALID_ENUM, "glDisable" );
	 }
         break;
   }
}