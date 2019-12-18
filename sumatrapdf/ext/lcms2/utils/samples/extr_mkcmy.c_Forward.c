#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double L; double a; double b; } ;
typedef  TYPE_1__ cmsCIELab ;
typedef  scalar_t__ WORD ;
struct TYPE_5__ {int /*<<< orphan*/  Lab2RGB; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  TYPE_2__* LPCARGO ;

/* Variables and functions */
 int TRUE ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,scalar_t__*,scalar_t__**,int) ; 
 int /*<<< orphan*/  cmsLabEncoded2Float (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  printf (char*,double,double,double) ; 

__attribute__((used)) static
int Forward(register WORD In[], register WORD Out[], register LPVOID Cargo)
{	
	LPCARGO C = (LPCARGO) Cargo;	
	WORD RGB[3];
    cmsCIELab Lab;

    cmsLabEncoded2Float(&Lab, In);

	printf("%g %g %g\n", Lab.L, Lab.a, Lab.b);

	cmsDoTransform(C ->Lab2RGB, In, &RGB, 1);


	Out[0] = 0xFFFF - RGB[0]; // Our CMY is negative of RGB
	Out[1] = 0xFFFF - RGB[1]; 
	Out[2] = 0xFFFF - RGB[2]; 
	
	
	return TRUE;

}