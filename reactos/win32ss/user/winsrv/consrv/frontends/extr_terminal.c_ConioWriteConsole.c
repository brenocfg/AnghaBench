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

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_22__ {int UnicodeChar; } ;
struct TYPE_28__ {int /*<<< orphan*/  Attributes; TYPE_3__ Char; } ;
struct TYPE_27__ {scalar_t__ ActiveBuffer; } ;
struct TYPE_26__ {TYPE_1__* Vtbl; TYPE_8__* Console; } ;
struct TYPE_23__ {scalar_t__ X; scalar_t__ Y; } ;
struct TYPE_21__ {size_t X; } ;
struct TYPE_25__ {int Mode; TYPE_4__ CursorPosition; TYPE_2__ ScreenBufferSize; int /*<<< orphan*/  ScreenDefaultAttrib; } ;
struct TYPE_24__ {size_t Left; size_t Top; int Right; size_t Bottom; } ;
struct TYPE_20__ {int /*<<< orphan*/  (* WriteStream ) (TYPE_7__*,TYPE_5__*,scalar_t__,scalar_t__,size_t,int*,size_t) ;int /*<<< orphan*/  (* RingBell ) (TYPE_7__*) ;} ;
typedef  TYPE_5__ SMALL_RECT ;
typedef  scalar_t__ SHORT ;
typedef  int* PWCHAR ;
typedef  TYPE_6__* PTEXTMODE_SCREEN_BUFFER ;
typedef  TYPE_7__* PFRONTEND ;
typedef  TYPE_8__* PCONSRV_CONSOLE ;
typedef  scalar_t__ PCONSOLE_SCREEN_BUFFER ;
typedef  TYPE_9__* PCHAR_INFO ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  size_t DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 TYPE_9__* ConioCoordToPointer (TYPE_6__*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  ConioIsRectEmpty (TYPE_5__*) ; 
 int /*<<< orphan*/  ConioNextLine (TYPE_6__*,TYPE_5__*,size_t*) ; 
 int ENABLE_PROCESSED_OUTPUT ; 
 int ENABLE_WRAP_AT_EOL_OUTPUT ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int TAB_WIDTH ; 
 void* max (int,size_t) ; 
 void* min (size_t,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_7__*,TYPE_5__*,scalar_t__,scalar_t__,size_t,int*,size_t) ; 

__attribute__((used)) static NTSTATUS
ConioWriteConsole(PFRONTEND FrontEnd,
                  PTEXTMODE_SCREEN_BUFFER Buff,
                  PWCHAR Buffer,
                  DWORD Length,
                  BOOL Attrib)
{
    PCONSRV_CONSOLE Console = FrontEnd->Console;

    UINT i;
    PCHAR_INFO Ptr;
    SMALL_RECT UpdateRect;
    SHORT CursorStartX, CursorStartY;
    UINT ScrolledLines;

    CursorStartX = Buff->CursorPosition.X;
    CursorStartY = Buff->CursorPosition.Y;
    UpdateRect.Left = Buff->ScreenBufferSize.X;
    UpdateRect.Top = Buff->CursorPosition.Y;
    UpdateRect.Right = -1;
    UpdateRect.Bottom = Buff->CursorPosition.Y;
    ScrolledLines = 0;

    for (i = 0; i < Length; i++)
    {
        /*
         * If we are in processed mode, interpret special characters and
         * display them correctly. Otherwise, just put them into the buffer.
         */
        if (Buff->Mode & ENABLE_PROCESSED_OUTPUT)
        {
            /* --- CR --- */
            if (Buffer[i] == L'\r')
            {
                Buff->CursorPosition.X = 0;
                UpdateRect.Left = min(UpdateRect.Left, Buff->CursorPosition.X);
                UpdateRect.Right = max(UpdateRect.Right, Buff->CursorPosition.X);
                continue;
            }
            /* --- LF --- */
            else if (Buffer[i] == L'\n')
            {
                Buff->CursorPosition.X = 0;
                ConioNextLine(Buff, &UpdateRect, &ScrolledLines);
                continue;
            }
            /* --- BS --- */
            else if (Buffer[i] == L'\b')
            {
                /* Only handle BS if we're not on the first pos of the first line */
                if (0 != Buff->CursorPosition.X || 0 != Buff->CursorPosition.Y)
                {
                    if (0 == Buff->CursorPosition.X)
                    {
                        /* slide virtual position up */
                        Buff->CursorPosition.X = Buff->ScreenBufferSize.X - 1;
                        Buff->CursorPosition.Y--;
                        UpdateRect.Top = min(UpdateRect.Top, Buff->CursorPosition.Y);
                    }
                    else
                    {
                        Buff->CursorPosition.X--;
                    }
                    Ptr = ConioCoordToPointer(Buff, Buff->CursorPosition.X, Buff->CursorPosition.Y);
                    Ptr->Char.UnicodeChar = L' ';
                    Ptr->Attributes  = Buff->ScreenDefaultAttrib;
                    UpdateRect.Left  = min(UpdateRect.Left, Buff->CursorPosition.X);
                    UpdateRect.Right = max(UpdateRect.Right, Buff->CursorPosition.X);
                }
                continue;
            }
            /* --- TAB --- */
            else if (Buffer[i] == L'\t')
            {
                UINT EndX;

                UpdateRect.Left = min(UpdateRect.Left, Buff->CursorPosition.X);
                EndX = (Buff->CursorPosition.X + TAB_WIDTH) & ~(TAB_WIDTH - 1);
                EndX = min(EndX, (UINT)Buff->ScreenBufferSize.X);
                Ptr = ConioCoordToPointer(Buff, Buff->CursorPosition.X, Buff->CursorPosition.Y);
                while ((UINT)Buff->CursorPosition.X < EndX)
                {
                    Ptr->Char.UnicodeChar = L' ';
                    Ptr->Attributes = Buff->ScreenDefaultAttrib;
                    ++Ptr;
                    Buff->CursorPosition.X++;
                }
                UpdateRect.Right = max(UpdateRect.Right, Buff->CursorPosition.X - 1);
                if (Buff->CursorPosition.X == Buff->ScreenBufferSize.X)
                {
                    if (Buff->Mode & ENABLE_WRAP_AT_EOL_OUTPUT)
                    {
                        Buff->CursorPosition.X = 0;
                        ConioNextLine(Buff, &UpdateRect, &ScrolledLines);
                    }
                    else
                    {
                        Buff->CursorPosition.X--;
                    }
                }
                continue;
            }
            /* --- BEL ---*/
            else if (Buffer[i] == L'\a')
            {
                FrontEnd->Vtbl->RingBell(FrontEnd);
                continue;
            }
        }
        UpdateRect.Left  = min(UpdateRect.Left, Buff->CursorPosition.X);
        UpdateRect.Right = max(UpdateRect.Right, Buff->CursorPosition.X);

        Ptr = ConioCoordToPointer(Buff, Buff->CursorPosition.X, Buff->CursorPosition.Y);
        Ptr->Char.UnicodeChar = Buffer[i];
        if (Attrib) Ptr->Attributes = Buff->ScreenDefaultAttrib;

        Buff->CursorPosition.X++;
        if (Buff->CursorPosition.X == Buff->ScreenBufferSize.X)
        {
            if (Buff->Mode & ENABLE_WRAP_AT_EOL_OUTPUT)
            {
                Buff->CursorPosition.X = 0;
                ConioNextLine(Buff, &UpdateRect, &ScrolledLines);
            }
            else
            {
                Buff->CursorPosition.X = CursorStartX;
            }
        }
    }

    if (!ConioIsRectEmpty(&UpdateRect) && (PCONSOLE_SCREEN_BUFFER)Buff == Console->ActiveBuffer)
    {
        // TermWriteStream(Console, &UpdateRect, CursorStartX, CursorStartY,
                        // ScrolledLines, Buffer, Length);
        FrontEnd->Vtbl->WriteStream(FrontEnd,
                                    &UpdateRect,
                                    CursorStartX,
                                    CursorStartY,
                                    ScrolledLines,
                                    Buffer,
                                    Length);
    }

    return STATUS_SUCCESS;
}