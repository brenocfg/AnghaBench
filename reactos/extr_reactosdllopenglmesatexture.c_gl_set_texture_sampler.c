#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gl_texture_object {scalar_t__ MinFilter; scalar_t__ MagFilter; float MinMagThresh; int Dimensions; int /*<<< orphan*/ * SampleFunc; TYPE_1__** Image; int /*<<< orphan*/  WrapT; int /*<<< orphan*/  WrapS; int /*<<< orphan*/  Complete; } ;
struct TYPE_2__ {int /*<<< orphan*/  Format; int /*<<< orphan*/  Border; } ;
typedef  int GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ GL_LINEAR ; 
 scalar_t__ GL_LINEAR_MIPMAP_NEAREST ; 
 scalar_t__ GL_NEAREST ; 
 scalar_t__ GL_NEAREST_MIPMAP_NEAREST ; 
 int /*<<< orphan*/  GL_REPEAT ; 
 int /*<<< orphan*/  GL_RGB ; 
 int /*<<< orphan*/  GL_RGBA ; 
 int /*<<< orphan*/  gl_problem (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * opt_sample_rgb_2d ; 
 int /*<<< orphan*/ * opt_sample_rgba_2d ; 
 int /*<<< orphan*/ * sample_lambda_1d ; 
 int /*<<< orphan*/ * sample_lambda_2d ; 
 int /*<<< orphan*/ * sample_linear_1d ; 
 int /*<<< orphan*/ * sample_linear_2d ; 
 int /*<<< orphan*/ * sample_nearest_1d ; 
 int /*<<< orphan*/ * sample_nearest_2d ; 

void gl_set_texture_sampler( struct gl_texture_object *t )
{
   if (!t->Complete) {
      t->SampleFunc = NULL;
   }
   else {
      GLboolean needLambda = (t->MinFilter != t->MagFilter);

      if (needLambda) {
         /* Compute min/mag filter threshold */
         if (t->MagFilter==GL_LINEAR
             && (t->MinFilter==GL_NEAREST_MIPMAP_NEAREST ||
                 t->MinFilter==GL_LINEAR_MIPMAP_NEAREST)) {
            t->MinMagThresh = 0.5F;
         }
         else {
            t->MinMagThresh = 0.0F;
         }
      }

      switch (t->Dimensions) {
         case 1:
            if (needLambda) {
               t->SampleFunc = sample_lambda_1d;
            }
            else if (t->MinFilter==GL_LINEAR) {
               t->SampleFunc = sample_linear_1d;
            }
            else {
               ASSERT(t->MinFilter==GL_NEAREST);
               t->SampleFunc = sample_nearest_1d;
            }
            break;
         case 2:
            if (needLambda) {
               t->SampleFunc = sample_lambda_2d;
            }
            else if (t->MinFilter==GL_LINEAR) {
               t->SampleFunc = sample_linear_2d;
            }
            else {
               ASSERT(t->MinFilter==GL_NEAREST);
               if (t->WrapS==GL_REPEAT && t->WrapT==GL_REPEAT
                   && t->Image[0]->Border==0 && t->Image[0]->Format==GL_RGB) {
                  t->SampleFunc = opt_sample_rgb_2d;
               }
               else if (t->WrapS==GL_REPEAT && t->WrapT==GL_REPEAT
                   && t->Image[0]->Border==0 && t->Image[0]->Format==GL_RGBA) {
                  t->SampleFunc = opt_sample_rgba_2d;
               }
               else
                  t->SampleFunc = sample_nearest_2d;
            }
            break;
         default:
            gl_problem(NULL, "invalid dimensions in gl_set_texture_sampler");
      }
   }
}