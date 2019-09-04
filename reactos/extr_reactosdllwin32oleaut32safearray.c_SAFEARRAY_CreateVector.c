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
typedef  int VARTYPE ;
typedef  int ULONG ;
struct TYPE_7__ {int cDims; int cbElements; int /*<<< orphan*/  fFeatures; TYPE_1__* rgsabound; struct TYPE_7__* pvData; } ;
struct TYPE_6__ {int cElements; int /*<<< orphan*/  lLbound; } ;
typedef  TYPE_2__ SAFEARRAY ;
typedef  int /*<<< orphan*/  LONG ;

/* Variables and functions */
 int /*<<< orphan*/  FADF_BSTR ; 
 int /*<<< orphan*/  FADF_CREATEVECTOR ; 
 int /*<<< orphan*/  FADF_DISPATCH ; 
 int /*<<< orphan*/  FADF_UNKNOWN ; 
 int /*<<< orphan*/  FADF_VARIANT ; 
 int /*<<< orphan*/  SAFEARRAY_AllocDescriptor (int,TYPE_2__**) ; 
 int /*<<< orphan*/  SAFEARRAY_SetFeatures (int,TYPE_2__*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
#define  VT_BSTR 131 
#define  VT_DISPATCH 130 
 int VT_RECORD ; 
#define  VT_UNKNOWN 129 
#define  VT_VARIANT 128 

__attribute__((used)) static SAFEARRAY* SAFEARRAY_CreateVector(VARTYPE vt, LONG lLbound, ULONG cElements, ULONG ulSize)
{
  SAFEARRAY *psa = NULL;

  if (ulSize || (vt == VT_RECORD))
  {
    /* Allocate the header and data together */
    if (SUCCEEDED(SAFEARRAY_AllocDescriptor(sizeof(SAFEARRAY) + ulSize * cElements, &psa)))
    {
      SAFEARRAY_SetFeatures(vt, psa);

      psa->cDims = 1;
      psa->fFeatures |= FADF_CREATEVECTOR;
      psa->pvData = &psa[1]; /* Data follows the header */
      psa->cbElements = ulSize;
      psa->rgsabound[0].cElements = cElements;
      psa->rgsabound[0].lLbound = lLbound;

      switch (vt)
      {
        case VT_BSTR:     psa->fFeatures |= FADF_BSTR; break;
        case VT_UNKNOWN:  psa->fFeatures |= FADF_UNKNOWN; break;
        case VT_DISPATCH: psa->fFeatures |= FADF_DISPATCH; break;
        case VT_VARIANT:  psa->fFeatures |= FADF_VARIANT; break;
      }
    }
  }
  return psa;
}