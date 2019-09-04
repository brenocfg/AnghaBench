#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* bSmoothShading; void* bEnableFiltering; void* bFinePerspective; void* bDoBlending; void* uiRotation; void* uiSpeed; void* uiNumStars; } ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  BM_GETCHECK ; 
 int /*<<< orphan*/  CB_GETCURSEL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IDC_CHECK_DOBLENDING ; 
 int /*<<< orphan*/  IDC_CHECK_FILTERING ; 
 int /*<<< orphan*/  IDC_CHECK_PERSPECTIVE ; 
 int /*<<< orphan*/  IDC_CHECK_SHADING ; 
 int /*<<< orphan*/  IDC_COMBO_ROTATION ; 
 int /*<<< orphan*/  IDC_SLIDER_NUM_OF_STARS ; 
 int /*<<< orphan*/  IDC_SLIDER_SPEED ; 
 int /*<<< orphan*/  IDC_TEXT_NUM_OF_STARS ; 
 int /*<<< orphan*/  IDC_TEXT_SPEED ; 
 void* SendDlgItemMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDlgItemInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 TYPE_1__ Settings ; 
 int /*<<< orphan*/  TBM_GETPOS ; 

__attribute__((used)) static void ReadSettings(HWND hWnd)
{
    Settings.uiNumStars = SendDlgItemMessage(hWnd, IDC_SLIDER_NUM_OF_STARS, TBM_GETPOS, 0, 0);
    SetDlgItemInt(hWnd, IDC_TEXT_NUM_OF_STARS, Settings.uiNumStars, FALSE);

    Settings.uiSpeed = SendDlgItemMessage(hWnd, IDC_SLIDER_SPEED, TBM_GETPOS, 0, 0);
    SetDlgItemInt(hWnd, IDC_TEXT_SPEED, Settings.uiSpeed, FALSE);

    Settings.uiRotation = SendDlgItemMessage(hWnd, IDC_COMBO_ROTATION, CB_GETCURSEL, 0, 0);

    Settings.bDoBlending      = SendDlgItemMessage(hWnd, IDC_CHECK_DOBLENDING,  BM_GETCHECK, 0, 0);
    Settings.bFinePerspective = SendDlgItemMessage(hWnd, IDC_CHECK_PERSPECTIVE, BM_GETCHECK, 0, 0);
    Settings.bEnableFiltering = SendDlgItemMessage(hWnd, IDC_CHECK_FILTERING,   BM_GETCHECK, 0, 0);
    Settings.bSmoothShading   = SendDlgItemMessage(hWnd, IDC_CHECK_SHADING,     BM_GETCHECK, 0, 0);
}