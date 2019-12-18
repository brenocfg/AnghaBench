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
 char* memory_startswith (char const*,size_t,char const*) ; 

__attribute__((used)) static bool line_begins(const char *s, size_t m, const char *word) {
        const char *p;

        p = memory_startswith(s, m, word);
        return p && (p == (s + m) || *p == ' ');
}