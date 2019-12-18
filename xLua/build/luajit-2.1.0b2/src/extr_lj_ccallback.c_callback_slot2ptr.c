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
typedef  void uint8_t ;
struct TYPE_4__ {scalar_t__ mcode; } ;
struct TYPE_5__ {TYPE_1__ cb; } ;
typedef  int /*<<< orphan*/  MSize ;
typedef  TYPE_2__ CTState ;

/* Variables and functions */
 int CALLBACK_SLOT2OFS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *callback_slot2ptr(CTState *cts, MSize slot)
{
  return (uint8_t *)cts->cb.mcode + CALLBACK_SLOT2OFS(slot);
}