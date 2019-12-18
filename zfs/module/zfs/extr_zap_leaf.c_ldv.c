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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CE_PANIC ; 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static uint64_t
ldv(int len, const void *addr)
{
	switch (len) {
	case 1:
		return (*(uint8_t *)addr);
	case 2:
		return (*(uint16_t *)addr);
	case 4:
		return (*(uint32_t *)addr);
	case 8:
		return (*(uint64_t *)addr);
	default:
		cmn_err(CE_PANIC, "bad int len %d", len);
	}
	return (0xFEEDFACEDEADBEEFULL);
}