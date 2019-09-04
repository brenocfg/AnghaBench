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
typedef  int GLint ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_TRUE ; 

__attribute__((used)) static GLboolean power_of_two( GLint k )
{
   GLint i, m = 1;
   for (i=0; i<32; i++) {
      if (k == m)
         return GL_TRUE;
      m = m << 1;
   }
   return GL_FALSE;
}