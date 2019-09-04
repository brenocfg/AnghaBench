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
struct TYPE_4__ {int style; int cbWndExtra; int /*<<< orphan*/  lpszClassName; scalar_t__ hbrBackground; int /*<<< orphan*/  hCursor; scalar_t__ cbClsExtra; int /*<<< orphan*/  lpfnWndProc; } ;
typedef  TYPE_1__ WNDCLASSA ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  scalar_t__ HBRUSH ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ COLOR_WINDOW ; 
 int CS_DBLCLKS ; 
 int CS_GLOBALCLASS ; 
 int CS_HREDRAW ; 
 int CS_VREDRAW ; 
 scalar_t__ IDC_ARROW ; 
 int /*<<< orphan*/  LoadCursorA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RICHEDIT_CLASS10A ; 
 int /*<<< orphan*/  RegisterClassA (TYPE_1__*) ; 
 int /*<<< orphan*/  RichEdit10ANSIWndProc ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 

__attribute__((used)) static BOOL RICHED32_Register(void)
{
    WNDCLASSA wndClass;

    ZeroMemory(&wndClass, sizeof(WNDCLASSA));
    wndClass.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS;
    wndClass.lpfnWndProc = RichEdit10ANSIWndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = sizeof(void *);
    wndClass.hCursor = LoadCursorA(0, (LPSTR)IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wndClass.lpszClassName = RICHEDIT_CLASS10A; /* WC_RICHED32A; */

    RegisterClassA(&wndClass);

    return TRUE;
}