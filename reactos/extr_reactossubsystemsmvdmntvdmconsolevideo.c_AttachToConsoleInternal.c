#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_14__ {scalar_t__ AsciiChar; } ;
struct TYPE_18__ {scalar_t__ Attributes; TYPE_1__ Char; } ;
struct TYPE_17__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_16__ {int X; int Y; } ;
struct TYPE_15__ {int Right; int Bottom; scalar_t__ Top; scalar_t__ Left; } ;
typedef  TYPE_2__ SMALL_RECT ;
typedef  int SHORT ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PVIDEO_HARDWARE_STATE_HEADER ;
typedef  TYPE_3__* PCOORD ;
typedef  int DWORD ;
typedef  TYPE_4__ COORD ;
typedef  scalar_t__ BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AnotherEvent ; 
 TYPE_8__* CharBuff ; 
 int /*<<< orphan*/  ConsoleInfo ; 
 int /*<<< orphan*/  DisplayMessage (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EmulatorTerminate () ; 
 int /*<<< orphan*/  EndEvent ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetConsoleScreenBufferInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int LOWORD (int) ; 
 int /*<<< orphan*/  ReadConsoleOutputA (int /*<<< orphan*/ ,TYPE_8__*,TYPE_3__,TYPE_4__,TYPE_2__*) ; 
 int /*<<< orphan*/  ResizeTextConsole (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StartEvent ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TextConsoleBuffer ; 
 int /*<<< orphan*/ * TextFramebuffer ; 
 TYPE_3__ TextResolution ; 
 int /*<<< orphan*/  UpdateCursorPosition () ; 
 size_t VGA_CRTC_OFFSET_REG ; 
 int VGA_NUM_BANKS ; 
 scalar_t__* VgaCrtcRegisters ; 
 int VgaGetAddressSize () ; 
 scalar_t__* VgaMemory ; 
 int /*<<< orphan*/  __RegisterConsoleVDM (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL AttachToConsoleInternal(PCOORD Resolution)
{
    BOOL Success;
    ULONG Length = 0;
    PVIDEO_HARDWARE_STATE_HEADER State;

#ifdef USE_REAL_REGISTERCONSOLEVDM
    PCHAR_INFO CharBuff = NULL;
#endif
    SHORT i, j;
    DWORD AddressSize, ScanlineSize;
    DWORD Address = 0;
    DWORD CurrentAddr;
    SMALL_RECT ConRect;
    COORD Origin = { 0, 0 };

    ASSERT(TextFramebuffer == NULL);

    TextResolution = *Resolution;

    /*
     * Windows 2k3 winsrv.dll calls NtVdmControl(VdmQueryVdmProcess == 14, &ConsoleHandle);
     * in the two following APIs:
     * SrvRegisterConsoleVDM  (corresponding Win32 API: RegisterConsoleVDM)
     * SrvVDMConsoleOperation (corresponding Win32 API: VDMConsoleOperation)
     * to check whether the current process is a VDM process, and fails otherwise
     * with the error 0xC0000022 (STATUS_ACCESS_DENIED).
     *
     * It is worth it to notice that also basesrv.dll does the same only for the
     * BaseSrvIsFirstVDM API...
     */

    /* Register with the console server */
    Success =
    __RegisterConsoleVDM(1,
                         StartEvent,
                         EndEvent,
                         AnotherEvent, // NULL,
                         0,
                         &Length, // NULL, <-- putting this (and null in the next var) makes the API returning error 12 "ERROR_INVALID_ACCESS"
                         (PVOID*)&State, // NULL,
                         NULL,
                         0,
                         TextResolution,
                         (PVOID*)&TextFramebuffer);
    if (!Success)
    {
        DisplayMessage(L"RegisterConsoleVDM failed with error %d\n", GetLastError());
        EmulatorTerminate();
        return FALSE;
    }

#ifdef USE_REAL_REGISTERCONSOLEVDM
    CharBuff = RtlAllocateHeap(RtlGetProcessHeap(),
                               HEAP_ZERO_MEMORY,
                               TextResolution.X * TextResolution.Y
                                                * sizeof(*CharBuff));
    ASSERT(CharBuff);
#endif

    /* Resize the console */
    ResizeTextConsole(Resolution, NULL);

    /* Update the saved console information */
    GetConsoleScreenBufferInfo(TextConsoleBuffer, &ConsoleInfo);

    /*
     * Copy console data into VGA memory
     */

    /* Read the data from the console into the framebuffer... */
    ConRect.Left   = ConRect.Top = 0;
    ConRect.Right  = TextResolution.X;
    ConRect.Bottom = TextResolution.Y;

    ReadConsoleOutputA(TextConsoleBuffer,
                       CharBuff,
                       TextResolution,
                       Origin,
                       &ConRect);

    /* ... and copy the framebuffer into the VGA memory */
    AddressSize  = VgaGetAddressSize();
    ScanlineSize = (DWORD)VgaCrtcRegisters[VGA_CRTC_OFFSET_REG] * 2;

    /* Loop through the scanlines */
    for (i = 0; i < TextResolution.Y; i++)
    {
        /* Loop through the characters */
        for (j = 0; j < TextResolution.X; j++)
        {
            CurrentAddr = LOWORD((Address + j) * AddressSize);

            /* Store the character in plane 0 */
            VgaMemory[CurrentAddr * VGA_NUM_BANKS] = CharBuff[i * TextResolution.X + j].Char.AsciiChar;

            /* Store the attribute in plane 1 */
            VgaMemory[CurrentAddr * VGA_NUM_BANKS + 1] = (BYTE)CharBuff[i * TextResolution.X + j].Attributes;
        }

        /* Move to the next scanline */
        Address += ScanlineSize;
    }

#ifdef USE_REAL_REGISTERCONSOLEVDM
    if (CharBuff) RtlFreeHeap(RtlGetProcessHeap(), 0, CharBuff);
#endif

    UpdateCursorPosition();

    return TRUE;
}