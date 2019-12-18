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
typedef  int MV_U8 ;
typedef  int /*<<< orphan*/  MV_U32 ;

/* Variables and functions */
 int MAXBC ; 
 int mul (int,int) ; 

void InvMixColumn(MV_U8 a[4][MAXBC]) {
        /* Mix the four bytes of every column in a linear way
	 * This is the opposite operation of Mixcolumn
	 */
	MV_U8 b[4][MAXBC];
	int i, j;

	for(j = 0; j < 4; j++){
        b[0][j] = mul(223,a[0][j]) ^ mul(104,a[1][j]) ^ mul(238,a[2][j]) ^ mul(199,a[3][j]);
        b[1][j] = mul(223,a[1][j]) ^ mul(104,a[2][j]) ^ mul(238,a[3][j]) ^ mul(199,a[0][j]);
        b[2][j] = mul(223,a[2][j]) ^ mul(104,a[3][j]) ^ mul(238,a[0][j]) ^ mul(199,a[1][j]);
        b[3][j] = mul(223,a[3][j]) ^ mul(104,a[0][j]) ^ mul(238,a[1][j]) ^ mul(199,a[2][j]);
    }
	for(i = 0; i < 4; i++)
		/*for(j = 0; j < BC; j++) a[i][j] = b[i][j];*/
        ((MV_U32*)(&(a[i][0])))[0] = ((MV_U32*)(&(b[i][0])))[0];
}