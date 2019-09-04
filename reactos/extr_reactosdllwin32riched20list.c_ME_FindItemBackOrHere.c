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
struct TYPE_4__ {struct TYPE_4__* prev; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ ME_DisplayItem ;
typedef  int /*<<< orphan*/  ME_DIType ;

/* Variables and functions */
 scalar_t__ ME_DITypesEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ME_DisplayItem *ME_FindItemBackOrHere(ME_DisplayItem *di, ME_DIType nTypeOrClass)
{
  while(di!=NULL) {
    if (ME_DITypesEqual(di->type, nTypeOrClass))
      return di;
    di = di->prev;
  }
  return NULL;
}