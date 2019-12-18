#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VDM_COMMAND_INFO ;
struct TYPE_9__ {int CmdLen; int AppLen; int PifLen; int CurDirectoryLen; int EnvLen; int DesktopLen; int TitleLen; int ReservedLen; int /*<<< orphan*/  Reserved; int /*<<< orphan*/  Title; int /*<<< orphan*/  Desktop; int /*<<< orphan*/  StartupInfo; int /*<<< orphan*/  Env; int /*<<< orphan*/  CurDirectory; int /*<<< orphan*/  PifFile; int /*<<< orphan*/  AppName; int /*<<< orphan*/  CmdLine; int /*<<< orphan*/  StdErr; int /*<<< orphan*/  StdOut; int /*<<< orphan*/  StdIn; int /*<<< orphan*/  CodePage; int /*<<< orphan*/  iTask; } ;
struct TYPE_8__ {int EnvLen; int DesktopLen; int TitleLen; int ReservedLen; int CmdLen; int AppLen; int PifLen; int CurDirectoryLen; int /*<<< orphan*/  VDMState; int /*<<< orphan*/ * Reserved; int /*<<< orphan*/ * Title; int /*<<< orphan*/ * Desktop; int /*<<< orphan*/  StartupInfo; int /*<<< orphan*/ * Env; int /*<<< orphan*/ * CurDirectory; int /*<<< orphan*/ * PifFile; int /*<<< orphan*/ * AppName; int /*<<< orphan*/ * CmdLine; int /*<<< orphan*/  StdErr; int /*<<< orphan*/  StdOut; int /*<<< orphan*/  StdIn; int /*<<< orphan*/  CodePage; int /*<<< orphan*/  ExitCode; int /*<<< orphan*/  TaskId; } ;
struct TYPE_7__ {TYPE_2__* CommandInfo; int /*<<< orphan*/  State; int /*<<< orphan*/  ExitCode; } ;
typedef  int /*<<< orphan*/  STARTUPINFOA ;
typedef  TYPE_1__* PVDM_DOS_RECORD ;
typedef  TYPE_2__* PVDM_COMMAND_INFO ;
typedef  TYPE_3__* PBASE_CHECK_VDM ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BaseSrvFreeVDMInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  BaseSrvHeap ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlMoveMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN BaseSrvCopyCommand(PBASE_CHECK_VDM CheckVdmRequest, PVDM_DOS_RECORD DosRecord)
{
    BOOLEAN Success = FALSE;
    PVDM_COMMAND_INFO CommandInfo = NULL;

    /* Allocate the command information structure */
    CommandInfo = (PVDM_COMMAND_INFO)RtlAllocateHeap(BaseSrvHeap,
                                                     HEAP_ZERO_MEMORY,
                                                     sizeof(VDM_COMMAND_INFO));
    if (CommandInfo == NULL) return FALSE;

    /* Fill the structure */
    CommandInfo->TaskId = CheckVdmRequest->iTask;
    CommandInfo->ExitCode = DosRecord->ExitCode;
    CommandInfo->CodePage = CheckVdmRequest->CodePage;
    CommandInfo->StdIn = CheckVdmRequest->StdIn;
    CommandInfo->StdOut = CheckVdmRequest->StdOut;
    CommandInfo->StdErr = CheckVdmRequest->StdErr;

    /* Allocate memory for the command line */
    CommandInfo->CmdLine = RtlAllocateHeap(BaseSrvHeap,
                                           HEAP_ZERO_MEMORY,
                                           CheckVdmRequest->CmdLen);
    if (CommandInfo->CmdLine == NULL) goto Cleanup;

    /* Copy the command line */
    RtlMoveMemory(CommandInfo->CmdLine, CheckVdmRequest->CmdLine, CheckVdmRequest->CmdLen);

    /* Allocate memory for the application name */
    CommandInfo->AppName = RtlAllocateHeap(BaseSrvHeap,
                                           HEAP_ZERO_MEMORY,
                                           CheckVdmRequest->AppLen);
    if (CommandInfo->AppName == NULL) goto Cleanup;

    /* Copy the application name */
    RtlMoveMemory(CommandInfo->AppName, CheckVdmRequest->AppName, CheckVdmRequest->AppLen);

    /* Allocate memory for the PIF file name */
    if (CheckVdmRequest->PifLen != 0)
    {
        CommandInfo->PifFile = RtlAllocateHeap(BaseSrvHeap,
                                               HEAP_ZERO_MEMORY,
                                               CheckVdmRequest->PifLen);
        if (CommandInfo->PifFile == NULL) goto Cleanup;

        /* Copy the PIF file name */
        RtlMoveMemory(CommandInfo->PifFile, CheckVdmRequest->PifFile, CheckVdmRequest->PifLen);
    }
    else CommandInfo->PifFile = NULL;

    /* Allocate memory for the current directory */
    if (CheckVdmRequest->CurDirectoryLen != 0)
    {
        CommandInfo->CurDirectory = RtlAllocateHeap(BaseSrvHeap,
                                                    HEAP_ZERO_MEMORY,
                                                    CheckVdmRequest->CurDirectoryLen);
        if (CommandInfo->CurDirectory == NULL) goto Cleanup;

        /* Copy the current directory */
        RtlMoveMemory(CommandInfo->CurDirectory,
                      CheckVdmRequest->CurDirectory,
                      CheckVdmRequest->CurDirectoryLen);
    }
    else CommandInfo->CurDirectory = NULL;

    /* Allocate memory for the environment block */
    CommandInfo->Env = RtlAllocateHeap(BaseSrvHeap,
                                       HEAP_ZERO_MEMORY,
                                       CheckVdmRequest->EnvLen);
    if (CommandInfo->Env == NULL) goto Cleanup;

    /* Copy the environment block */
    RtlMoveMemory(CommandInfo->Env, CheckVdmRequest->Env, CheckVdmRequest->EnvLen);

    CommandInfo->EnvLen = CheckVdmRequest->EnvLen;
    RtlMoveMemory(&CommandInfo->StartupInfo,
                  CheckVdmRequest->StartupInfo,
                  sizeof(STARTUPINFOA));

    /* Allocate memory for the desktop */
    if (CheckVdmRequest->DesktopLen != 0)
    {
        CommandInfo->Desktop = RtlAllocateHeap(BaseSrvHeap,
                                               HEAP_ZERO_MEMORY,
                                               CheckVdmRequest->DesktopLen);
        if (CommandInfo->Desktop == NULL) goto Cleanup;

        /* Copy the desktop name */
        RtlMoveMemory(CommandInfo->Desktop, CheckVdmRequest->Desktop, CheckVdmRequest->DesktopLen);
    }
    else CommandInfo->Desktop = NULL;

    CommandInfo->DesktopLen = CheckVdmRequest->DesktopLen;

    /* Allocate memory for the title */
    if (CheckVdmRequest->TitleLen != 0)
    {
        CommandInfo->Title = RtlAllocateHeap(BaseSrvHeap,
                                             HEAP_ZERO_MEMORY,
                                             CheckVdmRequest->TitleLen);
        if (CommandInfo->Title == NULL) goto Cleanup;

        /* Copy the title */
        RtlMoveMemory(CommandInfo->Title, CheckVdmRequest->Title, CheckVdmRequest->TitleLen);
    }
    else CommandInfo->Title = NULL;

    CommandInfo->TitleLen = CheckVdmRequest->TitleLen;

    /* Allocate memory for the reserved field */
    if (CheckVdmRequest->ReservedLen != 0)
    {
        CommandInfo->Reserved = RtlAllocateHeap(BaseSrvHeap,
                                                HEAP_ZERO_MEMORY,
                                                CheckVdmRequest->ReservedLen);
        if (CommandInfo->Reserved == NULL) goto Cleanup;

        /* Copy the reserved field */
        RtlMoveMemory(CommandInfo->Reserved,
                      CheckVdmRequest->Reserved,
                      CheckVdmRequest->ReservedLen);
    }
    else CommandInfo->Reserved = NULL;

    CommandInfo->ReservedLen = CheckVdmRequest->ReservedLen;

    CommandInfo->CmdLen = CheckVdmRequest->CmdLen;
    CommandInfo->AppLen = CheckVdmRequest->AppLen;
    CommandInfo->PifLen = CheckVdmRequest->PifLen;
    CommandInfo->CurDirectoryLen = CheckVdmRequest->CurDirectoryLen;
    CommandInfo->VDMState = DosRecord->State;
    // TODO: Set CommandInfo->CurrentDrive
    // TODO: Set CommandInfo->ComingFromBat

    /* Set the DOS record's command structure */
    DosRecord->CommandInfo = CommandInfo;

    /* The operation was successful */
    Success = TRUE;

Cleanup:
    /* If it wasn't successful, free the memory */
    if (!Success) BaseSrvFreeVDMInfo(CommandInfo);

    return Success;
}