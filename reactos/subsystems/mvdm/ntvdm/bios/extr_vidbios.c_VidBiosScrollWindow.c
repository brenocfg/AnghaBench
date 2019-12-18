#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
struct TYPE_5__ {int VideoPageSize; int VideoMode; int ScreenColumns; int ScreenRows; } ;
struct TYPE_4__ {scalar_t__ Left; scalar_t__ Right; scalar_t__ Top; scalar_t__ Bottom; } ;
typedef  TYPE_1__ SMALL_RECT ;
typedef  int SCROLL_DIRECTION ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int INT ;
typedef  int /*<<< orphan*/  FillCharacter ;
typedef  scalar_t__ DWORD ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 TYPE_3__* Bda ; 
 int /*<<< orphan*/  DPRINT1 (char*,int) ; 
 int /*<<< orphan*/  EmulatorContext ; 
 int /*<<< orphan*/  EmulatorCopyMemory (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  EmulatorWriteMemory (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MAKEWORD (char,int) ; 
#define  SCROLL_DOWN 131 
#define  SCROLL_LEFT 130 
#define  SCROLL_RIGHT 129 
#define  SCROLL_UP 128 
 int /*<<< orphan*/  TEXT_VIDEO_SEG ; 
 scalar_t__ TO_LINEAR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  max (scalar_t__,int /*<<< orphan*/ ) ; 
 void* min (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOLEAN VidBiosScrollWindow(SCROLL_DIRECTION Direction,
                                   DWORD Amount,
                                   SMALL_RECT Rectangle,
                                   BYTE Page,
                                   BYTE FillAttribute)
{
    INT i, j;
    DWORD VideoAddress = TO_LINEAR(TEXT_VIDEO_SEG, Page * Bda->VideoPageSize);
    WORD FillCharacter = MAKEWORD(' ', FillAttribute);

    WORD WindowWidth, WindowHeight;

    /* TODO: This function doesn't work in non-alphanumeric modes yet */
    if (Bda->VideoMode > 3)
    {
        DPRINT1("VidBiosScrollWindow: not implemented for mode 0%Xh\n", Bda->VideoMode);
        return FALSE;
    }

    /* Fixup the rectangle if needed */
    Rectangle.Left   = min(max(Rectangle.Left  , 0), Bda->ScreenColumns - 1);
    Rectangle.Right  = min(max(Rectangle.Right , 0), Bda->ScreenColumns - 1);
    Rectangle.Top    = min(max(Rectangle.Top   , 0), Bda->ScreenRows);
    Rectangle.Bottom = min(max(Rectangle.Bottom, 0), Bda->ScreenRows);

    WindowWidth  = Rectangle.Right  - Rectangle.Left + 1;
    WindowHeight = Rectangle.Bottom - Rectangle.Top  + 1;

    /* Amount == 0 means we clear all the rectangle */
    if ((Amount == 0) ||
        (((Direction == SCROLL_UP  ) || (Direction == SCROLL_DOWN )) && (Amount >= WindowHeight)) ||
        (((Direction == SCROLL_LEFT) || (Direction == SCROLL_RIGHT)) && (Amount >= WindowWidth )))
    {
        /* Fill the rectangle */
        for (i = Rectangle.Top; i <= Rectangle.Bottom; i++)
        {
            for (j = Rectangle.Left; j <= Rectangle.Right; j++)
            {
                EmulatorWriteMemory(&EmulatorContext,
                                    VideoAddress + (i * Bda->ScreenColumns + j) * sizeof(WORD),
                                    (LPVOID)&FillCharacter,
                                    sizeof(FillCharacter));
            }
        }

        return TRUE;
    }

    switch (Direction)
    {
        case SCROLL_UP:
        {
            /* Move text lines up */
            for (i = Rectangle.Top + Amount; i <= Rectangle.Bottom; i++)
            {
                EmulatorCopyMemory(&EmulatorContext,
                                   VideoAddress + ((i - Amount) * Bda->ScreenColumns + Rectangle.Left) * sizeof(WORD),
                                   VideoAddress + ( i           * Bda->ScreenColumns + Rectangle.Left) * sizeof(WORD),
                                   (Rectangle.Right - Rectangle.Left + 1) * sizeof(WORD));
            }

            /* Fill the bottom of the rectangle */
            for (i = Rectangle.Bottom - Amount + 1; i <= Rectangle.Bottom; i++)
            {
                for (j = Rectangle.Left; j <= Rectangle.Right; j++)
                {
                    EmulatorWriteMemory(&EmulatorContext,
                                        VideoAddress + (i * Bda->ScreenColumns + j) * sizeof(WORD),
                                        (LPVOID)&FillCharacter,
                                        sizeof(FillCharacter));
                }
            }

            break;
        }

        case SCROLL_DOWN:
        {
            INT Bottom;

            /* Move text lines down */
            for (i = Rectangle.Bottom - Amount; i >= Rectangle.Top; i--)
            {
                EmulatorCopyMemory(&EmulatorContext,
                                   VideoAddress + ((i + Amount) * Bda->ScreenColumns + Rectangle.Left) * sizeof(WORD),
                                   VideoAddress + ( i           * Bda->ScreenColumns + Rectangle.Left) * sizeof(WORD),
                                   (Rectangle.Right - Rectangle.Left + 1) * sizeof(WORD));
            }

            /* Fill the top of the rectangle */
            Bottom = Rectangle.Top + Amount - 1;
            for (i = Rectangle.Top; i <= Bottom; i++)
            {
                for (j = Rectangle.Left; j <= Rectangle.Right; j++)
                {
                    EmulatorWriteMemory(&EmulatorContext,
                                        VideoAddress + (i * Bda->ScreenColumns + j) * sizeof(WORD),
                                        (LPVOID)&FillCharacter,
                                        sizeof(FillCharacter));
                }
            }

            break;
        }

        case SCROLL_LEFT:
        {
            /* Move text lines left */
            for (i = Rectangle.Top; i <= Rectangle.Bottom; i++)
            {
                EmulatorCopyMemory(&EmulatorContext,
                                   VideoAddress + (i * Bda->ScreenColumns + Rectangle.Left         ) * sizeof(WORD),
                                   VideoAddress + (i * Bda->ScreenColumns + Rectangle.Left + Amount) * sizeof(WORD),
                                   (Rectangle.Right - Rectangle.Left - Amount + 1) * sizeof(WORD));
            }

            /* Fill the right of the rectangle */
            for (i = Rectangle.Top; i <= Rectangle.Bottom; i++)
            {
                for (j = Rectangle.Right - Amount + 1; j <= Rectangle.Right; j++)
                {
                    EmulatorWriteMemory(&EmulatorContext,
                                        VideoAddress + (i * Bda->ScreenColumns + j) * sizeof(WORD),
                                        (LPVOID)&FillCharacter,
                                        sizeof(FillCharacter));
                }
            }

            break;
        }

        case SCROLL_RIGHT:
        {
            INT Right;

            /* Move text lines right */
            for (i = Rectangle.Top; i <= Rectangle.Bottom; i++)
            {
                EmulatorCopyMemory(&EmulatorContext,
                                   VideoAddress + (i * Bda->ScreenColumns + Rectangle.Left + Amount) * sizeof(WORD),
                                   VideoAddress + (i * Bda->ScreenColumns + Rectangle.Left         ) * sizeof(WORD),
                                   (Rectangle.Right - Rectangle.Left - Amount + 1) * sizeof(WORD));
            }

            /* Fill the left of the rectangle */
            Right = Rectangle.Left + Amount - 1;
            for (i = Rectangle.Top; i <= Rectangle.Bottom; i++)
            {
                for (j = Rectangle.Left; j <= Right; j++)
                {
                    EmulatorWriteMemory(&EmulatorContext,
                                        VideoAddress + (i * Bda->ScreenColumns + j) * sizeof(WORD),
                                        (LPVOID)&FillCharacter,
                                        sizeof(FillCharacter));
                }
            }

            break;
        }
    }

    return TRUE;
}