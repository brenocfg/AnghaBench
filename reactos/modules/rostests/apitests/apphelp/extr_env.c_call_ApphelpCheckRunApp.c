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
typedef  int /*<<< orphan*/  USHORT ;
typedef  int /*<<< orphan*/  ULONG64 ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  PWCHAR ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PULONG ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  pApphelpCheckRunAppEx_w10 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pApphelpCheckRunAppEx_w7 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL call_ApphelpCheckRunApp(HANDLE FileHandle, PWCHAR ApplicationName, PVOID Environment, USHORT ExeType,
                                    PULONG Reason, PVOID* SdbQueryAppCompatData, PULONG SdbQueryAppCompatDataSize,
                                    PVOID* SxsData, PULONG SxsDataSize, PULONG FusionFlags)
{
    ULONG64 SomeFlag1 = 0;
    ULONG SomeFlag2 = 0;

    if (pApphelpCheckRunAppEx_w7)
    {
        return pApphelpCheckRunAppEx_w7(FileHandle, NULL, NULL, ApplicationName, Environment, ExeType, Reason,
                                        SdbQueryAppCompatData, SdbQueryAppCompatDataSize, SxsData, SxsDataSize,
                                        FusionFlags, &SomeFlag1, &SomeFlag2);
    }

    if (pApphelpCheckRunAppEx_w10)
    {
        return pApphelpCheckRunAppEx_w10(FileHandle, NULL, NULL, ApplicationName, Environment, NULL, ExeType, Reason,
                                        SdbQueryAppCompatData, SdbQueryAppCompatDataSize, SxsData, SxsDataSize,
                                        FusionFlags, &SomeFlag1, &SomeFlag2);
    }

    return FALSE;
}