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
struct string {scalar_t__ len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int nc_strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int
string_compare(const struct string *s1, const struct string *s2)
{
    if (s1->len != s2->len) {
        return s1->len > s2->len ? 1 : -1;
    }

    return nc_strncmp(s1->data, s2->data, s1->len);
}