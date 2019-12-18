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
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 double const pow (double,double const) ; 

__attribute__((used)) static double Rec709Math(cmsContext ContextID, int Type, const double Params[], double R)
{
    double Fun = 0;

    switch (Type)
    {
    case 709:

        if (R <= (Params[3]*Params[4])) Fun = R / Params[3];
        else Fun = pow(((R - Params[2])/Params[1]), Params[0]);
        break;

    case -709:

        if (R <= Params[4]) Fun = R * Params[3];
        else Fun = Params[1] * pow(R, (1/Params[0])) + Params[2];
        break;
    }
    return Fun;
}