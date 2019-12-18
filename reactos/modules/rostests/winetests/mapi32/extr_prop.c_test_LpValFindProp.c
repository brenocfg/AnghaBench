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
struct TYPE_4__ {int /*<<< orphan*/  ulPropTag; } ;
typedef  TYPE_1__ SPropValue ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROP_TAG (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  PT_NULL ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* pLpValFindProp (int /*<<< orphan*/ ,unsigned int,TYPE_1__*) ; 
 int /*<<< orphan*/ * ptTypes ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_LpValFindProp(void)
{
    SPropValue pvProp, *pRet;
    ULONG i;

    if (!pLpValFindProp)
    {
        win_skip("LpValFindProp is not available\n");
        return;
    }

    for (i = 0; i < ARRAY_SIZE(ptTypes); i++)
    {
        pvProp.ulPropTag = PROP_TAG(ptTypes[i], 1u);

        pRet = pLpValFindProp(PROP_TAG(ptTypes[i], 1u), 1u, &pvProp);
        ok(pRet == &pvProp,
           "LpValFindProp[%d]: Didn't find existing property id/type\n",
           ptTypes[i]);

        pRet = pLpValFindProp(PROP_TAG(ptTypes[i], 0u), 1u, &pvProp);
        ok(pRet == NULL, "LpValFindProp[%d]: Found nonexistent property id\n",
           ptTypes[i]);

        pRet = pLpValFindProp(PROP_TAG(PT_NULL, 0u), 1u, &pvProp);
        ok(pRet == NULL, "LpValFindProp[%d]: Found nonexistent property id/type\n",
           ptTypes[i]);

        pRet = pLpValFindProp(PROP_TAG(PT_NULL, 1u), 1u, &pvProp);
        ok(pRet == &pvProp,
           "LpValFindProp[%d]: Didn't find existing property id\n",
           ptTypes[i]);
    }
}