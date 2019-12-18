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
 int utf8_char_console_width (char const*) ; 
 char* utf8_next_char (char const*) ; 

size_t utf8_console_width(const char *str) {
        size_t n = 0;

        /* Returns the approximate width a string will take on screen when printed on a character cell
         * terminal/console. */

        while (*str) {
                int w;

                w = utf8_char_console_width(str);
                if (w < 0)
                        return (size_t) -1;

                n += w;
                str = utf8_next_char(str);
        }

        return n;
}