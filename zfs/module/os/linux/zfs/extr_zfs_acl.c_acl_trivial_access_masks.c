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
typedef  int uint32_t ;
typedef  int mode_t ;

/* Variables and functions */
 int ACE_APPEND_DATA ; 
 int ACE_EXECUTE ; 
 int ACE_READ_ACL ; 
 int ACE_READ_ATTRIBUTES ; 
 int ACE_READ_DATA ; 
 int ACE_READ_NAMED_ATTRS ; 
 int ACE_SYNCHRONIZE ; 
 int ACE_WRITE_ACL ; 
 int ACE_WRITE_ATTRIBUTES ; 
 int ACE_WRITE_DATA ; 
 int ACE_WRITE_NAMED_ATTRS ; 
 int ACE_WRITE_OWNER ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 

__attribute__((used)) static void
acl_trivial_access_masks(mode_t mode, uint32_t *allow0, uint32_t *deny1,
    uint32_t *deny2, uint32_t *owner, uint32_t *group, uint32_t *everyone)
{
	*deny1 = *deny2 = *allow0 = *group = 0;

	if (!(mode & S_IRUSR) && (mode & (S_IRGRP|S_IROTH)))
		*deny1 |= ACE_READ_DATA;
	if (!(mode & S_IWUSR) && (mode & (S_IWGRP|S_IWOTH)))
		*deny1 |= ACE_WRITE_DATA;
	if (!(mode & S_IXUSR) && (mode & (S_IXGRP|S_IXOTH)))
		*deny1 |= ACE_EXECUTE;

	if (!(mode & S_IRGRP) && (mode & S_IROTH))
		*deny2 = ACE_READ_DATA;
	if (!(mode & S_IWGRP) && (mode & S_IWOTH))
		*deny2 |= ACE_WRITE_DATA;
	if (!(mode & S_IXGRP) && (mode & S_IXOTH))
		*deny2 |= ACE_EXECUTE;

	if ((mode & S_IRUSR) && (!(mode & S_IRGRP) && (mode & S_IROTH)))
		*allow0 |= ACE_READ_DATA;
	if ((mode & S_IWUSR) && (!(mode & S_IWGRP) && (mode & S_IWOTH)))
		*allow0 |= ACE_WRITE_DATA;
	if ((mode & S_IXUSR) && (!(mode & S_IXGRP) && (mode & S_IXOTH)))
		*allow0 |= ACE_EXECUTE;

	*owner = ACE_WRITE_ATTRIBUTES|ACE_WRITE_OWNER|ACE_WRITE_ACL|
	    ACE_WRITE_NAMED_ATTRS|ACE_READ_ACL|ACE_READ_ATTRIBUTES|
	    ACE_READ_NAMED_ATTRS|ACE_SYNCHRONIZE;
	if (mode & S_IRUSR)
		*owner |= ACE_READ_DATA;
	if (mode & S_IWUSR)
		*owner |= ACE_WRITE_DATA|ACE_APPEND_DATA;
	if (mode & S_IXUSR)
		*owner |= ACE_EXECUTE;

	*group = ACE_READ_ACL|ACE_READ_ATTRIBUTES| ACE_READ_NAMED_ATTRS|
	    ACE_SYNCHRONIZE;
	if (mode & S_IRGRP)
		*group |= ACE_READ_DATA;
	if (mode & S_IWGRP)
		*group |= ACE_WRITE_DATA|ACE_APPEND_DATA;
	if (mode & S_IXGRP)
		*group |= ACE_EXECUTE;

	*everyone = ACE_READ_ACL|ACE_READ_ATTRIBUTES| ACE_READ_NAMED_ATTRS|
	    ACE_SYNCHRONIZE;
	if (mode & S_IROTH)
		*everyone |= ACE_READ_DATA;
	if (mode & S_IWOTH)
		*everyone |= ACE_WRITE_DATA|ACE_APPEND_DATA;
	if (mode & S_IXOTH)
		*everyone |= ACE_EXECUTE;
}