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
 int /*<<< orphan*/  NVS_OP_GETSIZE ; 
 int nvlist_common (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int,int /*<<< orphan*/ ) ; 

int
nvlist_size(nvlist_t *nvl, size_t *size, int encoding)
{
	return (nvlist_common(nvl, NULL, size, encoding, NVS_OP_GETSIZE));
}