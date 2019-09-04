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
struct TYPE_5__ {TYPE_1__* doc_obj; } ;
struct TYPE_4__ {int /*<<< orphan*/  update; scalar_t__ hwnd; } ;
typedef  TYPE_2__ HTMLDocument ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  SetTimer (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIMER_ID ; 

void update_doc(HTMLDocument *This, DWORD flags)
{
    if(!This->doc_obj->update && This->doc_obj->hwnd)
        SetTimer(This->doc_obj->hwnd, TIMER_ID, 100, NULL);

    This->doc_obj->update |= flags;
}