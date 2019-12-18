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
 char* ANSI_GREY ; 
 char* ANSI_HIGHLIGHT ; 
 char* ANSI_HIGHLIGHT_RED ; 
 char* ANSI_HIGHLIGHT_YELLOW ; 
 char* ANSI_NORMAL ; 
 int LOG_DEBUG ; 
 int LOG_ERR ; 
 int LOG_NOTICE ; 
 int LOG_WARNING ; 

void get_log_colors(int priority, const char **on, const char **off, const char **highlight) {
        /* Note that this will initialize output variables only when there's something to output.
         * The caller must pre-initalize to "" or NULL as appropriate. */

        if (priority <= LOG_ERR) {
                if (on)
                        *on = ANSI_HIGHLIGHT_RED;
                if (off)
                        *off = ANSI_NORMAL;
                if (highlight)
                        *highlight = ANSI_HIGHLIGHT;

        } else if (priority <= LOG_WARNING) {
                if (on)
                        *on = ANSI_HIGHLIGHT_YELLOW;
                if (off)
                        *off = ANSI_NORMAL;
                if (highlight)
                        *highlight = ANSI_HIGHLIGHT;

        } else if (priority <= LOG_NOTICE) {
                if (on)
                        *on = ANSI_HIGHLIGHT;
                if (off)
                        *off = ANSI_NORMAL;
                if (highlight)
                        *highlight = ANSI_HIGHLIGHT_RED;

        } else if (priority >= LOG_DEBUG) {
                if (on)
                        *on = ANSI_GREY;
                if (off)
                        *off = ANSI_NORMAL;
                if (highlight)
                        *highlight = ANSI_HIGHLIGHT_RED;
        }
}