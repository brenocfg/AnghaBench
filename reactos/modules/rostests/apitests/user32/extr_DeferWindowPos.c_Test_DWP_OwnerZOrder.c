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

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_CACHE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPECT_CHAIN (int,int,int,int) ; 
 int /*<<< orphan*/  FlushMessages () ; 
 int /*<<< orphan*/  OwnerZOrder1A_chain ; 
 int /*<<< orphan*/  OwnerZOrder1B_chain ; 
 int /*<<< orphan*/  OwnerZOrder2A_chain ; 
 int /*<<< orphan*/  OwnerZOrder2B_chain ; 
 int /*<<< orphan*/  OwnerZOrder3A_chain ; 
 int /*<<< orphan*/  OwnerZOrder3B_chain ; 
 int /*<<< orphan*/  OwnerZOrder4A_chain ; 
 int /*<<< orphan*/  OwnerZOrder4B_chain ; 
 int /*<<< orphan*/  OwnerZOrder5A_chain ; 
 int /*<<< orphan*/  OwnerZOrder5B_chain ; 
 int /*<<< orphan*/  OwnerZOrderAParams ; 
 int /*<<< orphan*/  OwnerZOrderBParams ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hWnd1 ; 
 int /*<<< orphan*/  hWnd2 ; 
 int /*<<< orphan*/  hWnd3 ; 
 int /*<<< orphan*/  hWnd4 ; 
 int /*<<< orphan*/  set_default_pos () ; 

__attribute__((used)) static void Test_DWP_OwnerZOrder()
{
    EXPECT_CHAIN(4,3,1,2);

    /* test how SetWindowPos can change the z order of owner windows */
    /* note that SWP_NOACTIVATE must be used because otherwise
       SetWindowPos will call SetWindowPos again with different parameters */
    SetWindowPos(hWnd1, 0, 0,0,0,0, OwnerZOrderAParams);
    FlushMessages();
    COMPARE_CACHE(OwnerZOrder1A_chain);
    EXPECT_CHAIN(4,3,1,2);

    SetWindowPos(hWnd2, 0, 0,0,0,0, OwnerZOrderAParams);
    FlushMessages();
    COMPARE_CACHE(OwnerZOrder2A_chain);
    EXPECT_CHAIN(2,4,3,1);

    SetWindowPos(hWnd3, 0, 0,0,0,0, OwnerZOrderAParams);
    FlushMessages();
    COMPARE_CACHE(OwnerZOrder3A_chain);
    EXPECT_CHAIN(3,4,1,2);

    SetWindowPos(hWnd1, 0, 0,0,0,0, OwnerZOrderAParams);
    FlushMessages();
    COMPARE_CACHE(OwnerZOrder4A_chain);
    EXPECT_CHAIN(3,4,1,2);

    SetWindowPos(hWnd4, 0, 0,0,0,0, OwnerZOrderAParams);
    FlushMessages();
    COMPARE_CACHE(OwnerZOrder5A_chain);
    EXPECT_CHAIN(4,3,1,2);

    /* now do the same thing one more time with SWP_NOOWNERZORDER */
    /* SWP_NOACTIVATE is needed because without it SetActiveWindow 
       will be calledit and it will call SetWindowPos again
       WITHOUT SWP_NOOWNERZORDER. that means that
       in order for SWP_NOOWNERZORDER to have effect we have to use 
       SWP_NOACTIVATE as well */
    set_default_pos();
    EXPECT_CHAIN(4,3,2,1);

    SetWindowPos(hWnd1, 0, 0,0,0,0, OwnerZOrderBParams);
    FlushMessages();
    COMPARE_CACHE(OwnerZOrder1B_chain);
    EXPECT_CHAIN(1,4,3,2);

    SetWindowPos(hWnd2, 0, 0,0,0,0, OwnerZOrderBParams);
    FlushMessages();
    COMPARE_CACHE(OwnerZOrder2B_chain);
    EXPECT_CHAIN(2,1,4,3);

    SetWindowPos(hWnd3, 0, 0,0,0,0, OwnerZOrderBParams);
    FlushMessages();
    COMPARE_CACHE(OwnerZOrder3B_chain);
    EXPECT_CHAIN(3,2,1,4);

    SetWindowPos(hWnd1, 0, 0,0,0,0, OwnerZOrderBParams);
    FlushMessages();
    COMPARE_CACHE(OwnerZOrder4B_chain);
    EXPECT_CHAIN(1,3,2,4);

    SetWindowPos(hWnd4, 0, 0,0,0,0, OwnerZOrderBParams);
    FlushMessages();
    COMPARE_CACHE(OwnerZOrder5B_chain);
    EXPECT_CHAIN(4,1,3,2);

}