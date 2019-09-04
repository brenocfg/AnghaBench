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
struct TYPE_3__ {int /*<<< orphan*/  Item; int /*<<< orphan*/  ItemType; } ;
typedef  int /*<<< orphan*/  TW_UINT32 ;
typedef  int /*<<< orphan*/  TW_UINT16 ;
typedef  TYPE_1__ TW_ONEVALUE ;
typedef  scalar_t__ TW_HANDLE ;

/* Variables and functions */
 scalar_t__ GlobalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GlobalFree (scalar_t__) ; 
 TYPE_1__* GlobalLock (scalar_t__) ; 
 int /*<<< orphan*/  GlobalUnlock (scalar_t__) ; 

__attribute__((used)) static TW_HANDLE alloc_and_set_onevalue(TW_UINT32 val, TW_UINT16 type)
{
    TW_HANDLE hcontainer;
    TW_ONEVALUE *onev;
    hcontainer = GlobalAlloc(0, sizeof(*onev));
    if (hcontainer)
    {
        onev = GlobalLock(hcontainer);
        if (onev)
        {
            onev->ItemType = type;
            onev->Item = val;
            GlobalUnlock(hcontainer);
        }
        else
        {
            GlobalFree(hcontainer);
            hcontainer = 0;
        }
    }
    return hcontainer;
}