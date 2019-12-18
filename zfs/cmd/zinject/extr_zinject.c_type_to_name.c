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
#define  DMU_OT_BPOBJ 133 
#define  DMU_OT_ERROR_LOG 132 
#define  DMU_OT_OBJECT_ARRAY 131 
#define  DMU_OT_OBJECT_DIRECTORY 130 
#define  DMU_OT_PACKED_NVLIST 129 
#define  DMU_OT_SPACE_MAP 128 

__attribute__((used)) static const char *
type_to_name(uint64_t type)
{
	switch (type) {
	case DMU_OT_OBJECT_DIRECTORY:
		return ("mosdir");
	case DMU_OT_OBJECT_ARRAY:
		return ("metaslab");
	case DMU_OT_PACKED_NVLIST:
		return ("config");
	case DMU_OT_BPOBJ:
		return ("bpobj");
	case DMU_OT_SPACE_MAP:
		return ("spacemap");
	case DMU_OT_ERROR_LOG:
		return ("errlog");
	default:
		return ("-");
	}
}