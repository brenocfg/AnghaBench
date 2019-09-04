#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct gl_material {float* Emission; int* Ambient; int* Diffuse; int* Specular; } ;
struct gl_light {int* Ambient; int** MatAmbient; int** MatDiffuse; int* Diffuse; int** MatSpecular; int* Specular; float* VP_inf_norm; float* Position; float* h_inf_norm; float* NormDirection; float* Direction; float dli; float sli; float SpotCutoff; struct gl_light* NextEnabled; scalar_t__ Enabled; } ;
struct TYPE_5__ {int* Ambient; scalar_t__ LocalViewer; } ;
struct TYPE_6__ {float** BaseColor; void* Fast; struct gl_light* FirstEnabled; scalar_t__ ColorMaterialEnabled; TYPE_1__ Model; struct gl_material* Material; struct gl_light* Light; int /*<<< orphan*/  Enabled; } ;
struct TYPE_7__ {TYPE_2__ Light; } ;
typedef  size_t GLint ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_3V (float*,float*) ; 
 void* GL_FALSE ; 
 void* GL_TRUE ; 
 size_t MAX_LIGHTS ; 
 float MIN2 (int,float) ; 
 int /*<<< orphan*/  NORMALIZE_3FV (float*) ; 

void gl_update_lighting( GLcontext *ctx )
{
   GLint i, side;
   struct gl_light *prev_enabled, *light;

   if (!ctx->Light.Enabled) {
      /* If lighting is not enabled, we can skip all this. */
      return;
   }

   /* Setup linked list of enabled light sources */
   prev_enabled = NULL;
   ctx->Light.FirstEnabled = NULL;
   for (i=0;i<MAX_LIGHTS;i++) {
      ctx->Light.Light[i].NextEnabled = NULL;
      if (ctx->Light.Light[i].Enabled) {
         if (prev_enabled) {
            prev_enabled->NextEnabled = &ctx->Light.Light[i];
         }
         else {
            ctx->Light.FirstEnabled = &ctx->Light.Light[i];
         }
         prev_enabled = &ctx->Light.Light[i];
      }
   }

   /* base color = material_emission + global_ambient * material_ambient */
   for (side=0; side<2; side++) {
      ctx->Light.BaseColor[side][0] = ctx->Light.Material[side].Emission[0]
         + ctx->Light.Model.Ambient[0] * ctx->Light.Material[side].Ambient[0];
      ctx->Light.BaseColor[side][1] = ctx->Light.Material[side].Emission[1]
         + ctx->Light.Model.Ambient[1] * ctx->Light.Material[side].Ambient[1];
      ctx->Light.BaseColor[side][2] = ctx->Light.Material[side].Emission[2]
         + ctx->Light.Model.Ambient[2] * ctx->Light.Material[side].Ambient[2];
      ctx->Light.BaseColor[side][3]
         = MIN2( ctx->Light.Material[side].Diffuse[3], 1.0F );
   }


   /* Precompute some lighting stuff */
   for (light = ctx->Light.FirstEnabled; light; light = light->NextEnabled) {
      for (side=0; side<2; side++) {
         struct gl_material *mat = &ctx->Light.Material[side];
         /* Add each light's ambient component to base color */
         ctx->Light.BaseColor[side][0] += light->Ambient[0] * mat->Ambient[0];
         ctx->Light.BaseColor[side][1] += light->Ambient[1] * mat->Ambient[1];
         ctx->Light.BaseColor[side][2] += light->Ambient[2] * mat->Ambient[2];
         /* compute product of light's ambient with front material ambient */
         light->MatAmbient[side][0] = light->Ambient[0] * mat->Ambient[0];
         light->MatAmbient[side][1] = light->Ambient[1] * mat->Ambient[1];
         light->MatAmbient[side][2] = light->Ambient[2] * mat->Ambient[2];
         /* compute product of light's diffuse with front material diffuse */
         light->MatDiffuse[side][0] = light->Diffuse[0] * mat->Diffuse[0];
         light->MatDiffuse[side][1] = light->Diffuse[1] * mat->Diffuse[1];
         light->MatDiffuse[side][2] = light->Diffuse[2] * mat->Diffuse[2];
         /* compute product of light's specular with front material specular */
         light->MatSpecular[side][0] = light->Specular[0] * mat->Specular[0];
         light->MatSpecular[side][1] = light->Specular[1] * mat->Specular[1];
         light->MatSpecular[side][2] = light->Specular[2] * mat->Specular[2];

         /* VP (VP) = Normalize( Position ) */
         COPY_3V( light->VP_inf_norm, light->Position );
         NORMALIZE_3FV( light->VP_inf_norm );

         /* h_inf_norm = Normalize( V_to_P + <0,0,1> ) */
         COPY_3V( light->h_inf_norm, light->VP_inf_norm );
         light->h_inf_norm[2] += 1.0F;
         NORMALIZE_3FV( light->h_inf_norm );

         COPY_3V( light->NormDirection, light->Direction );
         NORMALIZE_3FV( light->NormDirection );

         /* Compute color index diffuse and specular light intensities */
         light->dli = 0.30F * light->Diffuse[0]
                    + 0.59F * light->Diffuse[1]
                    + 0.11F * light->Diffuse[2];
         light->sli = 0.30F * light->Specular[0]
                    + 0.59F * light->Specular[1]
                    + 0.11F * light->Specular[2];

      } /* loop over materials */
   } /* loop over lights */

   /* Determine if the fast lighting function can be used */
   ctx->Light.Fast = GL_TRUE;
   if (    ctx->Light.BaseColor[0][0]<0.0F
        || ctx->Light.BaseColor[0][1]<0.0F
        || ctx->Light.BaseColor[0][2]<0.0F
        || ctx->Light.BaseColor[0][3]<0.0F
        || ctx->Light.BaseColor[1][0]<0.0F
        || ctx->Light.BaseColor[1][1]<0.0F
        || ctx->Light.BaseColor[1][2]<0.0F
        || ctx->Light.BaseColor[1][3]<0.0F
        || ctx->Light.Model.LocalViewer
        || ctx->Light.ColorMaterialEnabled) {
      ctx->Light.Fast = GL_FALSE;
   }
   else {
      for (light=ctx->Light.FirstEnabled; light; light=light->NextEnabled) {
         if (   light->Position[3]!=0.0F
             || light->SpotCutoff!=180.0F
             || light->MatDiffuse[0][0]<0.0F
             || light->MatDiffuse[0][1]<0.0F
             || light->MatDiffuse[0][2]<0.0F
             || light->MatSpecular[0][0]<0.0F
             || light->MatSpecular[0][1]<0.0F
             || light->MatSpecular[0][2]<0.0F
             || light->MatDiffuse[1][0]<0.0F
             || light->MatDiffuse[1][1]<0.0F
             || light->MatDiffuse[1][2]<0.0F
             || light->MatSpecular[1][0]<0.0F
             || light->MatSpecular[1][1]<0.0F
             || light->MatSpecular[1][2]<0.0F) {
            ctx->Light.Fast = GL_FALSE;
            break;
         }
      }
   }
}