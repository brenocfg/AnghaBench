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
typedef  int /*<<< orphan*/  cmsCIELab ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  LPVOID ;

/* Variables and functions */
 int /*<<< orphan*/  ITU2Lab (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int /*<<< orphan*/  cmsFloat2LabEncoded (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
int OutputDirection(register WORD In[], register WORD Out[], register LPVOID Cargo)
{	

	cmsCIELab Lab;

    ITU2Lab(In, &Lab);
    cmsFloat2LabEncoded(Out, &Lab);    

	return TRUE;
}