#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int dwMask; int wEffects; } ;
struct TYPE_8__ {TYPE_3__ fmt; } ;
struct TYPE_9__ {TYPE_1__ para; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_2__ member; } ;
typedef  TYPE_3__ PARAFORMAT2 ;
typedef  TYPE_4__ ME_DisplayItem ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 TYPE_4__* ME_GetParagraph (TYPE_4__*) ; 
 int PFE_TABLE ; 
 int PFM_TABLE ; 
 scalar_t__ diParagraph ; 
 scalar_t__ diRun ; 

BOOL ME_IsInTable(ME_DisplayItem *pItem)
{
  PARAFORMAT2 *pFmt;
  if (!pItem)
    return FALSE;
  if (pItem->type == diRun)
    pItem = ME_GetParagraph(pItem);
  if (pItem->type != diParagraph)
    return FALSE;
  pFmt = &pItem->member.para.fmt;
  return pFmt->dwMask & PFM_TABLE && pFmt->wEffects & PFE_TABLE;
}