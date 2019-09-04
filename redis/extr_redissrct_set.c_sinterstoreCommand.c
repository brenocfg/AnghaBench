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
struct TYPE_4__ {int /*<<< orphan*/ * argv; scalar_t__ argc; } ;
typedef  TYPE_1__ client ;

/* Variables and functions */
 int /*<<< orphan*/  sinterGenericCommand (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

void sinterstoreCommand(client *c) {
    sinterGenericCommand(c,c->argv+2,c->argc-2,c->argv[1]);
}