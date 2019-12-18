#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ToxAV ;
struct TYPE_2__ {int state; } ;
typedef  TYPE_1__ CallControl ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int /*<<< orphan*/ *) ; 

void t_toxav_call_state_cb(ToxAV *av, uint32_t friend_number, uint32_t state, void *user_data)
{
    printf("Handling CALL STATE callback: %d %p\n", state, av);
    ((CallControl *)user_data)[friend_number].state = state;
}