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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {struct TYPE_4__* Reserved; struct TYPE_4__* Title; struct TYPE_4__* Desktop; struct TYPE_4__* Env; struct TYPE_4__* CurDirectory; struct TYPE_4__* PifFile; struct TYPE_4__* AppName; struct TYPE_4__* CmdLine; } ;
typedef  TYPE_1__* PVDM_COMMAND_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  BaseSrvHeap ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

VOID BaseSrvFreeVDMInfo(PVDM_COMMAND_INFO CommandInfo)
{
    /* Free the allocated structure members */
    if (CommandInfo->CmdLine != NULL) RtlFreeHeap(BaseSrvHeap, 0, CommandInfo->CmdLine);
    if (CommandInfo->AppName != NULL) RtlFreeHeap(BaseSrvHeap, 0, CommandInfo->AppName);
    if (CommandInfo->PifFile != NULL) RtlFreeHeap(BaseSrvHeap, 0, CommandInfo->PifFile);
    if (CommandInfo->CurDirectory != NULL) RtlFreeHeap(BaseSrvHeap, 0, CommandInfo->CurDirectory);
    if (CommandInfo->Env != NULL) RtlFreeHeap(BaseSrvHeap, 0, CommandInfo->Env);
    if (CommandInfo->Desktop != NULL) RtlFreeHeap(BaseSrvHeap, 0, CommandInfo->Desktop);
    if (CommandInfo->Title != NULL) RtlFreeHeap(BaseSrvHeap, 0, CommandInfo->Title);
    if (CommandInfo->Reserved != NULL) RtlFreeHeap(BaseSrvHeap, 0, CommandInfo->Reserved);

    /* Free the structure itself */
    RtlFreeHeap(BaseSrvHeap, 0, CommandInfo);
}