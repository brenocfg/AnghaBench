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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VK_CONTROL ; 
 int /*<<< orphan*/  WM_KEYDOWN ; 
 int /*<<< orphan*/  hold_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_key (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT send_ctrl_key(HWND hwnd, UINT key)
{
    LRESULT result;
    hold_key(VK_CONTROL);
    result = SendMessageA(hwnd, WM_KEYDOWN, key, 1);
    release_key(VK_CONTROL);
    return result;
}