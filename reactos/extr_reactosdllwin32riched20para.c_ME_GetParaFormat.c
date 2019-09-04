#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_11__ {int cbSize; int /*<<< orphan*/  dwMask; } ;
struct TYPE_9__ {TYPE_3__ fmt; } ;
struct TYPE_10__ {TYPE_1__ para; } ;
struct TYPE_12__ {TYPE_2__ member; } ;
typedef  TYPE_3__ PARAFORMAT2 ;
typedef  int /*<<< orphan*/  ME_TextEditor ;
typedef  TYPE_4__ ME_DisplayItem ;

/* Variables and functions */
 int /*<<< orphan*/  CopyMemory (TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  PFM_ALL ; 

__attribute__((used)) static void ME_GetParaFormat(ME_TextEditor *editor,
                             const ME_DisplayItem *para,
                             PARAFORMAT2 *pFmt)
{
  UINT cbSize = pFmt->cbSize;
  if (pFmt->cbSize >= sizeof(PARAFORMAT2)) {
    *pFmt = para->member.para.fmt;
  } else {
    CopyMemory(pFmt, &para->member.para.fmt, pFmt->cbSize);
    pFmt->dwMask &= PFM_ALL;
  }
  pFmt->cbSize = cbSize;
}