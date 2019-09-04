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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int BUFFER_LEN ; 
 int /*<<< orphan*/  IDS_WINEFILE ; 
 int /*<<< orphan*/  MB_OK ; 
 int /*<<< orphan*/  MessageBoxW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NO_ERROR ; 
 int /*<<< orphan*/  RS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ WNetGetLastErrorW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void display_network_error(HWND hwnd)
{
	WCHAR msg[BUFFER_LEN], provider[BUFFER_LEN], b2[BUFFER_LEN];
	DWORD error;

	if (WNetGetLastErrorW(&error, msg, BUFFER_LEN, provider, BUFFER_LEN) == NO_ERROR)
		MessageBoxW(hwnd, msg, RS(b2,IDS_WINEFILE), MB_OK);
}