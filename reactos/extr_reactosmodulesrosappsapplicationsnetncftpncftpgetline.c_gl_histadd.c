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
 size_t HIST_SIZE ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ gl_init_done ; 
 char** hist_buf ; 
 char* hist_empty_elem ; 
 int /*<<< orphan*/  hist_init () ; 
 size_t hist_last ; 
 size_t hist_pos ; 
 char* hist_save (char*) ; 
 scalar_t__ strchr (char*,char) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,size_t) ; 

void
gl_histadd(char *buf)
{
    static char *prev = 0;
    char *p = buf;
    int len;

    /* in case we call gl_histadd() before we call getline() */
    if (gl_init_done < 0) {		/* -1 only on startup */
        hist_init();
        gl_init_done = 0;
    }
    while (*p == ' ' || *p == '\t' || *p == '\n')
	p++;
    if (*p) {
	len = (int) strlen(buf);
	if (strchr(p, '\n')) 	/* previously line already has NL stripped */
	    len--;
	if ((prev == 0) || ((int) strlen(prev) != len) ||
			    strncmp(prev, buf, (size_t) len) != 0) {
            hist_buf[hist_last] = hist_save(buf);
	    prev = hist_buf[hist_last];
            hist_last = (hist_last + 1) % HIST_SIZE;
            if (hist_buf[hist_last] && *hist_buf[hist_last]) {
	        free(hist_buf[hist_last]);
            }
	    hist_buf[hist_last] = hist_empty_elem;
	}
    }
    hist_pos = hist_last;
}