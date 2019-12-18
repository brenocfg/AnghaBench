#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wchar_t ;
typedef  size_t cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsUInt16Number ;
struct TYPE_7__ {int /*<<< orphan*/  (* Seek ) (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ;} ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_8__ {scalar_t__* Offsets; int* Sizes; } ;
typedef  TYPE_2__ _cmsDICelem ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ _cmsMallocZero (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  _cmsReadWCharArray (int /*<<< orphan*/ ,TYPE_1__*,size_t,scalar_t__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static
cmsBool ReadOneWChar(cmsContext ContextID, cmsIOHANDLER* io,  _cmsDICelem* e, cmsUInt32Number i, wchar_t ** wcstr)
{

    cmsUInt32Number nChars;

      // Special case for undefined strings (see ICC Votable
      // Proposal Submission, Dictionary Type and Metadata TAG Definition)
      if (e -> Offsets[i] == 0) {

          *wcstr = NULL;
          return TRUE;
      }

      if (!io -> Seek(ContextID, io, e -> Offsets[i])) return FALSE;

      nChars = e ->Sizes[i] / sizeof(cmsUInt16Number);


      *wcstr = (wchar_t*) _cmsMallocZero(ContextID, (nChars + 1) * sizeof(wchar_t));
      if (*wcstr == NULL) return FALSE;

      if (!_cmsReadWCharArray(ContextID, io, nChars, *wcstr)) {
          _cmsFree(ContextID, *wcstr);
          return FALSE;
      }

      // End of string marker
      (*wcstr)[nChars] = 0;
      return TRUE;
}