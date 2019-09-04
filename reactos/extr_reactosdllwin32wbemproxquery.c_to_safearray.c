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
struct array {int count; scalar_t__ ptr; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ VARTYPE ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  SAFEARRAY ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  CIMTYPE ;
typedef  void* BSTR ;

/* Variables and functions */
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * SafeArrayCreateVector (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SafeArrayDestroy (int /*<<< orphan*/ *) ; 
 scalar_t__ SafeArrayPutElement (int /*<<< orphan*/ *,int*,void*) ; 
 void* SysAllocString (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SysFreeString (void*) ; 
 scalar_t__ VT_BSTR ; 
 int get_type_size (int /*<<< orphan*/ ) ; 
 scalar_t__ to_vartype (int /*<<< orphan*/ ) ; 

SAFEARRAY *to_safearray( const struct array *array, CIMTYPE type )
{
    SAFEARRAY *ret;
    UINT size = get_type_size( type );
    VARTYPE vartype = to_vartype( type );
    LONG i;

    if (!array || !(ret = SafeArrayCreateVector( vartype, 0, array->count ))) return NULL;

    for (i = 0; i < array->count; i++)
    {
        void *ptr = (char *)array->ptr + i * size;
        if (vartype == VT_BSTR)
        {
            BSTR str = SysAllocString( *(const WCHAR **)ptr );
            if (!str || SafeArrayPutElement( ret, &i, str ) != S_OK)
            {
                SysFreeString( str );
                SafeArrayDestroy( ret );
                return NULL;
            }
            SysFreeString( str );
        }
        else if (SafeArrayPutElement( ret, &i, ptr ) != S_OK)
        {
            SafeArrayDestroy( ret );
            return NULL;
        }
    }
    return ret;
}