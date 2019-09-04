#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {TYPE_3__ IPersistStreamInit_iface; TYPE_2__ IPersistMemory_iface; TYPE_1__ IPersistStorage_iface; } ;
typedef  TYPE_4__ WebBrowser ;

/* Variables and functions */
 int /*<<< orphan*/  PersistMemoryVtbl ; 
 int /*<<< orphan*/  PersistStorageVtbl ; 
 int /*<<< orphan*/  PersistStreamInitVtbl ; 

void WebBrowser_Persist_Init(WebBrowser *This)
{
    This->IPersistStorage_iface.lpVtbl    = &PersistStorageVtbl;
    This->IPersistMemory_iface.lpVtbl     = &PersistMemoryVtbl;
    This->IPersistStreamInit_iface.lpVtbl = &PersistStreamInitVtbl;
}