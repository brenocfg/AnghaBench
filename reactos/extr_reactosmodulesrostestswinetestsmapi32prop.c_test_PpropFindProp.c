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
typedef  size_t ULONG ;
struct TYPE_4__ {void* ulPropTag; } ;
typedef  TYPE_1__ SPropValue ;

/* Variables and functions */
 size_t ARRAY_SIZE (void**) ; 
 void* PROP_TAG (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  PT_I2 ; 
 int /*<<< orphan*/  PT_UNSPECIFIED ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 TYPE_1__* pPpropFindProp (TYPE_1__*,unsigned int,void*) ; 
 void** ptTypes ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_PpropFindProp(void)
{
    SPropValue pvProp, *pRet;
    ULONG i;

    if (!pPpropFindProp)
    {
        win_skip("PpropFindProp is not available\n");
        return;
    }

    for (i = 0; i < ARRAY_SIZE(ptTypes); i++)
    {
        pvProp.ulPropTag = ptTypes[i];

        pRet = pPpropFindProp(&pvProp, 1u, ptTypes[i]);
        ok(pRet == &pvProp,
           "PpropFindProp[%d]: Didn't find existing property\n",
           ptTypes[i]);

        pRet = pPpropFindProp(&pvProp, 1u, i ? ptTypes[i-1] : ptTypes[i+1]);
        ok(pRet == NULL, "PpropFindProp[%d]: Found nonexistent property\n",
           ptTypes[i]);
    }

    pvProp.ulPropTag = PROP_TAG(PT_I2, 1u);
    pRet = pPpropFindProp(&pvProp, 1u, PROP_TAG(PT_UNSPECIFIED, 0u));
    ok(pRet == NULL, "PpropFindProp[UNSPECIFIED]: Matched on different id\n");
    pRet = pPpropFindProp(&pvProp, 1u, PROP_TAG(PT_UNSPECIFIED, 1u));
    ok(pRet == &pvProp, "PpropFindProp[UNSPECIFIED]: Didn't match id\n");
}