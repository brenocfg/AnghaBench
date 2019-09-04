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
struct TYPE_2__ {int /*<<< orphan*/  already_expired; int /*<<< orphan*/  expires; int /*<<< orphan*/  keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ rdbstate ; 

void rdbShowGenericInfo(void) {
    printf("[info] %lu keys read\n", rdbstate.keys);
    printf("[info] %lu expires\n", rdbstate.expires);
    printf("[info] %lu already expired\n", rdbstate.already_expired);
}