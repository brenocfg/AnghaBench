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
typedef  size_t cmsUInt32Number ;
typedef  int cmsUInt16Number ;
typedef  int cmsS1Fixed14Number ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_2__ {int* Shaper1R; int* Shaper1G; int* Shaper1B; int** Mat; int* Off; int* Shaper2R; int* Shaper2G; int* Shaper2B; } ;
typedef  TYPE_1__ MatShaper8Data ;

/* Variables and functions */
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void MatShaperEval16(cmsContext ContextID, register const cmsUInt16Number In[],
                     register cmsUInt16Number Out[],
                     register const void* D)
{
    MatShaper8Data* p = (MatShaper8Data*) D;
    cmsS1Fixed14Number l1, l2, l3, r, g, b;
    cmsUInt32Number ri, gi, bi;
    cmsUNUSED_PARAMETER(ContextID);

    // In this case (and only in this case!) we can use this simplification since
    // In[] is assured to come from a 8 bit number. (a << 8 | a)
    ri = In[0] & 0xFFU;
    gi = In[1] & 0xFFU;
    bi = In[2] & 0xFFU;

    // Across first shaper, which also converts to 1.14 fixed point
    r = p->Shaper1R[ri];
    g = p->Shaper1G[gi];
    b = p->Shaper1B[bi];

    // Evaluate the matrix in 1.14 fixed point
    l1 =  (p->Mat[0][0] * r + p->Mat[0][1] * g + p->Mat[0][2] * b + p->Off[0] + 0x2000) >> 14;
    l2 =  (p->Mat[1][0] * r + p->Mat[1][1] * g + p->Mat[1][2] * b + p->Off[1] + 0x2000) >> 14;
    l3 =  (p->Mat[2][0] * r + p->Mat[2][1] * g + p->Mat[2][2] * b + p->Off[2] + 0x2000) >> 14;

    // Now we have to clip to 0..1.0 range
    ri = (l1 < 0) ? 0 : ((l1 > 16384) ? 16384U : (cmsUInt32Number) l1);
    gi = (l2 < 0) ? 0 : ((l2 > 16384) ? 16384U : (cmsUInt32Number) l2);
    bi = (l3 < 0) ? 0 : ((l3 > 16384) ? 16384U : (cmsUInt32Number) l3);

    // And across second shaper,
    Out[0] = p->Shaper2R[ri];
    Out[1] = p->Shaper2G[gi];
    Out[2] = p->Shaper2B[bi];

}