#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ Implements; struct TYPE_10__* Next; } ;
typedef  TYPE_1__ cmsStage ;
struct TYPE_11__ {TYPE_1__* Elements; } ;
typedef  TYPE_2__ cmsPipeline ;
typedef  int /*<<< orphan*/  cmsMAT3 ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_12__ {scalar_t__ Double; int /*<<< orphan*/ * Offset; } ;
typedef  TYPE_3__ _cmsStageMatrixData ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _RemoveElement (int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  _cmsMAT3per (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsSigMatrixElemType ; 
 TYPE_1__* cmsStageAllocMatrix (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsStageData (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int cmsStageInputChannels (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int cmsStageOutputChannels (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  isFloatMatrixIdentity (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsBool _MultiplyMatrix(cmsContext ContextID, cmsPipeline* Lut)
{
       cmsStage** pt1;
       cmsStage** pt2;
       cmsStage*  chain;
       cmsBool AnyOpt = FALSE;

       pt1 = &Lut->Elements;
       if (*pt1 == NULL) return AnyOpt;

       while (*pt1 != NULL) {

              pt2 = &((*pt1)->Next);
              if (*pt2 == NULL) return AnyOpt;

              if ((*pt1)->Implements == cmsSigMatrixElemType && (*pt2)->Implements == cmsSigMatrixElemType) {

                     // Get both matrices
                     _cmsStageMatrixData* m1 = (_cmsStageMatrixData*) cmsStageData(ContextID, *pt1);
                     _cmsStageMatrixData* m2 = (_cmsStageMatrixData*) cmsStageData(ContextID, *pt2);
                     cmsMAT3 res;

                     // Input offset and output offset should be zero to use this optimization
                     if (m1->Offset != NULL || m2 ->Offset != NULL ||
                            cmsStageInputChannels(ContextID, *pt1) != 3 || cmsStageOutputChannels(ContextID, *pt1) != 3 ||
                            cmsStageInputChannels(ContextID, *pt2) != 3 || cmsStageOutputChannels(ContextID, *pt2) != 3)
                            return FALSE;

                     // Multiply both matrices to get the result
                     _cmsMAT3per(ContextID, &res, (cmsMAT3*)m2->Double, (cmsMAT3*)m1->Double);

                     // Get the next in chain after the matrices
                     chain = (*pt2)->Next;

                     // Remove both matrices
                     _RemoveElement(ContextID, pt2);
                     _RemoveElement(ContextID, pt1);

                     // Now what if the result is a plain identity?
                     if (!isFloatMatrixIdentity(ContextID, &res)) {

                            // We can not get rid of full matrix
                            cmsStage* Multmat = cmsStageAllocMatrix(ContextID, 3, 3, (const cmsFloat64Number*) &res, NULL);
                            if (Multmat == NULL) return FALSE;  // Should never happen

                            // Recover the chain
                            Multmat->Next = chain;
                            *pt1 = Multmat;
                     }

                     AnyOpt = TRUE;
              }
              else
                     pt1 = &((*pt1)->Next);
       }

       return AnyOpt;
}