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
typedef  int cmsInt32Number ;
typedef  int cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  MATRIX_DET_TOLERANCE ; 
 int PLUS_INF ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fabs (int const) ; 
 int const log (int const) ; 
 int const log10 (int) ; 
 int const pow (int const,int const) ; 

__attribute__((used)) static
cmsFloat64Number DefaultEvalParametricFn(cmsContext ContextID, cmsInt32Number Type, const cmsFloat64Number Params[], cmsFloat64Number R)
{
    cmsFloat64Number e, Val, disc;
    cmsUNUSED_PARAMETER(ContextID);

    switch (Type) {

   // X = Y ^ Gamma
    case 1:
        if (R < 0) {

            if (fabs(Params[0] - 1.0) < MATRIX_DET_TOLERANCE)
                Val = R;
            else
                Val = 0;
        }
        else
            Val = pow(R, Params[0]);
        break;

    // Type 1 Reversed: X = Y ^1/gamma
    case -1:
        if (R < 0) {

            if (fabs(Params[0] - 1.0) < MATRIX_DET_TOLERANCE)
                Val = R;
            else
                Val = 0;
        }
        else
        {
            if (fabs(Params[0]) < MATRIX_DET_TOLERANCE)
                Val = PLUS_INF;
            else
                Val = pow(R, 1 / Params[0]);
        }
        break;

    // CIE 122-1966
    // Y = (aX + b)^Gamma  | X >= -b/a
    // Y = 0               | else
    case 2:
    {

        if (fabs(Params[1]) < MATRIX_DET_TOLERANCE)
        {
            Val = 0;
        }
        else
        {
            disc = -Params[2] / Params[1];

            if (R >= disc) {

                e = Params[1] * R + Params[2];

                if (e > 0)
                    Val = pow(e, Params[0]);
                else
                    Val = 0;
            }
            else
                Val = 0;
        }
    }
    break;

     // Type 2 Reversed
     // X = (Y ^1/g  - b) / a
     case -2:
     {
         if (fabs(Params[0]) < MATRIX_DET_TOLERANCE ||
             fabs(Params[1]) < MATRIX_DET_TOLERANCE)
         {
             Val = 0;
         }
         else
         {
             if (R < 0)
                 Val = 0;
             else
                 Val = (pow(R, 1.0 / Params[0]) - Params[2]) / Params[1];

             if (Val < 0)
                 Val = 0;
         }
     }
     break;


    // IEC 61966-3
    // Y = (aX + b)^Gamma | X <= -b/a
    // Y = c              | else
    case 3:
    {
        if (fabs(Params[1]) < MATRIX_DET_TOLERANCE)
        {
            Val = 0;
        }
        else
        {
            disc = -Params[2] / Params[1];
            if (disc < 0)
                disc = 0;

            if (R >= disc) {

                e = Params[1] * R + Params[2];

                if (e > 0)
                    Val = pow(e, Params[0]) + Params[3];
                else
                    Val = 0;
            }
            else
                Val = Params[3];
        }
    }
    break;


    // Type 3 reversed
    // X=((Y-c)^1/g - b)/a      | (Y>=c)
    // X=-b/a                   | (Y<c)
    case -3:
    {
        if (fabs(Params[1]) < MATRIX_DET_TOLERANCE)
        {
            Val = 0;
        }
        else
        {
            if (R >= Params[3]) {

                e = R - Params[3];

                if (e > 0)
                    Val = (pow(e, 1 / Params[0]) - Params[2]) / Params[1];
                else
                    Val = 0;
            }
            else {
                Val = -Params[2] / Params[1];
            }
        }
    }
    break;


    // IEC 61966-2.1 (sRGB)
    // Y = (aX + b)^Gamma | X >= d
    // Y = cX             | X < d
    case 4:
        if (R >= Params[4]) {

            e = Params[1]*R + Params[2];

            if (e > 0)
                Val = pow(e, Params[0]);
            else
                Val = 0;
        }
        else
            Val = R * Params[3];
        break;

    // Type 4 reversed
    // X=((Y^1/g-b)/a)    | Y >= (ad+b)^g
    // X=Y/c              | Y< (ad+b)^g
    case -4:
    {
        if (fabs(Params[0]) < MATRIX_DET_TOLERANCE ||
            fabs(Params[1]) < MATRIX_DET_TOLERANCE ||
            fabs(Params[3]) < MATRIX_DET_TOLERANCE)
        {
            Val = 0;
        }
        else
        {
            e = Params[1] * Params[4] + Params[2];
            if (e < 0)
                disc = 0;
            else
                disc = pow(e, Params[0]);

            if (R >= disc) {

                Val = (pow(R, 1.0 / Params[0]) - Params[2]) / Params[1];
            }
            else {
                Val = R / Params[3];
            }
        }
    }
    break;


    // Y = (aX + b)^Gamma + e | X >= d
    // Y = cX + f             | X < d
    case 5:
        if (R >= Params[4]) {

            e = Params[1]*R + Params[2];

            if (e > 0)
                Val = pow(e, Params[0]) + Params[5];
            else
                Val = Params[5];
        }
        else
            Val = R*Params[3] + Params[6];
        break;


    // Reversed type 5
    // X=((Y-e)1/g-b)/a   | Y >=(ad+b)^g+e), cd+f
    // X=(Y-f)/c          | else
    case -5:
    {
        if (fabs(Params[1]) < MATRIX_DET_TOLERANCE ||
            fabs(Params[3]) < MATRIX_DET_TOLERANCE)
        {
            Val = 0;
        }
        else
        {
            disc = Params[3] * Params[4] + Params[6];
            if (R >= disc) {

                e = R - Params[5];
                if (e < 0)
                    Val = 0;
                else
                    Val = (pow(e, 1.0 / Params[0]) - Params[2]) / Params[1];
            }
            else {
                Val = (R - Params[6]) / Params[3];
            }
        }
    }
    break;


    // Types 6,7,8 comes from segmented curves as described in ICCSpecRevision_02_11_06_Float.pdf
    // Type 6 is basically identical to type 5 without d

    // Y = (a * X + b) ^ Gamma + c
    case 6:
        e = Params[1]*R + Params[2];

        if (e < 0)
            Val = Params[3];
        else
            Val = pow(e, Params[0]) + Params[3];
        break;

    // ((Y - c) ^1/Gamma - b) / a
    case -6:
    {
        if (fabs(Params[1]) < MATRIX_DET_TOLERANCE)
        {
            Val = 0;
        }
        else
        {
            e = R - Params[3];
            if (e < 0)
                Val = 0;
            else
                Val = (pow(e, 1.0 / Params[0]) - Params[2]) / Params[1];
        }
    }
    break;


    // Y = a * log (b * X^Gamma + c) + d
    case 7:

       e = Params[2] * pow(R, Params[0]) + Params[3];
       if (e <= 0)
           Val = Params[4];
       else
           Val = Params[1]*log10(e) + Params[4];
       break;

    // (Y - d) / a = log(b * X ^Gamma + c)
    // pow(10, (Y-d) / a) = b * X ^Gamma + c
    // pow((pow(10, (Y-d) / a) - c) / b, 1/g) = X
    case -7:
    {
        if (fabs(Params[0]) < MATRIX_DET_TOLERANCE ||
            fabs(Params[1]) < MATRIX_DET_TOLERANCE ||
            fabs(Params[2]) < MATRIX_DET_TOLERANCE)
        {
            Val = 0;
        }
        else
        {
            Val = pow((pow(10.0, (R - Params[4]) / Params[1]) - Params[3]) / Params[2], 1.0 / Params[0]);
        }
    }
    break;


   //Y = a * b^(c*X+d) + e
   case 8:
       Val = (Params[0] * pow(Params[1], Params[2] * R + Params[3]) + Params[4]);
       break;


   // Y = (log((y-e) / a) / log(b) - d ) / c
   // a=0, b=1, c=2, d=3, e=4,
   case -8:

       disc = R - Params[4];
       if (disc < 0) Val = 0;
       else
       {
           if (fabs(Params[0]) < MATRIX_DET_TOLERANCE ||
               fabs(Params[2]) < MATRIX_DET_TOLERANCE)
           {
               Val = 0;
           }
           else
           {
               Val = (log(disc / Params[0]) / log(Params[1]) - Params[3]) / Params[2];
           }
       }
       break;

   // S-Shaped: (1 - (1-x)^1/g)^1/g
   case 108:
       if (fabs(Params[0]) < MATRIX_DET_TOLERANCE)
           Val = 0;
       else
           Val = pow(1.0 - pow(1 - R, 1/Params[0]), 1/Params[0]);
      break;

    // y = (1 - (1-x)^1/g)^1/g
    // y^g = (1 - (1-x)^1/g)
    // 1 - y^g = (1-x)^1/g
    // (1 - y^g)^g = 1 - x
    // 1 - (1 - y^g)^g
    case -108:
        Val = 1 - pow(1 - pow(R, Params[0]), Params[0]);
        break;

    default:
        // Unsupported parametric curve. Should never reach here
        return 0;
    }

    return Val;
}