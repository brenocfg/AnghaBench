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
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ COMBO_ID ; 
 int /*<<< orphan*/  CreateWindowA (char*,char*,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int WS_CHILD ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  hMainWnd ; 

__attribute__((used)) static HWND build_combo(DWORD style)
{
    return CreateWindowA("ComboBox", "Combo", WS_VISIBLE|WS_CHILD|style, 5, 5, 100, 100, hMainWnd, (HMENU)COMBO_ID, NULL, 0);
}