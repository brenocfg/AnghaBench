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
typedef  int /*<<< orphan*/  VOID ;
typedef  int UINT_PTR ;
struct TYPE_3__ {int Transparancy; int /*<<< orphan*/  hSelf; int /*<<< orphan*/  bOpaque; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  TYPE_1__* PFLT_WND ;
typedef  int LONG_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GWL_EXSTYLE ; 
 int /*<<< orphan*/  GetCursorPos (int /*<<< orphan*/ *) ; 
 int GetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  ID_TIMER1 130 
#define  ID_TIMER2 129 
#define  ID_TIMER3 128 
 int /*<<< orphan*/  KillTimer (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  LWA_ALPHA ; 
 int /*<<< orphan*/  PtInRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLayeredWindowAttributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTimer (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int WS_EX_LAYERED ; 

__attribute__((used)) static VOID
DoTimer(PFLT_WND FltInfo,
        UINT_PTR idTimer)
{
    switch (idTimer)
    {
        /* timer to check if cursor is in toolbar coords */
        case ID_TIMER1:
        {
            POINT pt;

            /* kill timer if toobar is not opaque */
            if (FltInfo->bOpaque != TRUE)
            {
                KillTimer(FltInfo->hSelf,
                          ID_TIMER1);
                break;
            }

            if (GetCursorPos(&pt))
            {
                RECT rect;

                if (GetWindowRect(FltInfo->hSelf,
                                  &rect))
                {
                    if (!PtInRect(&rect,
                                  pt))
                    {
                        KillTimer(FltInfo->hSelf,
                                  ID_TIMER1);
                        KillTimer(FltInfo->hSelf,
                                  ID_TIMER2);

                        /* timer to fade out toolbar */
                        SetTimer(FltInfo->hSelf,
                                 ID_TIMER3,
                                 50,
                                 NULL);
                    }
                }
            }
        }
        break;

        /* timer to fade in toolbar */
        case ID_TIMER2:
        {
            SetLayeredWindowAttributes(FltInfo->hSelf,
                                       0,
                                       (255 * FltInfo->Transparancy) / 100,
                                       LWA_ALPHA);

            /* increment transparancy until it is opaque (100) */
            FltInfo->Transparancy += 5;

            if (FltInfo->Transparancy == 100)
            {
                SetWindowLongPtr(FltInfo->hSelf,
                                 GWL_EXSTYLE,
                                 GetWindowLongPtr(FltInfo->hSelf,
                                                  GWL_EXSTYLE) & ~WS_EX_LAYERED);

                FltInfo->bOpaque = TRUE;

                KillTimer(FltInfo->hSelf,
                          ID_TIMER2);
            }
        }
        break;

        case ID_TIMER3:
        {
            LONG_PTR Style;

            Style = GetWindowLongPtr(FltInfo->hSelf,
                                     GWL_EXSTYLE);

            if (Style & ~WS_EX_LAYERED)
            {
                SetWindowLongPtr(FltInfo->hSelf,
                                 GWL_EXSTYLE,
                                 Style | WS_EX_LAYERED);
            }

            FltInfo->Transparancy -= 5;

            if (FltInfo->Transparancy >= 60)
            {
                /* set the tranclucency to 60% */
                SetLayeredWindowAttributes(FltInfo->hSelf,
                                           0,
                                           (255 * FltInfo->Transparancy) / 100,
                                           LWA_ALPHA);

                if (FltInfo->Transparancy == 60)
                {
                    FltInfo->bOpaque = FALSE;

                    KillTimer(FltInfo->hSelf,
                              ID_TIMER3);
                }

            }
        }
        break;
    }
}