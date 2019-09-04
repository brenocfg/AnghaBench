#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_117__   TYPE_7__ ;
typedef  struct TYPE_116__   TYPE_6__ ;
typedef  struct TYPE_115__   TYPE_5__ ;
typedef  struct TYPE_114__   TYPE_4__ ;
typedef  struct TYPE_113__   TYPE_3__ ;
typedef  struct TYPE_112__   TYPE_2__ ;
typedef  struct TYPE_111__   TYPE_1__ ;

/* Type definitions */
struct gl_image {int dummy; } ;
struct TYPE_115__ {float* Normal; int Index; float* TexCoord; int /*<<< orphan*/  EdgeFlag; } ;
struct TYPE_114__ {int ListBase; } ;
struct TYPE_112__ {int /*<<< orphan*/  (* Color4f ) (TYPE_7__*,float,float,float,float) ;int /*<<< orphan*/  (* Color3f ) (TYPE_7__*,float,float,float) ;int /*<<< orphan*/  (* Color4ub ) (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* Vertex4f ) (TYPE_7__*,float,float,float,float) ;int /*<<< orphan*/  (* Vertex3f ) (TYPE_7__*,float,float,float) ;int /*<<< orphan*/  (* Vertex2f ) (TYPE_7__*,float,float) ;} ;
struct TYPE_117__ {int /*<<< orphan*/  CallDepth; TYPE_5__ Current; TYPE_4__ List; TYPE_3__* VB; TYPE_2__ Exec; TYPE_1__* Shared; } ;
struct TYPE_116__ {int opcode; float f; int ui; scalar_t__ next; int /*<<< orphan*/  i; scalar_t__ data; int /*<<< orphan*/  e; int /*<<< orphan*/  bf; int /*<<< orphan*/  us; int /*<<< orphan*/  b; int /*<<< orphan*/  ub; } ;
struct TYPE_113__ {int TexCoordSize; void* MonoColor; void* MonoNormal; } ;
struct TYPE_111__ {int /*<<< orphan*/  DisplayList; } ;
typedef  int OpCode ;
typedef  TYPE_6__ Node ;
typedef  int GLuint ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int /*<<< orphan*/  GLsizei ;
typedef  float GLfloat ;
typedef  TYPE_7__ GLcontext ;
typedef  int /*<<< orphan*/  GLclampd ;
typedef  void* GLboolean ;

