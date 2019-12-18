#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  osvi ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int member_0; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; TYPE_1__ member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_2__ OSVERSIONINFOEXW ;
typedef  int /*<<< orphan*/  DWORDLONG ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  VER_EQUAL ; 
 int /*<<< orphan*/  VER_NT_WORKSTATION ; 
 int /*<<< orphan*/  VER_PRODUCT_TYPE ; 
 int /*<<< orphan*/  VerSetConditionMask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VerifyVersionInfoW (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static BOOL
IsWindowsServer()
{
    OSVERSIONINFOEXW osvi = { sizeof(osvi), 0, 0, 0, 0, {0}, 0, 0, 0, VER_NT_WORKSTATION };
    DWORDLONG        const dwlConditionMask = VerSetConditionMask( 0, VER_PRODUCT_TYPE, VER_EQUAL );

    return !VerifyVersionInfoW(&osvi, VER_PRODUCT_TYPE, dwlConditionMask);
}