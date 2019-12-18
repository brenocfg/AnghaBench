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
typedef  int /*<<< orphan*/  zfs_type_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  zprop_valid_for_type (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

boolean_t
zfs_prop_valid_for_type(int prop, zfs_type_t types, boolean_t headcheck)
{
	return (zprop_valid_for_type(prop, types, headcheck));
}