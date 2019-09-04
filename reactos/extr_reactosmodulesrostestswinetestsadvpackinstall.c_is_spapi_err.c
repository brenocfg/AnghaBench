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
typedef  int const DWORD ;
typedef  int BOOL ;

/* Variables and functions */

__attribute__((used)) static BOOL is_spapi_err(DWORD err)
{
    const DWORD SPAPI_PREFIX = 0x800F0000L;
    const DWORD SPAPI_MASK = 0xFFFF0000L;

    return (((err & SPAPI_MASK) ^ SPAPI_PREFIX) == 0);
}