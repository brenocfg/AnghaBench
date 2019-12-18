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
typedef  int /*<<< orphan*/  sa_hdr_phys_t ;

/* Variables and functions */
 int SA_HDR_SIZE (int /*<<< orphan*/ *) ; 

int
sa_hdrsize(void *arg)
{
	sa_hdr_phys_t *hdr = arg;

	return (SA_HDR_SIZE(hdr));
}