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
 int /*<<< orphan*/  gl_error (char*) ; 
 int gl_termh ; 

void
gl_setheight(int w)
{
    if (w > 10) {
	gl_termh = w;
    } else {
	gl_error("\n*** Error: minimum screen height is 10\n");
    }
}