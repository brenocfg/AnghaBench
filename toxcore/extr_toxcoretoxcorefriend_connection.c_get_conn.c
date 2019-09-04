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
struct TYPE_4__ {int /*<<< orphan*/ * conns; } ;
typedef  TYPE_1__ Friend_Connections ;
typedef  int /*<<< orphan*/  Friend_Conn ;

/* Variables and functions */
 scalar_t__ friendconn_id_not_valid (TYPE_1__ const*,int) ; 

__attribute__((used)) static Friend_Conn *get_conn(const Friend_Connections *fr_c, int friendcon_id)
{
    if (friendconn_id_not_valid(fr_c, friendcon_id))
        return 0;

    return &fr_c->conns[friendcon_id];
}