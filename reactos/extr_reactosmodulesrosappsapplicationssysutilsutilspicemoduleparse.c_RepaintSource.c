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
struct TYPE_4__ {scalar_t__ Count; } ;
typedef  TYPE_1__ ARGS ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  PICE_memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Unassemble (TYPE_1__*) ; 
 scalar_t__ ulLastDisassEndAddress ; 
 scalar_t__ ulLastDisassStartAddress ; 

void RepaintSource(void)
{
    ARGS Args;

    ENTER_FUNC();

    // disassembly from current address
    PICE_memset(&Args,0,sizeof(ARGS));
    // make unassembler refresh all again
    ulLastDisassStartAddress=ulLastDisassEndAddress=0;
	Args.Count=0;
	Unassemble(&Args);

    LEAVE_FUNC();
}