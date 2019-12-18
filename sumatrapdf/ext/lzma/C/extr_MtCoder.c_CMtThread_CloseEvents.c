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
struct TYPE_3__ {int /*<<< orphan*/  canWrite; int /*<<< orphan*/  canRead; } ;
typedef  TYPE_1__ CMtThread ;

/* Variables and functions */
 int /*<<< orphan*/  Event_Close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CMtThread_CloseEvents(CMtThread *p)
{
  Event_Close(&p->canRead);
  Event_Close(&p->canWrite);
}