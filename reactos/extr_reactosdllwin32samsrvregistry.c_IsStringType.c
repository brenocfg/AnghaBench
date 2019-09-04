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
typedef  int BOOLEAN ;

/* Variables and functions */
 scalar_t__ REG_EXPAND_SZ ; 
 scalar_t__ REG_MULTI_SZ ; 
 scalar_t__ REG_SZ ; 

__attribute__((used)) static
BOOLEAN
IsStringType(ULONG Type)
{
    return (Type == REG_SZ) || (Type == REG_EXPAND_SZ) || (Type == REG_MULTI_SZ);
}