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
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  Color4ubv; int /*<<< orphan*/  Color4ub; int /*<<< orphan*/  Color4fv; int /*<<< orphan*/  Color4f; int /*<<< orphan*/  Color3fv; int /*<<< orphan*/  Color3f; } ;
struct TYPE_10__ {int /*<<< orphan*/  Color4ubv; int /*<<< orphan*/  Color4ub; int /*<<< orphan*/  Color4fv; int /*<<< orphan*/  Color4f; int /*<<< orphan*/  Color3fv; int /*<<< orphan*/  Color3f; } ;
struct TYPE_8__ {scalar_t__ ColorMaterialEnabled; } ;
struct TYPE_12__ {TYPE_4__ Exec; TYPE_3__ API; int /*<<< orphan*/  CompileFlag; TYPE_2__* Visual; TYPE_1__ Light; } ;
struct TYPE_9__ {scalar_t__ EightBitColor; } ;
typedef  TYPE_5__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  INSIDE_BEGIN_END (TYPE_5__*) ; 
 int /*<<< orphan*/  gl_Color3f ; 
 int /*<<< orphan*/  gl_Color3f8bit ; 
 int /*<<< orphan*/  gl_Color3fv ; 
 int /*<<< orphan*/  gl_Color3fv8bit ; 
 int /*<<< orphan*/  gl_Color4f ; 
 int /*<<< orphan*/  gl_Color4f8bit ; 
 int /*<<< orphan*/  gl_Color4fv ; 
 int /*<<< orphan*/  gl_Color4fv8bit ; 
 int /*<<< orphan*/  gl_Color4ub ; 
 int /*<<< orphan*/  gl_Color4ub8bit ; 
 int /*<<< orphan*/  gl_Color4ubv ; 
 int /*<<< orphan*/  gl_Color4ubv8bit ; 
 int /*<<< orphan*/  gl_ColorMat3f ; 
 int /*<<< orphan*/  gl_ColorMat3fv ; 
 int /*<<< orphan*/  gl_ColorMat4f ; 
 int /*<<< orphan*/  gl_ColorMat4fv ; 
 int /*<<< orphan*/  gl_ColorMat4ub ; 
 int /*<<< orphan*/  gl_ColorMat4ubv ; 

void gl_set_color_function( GLcontext *ctx )
{
   ASSERT( !INSIDE_BEGIN_END(ctx) );

   if (ctx->Light.ColorMaterialEnabled) {
      ctx->Exec.Color3f = gl_ColorMat3f;
      ctx->Exec.Color3fv = gl_ColorMat3fv;
      ctx->Exec.Color4f = gl_ColorMat4f;
      ctx->Exec.Color4fv = gl_ColorMat4fv;
      ctx->Exec.Color4ub = gl_ColorMat4ub;
      ctx->Exec.Color4ubv = gl_ColorMat4ubv;
   }
   else if (ctx->Visual->EightBitColor) {
      ctx->Exec.Color3f = gl_Color3f8bit;
      ctx->Exec.Color3fv = gl_Color3fv8bit;
      ctx->Exec.Color4f = gl_Color4f8bit;
      ctx->Exec.Color4fv = gl_Color4fv8bit;
      ctx->Exec.Color4ub = gl_Color4ub8bit;
      ctx->Exec.Color4ubv = gl_Color4ubv8bit;
   }
   else {
      ctx->Exec.Color3f = gl_Color3f;
      ctx->Exec.Color3fv = gl_Color3fv;
      ctx->Exec.Color4f = gl_Color4f;
      ctx->Exec.Color4fv = gl_Color4fv;
      ctx->Exec.Color4ub = gl_Color4ub;
      ctx->Exec.Color4ubv = gl_Color4ubv;
   }
   if (!ctx->CompileFlag) {
      ctx->API.Color3f = ctx->Exec.Color3f;
      ctx->API.Color3fv = ctx->Exec.Color3fv;
      ctx->API.Color4f = ctx->Exec.Color4f;
      ctx->API.Color4fv = ctx->Exec.Color4fv;
      ctx->API.Color4ub = ctx->Exec.Color4ub;
      ctx->API.Color4ubv = ctx->Exec.Color4ubv;
   }
}