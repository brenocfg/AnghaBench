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
struct vertex_buffer {size_t Count; int* MaterialMask; int /*<<< orphan*/  MonoMaterial; struct gl_material** Material; } ;
struct gl_material {scalar_t__ Shininess; scalar_t__ AmbientIndex; scalar_t__ DiffuseIndex; scalar_t__ SpecularIndex; int /*<<< orphan*/  Emission; int /*<<< orphan*/  Specular; int /*<<< orphan*/  Diffuse; int /*<<< orphan*/  Ambient; } ;
struct TYPE_5__ {struct gl_material* Material; } ;
struct TYPE_6__ {int /*<<< orphan*/  NewState; TYPE_1__ Light; struct vertex_buffer* VB; } ;
typedef  int GLuint ;
typedef  scalar_t__ GLfloat ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int BACK_AMBIENT_BIT ; 
 int BACK_DIFFUSE_BIT ; 
 int BACK_EMISSION_BIT ; 
 int BACK_INDEXES_BIT ; 
 int BACK_SHININESS_BIT ; 
 int BACK_SPECULAR_BIT ; 
 scalar_t__ CLAMP (scalar_t__ const,float,float) ; 
 int /*<<< orphan*/  COPY_4V (int /*<<< orphan*/ ,scalar_t__ const*) ; 
 int FRONT_AMBIENT_BIT ; 
 int FRONT_DIFFUSE_BIT ; 
 int FRONT_EMISSION_BIT ; 
 int FRONT_INDEXES_BIT ; 
 int FRONT_SHININESS_BIT ; 
 int FRONT_SPECULAR_BIT ; 
 int /*<<< orphan*/  GL_FALSE ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  NEW_LIGHTING ; 
 int /*<<< orphan*/  gl_compute_material_shine_table (struct gl_material*) ; 

void gl_set_material( GLcontext *ctx, GLuint bitmask, const GLfloat *params )
{
   struct gl_material *mat;

   if (INSIDE_BEGIN_END(ctx)) {
      struct vertex_buffer *VB = ctx->VB;
      /* Save per-vertex material changes in the Vertex Buffer.
       * The update_material function will eventually update the global
       * ctx->Light.Material values.
       */
      mat = VB->Material[VB->Count];
      VB->MaterialMask[VB->Count] |= bitmask;
      VB->MonoMaterial = GL_FALSE;
   }
   else {
      /* just update the global material property */
      mat = ctx->Light.Material;
      ctx->NewState |= NEW_LIGHTING;
   }

   if (bitmask & FRONT_AMBIENT_BIT) {
      COPY_4V( mat[0].Ambient, params );
   }
   if (bitmask & BACK_AMBIENT_BIT) {
      COPY_4V( mat[1].Ambient, params );
   }
   if (bitmask & FRONT_DIFFUSE_BIT) {
      COPY_4V( mat[0].Diffuse, params );
   }
   if (bitmask & BACK_DIFFUSE_BIT) {
      COPY_4V( mat[1].Diffuse, params );
   }
   if (bitmask & FRONT_SPECULAR_BIT) {
      COPY_4V( mat[0].Specular, params );
   }
   if (bitmask & BACK_SPECULAR_BIT) {
      COPY_4V( mat[1].Specular, params );
   }
   if (bitmask & FRONT_EMISSION_BIT) {
      COPY_4V( mat[0].Emission, params );
   }
   if (bitmask & BACK_EMISSION_BIT) {
      COPY_4V( mat[1].Emission, params );
   }
   if (bitmask & FRONT_SHININESS_BIT) {
      GLfloat shininess = CLAMP( params[0], 0.0F, 128.0F );
      if (mat[0].Shininess != shininess) {
         mat[0].Shininess = shininess;
         gl_compute_material_shine_table( &mat[0] );
      }
   }
   if (bitmask & BACK_SHININESS_BIT) {
      GLfloat shininess = CLAMP( params[0], 0.0F, 128.0F );
      if (mat[1].Shininess != shininess) {
         mat[1].Shininess = shininess;
         gl_compute_material_shine_table( &mat[1] );
      }
   }
   if (bitmask & FRONT_INDEXES_BIT) {
      mat[0].AmbientIndex = params[0];
      mat[0].DiffuseIndex = params[1];
      mat[0].SpecularIndex = params[2];
   }
   if (bitmask & BACK_INDEXES_BIT) {
      mat[1].AmbientIndex = params[0];
      mat[1].DiffuseIndex = params[1];
      mat[1].SpecularIndex = params[2];
   }
}