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
struct TYPE_4__ {scalar_t__ ret; int /*<<< orphan*/  mruA; } ;
typedef  TYPE_1__ create_lazya_t ;
typedef  int /*<<< orphan*/  MRUINFOA ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* create_lazyA ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pCreateMRUListLazyA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pFreeMRUList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_CreateMRUListLazyA(void)
{
    int i;

    if (!pCreateMRUListLazyA || !pFreeMRUList)
    {
        win_skip("CreateMRUListLazyA or FreeMRUList entry points not found\n");
        return;
    }

    for (i = 0; i < ARRAY_SIZE(create_lazyA); i++)
    {
        const create_lazya_t *ptr = &create_lazyA[i];
        HANDLE hMRU;

        hMRU = pCreateMRUListLazyA((MRUINFOA*)&ptr->mruA, 0, 0, 0);
        if (ptr->ret)
        {
            ok(hMRU != NULL, "%d: got %p\n", i, hMRU);
            pFreeMRUList(hMRU);
        }
        else
            ok(hMRU == NULL, "%d: got %p\n", i, hMRU);
    }
}