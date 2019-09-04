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
typedef  int WCHAR ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  size_t LONG ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int DWORD ;
typedef  int BSTR ;

/* Variables and functions */
 size_t ERROR_NO_MORE_ITEMS ; 
 size_t ERROR_SUCCESS ; 
 scalar_t__ E_OUTOFMEMORY ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 size_t RegEnumValueW (int /*<<< orphan*/ *,size_t,int*,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t RegOpenKeyExW (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 size_t RegQueryInfoKeyW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int SysAllocString (int*) ; 
 int /*<<< orphan*/  SysFreeString (int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VT_UI4 ; 
 int /*<<< orphan*/  debugstr_w (int const*) ; 
 int /*<<< orphan*/  free_bstr_array (int*,size_t) ; 
 int* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (int*) ; 
 int /*<<< orphan*/  set_variant (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ to_bstr_array (int*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ to_i4_array (int*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT enum_values( HKEY root, const WCHAR *subkey, VARIANT *names, VARIANT *types, VARIANT *retval )
{
    HKEY hkey = NULL;
    HRESULT hr = S_OK;
    BSTR *value_names = NULL;
    DWORD count, buflen, len, *value_types = NULL;
    LONG res, i = 0;
    WCHAR *buf = NULL;

    TRACE("%p, %s\n", root, debugstr_w(subkey));

    if ((res = RegOpenKeyExW( root, subkey, 0, KEY_QUERY_VALUE, &hkey ))) goto done;
    if ((res = RegQueryInfoKeyW( hkey, NULL, NULL, NULL, NULL, NULL, NULL, &count, &buflen, NULL, NULL, NULL )))
        goto done;

    hr = E_OUTOFMEMORY;
    if (!(buf = heap_alloc( (buflen + 1) * sizeof(WCHAR) ))) goto done;
    if (!(value_names = heap_alloc( count * sizeof(BSTR) ))) goto done;
    if (!(value_types = heap_alloc( count * sizeof(DWORD) ))) goto done;

    hr = S_OK;
    for (;;)
    {
        len = buflen + 1;
        res = RegEnumValueW( hkey, i, buf, &len, NULL, &value_types[i], NULL, NULL );
        if (res == ERROR_NO_MORE_ITEMS)
        {
            if (i) res = ERROR_SUCCESS;
            break;
        }
        if (res) break;
        if (!(value_names[i] = SysAllocString( buf )))
        {
            for (i--; i >= 0; i--) SysFreeString( value_names[i] );
            hr = E_OUTOFMEMORY;
            break;
        }
        i++;
    }
    if (hr == S_OK && !res)
    {
        hr = to_bstr_array( value_names, i, names );
        free_bstr_array( value_names, i );
        if (hr == S_OK) hr = to_i4_array( value_types, i, types );
    }

done:
    set_variant( VT_UI4, res, NULL, retval );
    RegCloseKey( hkey );
    heap_free( value_names );
    heap_free( value_types );
    heap_free( buf );
    return hr;
}