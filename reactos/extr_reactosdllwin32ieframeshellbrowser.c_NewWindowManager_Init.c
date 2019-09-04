#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {TYPE_3__* doc_host; TYPE_1__ INewWindowManager_iface; } ;
struct TYPE_7__ {TYPE_2__ nwm; } ;
typedef  TYPE_3__ DocHost ;

/* Variables and functions */
 int /*<<< orphan*/  NewWindowManagerVtbl ; 

void NewWindowManager_Init(DocHost *doc_host)
{
    doc_host->nwm.INewWindowManager_iface.lpVtbl = &NewWindowManagerVtbl;
    doc_host->nwm.doc_host = doc_host;
}