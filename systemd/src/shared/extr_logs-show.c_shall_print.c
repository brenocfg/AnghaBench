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
typedef  int OutputFlags ;

/* Variables and functions */
 int OUTPUT_SHOW_ALL ; 
 size_t PRINT_CHAR_THRESHOLD ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  utf8_is_printable (char const*,size_t) ; 

__attribute__((used)) static bool shall_print(const char *p, size_t l, OutputFlags flags) {
        assert(p);

        if (flags & OUTPUT_SHOW_ALL)
                return true;

        if (l >= PRINT_CHAR_THRESHOLD)
                return false;

        if (!utf8_is_printable(p, l))
                return false;

        return true;
}