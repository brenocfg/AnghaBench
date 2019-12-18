#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct _cms_typehandler_struct {int dummy; } ;
typedef  int cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsMLU ;
struct TYPE_12__ {int (* Tell ) (int /*<<< orphan*/ ,TYPE_1__*) ;} ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/ * cmsHANDLE ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
typedef  int /*<<< orphan*/  _cmsTagBase ;
struct TYPE_13__ {int /*<<< orphan*/  DisplayValue; int /*<<< orphan*/  DisplayName; int /*<<< orphan*/  Value; int /*<<< orphan*/  Name; } ;
typedef  TYPE_2__ _cmsDICarray ;

/* Variables and functions */
 int /*<<< orphan*/  AllocArray (int /*<<< orphan*/ ,TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeArray (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ReadOffsetArray (int /*<<< orphan*/ ,TYPE_1__*,TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  ReadOneMLUC (int /*<<< orphan*/ ,struct _cms_typehandler_struct*,TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ReadOneWChar (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _cmsReadUInt32Number (int /*<<< orphan*/ ,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  cmsDictAddEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsDictAlloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDictFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsERROR_CORRUPTION_DETECTED ; 
 int /*<<< orphan*/  cmsERROR_UNKNOWN_EXTENSION ; 
 int /*<<< orphan*/  cmsMLUfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsSignalError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static
void *Type_Dictionary_Read(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, cmsUInt32Number* nItems, cmsUInt32Number SizeOfTag)
{
   cmsHANDLE hDict;
   cmsUInt32Number i, Count, Length;
   cmsUInt32Number BaseOffset;
   _cmsDICarray a;
   wchar_t *NameWCS = NULL, *ValueWCS = NULL;
   cmsMLU *DisplayNameMLU = NULL, *DisplayValueMLU=NULL;
   cmsBool rc;

    *nItems = 0;

    // Get actual position as a basis for element offsets
    BaseOffset = io ->Tell(ContextID, io) - sizeof(_cmsTagBase);

    // Get name-value record count
    if (!_cmsReadUInt32Number(ContextID, io, &Count)) return NULL;
    SizeOfTag -= sizeof(cmsUInt32Number);

    // Get rec length
    if (!_cmsReadUInt32Number(ContextID, io, &Length)) return NULL;
    SizeOfTag -= sizeof(cmsUInt32Number);

    // Check for valid lengths
    if (Length != 16 && Length != 24 && Length != 32) {
         cmsSignalError(ContextID, cmsERROR_UNKNOWN_EXTENSION, "Unknown record length in dictionary '%d'", Length);
         return NULL;
    }

    // Creates an empty dictionary
    hDict = cmsDictAlloc(ContextID);
    if (hDict == NULL) return NULL;

    // On depending on record size, create column arrays
    if (!AllocArray(ContextID, &a, Count, Length)) goto Error;

    // Read column arrays
    if (!ReadOffsetArray(ContextID, io, &a, Count, Length, BaseOffset)) goto Error;

    // Seek to each element and read it
    for (i=0; i < Count; i++) {

        if (!ReadOneWChar(ContextID, io, &a.Name, i, &NameWCS)) goto Error;
        if (!ReadOneWChar(ContextID, io, &a.Value, i, &ValueWCS)) goto Error;

        if (Length > 16) {
            if (!ReadOneMLUC(ContextID, self, io, &a.DisplayName, i, &DisplayNameMLU)) goto Error;
        }

        if (Length > 24) {
            if (!ReadOneMLUC(ContextID, self, io, &a.DisplayValue, i, &DisplayValueMLU)) goto Error;
        }

        if (NameWCS == NULL || ValueWCS == NULL) {

            cmsSignalError(ContextID, cmsERROR_CORRUPTION_DETECTED, "Bad dictionary Name/Value");
            rc = FALSE;
        }
        else {

            rc = cmsDictAddEntry(ContextID, hDict, NameWCS, ValueWCS, DisplayNameMLU, DisplayValueMLU);
        }

        if (NameWCS != NULL) _cmsFree(ContextID, NameWCS);
        if (ValueWCS != NULL) _cmsFree(ContextID, ValueWCS);
        if (DisplayNameMLU != NULL) cmsMLUfree(ContextID, DisplayNameMLU);
        if (DisplayValueMLU != NULL) cmsMLUfree(ContextID, DisplayValueMLU);

        if (!rc) goto Error;
    }

   FreeArray(ContextID, &a);
   *nItems = 1;
   return (void*) hDict;

Error:
   FreeArray(ContextID, &a);
   cmsDictFree(ContextID, hDict);
   return NULL;
}