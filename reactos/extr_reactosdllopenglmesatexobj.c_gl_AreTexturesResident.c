#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct gl_texture_object {int dummy; } ;
struct TYPE_7__ {TYPE_1__* Shared; } ;
struct TYPE_6__ {int /*<<< orphan*/  TexObjects; } ;
typedef  scalar_t__ GLuint ;
typedef  scalar_t__ GLsizei ;
typedef  TYPE_2__ GLcontext ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 int /*<<< orphan*/  GL_INVALID_VALUE ; 
 int /*<<< orphan*/  GL_TRUE ; 
 scalar_t__ HashLookup (int /*<<< orphan*/ ,scalar_t__ const) ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

GLboolean gl_AreTexturesResident( GLcontext *ctx, GLsizei n,
                                  const GLuint *texName,
                                  GLboolean *residences )
{
   GLboolean resident = GL_TRUE;
   GLuint i;

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glAreTexturesResident" );
      return GL_FALSE;
   }
   if (n<0) {
      gl_error( ctx, GL_INVALID_VALUE, "glAreTexturesResident(n)" );
      return GL_FALSE;
   }

   for (i=0;i<n;i++) {
      struct gl_texture_object *t;
      if (texName[i]==0) {
         gl_error( ctx, GL_INVALID_VALUE, "glAreTexturesResident(textures)" );
         return GL_FALSE;
      }
      t = (struct gl_texture_object *)
         HashLookup(ctx->Shared->TexObjects, texName[i]);
      if (t) {
         /* we consider all valid texture objects to be resident */
         residences[i] = GL_TRUE;
      }
      else {
         gl_error( ctx, GL_INVALID_VALUE, "glAreTexturesResident(textures)" );
         return GL_FALSE;
      }
   }
   return resident;
}