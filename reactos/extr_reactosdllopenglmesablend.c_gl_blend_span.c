#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int /*<<< orphan*/  GLint ;
typedef  int /*<<< orphan*/  GLcontext ;

/* Variables and functions */
 int MAX_WIDTH ; 
 int /*<<< orphan*/  do_blend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_read_color_span (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void gl_blend_span( GLcontext* ctx, GLuint n, GLint x, GLint y,
		    GLubyte red[], GLubyte green[],
		    GLubyte blue[], GLubyte alpha[],
		    GLubyte mask[] )
{
   GLubyte rdest[MAX_WIDTH], gdest[MAX_WIDTH];
   GLubyte bdest[MAX_WIDTH], adest[MAX_WIDTH];

   /* Read span of current frame buffer pixels */
   gl_read_color_span( ctx, n, x, y, rdest, gdest, bdest, adest );

   do_blend( ctx, n, mask, red, green, blue, alpha, rdest, gdest, bdest, adest );
}