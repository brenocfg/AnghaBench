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
struct gl_texture_object {TYPE_1__** Image; } ;
struct TYPE_2__ {scalar_t__ WidthLog2; } ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  scalar_t__ GLint ;
typedef  float GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  sample_1d_nearest (struct gl_texture_object const*,TYPE_1__*,float,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sample_1d_nearest_mipmap_nearest( const struct gl_texture_object *tObj,
                                  GLfloat s, GLfloat lambda,
                                  GLubyte *red, GLubyte *green,
                                  GLubyte *blue, GLubyte *alpha )
{
   GLint level;
   if (lambda<=0.5F) {
      level = 0;
   }
   else {
      GLint widthlog2 = tObj->Image[0]->WidthLog2;
      level = (GLint) (lambda + 0.499999F);
      if (level>widthlog2 ) {
         level = widthlog2;
      }
   }
   sample_1d_nearest( tObj, tObj->Image[level],
                      s, red, green, blue, alpha );
}