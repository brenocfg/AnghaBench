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
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * conns; } ;
typedef  TYPE_1__ Friend_Connections ;
typedef  int /*<<< orphan*/  Friend_Conn ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int realloc_friendconns(Friend_Connections *fr_c, uint32_t num)
{
    if (num == 0) {
        free(fr_c->conns);
        fr_c->conns = NULL;
        return 0;
    }

    Friend_Conn *newgroup_cons = realloc(fr_c->conns, num * sizeof(Friend_Conn));

    if (newgroup_cons == NULL)
        return -1;

    fr_c->conns = newgroup_cons;
    return 0;
}