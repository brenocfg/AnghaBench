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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int read_secpar (void const*) ; 
 int /*<<< orphan*/  uint64_import (void const*,int) ; 

uint64_t FSPRG_GetEpoch(const void *state) {
        uint16_t secpar;
        secpar = read_secpar(state + 0);
        return uint64_import(state + 2 + 2 * secpar / 8, 8);
}