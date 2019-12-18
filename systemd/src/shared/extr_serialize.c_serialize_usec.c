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
typedef  scalar_t__ usec_t ;
typedef  char const FILE ;

/* Variables and functions */
 int /*<<< orphan*/  USEC_FMT ; 
 scalar_t__ USEC_INFINITY ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int serialize_item_format (char const*,char const*,int /*<<< orphan*/ ,scalar_t__) ; 

int serialize_usec(FILE *f, const char *key, usec_t usec) {
        assert(f);
        assert(key);

        if (usec == USEC_INFINITY)
                return 0;

        return serialize_item_format(f, key, USEC_FMT, usec);
}