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
typedef  scalar_t__ MV_U8 ;
typedef  int /*<<< orphan*/  MV_U32 ;

/* Variables and functions */
 int MAXBC ; 

void ShiftRow128Enc(MV_U8 a[4][MAXBC]) {
	/* Row 0 remains unchanged
	 * The other three rows are shifted a variable amount
	 */
	MV_U8 tmp[MAXBC];

    tmp[0] = a[1][1];
    tmp[1] = a[1][2];
    tmp[2] = a[1][3];
    tmp[3] = a[1][0];

    ((MV_U32*)(&(a[1][0])))[0] = ((MV_U32*)(&(tmp[0])))[0];
     /*
    a[1][0] = tmp[0];
    a[1][1] = tmp[1];
    a[1][2] = tmp[2];
    a[1][3] = tmp[3];
       */
    tmp[0] = a[2][2];
    tmp[1] = a[2][3];
    tmp[2] = a[2][0];
    tmp[3] = a[2][1];

    ((MV_U32*)(&(a[2][0])))[0] = ((MV_U32*)(&(tmp[0])))[0];
      /*
    a[2][0] = tmp[0];
    a[2][1] = tmp[1];
    a[2][2] = tmp[2];
    a[2][3] = tmp[3];
    */
    tmp[0] = a[3][3];
    tmp[1] = a[3][0];
    tmp[2] = a[3][1];
    tmp[3] = a[3][2];

    ((MV_U32*)(&(a[3][0])))[0] = ((MV_U32*)(&(tmp[0])))[0];
    /*
    a[3][0] = tmp[0];
    a[3][1] = tmp[1];
    a[3][2] = tmp[2];
    a[3][3] = tmp[3];
    */
}