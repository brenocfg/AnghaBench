#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_6__ {scalar_t__ status; } ;
struct TYPE_5__ {size_t num_cons; TYPE_3__* conns; } ;
typedef  TYPE_1__ Friend_Connections ;
typedef  int /*<<< orphan*/  Friend_Conn ;

/* Variables and functions */
 scalar_t__ FRIENDCONN_STATUS_NONE ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ realloc_friendconns (TYPE_1__*,int) ; 

__attribute__((used)) static int create_friend_conn(Friend_Connections *fr_c)
{
    uint32_t i;

    for (i = 0; i < fr_c->num_cons; ++i) {
        if (fr_c->conns[i].status == FRIENDCONN_STATUS_NONE)
            return i;
    }

    int id = -1;

    if (realloc_friendconns(fr_c, fr_c->num_cons + 1) == 0) {
        id = fr_c->num_cons;
        ++fr_c->num_cons;
        memset(&(fr_c->conns[id]), 0, sizeof(Friend_Conn));
    }

    return id;
}