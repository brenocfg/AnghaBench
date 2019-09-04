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
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int refs; TYPE_2__ IKindaEnumWidget_iface; } ;
typedef  TYPE_1__ KindaEnum ;
typedef  TYPE_2__ IKindaEnumWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KindaEnumWidget_VTable ; 

__attribute__((used)) static IKindaEnumWidget *KindaEnumWidget_Create(void)
{
    KindaEnum *This;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(*This));
    if (!This) return NULL;
    This->IKindaEnumWidget_iface.lpVtbl = &KindaEnumWidget_VTable;
    This->refs = 1;
    return &This->IKindaEnumWidget_iface;
}