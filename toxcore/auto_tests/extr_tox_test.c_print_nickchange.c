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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  Tox ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  name_changes ; 

void print_nickchange(Tox *m, uint32_t friendnumber, const uint8_t *string, size_t length, void *userdata)
{
    if (*((uint32_t *)userdata) != 974536)
        return;

    if (length == sizeof("Gentoo") && memcmp(string, "Gentoo", sizeof("Gentoo")) == 0)
        ++name_changes;
}