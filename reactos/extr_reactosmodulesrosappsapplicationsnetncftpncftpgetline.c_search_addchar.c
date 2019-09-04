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
 char* gl_buf ; 
 int /*<<< orphan*/  gl_fixup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * hist_buf ; 
 size_t hist_last ; 
 size_t hist_pos ; 
 int /*<<< orphan*/  search_back (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  search_forw (int /*<<< orphan*/ ) ; 
 scalar_t__ search_forw_flg ; 
 size_t search_last ; 
 scalar_t__ search_pos ; 
 int /*<<< orphan*/  search_prompt ; 
 int /*<<< orphan*/  search_string ; 
 int /*<<< orphan*/  search_update (int) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 char* strstr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
search_addchar(int c)
{
    char *loc;

    search_update(c);
    if (c < 0) {
	if (search_pos > 0) {
	    hist_pos = search_last;
	} else {
	    gl_buf[0] = 0;
	    hist_pos = hist_last;
	}
	strcpy(gl_buf, hist_buf[hist_pos]);
    }
    if ((loc = strstr(gl_buf, search_string)) != 0) {
	gl_fixup(search_prompt, 0, (int) (loc - gl_buf));
    } else if (search_pos > 0) {
        if (search_forw_flg) {
	    search_forw(0);
        } else {
	    search_back(0);
        }
    } else {
	gl_fixup(search_prompt, 0, 0);
    }
}