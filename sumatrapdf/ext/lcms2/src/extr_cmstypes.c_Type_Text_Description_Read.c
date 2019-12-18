#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  int /*<<< orphan*/  cmsUInt8Number ;
typedef  int cmsUInt32Number ;
typedef  char cmsUInt16Number ;
typedef  void cmsMLU ;
struct TYPE_9__ {int (* Read ) (int /*<<< orphan*/ ,TYPE_1__*,char*,int,int) ;} ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ _cmsMalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _cmsReadUInt16Number (int /*<<< orphan*/ ,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  _cmsReadUInt32Number (int /*<<< orphan*/ ,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  _cmsReadUInt8Number (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 void* cmsMLUalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmsMLUfree (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  cmsMLUsetASCII (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cmsNoCountry ; 
 int /*<<< orphan*/  cmsNoLanguage ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (struct _cms_typehandler_struct*) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_1__*,char*,int,int) ; 
 int stub2 (int /*<<< orphan*/ ,TYPE_1__*,char*,int,int) ; 
 int stub3 (int /*<<< orphan*/ ,TYPE_1__*,char*,int,int) ; 

__attribute__((used)) static
void *Type_Text_Description_Read(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, cmsUInt32Number* nItems, cmsUInt32Number SizeOfTag)
{
    char* Text = NULL;
    cmsMLU* mlu = NULL;
    cmsUInt32Number  AsciiCount;
    cmsUInt32Number  i, UnicodeCode, UnicodeCount;
    cmsUInt16Number  ScriptCodeCode, Dummy;
    cmsUInt8Number   ScriptCodeCount;
    cmsUNUSED_PARAMETER(self);

    *nItems = 0;

    //  One dword should be there
    if (SizeOfTag < sizeof(cmsUInt32Number)) return NULL;

    // Read len of ASCII
    if (!_cmsReadUInt32Number(ContextID, io, &AsciiCount)) return NULL;
    SizeOfTag -= sizeof(cmsUInt32Number);

    // Check for size
    if (SizeOfTag < AsciiCount) return NULL;

    // All seems Ok, allocate the container
    mlu = cmsMLUalloc(ContextID, 1);
    if (mlu == NULL) return NULL;

    // As many memory as size of tag
    Text = (char*) _cmsMalloc(ContextID, AsciiCount + 1);
    if (Text == NULL) goto Error;

    // Read it
    if (io ->Read(ContextID, io, Text, sizeof(char), AsciiCount) != AsciiCount) goto Error;
    SizeOfTag -= AsciiCount;

    // Make sure there is a terminator
    Text[AsciiCount] = 0;

    // Set the MLU entry. From here we can be tolerant to wrong types
    if (!cmsMLUsetASCII(ContextID, mlu, cmsNoLanguage, cmsNoCountry, Text)) goto Error;
    _cmsFree(ContextID, (void*) Text);
    Text = NULL;

    // Skip Unicode code
    if (SizeOfTag < 2* sizeof(cmsUInt32Number)) goto Done;
    if (!_cmsReadUInt32Number(ContextID, io, &UnicodeCode)) goto Done;
    if (!_cmsReadUInt32Number(ContextID, io, &UnicodeCount)) goto Done;
    SizeOfTag -= 2* sizeof(cmsUInt32Number);

    if (SizeOfTag < UnicodeCount*sizeof(cmsUInt16Number)) goto Done;

    for (i=0; i < UnicodeCount; i++) {
        if (!io ->Read(ContextID, io, &Dummy, sizeof(cmsUInt16Number), 1)) goto Done;
    }
    SizeOfTag -= UnicodeCount*sizeof(cmsUInt16Number);

    // Skip ScriptCode code if present. Some buggy profiles does have less
    // data that stricttly required. We need to skip it as this type may come
    // embedded in other types.

    if (SizeOfTag >= sizeof(cmsUInt16Number) + sizeof(cmsUInt8Number) + 67) {

        if (!_cmsReadUInt16Number(ContextID, io, &ScriptCodeCode)) goto Done;
        if (!_cmsReadUInt8Number(ContextID, io,  &ScriptCodeCount)) goto Done;

        // Skip rest of tag
        for (i=0; i < 67; i++) {
            if (!io ->Read(ContextID, io, &Dummy, sizeof(cmsUInt8Number), 1)) goto Error;
        }
    }

Done:

    *nItems = 1;
    return mlu;

Error:
    if (Text) _cmsFree(ContextID, (void*) Text);
    if (mlu) cmsMLUfree(ContextID, mlu);
    return NULL;
}