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
#define  SRC_SINC_BEST_QUALITY 130 
#define  SRC_SINC_FASTEST 129 
#define  SRC_SINC_MEDIUM_QUALITY 128 

const char*
sinc_get_name (int src_enum)
{
	switch (src_enum)
	{	case SRC_SINC_BEST_QUALITY :
			return "Best Sinc Interpolator" ;

		case SRC_SINC_MEDIUM_QUALITY :
			return "Medium Sinc Interpolator" ;

		case SRC_SINC_FASTEST :
			return "Fastest Sinc Interpolator" ;

		default: break ;
		} ;

	return NULL ;
}