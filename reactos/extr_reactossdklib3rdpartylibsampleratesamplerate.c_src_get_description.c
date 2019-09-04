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

/* Variables and functions */
 char* linear_get_description (int) ; 
 char* sinc_get_description (int) ; 
 char* zoh_get_description (int) ; 

const char *
src_get_description (int converter_type)
{	const char *desc ;

	if ((desc = sinc_get_description (converter_type)) != NULL)
		return desc ;

	if ((desc = zoh_get_description (converter_type)) != NULL)
		return desc ;

	if ((desc = linear_get_description (converter_type)) != NULL)
		return desc ;

	return NULL ;
}