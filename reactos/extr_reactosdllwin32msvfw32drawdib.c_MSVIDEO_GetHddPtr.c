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
struct TYPE_4__ {scalar_t__ hSelf; struct TYPE_4__* next; } ;
typedef  TYPE_1__ WINE_HDD ;
typedef  scalar_t__ HDRAWDIB ;

/* Variables and functions */
 TYPE_1__* HDD_FirstHdd ; 

__attribute__((used)) static WINE_HDD*       MSVIDEO_GetHddPtr(HDRAWDIB hd)
{
    WINE_HDD*   hdd;

    for (hdd = HDD_FirstHdd; hdd != NULL && hdd->hSelf != hd; hdd = hdd->next);
    return hdd;
}