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
typedef  int cmsUInt32Number ;
typedef  int cmsInt32Number ;

/* Variables and functions */
 int /*<<< orphan*/  Check1D (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static
cmsInt32Number ExhaustiveCheck1DLERPDown(void)
{
    cmsUInt32Number j;

    printf("\n");
    for (j=10; j <= 4096; j++) {

        if ((j % 10) == 0) printf("%u    \r", j);

        if (!Check1D(j, TRUE, 1)) return 0;
    }


    printf("\rResult is ");
    return 1;
}