#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
struct TYPE_2__ {int /*<<< orphan*/  RGB2Lab; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  TYPE_1__* LPCARGO ;

/* Variables and functions */
 int TRUE ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,scalar_t__**,scalar_t__*,int) ; 

__attribute__((used)) static
int Reverse(register WORD In[], register WORD Out[], register LPVOID Cargo)
{	

	LPCARGO C = (LPCARGO) Cargo;	
	WORD RGB[3];
  
	RGB[0] = 0xFFFF - In[0];
	RGB[1] = 0xFFFF - In[1];
	RGB[2] = 0xFFFF - In[2];

	cmsDoTransform(C ->RGB2Lab, &RGB, Out, 1);
	
	return TRUE;

}