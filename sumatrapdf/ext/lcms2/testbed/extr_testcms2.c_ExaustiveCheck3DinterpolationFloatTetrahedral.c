#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* LerpFloat ) (int /*<<< orphan*/ ,double*,double*,TYPE_2__*) ;} ;
struct TYPE_7__ {TYPE_1__ Interpolation; } ;
typedef  TYPE_2__ cmsInterpParams ;
typedef  int cmsInt32Number ;
typedef  double cmsFloat32Number ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_LERP_FLAGS_FLOAT ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  IsGoodFixed15_16 (char*,double,double) ; 
 double MaxErr ; 
 TYPE_2__* _cmsComputeInterpParams (int /*<<< orphan*/ ,int,int,int,double*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsFreeInterpParams (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  printf (char*,double) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,double*,double*,TYPE_2__*) ; 

__attribute__((used)) static
cmsInt32Number ExaustiveCheck3DinterpolationFloatTetrahedral(void)
{
    cmsInterpParams* p;
    cmsInt32Number r, g, b;
    cmsFloat32Number In[3], Out[3];
    cmsFloat32Number FloatTable[] = { //R     G    B

        0,    0,   0,     // B=0,G=0,R=0
        0,    0,  .25,    // B=1,G=0,R=0

        0,   .5,    0,    // B=0,G=1,R=0
        0,   .5,  .25,    // B=1,G=1,R=0

        1,    0,    0,    // B=0,G=0,R=1
        1,    0,  .25,    // B=1,G=0,R=1

        1,    .5,   0,    // B=0,G=1,R=1
        1,    .5,  .25    // B=1,G=1,R=1

    };

    p = _cmsComputeInterpParams(DbgThread(), 2, 3, 3, FloatTable, CMS_LERP_FLAGS_FLOAT);

    MaxErr = 0.0;
    for (r=0; r < 0xff; r++)
        for (g=0; g < 0xff; g++)
            for (b=0; b < 0xff; b++)
        {

            In[0] = (cmsFloat32Number) r / 255.0F;
            In[1] = (cmsFloat32Number) g / 255.0F;
            In[2] = (cmsFloat32Number) b / 255.0F;


        p ->Interpolation.LerpFloat(DbgThread(), In, Out, p);

       if (!IsGoodFixed15_16("Channel 1", Out[0], In[0])) goto Error;
       if (!IsGoodFixed15_16("Channel 2", Out[1], (cmsFloat32Number) In[1] / 2.F)) goto Error;
       if (!IsGoodFixed15_16("Channel 3", Out[2], (cmsFloat32Number) In[2] / 4.F)) goto Error;
     }

    if (MaxErr > 0) printf("|Err|<%lf ", MaxErr);
    _cmsFreeInterpParams(DbgThread(), p);
    return 1;

Error:
    _cmsFreeInterpParams(DbgThread(), p);
    return 0;
}