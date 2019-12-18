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
 void* octchar (unsigned char) ; 

int cescape_char(char c, char *buf) {
        char *buf_old = buf;

        /* Needs space for 4 characters in the buffer */

        switch (c) {

                case '\a':
                        *(buf++) = '\\';
                        *(buf++) = 'a';
                        break;
                case '\b':
                        *(buf++) = '\\';
                        *(buf++) = 'b';
                        break;
                case '\f':
                        *(buf++) = '\\';
                        *(buf++) = 'f';
                        break;
                case '\n':
                        *(buf++) = '\\';
                        *(buf++) = 'n';
                        break;
                case '\r':
                        *(buf++) = '\\';
                        *(buf++) = 'r';
                        break;
                case '\t':
                        *(buf++) = '\\';
                        *(buf++) = 't';
                        break;
                case '\v':
                        *(buf++) = '\\';
                        *(buf++) = 'v';
                        break;
                case '\\':
                        *(buf++) = '\\';
                        *(buf++) = '\\';
                        break;
                case '"':
                        *(buf++) = '\\';
                        *(buf++) = '"';
                        break;
                case '\'':
                        *(buf++) = '\\';
                        *(buf++) = '\'';
                        break;

                default:
                        /* For special chars we prefer octal over
                         * hexadecimal encoding, simply because glib's
                         * g_strescape() does the same */
                        if ((c < ' ') || (c >= 127)) {
                                *(buf++) = '\\';
                                *(buf++) = octchar((unsigned char) c >> 6);
                                *(buf++) = octchar((unsigned char) c >> 3);
                                *(buf++) = octchar((unsigned char) c);
                        } else
                                *(buf++) = c;
                        break;
        }

        return buf - buf_old;
}