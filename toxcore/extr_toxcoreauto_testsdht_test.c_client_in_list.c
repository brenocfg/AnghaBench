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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  public_key; } ;
typedef  TYPE_1__ Client_data ;

/* Variables and functions */
 scalar_t__ id_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int client_in_list(Client_data *list, uint32_t length, const uint8_t *public_key)
{
    int i;

    for (i = 0; i < (int)length; ++i)
        if (id_equal(public_key, list[i].public_key))
            return i;

    return -1;
}