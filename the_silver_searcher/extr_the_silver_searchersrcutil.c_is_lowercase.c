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
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  isascii (char const) ; 
 scalar_t__ isupper (char const) ; 

int is_lowercase(const char *s) {
    int i;
    for (i = 0; s[i] != '\0'; i++) {
        if (!isascii(s[i]) || isupper(s[i])) {
            return FALSE;
        }
    }
    return TRUE;
}