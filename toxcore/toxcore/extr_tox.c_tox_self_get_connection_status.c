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
struct TYPE_4__ {int /*<<< orphan*/  onion_c; } ;
typedef  TYPE_1__ Tox ;
typedef  int /*<<< orphan*/  TOX_CONNECTION ;
typedef  TYPE_1__ Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  TOX_CONNECTION_NONE ; 
 int /*<<< orphan*/  TOX_CONNECTION_TCP ; 
 int /*<<< orphan*/  TOX_CONNECTION_UDP ; 
 unsigned int onion_connection_status (int /*<<< orphan*/ ) ; 

TOX_CONNECTION tox_self_get_connection_status(const Tox *tox)
{
    const Messenger *m = tox;

    unsigned int ret = onion_connection_status(m->onion_c);

    if (ret == 2) {
        return TOX_CONNECTION_UDP;
    } else if (ret == 1) {
        return TOX_CONNECTION_TCP;
    } else {
        return TOX_CONNECTION_NONE;
    }
}