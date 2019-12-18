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
 int /*<<< orphan*/  nvlist_nv_alloc (int) ; 
 int nvlist_xpack (int /*<<< orphan*/ *,char**,size_t*,int,int /*<<< orphan*/ ) ; 

int
nvlist_pack(nvlist_t *nvl, char **bufp, size_t *buflen, int encoding,
    int kmflag)
{
	return (nvlist_xpack(nvl, bufp, buflen, encoding,
	    nvlist_nv_alloc(kmflag)));
}