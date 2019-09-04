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
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  SAFEARRAY ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SafeArrayAccessData (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * SafeArrayCreateVector (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SafeArrayDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SafeArrayUnaccessData (int /*<<< orphan*/ *) ; 
 int VT_ARRAY ; 
 int VT_UI1 ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_variant (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT to_byte_array( void *data, DWORD size, VARIANT *var )
{
    SAFEARRAY *sa;
    void *sadata;
    HRESULT hr;

    if (!(sa = SafeArrayCreateVector( VT_UI1, 0, size ))) return E_OUTOFMEMORY;

    hr = SafeArrayAccessData( sa, &sadata );

    if (SUCCEEDED(hr))
    {
        memcpy( sadata, data, size );

        SafeArrayUnaccessData( sa );
    }
    else
    {
        SafeArrayDestroy( sa );
        return hr;
    }

    set_variant( VT_UI1|VT_ARRAY, 0, sa, var );
    return S_OK;
}