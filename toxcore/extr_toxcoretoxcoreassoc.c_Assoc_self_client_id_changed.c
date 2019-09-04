#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  self_client_id; scalar_t__ self_hash; } ;
typedef  TYPE_1__ Assoc ;

/* Variables and functions */
 int /*<<< orphan*/  client_id_self_update (TYPE_1__*) ; 
 int /*<<< orphan*/  id_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

void Assoc_self_client_id_changed(Assoc *assoc, const uint8_t *id)
{
    if (assoc && id) {
        assoc->self_hash = 0;
        id_copy(assoc->self_client_id, id);
        client_id_self_update(assoc);
    }
}