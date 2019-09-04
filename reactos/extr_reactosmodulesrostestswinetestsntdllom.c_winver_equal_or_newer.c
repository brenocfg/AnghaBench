#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  info ;
typedef  void* WORD ;
typedef  int /*<<< orphan*/  ULONGLONG ;
struct TYPE_3__ {int member_0; void* dwMinorVersion; void* dwMajorVersion; } ;
typedef  TYPE_1__ OSVERSIONINFOEXW ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  VER_GREATER_EQUAL ; 
 int VER_MAJORVERSION ; 
 int VER_MINORVERSION ; 
 int /*<<< orphan*/  VER_SET_CONDITION (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VerifyVersionInfoW (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL winver_equal_or_newer(WORD major, WORD minor)
{
    OSVERSIONINFOEXW info = {sizeof(info)};
    ULONGLONG mask = 0;

    info.dwMajorVersion = major;
    info.dwMinorVersion = minor;

    VER_SET_CONDITION(mask, VER_MAJORVERSION, VER_GREATER_EQUAL);
    VER_SET_CONDITION(mask, VER_MINORVERSION, VER_GREATER_EQUAL);

    return VerifyVersionInfoW(&info, VER_MAJORVERSION | VER_MINORVERSION, mask);
}