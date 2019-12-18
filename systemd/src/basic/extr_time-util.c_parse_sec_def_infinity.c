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
typedef  int /*<<< orphan*/  usec_t ;

/* Variables and functions */
 int /*<<< orphan*/  USEC_INFINITY ; 
 int /*<<< orphan*/  WHITESPACE ; 
 scalar_t__ isempty (char const*) ; 
 int parse_sec (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strspn (char const*,int /*<<< orphan*/ ) ; 

int parse_sec_def_infinity(const char *t, usec_t *ret) {
        t += strspn(t, WHITESPACE);
        if (isempty(t)) {
                *ret = USEC_INFINITY;
                return 0;
        }
        return parse_sec(t, ret);
}