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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  LPWSTR ;

/* Variables and functions */
 int MB_ICONEXCLAMATION ; 
 int MB_OK ; 
 int /*<<< orphan*/  MessageBoxW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

VOID DisplayMessage(LPWSTR lpMsg)
{
    MessageBoxW(NULL, lpMsg, L"Note!", MB_ICONEXCLAMATION|MB_OK);
}