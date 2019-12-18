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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  NV_ENCODE_NATIVE ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_size (int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 

size_t
fnvlist_size(nvlist_t *nvl)
{
	size_t size;
	VERIFY0(nvlist_size(nvl, &size, NV_ENCODE_NATIVE));
	return (size);
}