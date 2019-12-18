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
 int /*<<< orphan*/  assert (char*) ; 
 scalar_t__ isspace (char) ; 
 scalar_t__ strchr (char const*,char) ; 
 int utf8_encoded_valid_unichar (char*,size_t) ; 
 scalar_t__ whitelisted_char_for_devnode (char,char const*) ; 

size_t util_replace_chars(char *str, const char *white) {
        size_t i = 0, replaced = 0;

        assert(str);

        while (str[i] != '\0') {
                int len;

                if (whitelisted_char_for_devnode(str[i], white)) {
                        i++;
                        continue;
                }

                /* accept hex encoding */
                if (str[i] == '\\' && str[i+1] == 'x') {
                        i += 2;
                        continue;
                }

                /* accept valid utf8 */
                len = utf8_encoded_valid_unichar(str + i, (size_t) -1);
                if (len > 1) {
                        i += len;
                        continue;
                }

                /* if space is allowed, replace whitespace with ordinary space */
                if (isspace(str[i]) && white && strchr(white, ' ')) {
                        str[i] = ' ';
                        i++;
                        replaced++;
                        continue;
                }

                /* everything else is replaced with '_' */
                str[i] = '_';
                i++;
                replaced++;
        }
        return replaced;
}