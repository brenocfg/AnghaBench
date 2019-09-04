#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int RowLength; int SkipPixels; int SkipRows; int Alignment; void* LsbFirst; void* SwapBytes; } ;
struct TYPE_8__ {int RowLength; int SkipPixels; int SkipRows; int Alignment; void* LsbFirst; void* SwapBytes; } ;
struct TYPE_10__ {TYPE_2__ Unpack; TYPE_1__ Pack; } ;
typedef  int GLint ;
typedef  int GLenum ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 void* GL_FALSE ; 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 int /*<<< orphan*/  GL_INVALID_VALUE ; 
#define  GL_PACK_ALIGNMENT 139 
#define  GL_PACK_LSB_FIRST 138 
#define  GL_PACK_ROW_LENGTH 137 
#define  GL_PACK_SKIP_PIXELS 136 
#define  GL_PACK_SKIP_ROWS 135 
#define  GL_PACK_SWAP_BYTES 134 
 void* GL_TRUE ; 
#define  GL_UNPACK_ALIGNMENT 133 
#define  GL_UNPACK_LSB_FIRST 132 
#define  GL_UNPACK_ROW_LENGTH 131 
#define  GL_UNPACK_SKIP_PIXELS 130 
#define  GL_UNPACK_SKIP_ROWS 129 
#define  GL_UNPACK_SWAP_BYTES 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_3__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  update_drawpixels_state (TYPE_3__*) ; 

void gl_PixelStorei( GLcontext *ctx, GLenum pname, GLint param )
{
   /* NOTE: this call can't be compiled into the display list */

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glPixelStore" );
      return;
   }

   switch (pname) {
      case GL_PACK_SWAP_BYTES:
         ctx->Pack.SwapBytes = param ? GL_TRUE : GL_FALSE;
	 break;
      case GL_PACK_LSB_FIRST:
         ctx->Pack.LsbFirst = param ? GL_TRUE : GL_FALSE;
	 break;
      case GL_PACK_ROW_LENGTH:
	 if (param<0) {
	    gl_error( ctx, GL_INVALID_VALUE, "glPixelStore(param)" );
	 }
	 else {
	    ctx->Pack.RowLength = param;
	 }
	 break;
      case GL_PACK_SKIP_PIXELS:
	 if (param<0) {
	    gl_error( ctx, GL_INVALID_VALUE, "glPixelStore(param)" );
	 }
	 else {
	    ctx->Pack.SkipPixels = param;
	 }
	 break;
      case GL_PACK_SKIP_ROWS:
	 if (param<0) {
	    gl_error( ctx, GL_INVALID_VALUE, "glPixelStore(param)" );
	 }
	 else {
	    ctx->Pack.SkipRows = param;
	 }
	 break;
      case GL_PACK_ALIGNMENT:
         if (param==1 || param==2 || param==4 || param==8) {
	    ctx->Pack.Alignment = param;
	 }
	 else {
	    gl_error( ctx, GL_INVALID_VALUE, "glPixelStore(param)" );
	 }
	 break;
      case GL_UNPACK_SWAP_BYTES:
	 ctx->Unpack.SwapBytes = param ? GL_TRUE : GL_FALSE;
         break;
      case GL_UNPACK_LSB_FIRST:
	 ctx->Unpack.LsbFirst = param ? GL_TRUE : GL_FALSE;
	 break;
      case GL_UNPACK_ROW_LENGTH:
	 if (param<0) {
	    gl_error( ctx, GL_INVALID_VALUE, "glPixelStore(param)" );
	 }
	 else {
	    ctx->Unpack.RowLength = param;
	 }
	 break;
      case GL_UNPACK_SKIP_PIXELS:
	 if (param<0) {
	    gl_error( ctx, GL_INVALID_VALUE, "glPixelStore(param)" );
	 }
	 else {
	    ctx->Unpack.SkipPixels = param;
	 }
	 break;
      case GL_UNPACK_SKIP_ROWS:
	 if (param<0) {
	    gl_error( ctx, GL_INVALID_VALUE, "glPixelStore(param)" );
	 }
	 else {
	    ctx->Unpack.SkipRows = param;
	 }
	 break;
      case GL_UNPACK_ALIGNMENT:
         if (param==1 || param==2 || param==4 || param==8) {
	    ctx->Unpack.Alignment = param;
	 }
	 else {
	    gl_error( ctx, GL_INVALID_VALUE, "glPixelStore" );
	 }
	 break;
      default:
	 gl_error( ctx, GL_INVALID_ENUM, "glPixelStore" );
   }
   update_drawpixels_state( ctx );
}