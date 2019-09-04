#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  client ;

/* Variables and functions */
 int /*<<< orphan*/  msetGenericCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void msetCommand(client *c) {
    msetGenericCommand(c,0);
}