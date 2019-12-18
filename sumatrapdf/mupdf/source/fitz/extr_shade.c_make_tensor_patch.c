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
struct TYPE_3__ {void*** pole; } ;
typedef  TYPE_1__ tensor_patch ;
typedef  void* fz_point ;

/* Variables and functions */
 void* compute_tensor_interior (void*,void*,void*,void*,void*,void*,void*,void*) ; 

__attribute__((used)) static void
make_tensor_patch(tensor_patch *p, int type, fz_point *pt)
{
	if (type == 6)
	{
		/* see control point stream order at page 325 in pdf 1.7 */

		p->pole[0][0] = pt[0];
		p->pole[0][1] = pt[1];
		p->pole[0][2] = pt[2];
		p->pole[0][3] = pt[3];
		p->pole[1][3] = pt[4];
		p->pole[2][3] = pt[5];
		p->pole[3][3] = pt[6];
		p->pole[3][2] = pt[7];
		p->pole[3][1] = pt[8];
		p->pole[3][0] = pt[9];
		p->pole[2][0] = pt[10];
		p->pole[1][0] = pt[11];

		/* see equations at page 330 in pdf 1.7 */

		p->pole[1][1] = compute_tensor_interior(
			p->pole[0][0], p->pole[0][1], p->pole[1][0], p->pole[0][3],
			p->pole[3][0], p->pole[3][1], p->pole[1][3], p->pole[3][3]);

		p->pole[1][2] = compute_tensor_interior(
			p->pole[0][3], p->pole[0][2], p->pole[1][3], p->pole[0][0],
			p->pole[3][3], p->pole[3][2], p->pole[1][0], p->pole[3][0]);

		p->pole[2][1] = compute_tensor_interior(
			p->pole[3][0], p->pole[3][1], p->pole[2][0], p->pole[3][3],
			p->pole[0][0], p->pole[0][1], p->pole[2][3], p->pole[0][3]);

		p->pole[2][2] = compute_tensor_interior(
			p->pole[3][3], p->pole[3][2], p->pole[2][3], p->pole[3][0],
			p->pole[0][3], p->pole[0][2], p->pole[2][0], p->pole[0][0]);
	}
	else if (type == 7)
	{
		/* see control point stream order at page 330 in pdf 1.7 */

		p->pole[0][0] = pt[0];
		p->pole[0][1] = pt[1];
		p->pole[0][2] = pt[2];
		p->pole[0][3] = pt[3];
		p->pole[1][3] = pt[4];
		p->pole[2][3] = pt[5];
		p->pole[3][3] = pt[6];
		p->pole[3][2] = pt[7];
		p->pole[3][1] = pt[8];
		p->pole[3][0] = pt[9];
		p->pole[2][0] = pt[10];
		p->pole[1][0] = pt[11];
		p->pole[1][1] = pt[12];
		p->pole[1][2] = pt[13];
		p->pole[2][2] = pt[14];
		p->pole[2][1] = pt[15];
	}
}