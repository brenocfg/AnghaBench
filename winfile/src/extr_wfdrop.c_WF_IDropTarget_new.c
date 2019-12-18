#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int m_lRefCount; int /*<<< orphan*/  m_fAllowDrop; int /*<<< orphan*/  m_hWnd; TYPE_1__ idt; } ;
typedef  TYPE_2__ WF_IDropTarget ;
typedef  int /*<<< orphan*/  IDropTargetVtbl ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  idt_vtbl ; 

WF_IDropTarget * WF_IDropTarget_new(HWND hwnd)
{
  WF_IDropTarget *result;

  result = calloc(1, sizeof(WF_IDropTarget));

  if (result)
  {
	  result->idt.lpVtbl = (IDropTargetVtbl*)&idt_vtbl;

	  result->m_lRefCount = 1;
	  result->m_hWnd = hwnd;
	  result->m_fAllowDrop = FALSE;

	  // return result;
  }

  return result;
}