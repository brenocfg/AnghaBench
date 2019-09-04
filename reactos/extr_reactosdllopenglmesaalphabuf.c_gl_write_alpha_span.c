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
typedef  size_t GLuint ;
typedef  scalar_t__ GLubyte ;
typedef  int /*<<< orphan*/  GLint ;
typedef  int /*<<< orphan*/  GLcontext ;

/* Variables and functions */
 scalar_t__* ALPHA_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void gl_write_alpha_span( GLcontext* ctx, GLuint n, GLint x, GLint y,
                          GLubyte alpha[], GLubyte mask[] )
{
   GLubyte *aptr = ALPHA_ADDR( x, y );
   GLuint i;

   if (mask) {
      for (i=0;i<n;i++) {
         if (mask[i]) {
            *aptr = alpha[i];
         }
         aptr++;
      }
   }
   else {
      for (i=0;i<n;i++) {
         *aptr++ = alpha[i];
      }
   }
}