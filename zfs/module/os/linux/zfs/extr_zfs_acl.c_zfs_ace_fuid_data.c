#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_object_ace_t ;
struct TYPE_3__ {int z_type; } ;
struct TYPE_4__ {TYPE_1__ z_hdr; } ;
typedef  TYPE_2__ zfs_ace_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
#define  ACE_ACCESS_ALLOWED_OBJECT_ACE_TYPE 131 
#define  ACE_ACCESS_DENIED_OBJECT_ACE_TYPE 130 
#define  ACE_SYSTEM_ALARM_OBJECT_ACE_TYPE 129 
#define  ACE_SYSTEM_AUDIT_OBJECT_ACE_TYPE 128 

__attribute__((used)) static int
zfs_ace_fuid_data(void *acep, void **datap)
{
	zfs_ace_t *zacep = acep;
	zfs_object_ace_t *zobjp;

	switch (zacep->z_hdr.z_type) {
	case ACE_ACCESS_ALLOWED_OBJECT_ACE_TYPE:
	case ACE_ACCESS_DENIED_OBJECT_ACE_TYPE:
	case ACE_SYSTEM_AUDIT_OBJECT_ACE_TYPE:
	case ACE_SYSTEM_ALARM_OBJECT_ACE_TYPE:
		zobjp = acep;
		*datap = (caddr_t)zobjp + sizeof (zfs_ace_t);
		return (sizeof (zfs_object_ace_t) - sizeof (zfs_ace_t));
	default:
		*datap = NULL;
		return (0);
	}
}