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
typedef  int uint8_t ;
typedef  int uint64_t ;
struct vlapic {int dummy; } ;

/* Variables and functions */
 int vlapic_get_tpr (struct vlapic*) ; 

uint64_t
vlapic_get_cr8(struct vlapic *vlapic)
{
	uint8_t tpr;

	tpr = vlapic_get_tpr(vlapic);
	return (tpr >> 4);
}