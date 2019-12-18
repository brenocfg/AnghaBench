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
typedef  scalar_t__ cmsTechnologySignature ;
typedef  void* cmsSignature ;
struct TYPE_7__ {TYPE_1__* seq; } ;
typedef  TYPE_2__ cmsSEQ ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_6__ {int /*<<< orphan*/  Model; int /*<<< orphan*/  Manufacturer; scalar_t__ technology; scalar_t__* attributes; void* deviceModel; void* deviceMfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsWriteProfileSequence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* cmsAllocProfileSequenceDescription (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmsFreeProfileSequenceDescription (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  cmsMLUsetASCII (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  cmsNoCountry ; 
 int /*<<< orphan*/  cmsNoLanguage ; 

__attribute__((used)) static
cmsBool  SetSeqDescTag(cmsContext ContextID, cmsHPROFILE hProfile, const char* Model)
{
    cmsBool  rc = FALSE;
    cmsSEQ* Seq = cmsAllocProfileSequenceDescription(ContextID, 1);

    if (Seq == NULL) return FALSE;

    Seq->seq[0].deviceMfg = (cmsSignature) 0;
    Seq->seq[0].deviceModel = (cmsSignature) 0;

#ifdef CMS_DONT_USE_INT64
    Seq->seq[0].attributes[0] = 0;
    Seq->seq[0].attributes[1] = 0;
#else
    Seq->seq[0].attributes = 0;
#endif

    Seq->seq[0].technology = (cmsTechnologySignature) 0;

    cmsMLUsetASCII(ContextID,  Seq->seq[0].Manufacturer, cmsNoLanguage, cmsNoCountry, "Little CMS");
    cmsMLUsetASCII(ContextID,  Seq->seq[0].Model,        cmsNoLanguage, cmsNoCountry, Model);

    if (!_cmsWriteProfileSequence(ContextID, hProfile, Seq)) goto Error;

    rc = TRUE;

Error:
    if (Seq)
        cmsFreeProfileSequenceDescription(ContextID, Seq);

    return rc;
}