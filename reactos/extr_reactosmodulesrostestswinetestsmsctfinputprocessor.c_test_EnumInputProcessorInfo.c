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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  IEnumGUID ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_FakeService ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IEnumGUID_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumGUID_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITfInputProcessorProfiles_EnumInputProcessorInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_ipp ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_EnumInputProcessorInfo(void)
{
    IEnumGUID *ppEnum;
    BOOL found = FALSE;

    if (SUCCEEDED(ITfInputProcessorProfiles_EnumInputProcessorInfo(g_ipp, &ppEnum)))
    {
        ULONG fetched;
        GUID g;
        while (IEnumGUID_Next(ppEnum, 1, &g, &fetched) == S_OK)
        {
            if(IsEqualGUID(&g,&CLSID_FakeService))
                found = TRUE;
        }
        IEnumGUID_Release(ppEnum);
    }
    ok(found,"Did not find registered text service\n");
}