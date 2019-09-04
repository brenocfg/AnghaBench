#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  FieldCount; } ;
struct TYPE_4__ {int /*<<< orphan*/ * Line; } ;
typedef  TYPE_1__* PINFCONTEXT ;
typedef  TYPE_2__* PINFCACHELINE ;
typedef  int /*<<< orphan*/  LONG ;

/* Variables and functions */

LONG
InfpGetFieldCount(PINFCONTEXT Context)
{
  if (Context == NULL || Context->Line == NULL)
    return 0;

  return ((PINFCACHELINE)Context->Line)->FieldCount;
}