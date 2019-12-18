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
 int /*<<< orphan*/  SIGNAL_VALID (int) ; 
 char const* signal_to_string (int) ; 

__attribute__((used)) static inline const char* signal_to_string_with_check(int n) {
        if (!SIGNAL_VALID(n))
                return NULL;

        return signal_to_string(n);
}