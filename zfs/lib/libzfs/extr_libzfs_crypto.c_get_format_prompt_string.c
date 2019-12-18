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
typedef  int zfs_keyformat_t ;

/* Variables and functions */
#define  ZFS_KEYFORMAT_HEX 130 
#define  ZFS_KEYFORMAT_PASSPHRASE 129 
#define  ZFS_KEYFORMAT_RAW 128 

__attribute__((used)) static const char *
get_format_prompt_string(zfs_keyformat_t format)
{
	switch (format) {
	case ZFS_KEYFORMAT_RAW:
		return ("raw key");
	case ZFS_KEYFORMAT_HEX:
		return ("hex key");
	case ZFS_KEYFORMAT_PASSPHRASE:
		return ("passphrase");
	default:
		/* shouldn't happen */
		return (NULL);
	}
}