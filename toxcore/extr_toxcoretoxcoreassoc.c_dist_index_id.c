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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/ * public_key; } ;
struct TYPE_5__ {TYPE_1__ client; } ;
typedef  TYPE_2__ Client_entry ;
typedef  int /*<<< orphan*/  Assoc ;

/* Variables and functions */
 TYPE_2__* dist_index_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t *dist_index_id(Assoc *assoc, uint64_t dist_ind)
{
    Client_entry *entry = dist_index_entry(assoc, dist_ind);

    if (entry)
        return entry->client.public_key;

    return NULL;
}