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
 scalar_t__* gl_buf ; 
 int /*<<< orphan*/  gl_fixup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int gl_search_mode ; 
 int /*<<< orphan*/  hist_last ; 
 char* hist_next () ; 
 int /*<<< orphan*/  hist_pos ; 
 int search_forw_flg ; 
 int /*<<< orphan*/  search_last ; 
 scalar_t__ search_pos ; 
 int /*<<< orphan*/  search_prompt ; 
 int /*<<< orphan*/  search_string ; 
 int /*<<< orphan*/  search_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (scalar_t__*,char*) ; 
 char* strstr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
search_forw(int new_search)
{
    int    found = 0;
    char  *p, *loc;

    search_forw_flg = 1;
    if (gl_search_mode == 0) {
	search_last = hist_pos = hist_last;
	search_update(0);
	gl_search_mode = 1;
        gl_buf[0] = 0;
	gl_fixup(search_prompt, 0, 0);
    } else if (search_pos > 0) {
	while (!found) {
	    p = hist_next();
	    if (*p == 0) {		/* not found, done looking */
	       gl_buf[0] = 0;
	       gl_fixup(search_prompt, 0, 0);
	       found = 1;
	    } else if ((loc = strstr(p, search_string)) != 0) {
	       strcpy(gl_buf, p);
	       gl_fixup(search_prompt, 0, (int) (loc - p));
	       if (new_search)
		   search_last = hist_pos;
	       found = 1;
	    }
	}
    } else {
        gl_beep();
    }
}