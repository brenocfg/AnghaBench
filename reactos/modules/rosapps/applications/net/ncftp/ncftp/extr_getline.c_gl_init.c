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
 scalar_t__ _isatty (int) ; 
 int atoi (char const*) ; 
 scalar_t__ getenv (char*) ; 
 int /*<<< orphan*/  gl_char_init () ; 
 int /*<<< orphan*/  gl_error (char*) ; 
 int gl_init_done ; 
 int /*<<< orphan*/  gl_setheight (int) ; 
 int /*<<< orphan*/  gl_setwidth (int) ; 
 int /*<<< orphan*/  hist_init () ; 

__attribute__((used)) static void
gl_init(void)
/* set up variables and terminal */
{
    const char *cp;
    int w;

    if (gl_init_done < 0) {		/* -1 only on startup */
	cp = (const char *) getenv("COLUMNS");
	if (cp != NULL) {
	    w = atoi(cp);
	    if (w > 20)
	        gl_setwidth(w);
	}
	cp = (const char *) getenv("ROWS");
	if (cp != NULL) {
	    w = atoi(cp);
	    if (w > 10)
	        gl_setheight(w);
	}
        hist_init();
    }
    if (_isatty(0) == 0 || _isatty(1) == 0)
	gl_error("\n*** Error: getline(): not interactive, use stdio.\n");
    gl_char_init();
    gl_init_done = 1;
}