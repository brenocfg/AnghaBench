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
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  pAddMRUData ; 
 int pFindMRUData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_AddMRUData(void)
{
    INT iRet;

    if (!pAddMRUData)
    {
        win_skip("AddMRUData entry point not found\n");
        return;
    }

    /* NULL handle */
    iRet = pFindMRUData(NULL, NULL, 0, NULL);
    ok(iRet == -1, "AddMRUData expected -1, got %d\n", iRet);
}