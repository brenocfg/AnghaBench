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

/* Variables and functions */
 int abs (int) ; 
 double log (double) ; 
 double pow (double,double) ; 

__attribute__((used)) static void PrecalcCoefs(int *Ct, double Dist25)
{
    double Gamma, Simil, C;

    Gamma = log(0.25) / log(1.0 - Dist25/255.0 - 0.00001);

    for (int i = -255*16; i <= 255*16; i++)
    {
        Simil = 1.0 - abs(i) / (16*255.0);
        C = pow(Simil, Gamma) * 65536.0 * (double)i / 16.0;
        Ct[16*256+i] = (C<0) ? (C-0.5) : (C+0.5);
    }

    Ct[0] = (Dist25 != 0);
}