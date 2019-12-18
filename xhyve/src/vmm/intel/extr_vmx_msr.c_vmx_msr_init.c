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
typedef  int uint64_t ;

/* Variables and functions */
 unsigned int misc_enable ; 
 int platform_info ; 
 scalar_t__ sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int turbo_ratio_limit ; 
 int /*<<< orphan*/  xhyve_abort (char*) ; 

void
vmx_msr_init(void) {
	uint64_t bus_freq, tsc_freq, ratio;
	size_t length;
	int i;
	
	length = sizeof(uint64_t);

	if (sysctlbyname("machdep.tsc.frequency", &tsc_freq, &length, NULL, 0)) {
	  xhyve_abort("machdep.tsc.frequency\n");
	}

	if (sysctlbyname("hw.busfrequency", &bus_freq, &length, NULL, 0)) {
	  xhyve_abort("hw.busfrequency\n");
	}

	/* Initialize emulated MSRs */
	/* FIXME */
	misc_enable = 1;
	/*
	 * Set mandatory bits
	 *  11:   branch trace disabled
	 *  12:   PEBS unavailable
	 * Clear unsupported features
	 *  16:   SpeedStep enable
	 *  18:   enable MONITOR FSM
	 */
	misc_enable |= (1u << 12) | (1u << 11);
	misc_enable &= ~((1u << 18) | (1u << 16));

	/*
	 * XXXtime
	 * The ratio should really be based on the virtual TSC frequency as
	 * opposed to the host TSC.
	 */
	ratio = (tsc_freq / bus_freq) & 0xff;

	/*
	 * The register definition is based on the micro-architecture
	 * but the following bits are always the same:
	 * [15:8]  Maximum Non-Turbo Ratio
	 * [28]    Programmable Ratio Limit for Turbo Mode
	 * [29]    Programmable TDC-TDP Limit for Turbo Mode
	 * [47:40] Maximum Efficiency Ratio
	 *
	 * The other bits can be safely set to 0 on all
	 * micro-architectures up to Haswell.
	 */
	platform_info = (ratio << 8) | (ratio << 40);

	/*
	 * The number of valid bits in the MSR_TURBO_RATIO_LIMITx register is
	 * dependent on the maximum cores per package supported by the micro-
	 * architecture. For e.g., Westmere supports 6 cores per package and
	 * uses the low 48 bits. Sandybridge support 8 cores per package and
	 * uses up all 64 bits.
	 *
	 * However, the unused bits are reserved so we pretend that all bits
	 * in this MSR are valid.
	 */
	for (i = 0; i < 8; i++) {
	  turbo_ratio_limit = (turbo_ratio_limit << 8) | ratio;
	}
}