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
typedef  size_t USHORT ;
typedef  int /*<<< orphan*/ * PEMS_HANDLE ;

/* Variables and functions */
 size_t ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EmsHandleTable ; 

__attribute__((used)) static inline PEMS_HANDLE GetEmsHandleRecord(USHORT Handle)
{
    if (Handle >= ARRAYSIZE(EmsHandleTable)) return NULL;
    return &EmsHandleTable[Handle];
}