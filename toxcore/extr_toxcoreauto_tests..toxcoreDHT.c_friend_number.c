#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_5__ {size_t num_friends; TYPE_1__* friends_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  public_key; } ;
typedef  TYPE_2__ DHT ;

/* Variables and functions */
 scalar_t__ id_equal (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int friend_number(const DHT *dht, const uint8_t *public_key)
{
    uint32_t i;

    for (i = 0; i < dht->num_friends; ++i) {
        if (id_equal(dht->friends_list[i].public_key, public_key))
            return i;
    }

    return -1;
}