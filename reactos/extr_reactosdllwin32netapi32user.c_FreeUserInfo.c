#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_28__ {TYPE_13__* Buffer; } ;
struct TYPE_27__ {TYPE_13__* Buffer; } ;
struct TYPE_26__ {TYPE_13__* Buffer; } ;
struct TYPE_25__ {TYPE_13__* Buffer; } ;
struct TYPE_24__ {TYPE_13__* Buffer; } ;
struct TYPE_23__ {TYPE_13__* Buffer; } ;
struct TYPE_22__ {TYPE_13__* Buffer; } ;
struct TYPE_21__ {TYPE_13__* Buffer; } ;
struct TYPE_20__ {TYPE_13__* Buffer; } ;
struct TYPE_18__ {TYPE_13__* LogonHours; } ;
struct TYPE_17__ {TYPE_13__* Buffer; } ;
struct TYPE_16__ {TYPE_13__* Buffer; } ;
struct TYPE_19__ {TYPE_12__ LogonHours; TYPE_11__ PrivateData; TYPE_10__ Parameters; TYPE_9__ UserComment; TYPE_8__ WorkStations; TYPE_7__ AdminComment; TYPE_6__ ProfilePath; TYPE_5__ ScriptPath; TYPE_4__ HomeDirectoryDrive; TYPE_3__ HomeDirectory; TYPE_2__ FullName; TYPE_1__ UserName; } ;
typedef  TYPE_13__* PUSER_ALL_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  SamFreeMemory (TYPE_13__*) ; 

__attribute__((used)) static
VOID
FreeUserInfo(PUSER_ALL_INFORMATION UserInfo)
{
    if (UserInfo->UserName.Buffer != NULL)
        SamFreeMemory(UserInfo->UserName.Buffer);

    if (UserInfo->FullName.Buffer != NULL)
        SamFreeMemory(UserInfo->FullName.Buffer);

    if (UserInfo->HomeDirectory.Buffer != NULL)
        SamFreeMemory(UserInfo->HomeDirectory.Buffer);

    if (UserInfo->HomeDirectoryDrive.Buffer != NULL)
        SamFreeMemory(UserInfo->HomeDirectoryDrive.Buffer);

    if (UserInfo->ScriptPath.Buffer != NULL)
        SamFreeMemory(UserInfo->ScriptPath.Buffer);

    if (UserInfo->ProfilePath.Buffer != NULL)
        SamFreeMemory(UserInfo->ProfilePath.Buffer);

    if (UserInfo->AdminComment.Buffer != NULL)
        SamFreeMemory(UserInfo->AdminComment.Buffer);

    if (UserInfo->WorkStations.Buffer != NULL)
        SamFreeMemory(UserInfo->WorkStations.Buffer);

    if (UserInfo->UserComment.Buffer != NULL)
        SamFreeMemory(UserInfo->UserComment.Buffer);

    if (UserInfo->Parameters.Buffer != NULL)
        SamFreeMemory(UserInfo->Parameters.Buffer);

    if (UserInfo->PrivateData.Buffer != NULL)
        SamFreeMemory(UserInfo->PrivateData.Buffer);

    if (UserInfo->LogonHours.LogonHours != NULL)
        SamFreeMemory(UserInfo->LogonHours.LogonHours);

    SamFreeMemory(UserInfo);
}