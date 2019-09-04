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
typedef  int /*<<< orphan*/  WINSPOOL_SECURITY_CONTAINER ;
typedef  int /*<<< orphan*/  WINSPOOL_PRINTER_HANDLE ;
typedef  int /*<<< orphan*/  WINSPOOL_PRINTER_CONTAINER ;
typedef  int /*<<< orphan*/  WINSPOOL_HANDLE ;
typedef  int /*<<< orphan*/  WINSPOOL_DEVMODE_CONTAINER ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_FUNCTION ; 
 int /*<<< orphan*/  UNIMPLEMENTED ; 

DWORD
_RpcAddPrinter(WINSPOOL_HANDLE pName, WINSPOOL_PRINTER_CONTAINER* pPrinterContainer, WINSPOOL_DEVMODE_CONTAINER* pDevModeContainer, WINSPOOL_SECURITY_CONTAINER* pSecurityContainer, WINSPOOL_PRINTER_HANDLE* pHandle)
{
    UNIMPLEMENTED;
    return ERROR_INVALID_FUNCTION;
}