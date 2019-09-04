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
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  CM_REMOVAL_POLICY_EXPECT_ORDERLY_REMOVAL 129 
#define  CM_REMOVAL_POLICY_EXPECT_SURPRISE_REMOVAL 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static __inline BOOL IsRemovable(const char* buffer)
{
	switch (*((DWORD*)buffer)) {
	case CM_REMOVAL_POLICY_EXPECT_SURPRISE_REMOVAL:
	case CM_REMOVAL_POLICY_EXPECT_ORDERLY_REMOVAL:
		return TRUE;
	default:
		return FALSE;
	}
}