#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  int cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  scalar_t__ cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 scalar_t__ _cmsCalloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  _cmsReadUInt32Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (struct _cms_typehandler_struct*) ; 

__attribute__((used)) static
void *Type_U16Fixed16_Read(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, cmsUInt32Number* nItems, cmsUInt32Number SizeOfTag)
{
    cmsFloat64Number*  array_double;
    cmsUInt32Number v;
    cmsUInt32Number i, n;
    cmsUNUSED_PARAMETER(self);

    *nItems = 0;
    n = SizeOfTag / sizeof(cmsUInt32Number);
    array_double = (cmsFloat64Number*) _cmsCalloc(ContextID, n, sizeof(cmsFloat64Number));
    if (array_double == NULL) return NULL;

    for (i=0; i < n; i++) {

        if (!_cmsReadUInt32Number(ContextID, io, &v)) {
            _cmsFree(ContextID, (void*) array_double);
            return NULL;
        }

        // Convert to cmsFloat64Number
        array_double[i] =  (cmsFloat64Number) (v / 65536.0);
    }

    *nItems = n;
    return (void*) array_double;
}