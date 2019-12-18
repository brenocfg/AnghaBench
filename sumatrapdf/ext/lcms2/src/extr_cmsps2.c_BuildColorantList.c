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
typedef  size_t cmsUInt32Number ;
typedef  double cmsUInt16Number ;

/* Variables and functions */
 size_t cmsMAXCHANNELS ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,double) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static
void BuildColorantList(char *Colorant, cmsUInt32Number nColorant, cmsUInt16Number Out[])
{
    char Buff[32];
    cmsUInt32Number j;

    Colorant[0] = 0;
    if (nColorant > cmsMAXCHANNELS)
        nColorant = cmsMAXCHANNELS;

    for (j = 0; j < nColorant; j++) {

        snprintf(Buff, 31, "%.3f", Out[j] / 65535.0);
        Buff[31] = 0;
        strcat(Colorant, Buff);
        if (j < nColorant - 1)
            strcat(Colorant, " ");

    }
}