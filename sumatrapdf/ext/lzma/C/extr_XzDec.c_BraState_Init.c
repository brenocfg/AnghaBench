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
struct TYPE_2__ {scalar_t__ methodId; int /*<<< orphan*/  deltaState; int /*<<< orphan*/  x86State; scalar_t__ bufTotal; scalar_t__ bufConv; scalar_t__ bufPos; } ;
typedef  TYPE_1__ CBraState ;

/* Variables and functions */
 int /*<<< orphan*/  Delta_Init (int /*<<< orphan*/ ) ; 
 scalar_t__ XZ_ID_Delta ; 
 int /*<<< orphan*/  x86_Convert_Init (int /*<<< orphan*/ ) ; 

void BraState_Init(void *pp)
{
  CBraState *p = ((CBraState *)pp);
  p->bufPos = p->bufConv = p->bufTotal = 0;
  x86_Convert_Init(p->x86State);
  if (p->methodId == XZ_ID_Delta)
    Delta_Init(p->deltaState);
}