#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_3__ {scalar_t__ DeviceType; struct TYPE_3__* Next; } ;
typedef  TYPE_1__* PDEVICE_LIST ;
typedef  int DWORD ;

/* Variables and functions */
 TYPE_1__* DeviceList ; 

DWORD GetDeviceCount(UINT DeviceType)
{
    int i;
    PDEVICE_LIST List;

    for (List = DeviceList, i = 0; List != NULL; List = List->Next)
        if (List->DeviceType == DeviceType)
            i ++;

    return i;
}