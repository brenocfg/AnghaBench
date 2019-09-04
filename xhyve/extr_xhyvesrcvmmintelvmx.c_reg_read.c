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
typedef  int /*<<< orphan*/  hv_x86_reg_t ;
typedef  int /*<<< orphan*/  hv_vcpuid_t ;

/* Variables and functions */
 int /*<<< orphan*/  hv_vcpu_read_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline uint64_t
reg_read(int vcpuid, hv_x86_reg_t reg) {
	uint64_t val;

	hv_vcpu_read_register(((hv_vcpuid_t) vcpuid), reg, &val);
	return val;
}