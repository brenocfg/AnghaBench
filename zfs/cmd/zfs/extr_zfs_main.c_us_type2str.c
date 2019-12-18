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

/* Variables and functions */
#define  USTYPE_PROJ 132 
#define  USTYPE_PSX_GRP 131 
#define  USTYPE_PSX_USR 130 
#define  USTYPE_SMB_GRP 129 
#define  USTYPE_SMB_USR 128 

__attribute__((used)) static inline const char *
us_type2str(unsigned field_type)
{
	switch (field_type) {
	case USTYPE_PSX_USR:
		return ("POSIX User");
	case USTYPE_PSX_GRP:
		return ("POSIX Group");
	case USTYPE_SMB_USR:
		return ("SMB User");
	case USTYPE_SMB_GRP:
		return ("SMB Group");
	case USTYPE_PROJ:
		return ("Project");
	default:
		return ("Undefined");
	}
}