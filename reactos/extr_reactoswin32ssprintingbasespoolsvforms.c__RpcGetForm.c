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
typedef  int /*<<< orphan*/  WINSPOOL_PRINTER_HANDLE ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_FUNCTION ; 
 int /*<<< orphan*/  UNIMPLEMENTED ; 

DWORD
_RpcGetForm(WINSPOOL_PRINTER_HANDLE hPrinter, WCHAR* pFormName, DWORD Level, BYTE* pForm, DWORD cbBuf, DWORD* pcbNeeded)
{
    UNIMPLEMENTED;
    return ERROR_INVALID_FUNCTION;
}