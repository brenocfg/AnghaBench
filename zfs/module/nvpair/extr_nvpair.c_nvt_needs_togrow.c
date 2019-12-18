#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nvp_nentries; int nvp_nbuckets; } ;
typedef  TYPE_1__ nvpriv_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int UINT32_MAX ; 

__attribute__((used)) static boolean_t
nvt_needs_togrow(nvpriv_t *priv)
{
	/*
	 * Grow only when we have more elements than buckets
	 * and the # of buckets doesn't overflow.
	 */
	return (priv->nvp_nentries > priv->nvp_nbuckets &&
	    (UINT32_MAX >> 1) >= priv->nvp_nbuckets);
}