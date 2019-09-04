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
struct TYPE_4__ {int /*<<< orphan*/  CompileFlag; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  TYPE_1__ GLcontext ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  execute_list (TYPE_1__*,int /*<<< orphan*/ ) ; 

void gl_CallList( GLcontext *ctx, GLuint list )
{
   /* VERY IMPORTANT:  Save the CompileFlag status, turn it off, */
   /* execute the display list, and restore the CompileFlag. */
   GLboolean save_compile_flag;
   save_compile_flag = ctx->CompileFlag;
   ctx->CompileFlag = GL_FALSE;
   execute_list( ctx, list );
   ctx->CompileFlag = save_compile_flag;
}