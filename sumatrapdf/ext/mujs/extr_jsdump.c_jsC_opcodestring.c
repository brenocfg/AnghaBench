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
typedef  enum js_OpCode { ____Placeholder_js_OpCode } js_OpCode ;

/* Variables and functions */
 int nelem (char const**) ; 
 char const** opname ; 

const char *jsC_opcodestring(enum js_OpCode opcode)
{
	if (opcode < nelem(opname)-1)
		return opname[opcode];
	return "<unknown>";
}