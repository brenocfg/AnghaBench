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
typedef  int uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  public_key; } ;
typedef  TYPE_1__ Client_data ;

/* Variables and functions */
 int id_closest (int const*,int const*,int /*<<< orphan*/ ) ; 

uint8_t is_furthest(const uint8_t *comp_client_id, Client_data *list, uint32_t length, const uint8_t *public_key)
{
    uint32_t i;

    for (i = 0; i < length; ++i)
        if (id_closest(comp_client_id, public_key, list[i].public_key) == 1)
            return 0;

    return 1;
}