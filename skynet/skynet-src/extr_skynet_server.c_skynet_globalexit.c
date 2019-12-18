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
struct TYPE_2__ {int /*<<< orphan*/  handle_key; } ;

/* Variables and functions */
 TYPE_1__ G_NODE ; 
 int /*<<< orphan*/  pthread_key_delete (int /*<<< orphan*/ ) ; 

void 
skynet_globalexit(void) {
	pthread_key_delete(G_NODE.handle_key);
}