/* Variables and functions */
 void* GL_FALSE ; 
 void* GL_TRUE ; 
 scalar_t__ HashLookup (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * InstSize ; 
 int /*<<< orphan*/  MAX_LIST_NESTING ; 
#define  OPCODE_ACCUM 235 
#define  OPCODE_ALPHA_FUNC 234 
#define  OPCODE_BEGIN 233 
#define  OPCODE_BIND_TEXTURE 232 
#define  OPCODE_BITMAP 231 
#define  OPCODE_BLEND_FUNC 230 
#define  OPCODE_CALL_LIST 229 
#define  OPCODE_CALL_LIST_OFFSET 228 
#define  OPCODE_CLEAR 227 
#define  OPCODE_CLEAR_ACCUM 226 
#define  OPCODE_CLEAR_COLOR 225 
#define  OPCODE_CLEAR_DEPTH 224 
#define  OPCODE_CLEAR_INDEX 223 
#define  OPCODE_CLEAR_STENCIL 222 
#define  OPCODE_CLIP_PLANE 221 
#define  OPCODE_COLOR_3F 220 
#define  OPCODE_COLOR_4F 219 
#define  OPCODE_COLOR_4UB 218 
#define  OPCODE_COLOR_MASK 217 
#define  OPCODE_COLOR_MATERIAL 216 
#define  OPCODE_COLOR_SUB_TABLE 215 
#define  OPCODE_COLOR_TABLE 214 
#define  OPCODE_CONTINUE 213 
#define  OPCODE_COPY_PIXELS 212 
#define  OPCODE_COPY_TEX_IMAGE1D 211 
#define  OPCODE_COPY_TEX_IMAGE2D 210 
#define  OPCODE_COPY_TEX_SUB_IMAGE1D 209 
#define  OPCODE_COPY_TEX_SUB_IMAGE2D 208 
#define  OPCODE_CULL_FACE 207 
#define  OPCODE_DEPTH_FUNC 206 
#define  OPCODE_DEPTH_MASK 205 
#define  OPCODE_DEPTH_RANGE 204 
#define  OPCODE_DISABLE 203 
#define  OPCODE_DRAW_BUFFER 202 
#define  OPCODE_DRAW_PIXELS 201 
#define  OPCODE_EDGE_FLAG 200 
#define  OPCODE_ENABLE 199 
#define  OPCODE_END 198 
#define  OPCODE_END_OF_LIST 197 
#define  OPCODE_EVALCOORD1 196 
#define  OPCODE_EVALCOORD2 195 
#define  OPCODE_EVALMESH1 194 
#define  OPCODE_EVALMESH2 193 
#define  OPCODE_EVALPOINT1 192 
#define  OPCODE_EVALPOINT2 191 
#define  OPCODE_FOG 190 
#define  OPCODE_FRONT_FACE 189 
#define  OPCODE_FRUSTUM 188 
#define  OPCODE_HINT 187 
#define  OPCODE_INDEX 186 
#define  OPCODE_INDEX_MASK 185 
#define  OPCODE_INIT_NAMES 184 
#define  OPCODE_LIGHT 183 
#define  OPCODE_LIGHT_MODEL 182 
#define  OPCODE_LINE_STIPPLE 181 
#define  OPCODE_LINE_WIDTH 180 
#define  OPCODE_LIST_BASE 179 
#define  OPCODE_LOAD_IDENTITY 178 
#define  OPCODE_LOAD_MATRIX 177 
#define  OPCODE_LOAD_NAME 176 
#define  OPCODE_LOGIC_OP 175 
#define  OPCODE_MAP1 174 
#define  OPCODE_MAP2 173 
#define  OPCODE_MAPGRID1 172 
#define  OPCODE_MAPGRID2 171 
#define  OPCODE_MATERIAL 170 
#define  OPCODE_MATRIX_MODE 169 
#define  OPCODE_MULT_MATRIX 168 
#define  OPCODE_NORMAL 167 
#define  OPCODE_ORTHO 166 
#define  OPCODE_PASSTHROUGH 165 
#define  OPCODE_PIXEL_MAP 164 
#define  OPCODE_PIXEL_TRANSFER 163 
#define  OPCODE_PIXEL_ZOOM 162 
#define  OPCODE_POINT_SIZE 161 
#define  OPCODE_POLYGON_MODE 160 
#define  OPCODE_POLYGON_OFFSET 159 
#define  OPCODE_POLYGON_STIPPLE 158 
#define  OPCODE_POP_ATTRIB 157 
#define  OPCODE_POP_MATRIX 156 
#define  OPCODE_POP_NAME 155 
#define  OPCODE_PRIORITIZE_TEXTURE 154 
#define  OPCODE_PUSH_ATTRIB 153 
#define  OPCODE_PUSH_MATRIX 152 
#define  OPCODE_PUSH_NAME 151 
#define  OPCODE_RASTER_POS 150 
#define  OPCODE_READ_BUFFER 149 
#define  OPCODE_RECTF 148 
#define  OPCODE_SCALE 147 
#define  OPCODE_SCISSOR 146 
#define  OPCODE_SHADE_MODEL 145 
#define  OPCODE_STENCIL_FUNC 144 
#define  OPCODE_STENCIL_MASK 143 
#define  OPCODE_STENCIL_OP 142 
#define  OPCODE_TEXCOORD2 141 
#define  OPCODE_TEXCOORD4 140 
#define  OPCODE_TEXENV 139 
#define  OPCODE_TEXGEN 138 
#define  OPCODE_TEXPARAMETER 137 
#define  OPCODE_TEX_IMAGE1D 136 
#define  OPCODE_TEX_IMAGE2D 135 
#define  OPCODE_TEX_SUB_IMAGE1D 134 
#define  OPCODE_TEX_SUB_IMAGE2D 133 
#define  OPCODE_TRANSLATE 132 
#define  OPCODE_VERTEX2 131 
#define  OPCODE_VERTEX3 130 
#define  OPCODE_VERTEX4 129 
#define  OPCODE_VIEWPORT 128 
 int /*<<< orphan*/  gl_Accum (TYPE_7__*,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  gl_AlphaFunc (TYPE_7__*,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  gl_Begin (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_BindTexture (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gl_Bitmap (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,float,float,float,struct gl_image*) ; 
 int /*<<< orphan*/  gl_BlendFunc (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_Clear (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_ClearAccum (TYPE_7__*,float,float,float,float) ; 
 int /*<<< orphan*/  gl_ClearColor (TYPE_7__*,float,float,float,float) ; 
 int /*<<< orphan*/  gl_ClearDepth (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_ClearIndex (TYPE_7__*,int) ; 
 int /*<<< orphan*/  gl_ClearStencil (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_ClipPlane (TYPE_7__*,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  gl_ColorMask (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_ColorMaterial (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_ColorSubTable (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gl_image*) ; 
 int /*<<< orphan*/  gl_ColorTable (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gl_image*) ; 
 int /*<<< orphan*/  gl_CopyPixels (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_CopyTexImage1D (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_CopyTexImage2D (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_CopyTexSubImage1D (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_CopyTexSubImage2D (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_CullFace (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_DepthFunc (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_DepthMask (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_DepthRange (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_Disable (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_DrawBuffer (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_DrawPixels (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gl_Enable (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_End (TYPE_7__*) ; 
 int /*<<< orphan*/  gl_EvalCoord1f (TYPE_7__*,float) ; 
 int /*<<< orphan*/  gl_EvalCoord2f (TYPE_7__*,float,float) ; 
 int /*<<< orphan*/  gl_EvalMesh1 (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_EvalMesh2 (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_EvalPoint1 (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_EvalPoint2 (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_Fogfv (TYPE_7__*,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  gl_FrontFace (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_Frustum (TYPE_7__*,float,float,float,float,float,float) ; 
 int /*<<< orphan*/  gl_Hint (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_IndexMask (TYPE_7__*,int) ; 
 int /*<<< orphan*/  gl_InitNames (TYPE_7__*) ; 
 int /*<<< orphan*/  gl_IsList (TYPE_7__*,int) ; 
 int /*<<< orphan*/  gl_LightModelfv (TYPE_7__*,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  gl_Lightfv (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*,int) ; 
 int /*<<< orphan*/  gl_LineStipple (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_LineWidth (TYPE_7__*,float) ; 
 int /*<<< orphan*/  gl_ListBase (TYPE_7__*,int) ; 
 int /*<<< orphan*/  gl_LoadIdentity (TYPE_7__*) ; 
 int /*<<< orphan*/  gl_LoadMatrixf (TYPE_7__*,float*) ; 
 int /*<<< orphan*/  gl_LoadName (TYPE_7__*,int) ; 
 int /*<<< orphan*/  gl_LogicOp (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_Map1f (TYPE_7__*,int /*<<< orphan*/ ,float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*,void*) ; 
 int /*<<< orphan*/  gl_Map2f (TYPE_7__*,int /*<<< orphan*/ ,float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*,void*) ; 
 int /*<<< orphan*/  gl_MapGrid1f (TYPE_7__*,int /*<<< orphan*/ ,float,float) ; 
 int /*<<< orphan*/  gl_MapGrid2f (TYPE_7__*,int /*<<< orphan*/ ,float,float,int /*<<< orphan*/ ,float,float) ; 
 int /*<<< orphan*/  gl_Materialfv (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  gl_MatrixMode (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_MultMatrixf (TYPE_7__*,float*) ; 
 int /*<<< orphan*/  gl_Ortho (TYPE_7__*,float,float,float,float,float,float) ; 
 int /*<<< orphan*/  gl_PassThrough (TYPE_7__*,float) ; 
 int /*<<< orphan*/  gl_PixelMapfv (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  gl_PixelTransferf (TYPE_7__*,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  gl_PixelZoom (TYPE_7__*,float,float) ; 
 int /*<<< orphan*/  gl_PointSize (TYPE_7__*,float) ; 
 int /*<<< orphan*/  gl_PolygonMode (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_PolygonOffset (TYPE_7__*,float,float) ; 
 int /*<<< orphan*/  gl_PolygonStipple (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_PopAttrib (TYPE_7__*) ; 
 int /*<<< orphan*/  gl_PopMatrix (TYPE_7__*) ; 
 int /*<<< orphan*/  gl_PopName (TYPE_7__*) ; 
 int /*<<< orphan*/  gl_PrioritizeTextures (TYPE_7__*,int,int*,float*) ; 
 int /*<<< orphan*/  gl_PushAttrib (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_PushMatrix (TYPE_7__*) ; 
 int /*<<< orphan*/  gl_PushName (TYPE_7__*,int) ; 
 int /*<<< orphan*/  gl_RasterPos4f (TYPE_7__*,float,float,float,float) ; 
 int /*<<< orphan*/  gl_ReadBuffer (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_Rectf (TYPE_7__*,float,float,float,float) ; 
 int /*<<< orphan*/  gl_Scalef (TYPE_7__*,float,float,float) ; 
 int /*<<< orphan*/  gl_Scissor (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_ShadeModel (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_StencilFunc (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gl_StencilMask (TYPE_7__*,int) ; 
 int /*<<< orphan*/  gl_StencilOp (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_TexEnvfv (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  gl_TexGenfv (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  gl_TexImage1D (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gl_image*) ; 
 int /*<<< orphan*/  gl_TexImage2D (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gl_image*) ; 
 int /*<<< orphan*/  gl_TexParameterfv (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  gl_TexSubImage1D (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gl_image*) ; 
 int /*<<< orphan*/  gl_TexSubImage2D (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gl_image*) ; 
 int /*<<< orphan*/  gl_Translatef (TYPE_7__*,float,float,float) ; 
 int /*<<< orphan*/  gl_Viewport (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_problem (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  gl_set_vertex_function (TYPE_7__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,float,float) ; 
 int /*<<< orphan*/  stub2 (TYPE_7__*,float,float,float) ; 
 int /*<<< orphan*/  stub3 (TYPE_7__*,float,float,float,float) ; 
 int /*<<< orphan*/  stub4 (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (TYPE_7__*,float,float,float) ; 
 int /*<<< orphan*/  stub6 (TYPE_7__*,float,float,float,float) ; 

__attribute__((used)) static void execute_list( GLcontext *ctx, GLuint list )
{
   Node *n;
   GLboolean done;
   OpCode opcode;

   if (!gl_IsList(ctx,list))
      return;

   ctx->CallDepth++;

   n = (Node *) HashLookup(ctx->Shared->DisplayList, list);

   done = GL_FALSE;
   while (!done) {
      opcode = n[0].opcode;

      switch (opcode) {
	 /* Frequently called functions: */
         case OPCODE_VERTEX2:
            (*ctx->Exec.Vertex2f)( ctx, n[1].f, n[2].f );
            break;
         case OPCODE_VERTEX3:
            (*ctx->Exec.Vertex3f)( ctx, n[1].f, n[2].f, n[3].f );
            break;
         case OPCODE_VERTEX4:
            (*ctx->Exec.Vertex4f)( ctx, n[1].f, n[2].f, n[3].f, n[4].f );
            break;
         case OPCODE_NORMAL:
            ctx->Current.Normal[0] = n[1].f;
            ctx->Current.Normal[1] = n[2].f;
            ctx->Current.Normal[2] = n[3].f;
            ctx->VB->MonoNormal = GL_FALSE;
            break;
	 case OPCODE_COLOR_4UB:
            (*ctx->Exec.Color4ub)( ctx, n[1].ub, n[2].ub, n[3].ub, n[4].ub );
	    break;
	 case OPCODE_COLOR_3F:
            (*ctx->Exec.Color3f)( ctx, n[1].f, n[2].f, n[3].f );
            break;
	 case OPCODE_COLOR_4F:
            (*ctx->Exec.Color4f)( ctx, n[1].f, n[2].f, n[3].f, n[4].f );
            break;
         case OPCODE_INDEX:
            ctx->Current.Index = n[1].ui;
            ctx->VB->MonoColor = GL_FALSE;
            break;
         case OPCODE_BEGIN:
            gl_Begin( ctx, n[1].e );
            break;
         case OPCODE_END:
            gl_End( ctx );
            break;
	 case OPCODE_TEXCOORD2:
	    ctx->Current.TexCoord[0] = n[1].f;
	    ctx->Current.TexCoord[1] = n[2].f;
            if (ctx->VB->TexCoordSize==4) {
               ctx->Current.TexCoord[2] = 0.0F;
               ctx->Current.TexCoord[3] = 1.0F;
            }
	    break;
	 case OPCODE_TEXCOORD4:
	    ctx->Current.TexCoord[0] = n[1].f;
	    ctx->Current.TexCoord[1] = n[2].f;
	    ctx->Current.TexCoord[2] = n[3].f;
	    ctx->Current.TexCoord[3] = n[4].f;
            if (ctx->VB->TexCoordSize==2) {
               /* Switch to 4-component texcoords */
               ctx->VB->TexCoordSize = 4;
               gl_set_vertex_function(ctx);
            }
	    break;

	 /* Everything Else: */
         case OPCODE_ACCUM:
	    gl_Accum( ctx, n[1].e, n[2].f );
	    break;
         case OPCODE_ALPHA_FUNC:
	    gl_AlphaFunc( ctx, n[1].e, n[2].f );
	    break;
         case OPCODE_BIND_TEXTURE:
            gl_BindTexture( ctx, n[1].e, n[2].ui );
            break;
	 case OPCODE_BITMAP:
	    gl_Bitmap( ctx, (GLsizei) n[1].i, (GLsizei) n[2].i,
		       n[3].f, n[4].f,
		       n[5].f, n[6].f,
		       (struct gl_image *) n[7].data );
	    break;
	 case OPCODE_BLEND_FUNC:
	    gl_BlendFunc( ctx, n[1].e, n[2].e );
	    break;
         case OPCODE_CALL_LIST:
	    /* Generated by glCallList(), don't add ListBase */
            if (ctx->CallDepth<MAX_LIST_NESTING) {
               execute_list( ctx, n[1].ui );
            }
            break;
         case OPCODE_CALL_LIST_OFFSET:
	    /* Generated by glCallLists() so we must add ListBase */
            if (ctx->CallDepth<MAX_LIST_NESTING) {
               execute_list( ctx, ctx->List.ListBase + n[1].ui );
            }
            break;
	 case OPCODE_CLEAR:
	    gl_Clear( ctx, n[1].bf );
	    break;
	 case OPCODE_CLEAR_COLOR:
	    gl_ClearColor( ctx, n[1].f, n[2].f, n[3].f, n[4].f );
	    break;
	 case OPCODE_CLEAR_ACCUM:
	    gl_ClearAccum( ctx, n[1].f, n[2].f, n[3].f, n[4].f );
	    break;
	 case OPCODE_CLEAR_DEPTH:
	    gl_ClearDepth( ctx, (GLclampd) n[1].f );
	    break;
	 case OPCODE_CLEAR_INDEX:
	    gl_ClearIndex( ctx, n[1].ui );
	    break;
	 case OPCODE_CLEAR_STENCIL:
	    gl_ClearStencil( ctx, n[1].i );
	    break;
         case OPCODE_CLIP_PLANE:
            {
               GLfloat equ[4];
               equ[0] = n[2].f;
               equ[1] = n[3].f;
               equ[2] = n[4].f;
               equ[3] = n[5].f;
               gl_ClipPlane( ctx, n[1].e, equ );
            }
            break;
	 case OPCODE_COLOR_MASK:
	    gl_ColorMask( ctx, n[1].b, n[2].b, n[3].b, n[4].b );
	    break;
	 case OPCODE_COLOR_MATERIAL:
	    gl_ColorMaterial( ctx, n[1].e, n[2].e );
	    break;
         case OPCODE_COLOR_TABLE:
            gl_ColorTable( ctx, n[1].e, n[2].e, (struct gl_image *) n[3].data);
            break;
         case OPCODE_COLOR_SUB_TABLE:
            gl_ColorSubTable( ctx, n[1].e, n[2].i,
                              (struct gl_image *) n[3].data);
            break;
	 case OPCODE_COPY_PIXELS:
	    gl_CopyPixels( ctx, n[1].i, n[2].i,
			   (GLsizei) n[3].i, (GLsizei) n[4].i, n[5].e );
	    break;
         case OPCODE_COPY_TEX_IMAGE1D:
	    gl_CopyTexImage1D( ctx, n[1].e, n[2].i, n[3].e, n[4].i,
                               n[5].i, n[6].i, n[7].i );
            break;
         case OPCODE_COPY_TEX_IMAGE2D:
	    gl_CopyTexImage2D( ctx, n[1].e, n[2].i, n[3].e, n[4].i,
                               n[5].i, n[6].i, n[7].i, n[8].i );
            break;
         case OPCODE_COPY_TEX_SUB_IMAGE1D:
	    gl_CopyTexSubImage1D( ctx, n[1].e, n[2].i, n[3].i, n[4].i,
                                  n[5].i, n[6].i );
            break;
         case OPCODE_COPY_TEX_SUB_IMAGE2D:
	    gl_CopyTexSubImage2D( ctx, n[1].e, n[2].i, n[3].i, n[4].i,
                                  n[5].i, n[6].i, n[7].i, n[8].i );
            break;
	 case OPCODE_CULL_FACE:
	    gl_CullFace( ctx, n[1].e );
	    break;
	 case OPCODE_DEPTH_FUNC:
	    gl_DepthFunc( ctx, n[1].e );
	    break;
	 case OPCODE_DEPTH_MASK:
	    gl_DepthMask( ctx, n[1].b );
	    break;
	 case OPCODE_DEPTH_RANGE:
	    gl_DepthRange( ctx, (GLclampd) n[1].f, (GLclampd) n[2].f );
	    break;
	 case OPCODE_DISABLE:
	    gl_Disable( ctx, n[1].e );
	    break;
	 case OPCODE_DRAW_BUFFER:
	    gl_DrawBuffer( ctx, n[1].e );
	    break;
	 case OPCODE_DRAW_PIXELS:
	    gl_DrawPixels( ctx, (GLsizei) n[1].i, (GLsizei) n[2].i,
			   n[3].e, n[4].e, n[5].data );
	    break;
	 case OPCODE_EDGE_FLAG:
            ctx->Current.EdgeFlag = n[1].b;
            break;
	 case OPCODE_ENABLE:
	    gl_Enable( ctx, n[1].e );
	    break;
	 case OPCODE_EVALCOORD1:
	    gl_EvalCoord1f( ctx, n[1].f );
	    break;
	 case OPCODE_EVALCOORD2:
	    gl_EvalCoord2f( ctx, n[1].f, n[2].f );
	    break;
	 case OPCODE_EVALMESH1:
	    gl_EvalMesh1( ctx, n[1].e, n[2].i, n[3].i );
	    break;
	 case OPCODE_EVALMESH2:
	    gl_EvalMesh2( ctx, n[1].e, n[2].i, n[3].i, n[4].i, n[5].i );
	    break;
	 case OPCODE_EVALPOINT1:
	    gl_EvalPoint1( ctx, n[1].i );
	    break;
	 case OPCODE_EVALPOINT2:
	    gl_EvalPoint2( ctx, n[1].i, n[2].i );
	    break;
	 case OPCODE_FOG:
	    {
	       GLfloat p[4];
	       p[0] = n[2].f;
	       p[1] = n[3].f;
	       p[2] = n[4].f;
	       p[3] = n[5].f;
	       gl_Fogfv( ctx, n[1].e, p );
	    }
	    break;
	 case OPCODE_FRONT_FACE:
	    gl_FrontFace( ctx, n[1].e );
	    break;
         case OPCODE_FRUSTUM:
            gl_Frustum( ctx, n[1].f, n[2].f, n[3].f, n[4].f, n[5].f, n[6].f );
            break;
	 case OPCODE_HINT:
	    gl_Hint( ctx, n[1].e, n[2].e );
	    break;
	 case OPCODE_INDEX_MASK:
	    gl_IndexMask( ctx, n[1].ui );
	    break;
	 case OPCODE_INIT_NAMES:
	    gl_InitNames( ctx );
	    break;
         case OPCODE_LIGHT:
	    {
	       GLfloat p[4];
	       p[0] = n[3].f;
	       p[1] = n[4].f;
	       p[2] = n[5].f;
	       p[3] = n[6].f;
	       gl_Lightfv( ctx, n[1].e, n[2].e, p, 4 );
	    }
	    break;
         case OPCODE_LIGHT_MODEL:
	    {
	       GLfloat p[4];
	       p[0] = n[2].f;
	       p[1] = n[3].f;
	       p[2] = n[4].f;
	       p[3] = n[5].f;
	       gl_LightModelfv( ctx, n[1].e, p );
	    }
	    break;
	 case OPCODE_LINE_STIPPLE:
	    gl_LineStipple( ctx, n[1].i, n[2].us );
	    break;
	 case OPCODE_LINE_WIDTH:
	    gl_LineWidth( ctx, n[1].f );
	    break;
	 case OPCODE_LIST_BASE:
	    gl_ListBase( ctx, n[1].ui );
	    break;
	 case OPCODE_LOAD_IDENTITY:
            gl_LoadIdentity( ctx );
            break;
	 case OPCODE_LOAD_MATRIX:
	    if (sizeof(Node)==sizeof(GLfloat)) {
	       gl_LoadMatrixf( ctx, &n[1].f );
	    }
	    else {
	       GLfloat m[16];
	       GLuint i;
	       for (i=0;i<16;i++) {
		  m[i] = n[1+i].f;
	       }
	       gl_LoadMatrixf( ctx, m );
	    }
	    break;
	 case OPCODE_LOAD_NAME:
	    gl_LoadName( ctx, n[1].ui );
	    break;
	 case OPCODE_LOGIC_OP:
	    gl_LogicOp( ctx, n[1].e );
	    break;
	 case OPCODE_MAP1:
	    gl_Map1f( ctx, n[1].e, n[2].f, n[3].f,
                      n[4].i, n[5].i, (GLfloat *) n[6].data, GL_TRUE );
	    break;
	 case OPCODE_MAP2:
	    gl_Map2f( ctx, n[1].e,
                      n[2].f, n[3].f,  /* u1, u2 */
		      n[6].i, n[8].i,  /* ustride, uorder */
		      n[4].f, n[5].f,  /* v1, v2 */
		      n[7].i, n[9].i,  /* vstride, vorder */
		      (GLfloat *) n[10].data,
                      GL_TRUE);
	    break;
	 case OPCODE_MAPGRID1:
	    gl_MapGrid1f( ctx, n[1].i, n[2].f, n[3].f );
	    break;
	 case OPCODE_MAPGRID2:
	    gl_MapGrid2f( ctx, n[1].i, n[2].f, n[3].f, n[4].i, n[5].f, n[6].f);
	    break;
	 case OPCODE_MATERIAL:
	    {
	       GLfloat params[4];
	       params[0] = n[3].f;
	       params[1] = n[4].f;
	       params[2] = n[5].f;
	       params[3] = n[6].f;
	       gl_Materialfv( ctx, n[1].e, n[2].e, params );
	    }
	    break;
         case OPCODE_MATRIX_MODE:
            gl_MatrixMode( ctx, n[1].e );
            break;
	 case OPCODE_MULT_MATRIX:
	    if (sizeof(Node)==sizeof(GLfloat)) {
	       gl_MultMatrixf( ctx, &n[1].f );
	    }
	    else {
	       GLfloat m[16];
	       GLuint i;
	       for (i=0;i<16;i++) {
		  m[i] = n[1+i].f;
	       }
	       gl_MultMatrixf( ctx, m );
	    }
	    break;
         case OPCODE_ORTHO:
            gl_Ortho( ctx, n[1].f, n[2].f, n[3].f, n[4].f, n[5].f, n[6].f );
            break;
	 case OPCODE_PASSTHROUGH:
	    gl_PassThrough( ctx, n[1].f );
	    break;
	 case OPCODE_PIXEL_MAP:
	    gl_PixelMapfv( ctx, n[1].e, n[2].i, (GLfloat *) n[3].data );
	    break;
	 case OPCODE_PIXEL_TRANSFER:
	    gl_PixelTransferf( ctx, n[1].e, n[2].f );
	    break;
	 case OPCODE_PIXEL_ZOOM:
	    gl_PixelZoom( ctx, n[1].f, n[2].f );
	    break;
	 case OPCODE_POINT_SIZE:
	    gl_PointSize( ctx, n[1].f );
	    break;
	 case OPCODE_POLYGON_MODE:
	    gl_PolygonMode( ctx, n[1].e, n[2].e );
	    break;
	 case OPCODE_POLYGON_STIPPLE:
	    gl_PolygonStipple( ctx, (GLubyte *) n[1].data );
	    break;
	 case OPCODE_POLYGON_OFFSET:
	    gl_PolygonOffset( ctx, n[1].f, n[2].f );
	    break;
	 case OPCODE_POP_ATTRIB:
	    gl_PopAttrib( ctx );
	    break;
	 case OPCODE_POP_MATRIX:
	    gl_PopMatrix( ctx );
	    break;
	 case OPCODE_POP_NAME:
	    gl_PopName( ctx );
	    break;
	 case OPCODE_PRIORITIZE_TEXTURE:
            gl_PrioritizeTextures( ctx, 1, &n[1].ui, &n[2].f );
	    break;
	 case OPCODE_PUSH_ATTRIB:
	    gl_PushAttrib( ctx, n[1].bf );
	    break;
	 case OPCODE_PUSH_MATRIX:
	    gl_PushMatrix( ctx );
	    break;
	 case OPCODE_PUSH_NAME:
	    gl_PushName( ctx, n[1].ui );
	    break;
	 case OPCODE_RASTER_POS:
            gl_RasterPos4f( ctx, n[1].f, n[2].f, n[3].f, n[4].f );
	    break;
	 case OPCODE_READ_BUFFER:
	    gl_ReadBuffer( ctx, n[1].e );
	    break;
         case OPCODE_RECTF:
            gl_Rectf( ctx, n[1].f, n[2].f, n[3].f, n[4].f );
            break;
         case OPCODE_SCALE:
            gl_Scalef( ctx, n[1].f, n[2].f, n[3].f );
            break;
	 case OPCODE_SCISSOR:
	    gl_Scissor( ctx, n[1].i, n[2].i, n[3].i, n[4].i );
	    break;
	 case OPCODE_SHADE_MODEL:
	    gl_ShadeModel( ctx, n[1].e );
	    break;
	 case OPCODE_STENCIL_FUNC:
	    gl_StencilFunc( ctx, n[1].e, n[2].i, n[3].ui );
	    break;
	 case OPCODE_STENCIL_MASK:
	    gl_StencilMask( ctx, n[1].ui );
	    break;
	 case OPCODE_STENCIL_OP:
	    gl_StencilOp( ctx, n[1].e, n[2].e, n[3].e );
	    break;
         case OPCODE_TEXENV:
            {
               GLfloat params[4];
               params[0] = n[3].f;
               params[1] = n[4].f;
               params[2] = n[5].f;
               params[3] = n[6].f;
               gl_TexEnvfv( ctx, n[1].e, n[2].e, params );
            }
            break;
         case OPCODE_TEXGEN:
            {
               GLfloat params[4];
               params[0] = n[3].f;
               params[1] = n[4].f;
               params[2] = n[5].f;
               params[3] = n[6].f;
               gl_TexGenfv( ctx, n[1].e, n[2].e, params );
            }
            break;
         case OPCODE_TEXPARAMETER:
            {
               GLfloat params[4];
               params[0] = n[3].f;
               params[1] = n[4].f;
               params[2] = n[5].f;
               params[3] = n[6].f;
               gl_TexParameterfv( ctx, n[1].e, n[2].e, params );
            }
            break;
	 case OPCODE_TEX_IMAGE1D:
	    gl_TexImage1D( ctx,
                           n[1].e, /* target */
                           n[2].i, /* level */
                           n[3].i, /* components */
                           n[4].i, /* width */
                           n[5].e, /* border */
                           n[6].e, /* format */
                           n[7].e, /* type */
                           (struct gl_image *) n[8].data );
	    break;
	 case OPCODE_TEX_IMAGE2D:
	    gl_TexImage2D( ctx,
                           n[1].e, /* target */
                           n[2].i, /* level */
                           n[3].i, /* components */
                           n[4].i, /* width */
                           n[5].i, /* height */
                           n[6].e, /* border */
                           n[7].e, /* format */
                           n[8].e, /* type */
                           (struct gl_image *) n[9].data );
	    break;
         case OPCODE_TEX_SUB_IMAGE1D:
            gl_TexSubImage1D( ctx, n[1].e, n[2].i, n[3].i, n[4].i, n[5].e,
                              n[6].e, (struct gl_image *) n[7].data );
            break;
         case OPCODE_TEX_SUB_IMAGE2D:
            gl_TexSubImage2D( ctx, n[1].e, n[2].i, n[3].i, n[4].i, n[5].e,
                              n[6].i, n[7].e, n[8].e,
                              (struct gl_image *) n[9].data );
            break;
         case OPCODE_TRANSLATE:
            gl_Translatef( ctx, n[1].f, n[2].f, n[3].f );
            break;
	 case OPCODE_VIEWPORT:
	    gl_Viewport( ctx,
                         n[1].i, n[2].i, (GLsizei) n[3].i, (GLsizei) n[4].i );
	    break;
	 case OPCODE_CONTINUE:
	    n = (Node *) n[1].next;
	    break;
	 case OPCODE_END_OF_LIST:
	    done = GL_TRUE;
	    break;
	 default:
            {
               char msg[1000];
               sprintf(msg, "Error in execute_list: opcode=%d", (int) opcode);
               gl_problem( ctx, msg );
            }
            done = GL_TRUE;
      }

      /* increment n to point to next compiled command */
      if (opcode!=OPCODE_CONTINUE) {
	 n += InstSize[opcode];
      }

   }
   ctx->CallDepth--;
}