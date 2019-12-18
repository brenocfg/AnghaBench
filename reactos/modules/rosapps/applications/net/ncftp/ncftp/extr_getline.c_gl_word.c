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
 int /*<<< orphan*/ * gl_buf ; 
 int gl_cnt ; 
 int /*<<< orphan*/  gl_fixup (int /*<<< orphan*/ ,int,int) ; 
 int gl_pos ; 
 int /*<<< orphan*/  gl_prompt ; 
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gl_word(int direction)

/* move forward or backword one word */
{
    int pos = gl_pos;

    if (direction > 0) {		/* forward */
        while (!isspace(gl_buf[pos]) && pos < gl_cnt)
	    pos++;
	while (isspace(gl_buf[pos]) && pos < gl_cnt)
	    pos++;
    } else {				/* backword */
	if (pos > 0)
	    pos--;
	while (isspace(gl_buf[pos]) && pos > 0)
	    pos--;
        while (!isspace(gl_buf[pos]) && pos > 0)
	    pos--;
	if (pos < gl_cnt && isspace(gl_buf[pos]))   /* move onto word */
	    pos++;
    }
    gl_fixup(gl_prompt, -1, pos);
}