#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t zfs_share_proto_t ;
struct TYPE_2__ {int /*<<< orphan*/  p_name; } ;

/* Variables and functions */
 TYPE_1__* proto_table ; 
 int sa_parse_legacy_options (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

int
zfs_parse_options(char *options, zfs_share_proto_t proto)
{
	return (sa_parse_legacy_options(NULL, options,
	    proto_table[proto].p_name));
}