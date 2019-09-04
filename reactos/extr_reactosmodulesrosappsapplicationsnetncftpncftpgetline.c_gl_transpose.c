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
 int /*<<< orphan*/  gl_beep () ; 
 int* gl_buf ; 
 int gl_cnt ; 
 int gl_extent ; 
 int /*<<< orphan*/  gl_fixup (int /*<<< orphan*/ ,int,int) ; 
 int gl_pos ; 
 int /*<<< orphan*/  gl_prompt ; 

__attribute__((used)) static void
gl_transpose(void)
/* switch character under cursor and to left of cursor */
{
    int    c;

    if (gl_pos > 0 && gl_cnt > gl_pos) {
	c = gl_buf[gl_pos-1];
	gl_buf[gl_pos-1] = gl_buf[gl_pos];
	gl_buf[gl_pos] = (char) c;
	gl_extent = 2;
	gl_fixup(gl_prompt, gl_pos-1, gl_pos);
    } else
	gl_beep();
}