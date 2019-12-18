#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  strA ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  scalar_t__ REFGUID ;
typedef  int /*<<< orphan*/  ITfCompartmentMgr ;
typedef  int /*<<< orphan*/  IEnumGUID ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int FALSE ; 
 scalar_t__ IEnumGUID_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumGUID_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITfCompartmentMgr_EnumCompartments (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IsEqualGUID (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void enum_compartments(ITfCompartmentMgr *cmpmgr, REFGUID present, REFGUID absent)
{
    BOOL found,found2;
    IEnumGUID *ppEnum;
    found = FALSE;
    found2 = FALSE;
    if (SUCCEEDED(ITfCompartmentMgr_EnumCompartments(cmpmgr, &ppEnum)))
    {
        ULONG fetched;
        GUID g;
        while (IEnumGUID_Next(ppEnum, 1, &g, &fetched) == S_OK)
        {
            WCHAR str[50];
            CHAR strA[50];
            StringFromGUID2(&g,str,ARRAY_SIZE(str));
            WideCharToMultiByte(CP_ACP,0,str,-1,strA,sizeof(strA),0,0);
            trace("found %s\n",strA);
            if (present && IsEqualGUID(present,&g))
                found = TRUE;
            if (absent && IsEqualGUID(absent, &g))
                found2 = TRUE;
        }
        IEnumGUID_Release(ppEnum);
    }
    if (present)
        ok(found,"Did not find compartment\n");
    if (absent)
        ok(!found2,"Found compartment that should be absent\n");
}