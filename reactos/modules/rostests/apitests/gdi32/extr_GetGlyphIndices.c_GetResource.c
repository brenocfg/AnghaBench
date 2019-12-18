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
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/ * LPDWORD ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HRSRC ;

/* Variables and functions */
 int /*<<< orphan*/  FindResourceW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetModuleHandleW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LoadResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LockResource (int /*<<< orphan*/ ) ; 
 scalar_t__ RT_RCDATA ; 
 int /*<<< orphan*/  SizeofResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LPVOID GetResource(LPCWSTR FontName, LPDWORD Size)
{
    HRSRC hRsrc;
    LPVOID Data;

    hRsrc = FindResourceW(GetModuleHandleW(NULL), FontName, (LPCWSTR)RT_RCDATA);
    if (!hRsrc) return NULL;

    Data = LockResource(LoadResource(GetModuleHandleW(NULL), hRsrc));
    if (!Data) return NULL;

    *Size = SizeofResource(GetModuleHandleW(NULL), hRsrc);
    if (*Size == 0) return NULL;

    return Data;
}