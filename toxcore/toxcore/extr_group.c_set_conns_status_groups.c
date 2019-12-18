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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ num_chats; } ;
typedef  TYPE_1__ Group_Chats ;

/* Variables and functions */
 int /*<<< orphan*/  set_conns_type_close (TYPE_1__*,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_conns_status_groups(Group_Chats *g_c, int friendcon_id, uint8_t type)
{
    uint32_t i;

    for (i = 0; i < g_c->num_chats; ++i) {
        set_conns_type_close(g_c, i, friendcon_id, type);
    }
}