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
 char* gl_buf ; 
 int gl_cnt ; 
 int /*<<< orphan*/  gl_fixup (int /*<<< orphan*/ ,int,int) ; 
 char* gl_killbuf ; 
 int gl_pos ; 
 int /*<<< orphan*/  gl_prompt ; 
 scalar_t__ gl_vi_mode ; 

__attribute__((used)) static void
gl_del(int loc, int killsave)

/*
 * Delete a character.  The loc variable can be:
 *    -1 : delete character to left of cursor
 *     0 : delete character under cursor
 */
{
    int i, j;

    if ((loc == -1 && gl_pos > 0) || (loc == 0 && gl_pos < gl_cnt)) {
        for (j=0, i=gl_pos+loc; i < gl_cnt; i++) {
	    if ((j == 0) && (killsave != 0) && (gl_vi_mode != 0)) {
	    	gl_killbuf[0] = gl_buf[i];
	    	gl_killbuf[1] = '\0';
		j = 1;
	    }
	    gl_buf[i] = gl_buf[i+1];
	}
	gl_fixup(gl_prompt, gl_pos+loc, gl_pos+loc);
    } else
	gl_beep();
}