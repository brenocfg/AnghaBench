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
typedef  int /*<<< orphan*/  uchar_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_lookup_byte (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

uchar_t
fnvlist_lookup_byte(nvlist_t *nvl, const char *name)
{
	uchar_t rv;
	VERIFY0(nvlist_lookup_byte(nvl, name, &rv));
	return (rv);
}