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
 int GL_BUF_SIZE ; 
 char* gl_buf ; 
 int gl_cnt ; 
 int /*<<< orphan*/  gl_error (char*) ; 
 int gl_extent ; 
 int /*<<< orphan*/  gl_fixup (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ gl_overwrite ; 
 int gl_pos ; 
 int /*<<< orphan*/  gl_prompt ; 

__attribute__((used)) static void
gl_addchar(int c)

/* adds the character c to the input buffer at current location */
{
    int  i;

    if (gl_cnt >= GL_BUF_SIZE - 1)
	gl_error("\n*** Error: getline(): input buffer overflow\n");
    if (gl_overwrite == 0 || gl_pos == gl_cnt) {
        for (i=gl_cnt; i >= gl_pos; i--)
            gl_buf[i+1] = gl_buf[i];
        gl_buf[gl_pos] = (char) c;
        gl_fixup(gl_prompt, gl_pos, gl_pos+1);
    } else {
	gl_buf[gl_pos] = (char) c;
	gl_extent = 1;
        gl_fixup(gl_prompt, gl_pos, gl_pos+1);
    }
}