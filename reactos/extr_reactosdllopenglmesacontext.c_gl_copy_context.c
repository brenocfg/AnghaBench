#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gl_viewport_attrib {int dummy; } ;
struct gl_transform_attrib {int dummy; } ;
struct gl_texture_attrib {int dummy; } ;
struct gl_stencil_attrib {int dummy; } ;
struct gl_scissor_attrib {int dummy; } ;
struct gl_polygon_attrib {int dummy; } ;
struct gl_point_attrib {int dummy; } ;
struct gl_pixel_attrib {int dummy; } ;
struct gl_list_attrib {int dummy; } ;
struct gl_line_attrib {int dummy; } ;
struct gl_light_attrib {int dummy; } ;
struct gl_hint_attrib {int dummy; } ;
struct gl_fog_attrib {int dummy; } ;
struct gl_eval_attrib {int dummy; } ;
struct gl_depthbuffer_attrib {int dummy; } ;
struct gl_current_attrib {int dummy; } ;
struct gl_colorbuffer_attrib {int dummy; } ;
struct gl_accum_attrib {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  Viewport; int /*<<< orphan*/  Transform; int /*<<< orphan*/  Texture; int /*<<< orphan*/  Stencil; int /*<<< orphan*/  Scissor; int /*<<< orphan*/ * PolygonStipple; int /*<<< orphan*/  Polygon; int /*<<< orphan*/  Point; int /*<<< orphan*/  Pixel; int /*<<< orphan*/  List; int /*<<< orphan*/  Line; int /*<<< orphan*/  Light; int /*<<< orphan*/  Hint; int /*<<< orphan*/  Fog; int /*<<< orphan*/  Eval; int /*<<< orphan*/  Depth; int /*<<< orphan*/  Current; int /*<<< orphan*/  Color; int /*<<< orphan*/  Accum; } ;
typedef  int GLuint ;
typedef  TYPE_1__ GLcontext ;

/* Variables and functions */
 int GL_ACCUM_BUFFER_BIT ; 
 int GL_COLOR_BUFFER_BIT ; 
 int GL_CURRENT_BIT ; 
 int GL_DEPTH_BUFFER_BIT ; 
 int GL_ENABLE_BIT ; 
 int GL_EVAL_BIT ; 
 int GL_FOG_BIT ; 
 int GL_HINT_BIT ; 
 int GL_LIGHTING_BIT ; 
 int GL_LINE_BIT ; 
 int GL_LIST_BIT ; 
 int GL_PIXEL_MODE_BIT ; 
 int GL_POINT_BIT ; 
 int GL_POLYGON_BIT ; 
 int GL_POLYGON_STIPPLE_BIT ; 
 int GL_SCISSOR_BIT ; 
 int GL_STENCIL_BUFFER_BIT ; 
 int GL_TEXTURE_BIT ; 
 int GL_TRANSFORM_BIT ; 
 int GL_VIEWPORT_BIT ; 
 int /*<<< orphan*/  MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void gl_copy_context( const GLcontext *src, GLcontext *dst, GLuint mask )
{
   if (mask & GL_ACCUM_BUFFER_BIT) {
      MEMCPY( &dst->Accum, &src->Accum, sizeof(struct gl_accum_attrib) );
   }
   if (mask & GL_COLOR_BUFFER_BIT) {
      MEMCPY( &dst->Color, &src->Color, sizeof(struct gl_colorbuffer_attrib) );
   }
   if (mask & GL_CURRENT_BIT) {
      MEMCPY( &dst->Current, &src->Current, sizeof(struct gl_current_attrib) );
   }
   if (mask & GL_DEPTH_BUFFER_BIT) {
      MEMCPY( &dst->Depth, &src->Depth, sizeof(struct gl_depthbuffer_attrib) );
   }
   if (mask & GL_ENABLE_BIT) {
      /* no op */
   }
   if (mask & GL_EVAL_BIT) {
      MEMCPY( &dst->Eval, &src->Eval, sizeof(struct gl_eval_attrib) );
   }
   if (mask & GL_FOG_BIT) {
      MEMCPY( &dst->Fog, &src->Fog, sizeof(struct gl_fog_attrib) );
   }
   if (mask & GL_HINT_BIT) {
      MEMCPY( &dst->Hint, &src->Hint, sizeof(struct gl_hint_attrib) );
   }
   if (mask & GL_LIGHTING_BIT) {
      MEMCPY( &dst->Light, &src->Light, sizeof(struct gl_light_attrib) );
   }
   if (mask & GL_LINE_BIT) {
      MEMCPY( &dst->Line, &src->Line, sizeof(struct gl_line_attrib) );
   }
   if (mask & GL_LIST_BIT) {
      MEMCPY( &dst->List, &src->List, sizeof(struct gl_list_attrib) );
   }
   if (mask & GL_PIXEL_MODE_BIT) {
      MEMCPY( &dst->Pixel, &src->Pixel, sizeof(struct gl_pixel_attrib) );
   }
   if (mask & GL_POINT_BIT) {
      MEMCPY( &dst->Point, &src->Point, sizeof(struct gl_point_attrib) );
   }
   if (mask & GL_POLYGON_BIT) {
      MEMCPY( &dst->Polygon, &src->Polygon, sizeof(struct gl_polygon_attrib) );
   }
   if (mask & GL_POLYGON_STIPPLE_BIT) {
      /* Use loop instead of MEMCPY due to problem with Portland Group's
       * C compiler.  Reported by John Stone.
       */
      int i;
      for (i=0;i<32;i++) {
         dst->PolygonStipple[i] = src->PolygonStipple[i];
      }
   }
   if (mask & GL_SCISSOR_BIT) {
      MEMCPY( &dst->Scissor, &src->Scissor, sizeof(struct gl_scissor_attrib) );
   }
   if (mask & GL_STENCIL_BUFFER_BIT) {
      MEMCPY( &dst->Stencil, &src->Stencil, sizeof(struct gl_stencil_attrib) );
   }
   if (mask & GL_TEXTURE_BIT) {
      MEMCPY( &dst->Texture, &src->Texture, sizeof(struct gl_texture_attrib) );
   }
   if (mask & GL_TRANSFORM_BIT) {
      MEMCPY( &dst->Transform, &src->Transform, sizeof(struct gl_transform_attrib) );
   }
   if (mask & GL_VIEWPORT_BIT) {
      MEMCPY( &dst->Viewport, &src->Viewport, sizeof(struct gl_viewport_attrib) );
   }
}