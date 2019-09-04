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
struct TYPE_2__ {scalar_t__ saveparamslen; int /*<<< orphan*/ * saveparams; } ;

/* Variables and functions */
 TYPE_1__ server ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

void resetServerSaveParams(void) {
    zfree(server.saveparams);
    server.saveparams = NULL;
    server.saveparamslen = 0;
}