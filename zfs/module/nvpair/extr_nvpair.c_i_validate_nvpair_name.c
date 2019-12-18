#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nvp_name_sz; scalar_t__ nvp_size; } ;
typedef  TYPE_1__ nvpair_t ;

/* Variables and functions */
 int EFAULT ; 
 char* NVP_NAME (TYPE_1__*) ; 
 scalar_t__ NVP_SIZE_CALC (int,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
i_validate_nvpair_name(nvpair_t *nvp)
{
	if ((nvp->nvp_name_sz <= 0) ||
	    (nvp->nvp_size < NVP_SIZE_CALC(nvp->nvp_name_sz, 0)))
		return (EFAULT);

	/* verify the name string, make sure its terminated */
	if (NVP_NAME(nvp)[nvp->nvp_name_sz - 1] != '\0')
		return (EFAULT);

	return (strlen(NVP_NAME(nvp)) == nvp->nvp_name_sz - 1 ? 0 : EFAULT);
}