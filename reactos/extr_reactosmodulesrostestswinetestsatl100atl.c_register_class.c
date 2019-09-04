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
struct TYPE_3__ {char* lpszClassName; int /*<<< orphan*/ * lpszMenuName; scalar_t__ hbrBackground; int /*<<< orphan*/  hCursor; int /*<<< orphan*/ * hIcon; int /*<<< orphan*/  hInstance; scalar_t__ cbWndExtra; scalar_t__ cbClsExtra; int /*<<< orphan*/  lpfnWndProc; scalar_t__ style; } ;
typedef  TYPE_1__ WNDCLASSA ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  scalar_t__ HBRUSH ;
typedef  int /*<<< orphan*/  ATOM ;

/* Variables and functions */
 scalar_t__ COLOR_BTNFACE ; 
 int /*<<< orphan*/  DefWindowProcA ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 scalar_t__ IDC_ARROW ; 
 int /*<<< orphan*/  LoadCursorA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegisterClassA (TYPE_1__*) ; 

__attribute__((used)) static ATOM register_class(void)
{
    WNDCLASSA wndclassA;

    wndclassA.style = 0;
    wndclassA.lpfnWndProc = DefWindowProcA;
    wndclassA.cbClsExtra = 0;
    wndclassA.cbWndExtra = 0;
    wndclassA.hInstance = GetModuleHandleA(NULL);
    wndclassA.hIcon = NULL;
    wndclassA.hCursor = LoadCursorA(NULL, (LPSTR)IDC_ARROW);
    wndclassA.hbrBackground = (HBRUSH)(COLOR_BTNFACE+1);
    wndclassA.lpszMenuName = NULL;
    wndclassA.lpszClassName = "WineAtlTestClass";

    return RegisterClassA(&wndclassA);
}