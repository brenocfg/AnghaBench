#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_11__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
struct TYPE_37__ {scalar_t__ GenModeS; int TexGenEnabled; scalar_t__ GenModeT; scalar_t__ Enabled; } ;
struct TYPE_36__ {scalar_t__ Enabled; } ;
struct TYPE_30__ {scalar_t__ TwoSide; } ;
struct TYPE_35__ {scalar_t__ ShadeModel; TYPE_2__ Model; scalar_t__ Enabled; } ;
struct TYPE_34__ {int /*<<< orphan*/  (* UpdateState ) (TYPE_11__*) ;int /*<<< orphan*/ * RectFunc; int /*<<< orphan*/ * QuadFunc; int /*<<< orphan*/ * TriangleFunc; int /*<<< orphan*/ * LineFunc; int /*<<< orphan*/ * PointsFunc; int /*<<< orphan*/  ReadDepthSpanInt; int /*<<< orphan*/  ReadDepthSpanFloat; void* DepthTestPixels; void* DepthTestSpan; int /*<<< orphan*/  ClearDepthBuffer; int /*<<< orphan*/  AllocDepthBuffer; int /*<<< orphan*/  (* Dither ) (TYPE_11__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_33__ {int Func; scalar_t__ Mask; } ;
struct TYPE_32__ {int X; int Y; int Width; int Height; scalar_t__ Enabled; } ;
struct TYPE_31__ {int Xmin; int Ymin; int Xmax; int Width; int Ymax; int Height; } ;
struct TYPE_29__ {int CullBits; scalar_t__ CullFaceMode; int OffsetAny; scalar_t__ CullFlag; scalar_t__ Unfilled; scalar_t__ OffsetFill; scalar_t__ OffsetLine; scalar_t__ OffsetPoint; } ;
struct TYPE_27__ {scalar_t__ SWLogicOpEnabled; scalar_t__ SWmasking; scalar_t__ BlendEnabled; int /*<<< orphan*/  DitherFlag; } ;
struct TYPE_28__ {int NewState; double PointZoffset; double LineZoffset; double PolygonZoffset; scalar_t__ RenderMode; TYPE_6__ Driver; TYPE_5__ Depth; TYPE_4__ Scissor; TYPE_3__* Buffer; void* DirectTriangles; TYPE_7__ Light; TYPE_1__ Polygon; void* MonoPixels; TYPE_10__ Color; TYPE_9__ Texture; TYPE_8__ Fog; void* MutablePixels; void* NeedNormals; } ;
typedef  TYPE_11__ GLcontext ;
typedef  int GLboolean ;

/* Variables and functions */
 scalar_t__ GL_BACK ; 
 void* GL_FALSE ; 
 scalar_t__ GL_FRONT ; 
 scalar_t__ GL_FRONT_AND_BACK ; 
#define  GL_GREATER 129 
#define  GL_LESS 128 
 scalar_t__ GL_RENDER ; 
 scalar_t__ GL_SMOOTH ; 
 scalar_t__ GL_SPHERE_MAP ; 
 void* GL_TRUE ; 
 int NEW_LIGHTING ; 
 int NEW_POLYGON ; 
 int NEW_RASTER_OPS ; 
 int NEW_TEXTURING ; 
 int S_BIT ; 
 int T_BIT ; 
 int /*<<< orphan*/  gl_alloc_depth_buffer ; 
 int /*<<< orphan*/  gl_clear_depth_buffer ; 
 void* gl_depth_test_pixels_generic ; 
 void* gl_depth_test_pixels_greater ; 
 void* gl_depth_test_pixels_less ; 
 void* gl_depth_test_span_generic ; 
 void* gl_depth_test_span_greater ; 
 void* gl_depth_test_span_less ; 
 int /*<<< orphan*/  gl_read_depth_span_float ; 
 int /*<<< orphan*/  gl_read_depth_span_int ; 
 int /*<<< orphan*/  gl_set_color_function (TYPE_11__*) ; 
 int /*<<< orphan*/  gl_set_line_function (TYPE_11__*) ; 
 int /*<<< orphan*/  gl_set_point_function (TYPE_11__*) ; 
 int /*<<< orphan*/  gl_set_quad_function (TYPE_11__*) ; 
 int /*<<< orphan*/  gl_set_triangle_function (TYPE_11__*) ; 
 int /*<<< orphan*/  gl_set_vertex_function (TYPE_11__*) ; 
 int /*<<< orphan*/  gl_update_lighting (TYPE_11__*) ; 
 int /*<<< orphan*/  gl_update_texture_state (TYPE_11__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_11__*) ; 
 int /*<<< orphan*/  update_clipmask (TYPE_11__*) ; 
 int /*<<< orphan*/  update_pixel_logic (TYPE_11__*) ; 
 int /*<<< orphan*/  update_pixel_masking (TYPE_11__*) ; 
 int /*<<< orphan*/  update_rasterflags (TYPE_11__*) ; 

void gl_update_state( GLcontext *ctx )
{
   if (ctx->NewState & NEW_RASTER_OPS) {
      update_pixel_logic(ctx);
      update_pixel_masking(ctx);
      update_rasterflags(ctx);
      if (ctx->Driver.Dither) {
         (*ctx->Driver.Dither)( ctx, ctx->Color.DitherFlag );
      }
   }

   if (ctx->NewState & (NEW_RASTER_OPS | NEW_LIGHTING)) {
      update_clipmask(ctx);
   }

   if (ctx->NewState & NEW_LIGHTING) {
      gl_update_lighting(ctx);
      gl_set_color_function(ctx);
   }

   if (ctx->NewState & NEW_TEXTURING) {
      gl_update_texture_state(ctx);
   }

   if (ctx->NewState & (NEW_LIGHTING | NEW_TEXTURING)) {
      /* Check if normal vectors are needed */
      GLboolean sphereGen = ctx->Texture.Enabled
         && ((ctx->Texture.GenModeS==GL_SPHERE_MAP
              && (ctx->Texture.TexGenEnabled & S_BIT))
             || (ctx->Texture.GenModeT==GL_SPHERE_MAP
                 && (ctx->Texture.TexGenEnabled & T_BIT)));
      if (ctx->Light.Enabled || sphereGen) {
         ctx->NeedNormals = GL_TRUE;
      }
      else {
         ctx->NeedNormals = GL_FALSE;
      }
   }

   if (ctx->NewState & NEW_RASTER_OPS) {
      /* Check if incoming colors can be modified during rasterization */
      if (ctx->Fog.Enabled ||
          ctx->Texture.Enabled ||
          ctx->Color.BlendEnabled ||
          ctx->Color.SWmasking ||
          ctx->Color.SWLogicOpEnabled) {
         ctx->MutablePixels = GL_TRUE;
      }
      else {
         ctx->MutablePixels = GL_FALSE;
      }
   }

   if (ctx->NewState & (NEW_RASTER_OPS | NEW_LIGHTING)) {
      /* Check if all pixels generated are likely to be the same color */
      if (ctx->Light.ShadeModel==GL_SMOOTH ||
          ctx->Light.Enabled ||
          ctx->Fog.Enabled ||
          ctx->Texture.Enabled ||
          ctx->Color.BlendEnabled ||
          ctx->Color.SWmasking ||
          ctx->Color.SWLogicOpEnabled) {
         ctx->MonoPixels = GL_FALSE;       /* pixels probably multicolored */
      }
      else {
         /* pixels will all be same color,
          * only glColor() can invalidate this.
          */
         ctx->MonoPixels = GL_TRUE;
      }
   }

   if (ctx->NewState & NEW_POLYGON) {
      /* Setup CullBits bitmask */
      ctx->Polygon.CullBits = 0;
      if (ctx->Polygon.CullFlag) {
         if (ctx->Polygon.CullFaceMode==GL_FRONT ||
             ctx->Polygon.CullFaceMode==GL_FRONT_AND_BACK) {
            ctx->Polygon.CullBits |= 1;
         }
         if (ctx->Polygon.CullFaceMode==GL_BACK ||
             ctx->Polygon.CullFaceMode==GL_FRONT_AND_BACK) {
            ctx->Polygon.CullBits |= 2;
         }
      }
      /* Any Polygon offsets enabled? */
      ctx->Polygon.OffsetAny = ctx->Polygon.OffsetPoint ||
                               ctx->Polygon.OffsetLine ||
                               ctx->Polygon.OffsetFill;
      /* reset Z offsets now */
      ctx->PointZoffset   = 0.0;
      ctx->LineZoffset    = 0.0;
      ctx->PolygonZoffset = 0.0;
   }

   if (ctx->NewState & (NEW_POLYGON | NEW_LIGHTING)) {
      /* Determine if we can directly call the triangle rasterizer */
      if (   ctx->Polygon.Unfilled
          || ctx->Polygon.OffsetAny
          || ctx->Polygon.CullFlag
          || ctx->Light.Model.TwoSide
          || ctx->RenderMode!=GL_RENDER) {
         ctx->DirectTriangles = GL_FALSE;
      }
      else {
         ctx->DirectTriangles = GL_TRUE;
      }
   }

   /* update scissor region */
   ctx->Buffer->Xmin = 0;
   ctx->Buffer->Ymin = 0;
   ctx->Buffer->Xmax = ctx->Buffer->Width-1;
   ctx->Buffer->Ymax = ctx->Buffer->Height-1;
   if (ctx->Scissor.Enabled) {
      if (ctx->Scissor.X > ctx->Buffer->Xmin) {
         ctx->Buffer->Xmin = ctx->Scissor.X;
      }
      if (ctx->Scissor.Y > ctx->Buffer->Ymin) {
         ctx->Buffer->Ymin = ctx->Scissor.Y;
      }
      if (ctx->Scissor.X + ctx->Scissor.Width - 1 < ctx->Buffer->Xmax) {
         ctx->Buffer->Xmax = ctx->Scissor.X + ctx->Scissor.Width - 1;
      }
      if (ctx->Scissor.Y + ctx->Scissor.Height - 1 < ctx->Buffer->Ymax) {
         ctx->Buffer->Ymax = ctx->Scissor.Y + ctx->Scissor.Height - 1;
      }
   }

   /*
    * Update Device Driver interface
    */
   if (ctx->NewState & NEW_RASTER_OPS) {
      ctx->Driver.AllocDepthBuffer = gl_alloc_depth_buffer;
      ctx->Driver.ClearDepthBuffer = gl_clear_depth_buffer;
      if (ctx->Depth.Mask) {
         switch (ctx->Depth.Func) {
            case GL_LESS:
               ctx->Driver.DepthTestSpan = gl_depth_test_span_less;
               ctx->Driver.DepthTestPixels = gl_depth_test_pixels_less;
               break;
            case GL_GREATER:
               ctx->Driver.DepthTestSpan = gl_depth_test_span_greater;
               ctx->Driver.DepthTestPixels = gl_depth_test_pixels_greater;
               break;
            default:
               ctx->Driver.DepthTestSpan = gl_depth_test_span_generic;
               ctx->Driver.DepthTestPixels = gl_depth_test_pixels_generic;
         }
      }
      else {
         ctx->Driver.DepthTestSpan = gl_depth_test_span_generic;
         ctx->Driver.DepthTestPixels = gl_depth_test_pixels_generic;
      }
      ctx->Driver.ReadDepthSpanFloat = gl_read_depth_span_float;
      ctx->Driver.ReadDepthSpanInt = gl_read_depth_span_int;
   }

   ctx->Driver.PointsFunc = NULL;
   ctx->Driver.LineFunc = NULL;
   ctx->Driver.TriangleFunc = NULL;
   ctx->Driver.QuadFunc = NULL;
   ctx->Driver.RectFunc = NULL;

   if (ctx->Driver.UpdateState) {
      (*ctx->Driver.UpdateState)(ctx);
   }

   gl_set_point_function(ctx);
   gl_set_line_function(ctx);
   gl_set_triangle_function(ctx);
   gl_set_quad_function(ctx);

   gl_set_vertex_function(ctx);

   ctx->NewState = 0;
}