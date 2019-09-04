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
typedef  int /*<<< orphan*/  buf ;
typedef  char WCHAR ;
typedef  size_t UINT ;
struct TYPE_2__ {size_t uDevType; scalar_t__ lpTable; } ;
typedef  char const* LPCWSTR ;
typedef  scalar_t__ HRSRC ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 scalar_t__ FindResourceW (int /*<<< orphan*/ ,char const*,char const*) ; 
 scalar_t__ LoadResource (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LoadStringW (int /*<<< orphan*/ ,size_t,char*,int) ; 
 size_t MAX_MCICMDTABLE ; 
 size_t MCI_DEVTYPE_FIRST ; 
 size_t MCI_DEVTYPE_LAST ; 
 size_t MCI_NO_COMMAND_TABLE ; 
 size_t MCI_SetCommandTable (scalar_t__,size_t) ; 
 scalar_t__ RT_RCDATA ; 
 TYPE_1__* S_MciCmdTable ; 
 int /*<<< orphan*/  TRACE (char*,size_t) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (char const*) ; 
 int /*<<< orphan*/  hWinMM32Instance ; 

__attribute__((used)) static	UINT		MCI_GetCommandTable(UINT uDevType)
{
    UINT	uTbl;
    WCHAR	buf[32];
    LPCWSTR	str = NULL;

    /* first look up existing for existing devType */
    for (uTbl = 0; uTbl < MAX_MCICMDTABLE; uTbl++) {
	if (S_MciCmdTable[uTbl].lpTable && S_MciCmdTable[uTbl].uDevType == uDevType)
	    return uTbl;
    }

    /* well try to load id */
    if (uDevType >= MCI_DEVTYPE_FIRST && uDevType <= MCI_DEVTYPE_LAST) {
	if (LoadStringW(hWinMM32Instance, uDevType, buf, sizeof(buf) / sizeof(WCHAR))) {
	    str = buf;
	}
    } else if (uDevType == 0) {
        static const WCHAR wszCore[] = {'C','O','R','E',0};
	str = wszCore;
    }
    uTbl = MCI_NO_COMMAND_TABLE;
    if (str) {
	HRSRC 	hRsrc = FindResourceW(hWinMM32Instance, str, (LPCWSTR)RT_RCDATA);
	HANDLE	hMem = 0;

	if (hRsrc) hMem = LoadResource(hWinMM32Instance, hRsrc);
	if (hMem) {
	    uTbl = MCI_SetCommandTable(hMem, uDevType);
	} else {
	    WARN("No command table found in resource %p[%s]\n",
		 hWinMM32Instance, debugstr_w(str));
	}
    }
    TRACE("=> %d\n", uTbl);
    return uTbl;
}