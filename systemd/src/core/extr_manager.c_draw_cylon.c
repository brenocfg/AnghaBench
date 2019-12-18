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
 int /*<<< orphan*/  ANSI_HIGHLIGHT_RED ; 
 int /*<<< orphan*/  ANSI_NORMAL ; 
 int /*<<< orphan*/  ANSI_RED ; 
 unsigned int CYLON_BUFFER_EXTRA ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ log_get_show_color () ; 
 char* mempset (char*,char,unsigned int) ; 
 char* stpcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void draw_cylon(char buffer[], size_t buflen, unsigned width, unsigned pos) {
        char *p = buffer;

        assert(buflen >= CYLON_BUFFER_EXTRA + width + 1);
        assert(pos <= width+1); /* 0 or width+1 mean that the center light is behind the corner */

        if (pos > 1) {
                if (pos > 2)
                        p = mempset(p, ' ', pos-2);
                if (log_get_show_color())
                        p = stpcpy(p, ANSI_RED);
                *p++ = '*';
        }

        if (pos > 0 && pos <= width) {
                if (log_get_show_color())
                        p = stpcpy(p, ANSI_HIGHLIGHT_RED);
                *p++ = '*';
        }

        if (log_get_show_color())
                p = stpcpy(p, ANSI_NORMAL);

        if (pos < width) {
                if (log_get_show_color())
                        p = stpcpy(p, ANSI_RED);
                *p++ = '*';
                if (pos < width-1)
                        p = mempset(p, ' ', width-1-pos);
                if (log_get_show_color())
                        strcpy(p, ANSI_NORMAL);
        }
}