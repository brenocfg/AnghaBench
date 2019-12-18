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
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

size_t util_path_encode(const char *src, char *dest, size_t size) {
        size_t i, j;

        assert(src);
        assert(dest);

        for (i = 0, j = 0; src[i] != '\0'; i++) {
                if (src[i] == '/') {
                        if (j+4 >= size) {
                                j = 0;
                                break;
                        }
                        memcpy(&dest[j], "\\x2f", 4);
                        j += 4;
                } else if (src[i] == '\\') {
                        if (j+4 >= size) {
                                j = 0;
                                break;
                        }
                        memcpy(&dest[j], "\\x5c", 4);
                        j += 4;
                } else {
                        if (j+1 >= size) {
                                j = 0;
                                break;
                        }
                        dest[j] = src[i];
                        j++;
                }
        }
        dest[j] = '\0';
        return j;
}