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

/* Variables and functions */
 int /*<<< orphan*/  glRotatef (int,int,int /*<<< orphan*/ ,int) ; 

void stbgl_initCamera_zup_facing_x(void)
{
   glRotatef(-90, 1,0,0);
   glRotatef( 90, 0,0,1);
}