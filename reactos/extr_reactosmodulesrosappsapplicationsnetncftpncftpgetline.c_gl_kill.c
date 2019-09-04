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
 int /*<<< orphan*/  gl_killbuf ; 
 int /*<<< orphan*/  gl_prompt ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
gl_kill(int pos)

/* delete from pos to the end of line */
{
    if (pos < gl_cnt) {
	strcpy(gl_killbuf, gl_buf + pos);
	gl_buf[pos] = '\0';
	gl_fixup(gl_prompt, pos, pos);
    } else
	gl_beep();
}