#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ CmdLen; scalar_t__ AppLen; scalar_t__ PifLen; scalar_t__ CurDirectoryLen; scalar_t__ EnvLen; int DesktopLen; int TitleLen; int ReservedLen; int /*<<< orphan*/  Reserved; int /*<<< orphan*/  Title; int /*<<< orphan*/  Desktop; int /*<<< orphan*/  StartupInfo; int /*<<< orphan*/  Env; int /*<<< orphan*/  CurDirectory; int /*<<< orphan*/  PifFile; int /*<<< orphan*/  AppName; int /*<<< orphan*/  CmdLine; int /*<<< orphan*/  fComingFromBat; int /*<<< orphan*/  VDMState; int /*<<< orphan*/  CurrentDrive; int /*<<< orphan*/  ExitCode; int /*<<< orphan*/  dwCreationFlags; int /*<<< orphan*/  CodePage; int /*<<< orphan*/  StdErr; int /*<<< orphan*/  StdOut; int /*<<< orphan*/  StdIn; int /*<<< orphan*/  iTask; } ;
struct TYPE_5__ {scalar_t__ CmdLen; scalar_t__ AppLen; scalar_t__ PifLen; scalar_t__ CurDirectoryLen; scalar_t__ EnvLen; int DesktopLen; int TitleLen; int ReservedLen; int /*<<< orphan*/ * Reserved; int /*<<< orphan*/ * Title; int /*<<< orphan*/ * Desktop; int /*<<< orphan*/  StartupInfo; int /*<<< orphan*/ * Env; int /*<<< orphan*/ * CurDirectory; int /*<<< orphan*/ * PifFile; int /*<<< orphan*/ * AppName; int /*<<< orphan*/ * CmdLine; int /*<<< orphan*/  ComingFromBat; int /*<<< orphan*/  VDMState; int /*<<< orphan*/  CurrentDrive; int /*<<< orphan*/  ExitCode; int /*<<< orphan*/  CreationFlags; int /*<<< orphan*/  CodePage; int /*<<< orphan*/  StdErr; int /*<<< orphan*/  StdOut; int /*<<< orphan*/  StdIn; int /*<<< orphan*/  TaskId; } ;
typedef  int /*<<< orphan*/  STARTUPINFOA ;
typedef  TYPE_1__* PVDM_COMMAND_INFO ;
typedef  TYPE_2__* PBASE_GET_NEXT_VDM_COMMAND ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  RtlMoveMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS BaseSrvFillCommandInfo(PVDM_COMMAND_INFO CommandInfo,
                                PBASE_GET_NEXT_VDM_COMMAND Message)
{
    NTSTATUS Status = STATUS_SUCCESS;

    /* Copy the data */
    Message->iTask = CommandInfo->TaskId;
    Message->StdIn = CommandInfo->StdIn;
    Message->StdOut = CommandInfo->StdOut;
    Message->StdErr = CommandInfo->StdErr;
    Message->CodePage = CommandInfo->CodePage;
    Message->dwCreationFlags = CommandInfo->CreationFlags;
    Message->ExitCode = CommandInfo->ExitCode;
    Message->CurrentDrive = CommandInfo->CurrentDrive;
    Message->VDMState = CommandInfo->VDMState;
    Message->fComingFromBat = CommandInfo->ComingFromBat;

    if (Message->CmdLen >= CommandInfo->CmdLen)
    {
        /* Copy the command line */
        RtlMoveMemory(Message->CmdLine, CommandInfo->CmdLine, CommandInfo->CmdLen);
    }
    else Status = STATUS_INVALID_PARAMETER;
    Message->CmdLen = CommandInfo->CmdLen;

    if (Message->AppLen >= CommandInfo->AppLen)
    {
        /* Copy the application name */
        RtlMoveMemory(Message->AppName, CommandInfo->AppName, CommandInfo->AppLen);
    }
    else Status = STATUS_INVALID_PARAMETER;
    Message->AppLen = CommandInfo->AppLen;

    if (Message->PifLen >= CommandInfo->PifLen)
    {
        /* Copy the PIF file name */
        RtlMoveMemory(Message->PifFile, CommandInfo->PifFile, CommandInfo->PifLen);
    }
    else Status = STATUS_INVALID_PARAMETER;
    Message->PifLen = CommandInfo->PifLen;

    if (Message->CurDirectoryLen >= CommandInfo->CurDirectoryLen)
    {
        /* Copy the current directory */
        RtlMoveMemory(Message->CurDirectory, CommandInfo->CurDirectory, CommandInfo->CurDirectoryLen);
    }
    else Status = STATUS_INVALID_PARAMETER;
    Message->CurDirectoryLen = CommandInfo->CurDirectoryLen;

    if (Message->EnvLen >= CommandInfo->EnvLen)
    {
        /* Copy the environment */
        RtlMoveMemory(Message->Env, CommandInfo->Env, CommandInfo->EnvLen);
    }
    else Status = STATUS_INVALID_PARAMETER;
    Message->EnvLen = CommandInfo->EnvLen;

    /* Copy the startup info */
    RtlMoveMemory(Message->StartupInfo,
                  &CommandInfo->StartupInfo,
                  sizeof(STARTUPINFOA));

    if (Message->DesktopLen >= CommandInfo->DesktopLen)
    {
        /* Copy the desktop name */
        RtlMoveMemory(Message->Desktop, CommandInfo->Desktop, CommandInfo->DesktopLen);
    }
    else Status = STATUS_INVALID_PARAMETER;
    Message->DesktopLen = CommandInfo->DesktopLen;

    if (Message->TitleLen >= CommandInfo->TitleLen)
    {
        /* Copy the title */
        RtlMoveMemory(Message->Title, CommandInfo->Title, CommandInfo->TitleLen);
    }
    else Status = STATUS_INVALID_PARAMETER;
    Message->TitleLen = CommandInfo->TitleLen;

    if (Message->ReservedLen >= CommandInfo->ReservedLen)
    {
        /* Copy the reserved parameter */
        RtlMoveMemory(Message->Reserved, CommandInfo->Reserved, CommandInfo->ReservedLen);
    }
    else Status = STATUS_INVALID_PARAMETER;
    Message->ReservedLen = CommandInfo->ReservedLen;

    return Status;
}