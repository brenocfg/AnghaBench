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
struct TYPE_4__ {int /*<<< orphan*/  group_chat_object; } ;
typedef  TYPE_1__ Tox ;
typedef  TYPE_1__ Messenger ;

/* Variables and functions */
 int group_peer_pubkey (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

int tox_group_peer_pubkey(const Tox *tox, int groupnumber, int peernumber, uint8_t *public_key)
{
    const Messenger *m = tox;
    return group_peer_pubkey(m->group_chat_object, groupnumber, peernumber, public_key);
}