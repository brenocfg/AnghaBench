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
 int HIST_SIZE ; 
 int /*<<< orphan*/  gl_beep () ; 
 char** hist_buf ; 
 char* hist_empty_elem ; 
 int hist_last ; 
 int hist_pos ; 

__attribute__((used)) static char *
hist_prev(void)
/* loads previous hist entry into input buffer, sticks on first */
{
    char *p = 0;
    int   next = (hist_pos - 1 + HIST_SIZE) % HIST_SIZE;

    if (hist_buf[hist_pos] != 0 && next != hist_last) {
        hist_pos = next;
        p = hist_buf[hist_pos];
    }
    if (p == 0) {
	p = hist_empty_elem;
	gl_beep();
    }
    return p;
}