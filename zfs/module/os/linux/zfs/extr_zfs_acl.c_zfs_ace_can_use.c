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
typedef  int /*<<< orphan*/  umode_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int ACE_DIRECTORY_INHERIT_ACE ; 
 int ACE_FILE_INHERIT_ACE ; 
 int ACE_NO_PROPAGATE_INHERIT_ACE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_ace_can_use(umode_t obj_mode, uint16_t acep_flags)
{
	int	iflags = (acep_flags & 0xf);

	if (S_ISDIR(obj_mode) && (iflags & ACE_DIRECTORY_INHERIT_ACE))
		return (1);
	else if (iflags & ACE_FILE_INHERIT_ACE)
		return (!(S_ISDIR(obj_mode) &&
		    (iflags & ACE_NO_PROPAGATE_INHERIT_ACE)));
	return (0);
}