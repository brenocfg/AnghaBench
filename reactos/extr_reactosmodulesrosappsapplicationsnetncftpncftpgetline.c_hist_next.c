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
hist_next(void)
/* loads next hist entry into input buffer, clears on last */
{
    char *p = 0;

    if (hist_pos != hist_last) {
        hist_pos = (hist_pos+1) % HIST_SIZE;
	p = hist_buf[hist_pos];
    }
    if (p == 0) {
	p = hist_empty_elem;
	gl_beep();
    }
    return p;
}