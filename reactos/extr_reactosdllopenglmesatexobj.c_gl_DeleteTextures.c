#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct gl_texture_object {scalar_t__ RefCount; } ;
struct TYPE_12__ {struct gl_texture_object* Default2D; struct gl_texture_object* Default1D; int /*<<< orphan*/  TexObjects; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* DeleteTexture ) (TYPE_3__*,struct gl_texture_object*) ;} ;
struct TYPE_9__ {struct gl_texture_object* Current2D; struct gl_texture_object* Current1D; } ;
struct TYPE_11__ {TYPE_5__* Shared; TYPE_2__ Driver; TYPE_1__ Texture; } ;
typedef  size_t GLuint ;
typedef  size_t GLsizei ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 scalar_t__ HashLookup (int /*<<< orphan*/ ,size_t const) ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  gl_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_free_texture_object (TYPE_5__*,struct gl_texture_object*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,struct gl_texture_object*) ; 

void gl_DeleteTextures( GLcontext *ctx, GLsizei n, const GLuint *texName)
{
   GLuint i;

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glAreTexturesResident" );
      return;
   }

   for (i=0;i<n;i++) {
      struct gl_texture_object *t;
      if (texName[i]>0) {
         t = (struct gl_texture_object *)
            HashLookup(ctx->Shared->TexObjects, texName[i]);
         if (t) {
            if (ctx->Texture.Current1D==t) {
               /* revert to default 1-D texture */
               ctx->Texture.Current1D = ctx->Shared->Default1D;
               t->RefCount--;
               assert( t->RefCount >= 0 );
            }
            else if (ctx->Texture.Current2D==t) {
               /* revert to default 2-D texture */
               ctx->Texture.Current2D = ctx->Shared->Default2D;
               t->RefCount--;
               assert( t->RefCount >= 0 );
            }

            /* tell device driver to delete texture */
            if (ctx->Driver.DeleteTexture) {
               (*ctx->Driver.DeleteTexture)( ctx, t );
            }

            if (t->RefCount==0) {
               gl_free_texture_object(ctx->Shared, t);
            }
         }
      }
   }
}