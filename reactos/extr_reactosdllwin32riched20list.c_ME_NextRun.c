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
struct TYPE_4__ {scalar_t__ type; struct TYPE_4__* next; } ;
typedef  TYPE_1__ ME_DisplayItem ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ diParagraph ; 
 scalar_t__ diRun ; 
 scalar_t__ diTextEnd ; 

BOOL ME_NextRun(ME_DisplayItem **para, ME_DisplayItem **run, BOOL all_para)
{
  ME_DisplayItem *p = (*run)->next;
  while (p->type != diTextEnd)
  {
    if (p->type == diParagraph) {
      if (!all_para) return FALSE;
      *para = p;
    } else if (p->type == diRun) {
      *run = p;
      return TRUE;
    }
    p = p->next;
  }
  return FALSE;
}