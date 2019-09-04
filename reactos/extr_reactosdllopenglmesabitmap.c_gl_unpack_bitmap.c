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
struct gl_image {int dummy; } ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int /*<<< orphan*/  GLsizei ;
typedef  int /*<<< orphan*/  GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_BITMAP ; 
 int /*<<< orphan*/  GL_COLOR_INDEX ; 
 struct gl_image* gl_unpack_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

struct gl_image *gl_unpack_bitmap( GLcontext* ctx,
                                   GLsizei width, GLsizei height,
                                   const GLubyte *bitmap )
{
   return gl_unpack_image( ctx, width, height,
                           GL_COLOR_INDEX, GL_BITMAP, bitmap );
}