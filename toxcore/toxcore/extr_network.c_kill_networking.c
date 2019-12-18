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
struct TYPE_4__ {scalar_t__ family; int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ Networking_Core ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  kill_sock (int /*<<< orphan*/ ) ; 

void kill_networking(Networking_Core *net)
{
    if (!net)
        return;

    if (net->family != 0) /* Socket not initialized */
        kill_sock(net->sock);

    free(net);
    return;
}