#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct RARFilter {int* initialregisters; int filteredblockaddress; int filteredblocklength; } ;
struct TYPE_3__ {scalar_t__* memory; } ;
typedef  TYPE_1__ RARVirtualMachine ;

/* Variables and functions */
 int RARProgramWorkSize ; 

__attribute__((used)) static bool rar_execute_filter_delta(struct RARFilter *filter, RARVirtualMachine *vm)
{
    uint32_t length = filter->initialregisters[4];
    uint32_t numchannels = filter->initialregisters[0];
    uint8_t *src, *dst;
    uint32_t i, idx;

    if (length > RARProgramWorkSize / 2)
        return false;

    src = &vm->memory[0];
    dst = &vm->memory[length];
    for (i = 0; i < numchannels; i++) {
        uint8_t lastbyte = 0;
        for (idx = i; idx < length; idx += numchannels)
            lastbyte = dst[idx] = lastbyte - *src++;
    }

    filter->filteredblockaddress = length;
    filter->filteredblocklength = length;

    return true;
}