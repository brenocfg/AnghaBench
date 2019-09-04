#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pagesetup_data ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  COMDLG32_hInstance ; 
 scalar_t__ LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PD32_MARGINS_IN_INCHES ; 
 int /*<<< orphan*/  PD32_MARGINS_IN_MILLIMETERS ; 
 int /*<<< orphan*/  SetDlgItemTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  grp4 ; 
 scalar_t__ is_metric (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void set_margin_groupbox_title(HWND hDlg, const pagesetup_data *data)
{
    WCHAR title[256];

    if(LoadStringW(COMDLG32_hInstance, is_metric(data) ? PD32_MARGINS_IN_MILLIMETERS : PD32_MARGINS_IN_INCHES,
                   title, ARRAY_SIZE(title)))
        SetDlgItemTextW(hDlg, grp4, title);
}