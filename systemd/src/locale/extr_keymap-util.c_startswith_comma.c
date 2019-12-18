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
 int IN_SET (char const,char,char) ; 
 char* startswith (char const*,char const*) ; 

__attribute__((used)) static bool startswith_comma(const char *s, const char *prefix) {
        s = startswith(s, prefix);
        if (!s)
                return false;

        return IN_SET(*s, ',', '\0');
}