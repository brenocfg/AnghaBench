#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  assoc4; int /*<<< orphan*/  assoc6; } ;
typedef  TYPE_1__ Client_data ;

/* Variables and functions */
 int /*<<< orphan*/  mark_good (int /*<<< orphan*/ *) ; 

void mark_all_good(Client_data *list, uint32_t length, uint8_t ipv6)
{
    uint32_t i;

    for (i = 0; i < length; ++i) {
        if (ipv6)
            mark_good(&list[i].assoc6);
        else
            mark_good(&list[i].assoc4);
    }
}