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
struct TYPE_5__ {TYPE_1__* entries; } ;
struct TYPE_4__ {int /*<<< orphan*/  public_key; int /*<<< orphan*/  time; } ;
typedef  TYPE_2__ Onion_Announce ;

/* Variables and functions */
 unsigned int ONION_ANNOUNCE_MAX_ENTRIES ; 
 int /*<<< orphan*/  ONION_ANNOUNCE_TIMEOUT ; 
 int /*<<< orphan*/  is_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ public_key_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int in_entries(const Onion_Announce *onion_a, const uint8_t *public_key)
{
    unsigned int i;

    for (i = 0; i < ONION_ANNOUNCE_MAX_ENTRIES; ++i) {
        if (!is_timeout(onion_a->entries[i].time, ONION_ANNOUNCE_TIMEOUT)
                && public_key_cmp(onion_a->entries[i].public_key, public_key) == 0)
            return i;
    }

    return -1;
}