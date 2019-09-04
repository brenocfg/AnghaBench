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
typedef  scalar_t__ ULONG ;

/* Variables and functions */
 scalar_t__ EXCEPTION_ACCESS_VIOLATION ; 
 int EXCEPTION_CONTINUE_SEARCH ; 
 int EXCEPTION_EXECUTE_HANDLER ; 
 scalar_t__ EXCEPTION_PRIV_INSTRUCTION ; 

int page_fault(ULONG ExceptionCode)
{
    if (ExceptionCode == EXCEPTION_ACCESS_VIOLATION ||
        ExceptionCode == EXCEPTION_PRIV_INSTRUCTION)
        return EXCEPTION_EXECUTE_HANDLER;
    return EXCEPTION_CONTINUE_SEARCH;
}