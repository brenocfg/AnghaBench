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
struct TYPE_6__ {int LogicOp; } ;
struct TYPE_7__ {int /*<<< orphan*/  NewState; TYPE_1__ Color; } ;
typedef  int GLenum ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
#define  GL_AND 143 
#define  GL_AND_INVERTED 142 
#define  GL_AND_REVERSE 141 
#define  GL_CLEAR 140 
#define  GL_COPY 139 
#define  GL_COPY_INVERTED 138 
#define  GL_EQUIV 137 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_INVERT 136 
#define  GL_NAND 135 
#define  GL_NOOP 134 
#define  GL_NOR 133 
#define  GL_OR 132 
#define  GL_OR_INVERTED 131 
#define  GL_OR_REVERSE 130 
#define  GL_SET 129 
#define  GL_XOR 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  NEW_RASTER_OPS ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_LogicOp( GLcontext *ctx, GLenum opcode )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glLogicOp" );
      return;
   }
   switch (opcode) {
      case GL_CLEAR:
      case GL_SET:
      case GL_COPY:
      case GL_COPY_INVERTED:
      case GL_NOOP:
      case GL_INVERT:
      case GL_AND:
      case GL_NAND:
      case GL_OR:
      case GL_NOR:
      case GL_XOR:
      case GL_EQUIV:
      case GL_AND_REVERSE:
      case GL_AND_INVERTED:
      case GL_OR_REVERSE:
      case GL_OR_INVERTED:
         ctx->Color.LogicOp = opcode;
         ctx->NewState |= NEW_RASTER_OPS;
	 return;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glLogicOp" );
	 return;
   }
}