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
typedef  int uchar_t ;
typedef  int processorid_t ;

/* Variables and functions */
 int ENA_FMT1_CPUID_MASK ; 
 int ENA_FMT1_CPUID_SHFT ; 
 int ENA_FMT1_TIME_MASK ; 
 int ENA_FMT1_TIME_SHFT ; 
 int ENA_FMT2_TIME_MASK ; 
 int ENA_FMT2_TIME_SHFT ; 
 int ENA_FORMAT_MASK ; 
#define  FM_ENA_FMT1 129 
#define  FM_ENA_FMT2 128 
 int gethrtime () ; 

uint64_t
fm_ena_generate_cpu(uint64_t timestamp, processorid_t cpuid, uchar_t format)
{
	uint64_t ena = 0;

	switch (format) {
	case FM_ENA_FMT1:
		if (timestamp) {
			ena = (uint64_t)((format & ENA_FORMAT_MASK) |
			    ((cpuid << ENA_FMT1_CPUID_SHFT) &
			    ENA_FMT1_CPUID_MASK) |
			    ((timestamp << ENA_FMT1_TIME_SHFT) &
			    ENA_FMT1_TIME_MASK));
		} else {
			ena = (uint64_t)((format & ENA_FORMAT_MASK) |
			    ((cpuid << ENA_FMT1_CPUID_SHFT) &
			    ENA_FMT1_CPUID_MASK) |
			    ((gethrtime() << ENA_FMT1_TIME_SHFT) &
			    ENA_FMT1_TIME_MASK));
		}
		break;
	case FM_ENA_FMT2:
		ena = (uint64_t)((format & ENA_FORMAT_MASK) |
		    ((timestamp << ENA_FMT2_TIME_SHFT) & ENA_FMT2_TIME_MASK));
		break;
	default:
		break;
	}

	return (ena);
}