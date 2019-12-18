#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int SizeOfStruct; scalar_t__ SymType; char CVSig; } ;
typedef  int /*<<< orphan*/  ModuleInfo ;
typedef  TYPE_1__ IMAGEHLP_MODULE64 ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD64 ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ SymDia ; 
 int SymGetModuleInfo64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOL supports_rsym(HANDLE hProc, DWORD64 BaseAddress)
{
    IMAGEHLP_MODULE64 ModuleInfo;
    BOOL Ret;

    memset(&ModuleInfo, 0, sizeof(ModuleInfo));
    ModuleInfo.SizeOfStruct = sizeof(ModuleInfo);
    Ret = SymGetModuleInfo64(hProc, BaseAddress, &ModuleInfo);

    return Ret &&
        ModuleInfo.SymType == SymDia &&
        ModuleInfo.CVSig == ('R' | ('S' << 8) | ('Y' << 16) | ('M' << 24));
}