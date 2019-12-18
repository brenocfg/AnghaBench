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
struct TYPE_7__ {scalar_t__ ConType; int Cap; int /*<<< orphan*/  hContainer; } ;
struct TYPE_6__ {int* ItemList; int NumItems; scalar_t__ ItemType; size_t CurrentIndex; size_t DefaultIndex; } ;
struct TYPE_5__ {int Item; int /*<<< orphan*/  ItemType; } ;
typedef  int TW_UINT8 ;
typedef  int TW_UINT32 ;
typedef  int TW_UINT16 ;
typedef  TYPE_1__ TW_ONEVALUE ;
typedef  int TW_INT32 ;
typedef  TYPE_2__ TW_ENUMERATION ;
typedef  TYPE_3__ TW_CAPABILITY ;

/* Variables and functions */
 void* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 scalar_t__ TWON_ENUMERATION ; 
 scalar_t__ TWON_ONEVALUE ; 
 int TWQC_GETCURRENT ; 
 scalar_t__ TWTY_INT16 ; 
 scalar_t__ TWTY_INT32 ; 
 scalar_t__ TWTY_INT8 ; 
 scalar_t__ TWTY_UINT16 ; 
 scalar_t__ TWTY_UINT32 ; 
 scalar_t__ TWTY_UINT8 ; 
 int /*<<< orphan*/  ok (int,char*,int,int,int) ; 
 int /*<<< orphan*/  trace (char*,int,int,...) ; 

__attribute__((used)) static void check_get(TW_CAPABILITY *pCapability, TW_INT32 actual_support,
                TW_UINT32 orig_value, TW_UINT32 default_value, TW_UINT32 *suggested_set_value)
{
    void *p;
    if (suggested_set_value)
        *suggested_set_value = orig_value + 1;
    p = GlobalLock(pCapability->hContainer);
    if (p)
    {
        if (pCapability->ConType == TWON_ONEVALUE)
        {
            TW_ONEVALUE *onev = p;
            ok(onev->Item == orig_value || !(actual_support & TWQC_GETCURRENT), "MSG_GET of 0x%x returned 0x%x, expecting 0x%x\n",
                pCapability->Cap, onev->Item, orig_value);
            trace("MSG_GET of 0x%x returned val 0x%x, type %d\n", pCapability->Cap, onev->Item, onev->ItemType);
            if (suggested_set_value)
                *suggested_set_value = onev->Item;
        }
        else if (pCapability->ConType == TWON_ENUMERATION)
        {
            int i;
            TW_UINT8 *p8;
            TW_UINT16 *p16;
            TW_UINT32 *p32;
            TW_ENUMERATION *enumv = p;
            p8 = enumv->ItemList;
            p16 = (TW_UINT16 *) p8;
            p32 = (TW_UINT32 *) p8;
            trace("MSG_GET of 0x%x returned %d items:\n", pCapability->Cap, enumv->NumItems);
            for (i = 0; i < enumv->NumItems; i++)
            {
                if (enumv->ItemType == TWTY_UINT8 || enumv->ItemType == TWTY_INT8)
                    trace("  %d: 0x%x\n", i, p8[i]);
                if (enumv->ItemType == TWTY_UINT16 || enumv->ItemType == TWTY_INT16)
                    trace("  %d: 0x%x\n", i, p16[i]);
                if (enumv->ItemType == TWTY_UINT32 || enumv->ItemType == TWTY_INT32)
                    trace("  %d: 0x%x\n", i, p32[i]);
            }
            if (enumv->ItemType == TWTY_UINT16 || enumv->ItemType == TWTY_INT16)
            {
                ok(p16[enumv->CurrentIndex] == orig_value,
                    "Type 0x%x, values from MSG_GET (0x%x) and MSG_GETCURRENT (0x%x) do not match.\n",
                    pCapability->Cap, p16[enumv->CurrentIndex], orig_value);
                ok(p16[enumv->DefaultIndex] == default_value,
                    "Type 0x%x, values from MSG_GET (0x%x) and MSG_GETDEFAULT (0x%x) do not match.\n",
                    pCapability->Cap, p16[enumv->DefaultIndex], default_value);
                if (suggested_set_value)
                    *suggested_set_value = p16[(enumv->CurrentIndex + 1) % enumv->NumItems];
            }
            if (enumv->ItemType == TWTY_UINT32 || enumv->ItemType == TWTY_INT32)
            {
                ok(p32[enumv->CurrentIndex] == orig_value,
                    "Type 0x%x, values from MSG_GET (0x%x) and MSG_GETCURRENT (0x%x) do not match.\n",
                    pCapability->Cap, p32[enumv->CurrentIndex], orig_value);
                ok(p32[enumv->DefaultIndex] == default_value,
                    "Type 0x%x, values from MSG_GET (0x%x) and MSG_GETDEFAULT (0x%x) do not match.\n",
                    pCapability->Cap, p32[enumv->DefaultIndex], default_value);
                if (suggested_set_value)
                    *suggested_set_value = p32[(enumv->CurrentIndex + 1) % enumv->NumItems];
            }
        }
        else
            trace("MSG_GET on type 0x%x returned type 0x%x, which we didn't check.\n", pCapability->Cap, pCapability->ConType);
        GlobalUnlock(pCapability->hContainer);
    }
}