#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/ * Desc; TYPE_2__* Bg; TYPE_1__* Ucr; } ;
typedef  TYPE_3__ cmsUcrBg ;
typedef  int cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsUInt16Number ;
struct TYPE_12__ {int (* Read ) (int /*<<< orphan*/ ,TYPE_4__*,char*,int,int) ;} ;
typedef  TYPE_4__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_10__ {int /*<<< orphan*/  Table16; } ;
struct TYPE_9__ {int /*<<< orphan*/  Table16; } ;

/* Variables and functions */
 int UINT_MAX ; 
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _cmsMalloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ _cmsMallocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _cmsReadUInt16Array (int /*<<< orphan*/ ,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsReadUInt32Number (int /*<<< orphan*/ ,TYPE_4__*,int*) ; 
 void* cmsBuildTabulatedToneCurve16 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsMLUalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmsMLUsetASCII (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cmsNoCountry ; 
 int /*<<< orphan*/  cmsNoLanguage ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (struct _cms_typehandler_struct*) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_4__*,char*,int,int) ; 

__attribute__((used)) static
void *Type_UcrBg_Read(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, cmsUInt32Number* nItems, cmsUInt32Number SizeOfTag)
{
    cmsUcrBg* n = (cmsUcrBg*) _cmsMallocZero(ContextID, sizeof(cmsUcrBg));
    cmsUInt32Number CountUcr, CountBg;
    char* ASCIIString;
    cmsUNUSED_PARAMETER(self);

    *nItems = 0;
    if (n == NULL) return NULL;

    // First curve is Under color removal
    if (!_cmsReadUInt32Number(ContextID, io, &CountUcr)) return NULL;
    if (SizeOfTag < sizeof(cmsUInt32Number)) return NULL;
    SizeOfTag -= sizeof(cmsUInt32Number);

    n ->Ucr = cmsBuildTabulatedToneCurve16(ContextID, CountUcr, NULL);
    if (n ->Ucr == NULL) return NULL;

    if (!_cmsReadUInt16Array(ContextID, io, CountUcr, n ->Ucr->Table16)) return NULL;
    if (SizeOfTag < sizeof(cmsUInt32Number)) return NULL;
    SizeOfTag -= CountUcr * sizeof(cmsUInt16Number);

    // Second curve is Black generation
    if (!_cmsReadUInt32Number(ContextID, io, &CountBg)) return NULL;
    if (SizeOfTag < sizeof(cmsUInt32Number)) return NULL;
    SizeOfTag -= sizeof(cmsUInt32Number);

    n ->Bg = cmsBuildTabulatedToneCurve16(ContextID, CountBg, NULL);
    if (n ->Bg == NULL) return NULL;
    if (!_cmsReadUInt16Array(ContextID, io, CountBg, n ->Bg->Table16)) return NULL;
    if (SizeOfTag < CountBg * sizeof(cmsUInt16Number)) return NULL;
    SizeOfTag -= CountBg * sizeof(cmsUInt16Number);
    if (SizeOfTag == UINT_MAX) return NULL;

    // Now comes the text. The length is specified by the tag size
    n ->Desc = cmsMLUalloc(ContextID, 1);
    if (n ->Desc == NULL) return NULL;

    ASCIIString = (char*) _cmsMalloc(ContextID, SizeOfTag + 1);
    if (io ->Read(ContextID, io,ASCIIString, sizeof(char), SizeOfTag) != SizeOfTag) return NULL;
    ASCIIString[SizeOfTag] = 0;
    cmsMLUsetASCII(ContextID, n ->Desc, cmsNoLanguage, cmsNoCountry, ASCIIString);
    _cmsFree(ContextID, ASCIIString);

    *nItems = 1;
    return (void*) n;
}