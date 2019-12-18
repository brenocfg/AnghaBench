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
typedef  int cmsUInt16Number ;
struct TYPE_6__ {int /*<<< orphan*/  (* Lerp16 ) (int /*<<< orphan*/ ,int*,int*,TYPE_2__*) ;} ;
struct TYPE_7__ {TYPE_1__ Interpolation; } ;
typedef  TYPE_2__ cmsInterpParams ;
typedef  int cmsInt32Number ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_LERP_FLAGS_16BITS ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  IsGoodWord (char*,int,int) ; 
 double MaxErr ; 
 TYPE_2__* _cmsComputeInterpParams (int /*<<< orphan*/ ,int,int,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsFreeInterpParams (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  printf (char*,double) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int*,int*,TYPE_2__*) ; 

__attribute__((used)) static
cmsInt32Number Check3DinterpolationTetrahedral16(void)
{
    cmsInterpParams* p;
    cmsInt32Number i;
    cmsUInt16Number In[3], Out[3];
    cmsUInt16Number Table[] = {

        0,    0,   0,
        0,    0,   0xffff,

        0,    0xffff,    0,
        0,    0xffff,    0xffff,

        0xffff,    0,    0,
        0xffff,    0,    0xffff,

        0xffff,    0xffff,   0,
        0xffff,    0xffff,   0xffff
    };

    p = _cmsComputeInterpParams(DbgThread(), 2, 3, 3, Table, CMS_LERP_FLAGS_16BITS);

    MaxErr = 0.0;
     for (i=0; i < 0xffff; i++) {

       In[0] = In[1] = In[2] = (cmsUInt16Number) i;

        p ->Interpolation.Lerp16(DbgThread(), In, Out, p);

       if (!IsGoodWord("Channel 1", Out[0], In[0])) goto Error;
       if (!IsGoodWord("Channel 2", Out[1], In[1])) goto Error;
       if (!IsGoodWord("Channel 3", Out[2], In[2])) goto Error;
     }

    if (MaxErr > 0) printf("|Err|<%lf ", MaxErr);
    _cmsFreeInterpParams(DbgThread(), p);
    return 1;

Error:
    _cmsFreeInterpParams(DbgThread(), p);
    return 0;
}