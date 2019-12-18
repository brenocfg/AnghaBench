#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  int cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsMLU ;
struct TYPE_4__ {int (* Read ) (int /*<<< orphan*/ ,TYPE_1__*,char*,int,int) ;} ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int UINT_MAX ; 
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _cmsMalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * cmsMLUalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmsMLUfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsMLUsetASCII (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cmsNoCountry ; 
 int /*<<< orphan*/  cmsNoLanguage ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (struct _cms_typehandler_struct*) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_1__*,char*,int,int) ; 

__attribute__((used)) static
void *Type_Text_Read(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, cmsUInt32Number* nItems, cmsUInt32Number SizeOfTag)
{
    char* Text = NULL;
    cmsMLU* mlu = NULL;
    cmsUNUSED_PARAMETER(self);

    // Create a container
    mlu = cmsMLUalloc(ContextID, 1);
    if (mlu == NULL) return NULL;

    *nItems = 0;

    // We need to store the "\0" at the end, so +1
    if (SizeOfTag == UINT_MAX) goto Error;

    Text = (char*) _cmsMalloc(ContextID, SizeOfTag + 1);
    if (Text == NULL) goto Error;

    if (io -> Read(ContextID, io, Text, sizeof(char), SizeOfTag) != SizeOfTag) goto Error;

    // Make sure text is properly ended
    Text[SizeOfTag] = 0;
    *nItems = 1;

    // Keep the result
    if (!cmsMLUsetASCII(ContextID, mlu, cmsNoLanguage, cmsNoCountry, Text)) goto Error;

    _cmsFree(ContextID, Text);
    return (void*) mlu;

Error:
    if (mlu != NULL)
        cmsMLUfree(ContextID, mlu);
    if (Text != NULL)
        _cmsFree(ContextID, Text);

    return NULL;
}