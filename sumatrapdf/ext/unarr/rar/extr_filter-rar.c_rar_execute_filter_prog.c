#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct RARFilter {scalar_t__ globaldatalen; int /*<<< orphan*/ * globaldata; TYPE_1__* prog; int /*<<< orphan*/  initialregisters; } ;
struct TYPE_8__ {int /*<<< orphan*/ * memory; } ;
struct TYPE_7__ {scalar_t__ staticdatalen; int /*<<< orphan*/  prog; int /*<<< orphan*/ * staticdata; } ;
typedef  TYPE_2__ RARVirtualMachine ;

/* Variables and functions */
 int /*<<< orphan*/  RARExecuteProgram (TYPE_2__*,int /*<<< orphan*/ ) ; 
 size_t RARProgramSystemGlobalAddress ; 
 scalar_t__ RARProgramSystemGlobalSize ; 
 size_t RARProgramUserGlobalAddress ; 
 scalar_t__ RARProgramUserGlobalSize ; 
 int /*<<< orphan*/  RARSetVirtualMachineRegisters (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ RARVirtualMachineRead32 (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static bool rar_execute_filter_prog(struct RARFilter *filter, RARVirtualMachine *vm)
{
    uint32_t newgloballength;
    uint32_t globallength = filter->globaldatalen;
    if (globallength > RARProgramSystemGlobalSize)
        globallength = RARProgramSystemGlobalSize;
    memcpy(&vm->memory[RARProgramSystemGlobalAddress], filter->globaldata, globallength);
    if (filter->prog->staticdata) {
        uint32_t staticlength = filter->prog->staticdatalen;
        if (staticlength > RARProgramUserGlobalSize - globallength)
            staticlength = RARProgramUserGlobalSize - globallength;
        memcpy(&vm->memory[RARProgramUserGlobalAddress], filter->prog->staticdata, staticlength);
    }
    RARSetVirtualMachineRegisters(vm, filter->initialregisters);

    if (!RARExecuteProgram(vm, filter->prog->prog)) {
        warn("Error while executing program in RAR VM");
        return false;
    }

    newgloballength = RARVirtualMachineRead32(vm, RARProgramSystemGlobalAddress + 0x30);
    if (newgloballength > RARProgramUserGlobalSize)
        newgloballength = RARProgramUserGlobalSize;
    if (newgloballength > 0) {
        uint32_t newglobaldatalength = RARProgramSystemGlobalSize + newgloballength;
        if (newglobaldatalength > filter->globaldatalen) {
            uint8_t *newglobaldata = malloc(newglobaldatalength);
            if (!newglobaldata)
                return false;
            free(filter->globaldata);
            filter->globaldata = newglobaldata;
        }
        filter->globaldatalen = newglobaldatalength;
        memcpy(filter->globaldata, &vm->memory[RARProgramSystemGlobalAddress], filter->globaldatalen);
    }
    else
        filter->globaldatalen = 0;

    return true;
}