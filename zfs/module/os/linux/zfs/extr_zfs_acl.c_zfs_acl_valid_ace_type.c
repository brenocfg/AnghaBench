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
typedef  int uint_t ;
typedef  int uint16_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int ACE_EVERYONE ; 
 int ACE_IDENTIFIER_GROUP ; 
 int ACE_OWNER ; 
#define  ACE_SYSTEM_ALARM_ACE_TYPE 131 
#define  ACE_SYSTEM_AUDIT_ACE_TYPE 130 
 int ACE_TYPE_FLAGS ; 
#define  ALLOW 129 
 int B_FALSE ; 
 int B_TRUE ; 
#define  DENY 128 
 int MAX_ACE_TYPE ; 
 int MIN_ACE_TYPE ; 
 int OWNING_GROUP ; 

__attribute__((used)) static boolean_t
zfs_acl_valid_ace_type(uint_t type, uint_t flags)
{
	uint16_t entry_type;

	switch (type) {
	case ALLOW:
	case DENY:
	case ACE_SYSTEM_AUDIT_ACE_TYPE:
	case ACE_SYSTEM_ALARM_ACE_TYPE:
		entry_type = flags & ACE_TYPE_FLAGS;
		return (entry_type == ACE_OWNER ||
		    entry_type == OWNING_GROUP ||
		    entry_type == ACE_EVERYONE || entry_type == 0 ||
		    entry_type == ACE_IDENTIFIER_GROUP);
	default:
		if (type >= MIN_ACE_TYPE && type <= MAX_ACE_TYPE)
			return (B_TRUE);
	}
	return (B_FALSE);
}