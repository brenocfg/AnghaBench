#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_4__ {int lVal; char* pwszVal; char* pszVal; int /*<<< orphan*/ * bstrVal; int /*<<< orphan*/  boolVal; } ;
struct TYPE_5__ {TYPE_1__ u; void* vt; } ;
typedef  TYPE_2__ PROPVARIANT ;
typedef  char* LPCWSTR ;
typedef  char CHAR ;

/* Variables and functions */
 char* PropVariantToStringWithDefault (TYPE_2__*,char*) ; 
 void* SysAllocString (char*) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARIANT_TRUE ; 
 void* VT_BOOL ; 
 void* VT_BSTR ; 
 void* VT_EMPTY ; 
 void* VT_I4 ; 
 void* VT_LPSTR ; 
 void* VT_LPWSTR ; 
 void* VT_NULL ; 
 int /*<<< orphan*/  lstrcmpW (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_PropVariantToStringWithDefault(void)
{
    PROPVARIANT propvar;
    static WCHAR default_value[] = {'t', 'e', 's', 't', 0};
    static WCHAR wstr_test2[] =  {'t', 'e', 's', 't', '2', 0};
    static WCHAR wstr_empty[] = {0};
    static WCHAR wstr_space[] = {' ', 0};
    static CHAR str_test2[] =  "test2";
    static CHAR str_empty[] = "";
    static CHAR str_space[] = " ";
    LPCWSTR result;

    propvar.vt = VT_EMPTY;
    result = PropVariantToStringWithDefault(&propvar, default_value);
    ok(result == default_value, "Unexpected value %s\n", wine_dbgstr_w(result));

    propvar.vt = VT_NULL;
    result = PropVariantToStringWithDefault(&propvar, default_value);
    ok(result == default_value, "Unexpected value %s\n", wine_dbgstr_w(result));

    propvar.vt = VT_BOOL;
    propvar.u.boolVal = VARIANT_TRUE;
    result = PropVariantToStringWithDefault(&propvar, default_value);
    ok(result == default_value, "Unexpected value %s\n", wine_dbgstr_w(result));

    propvar.vt = VT_I4;
    propvar.u.lVal = 15;
    result = PropVariantToStringWithDefault(&propvar, default_value);
    ok(result == default_value, "Unexpected value %s\n", wine_dbgstr_w(result));

    /* VT_LPWSTR */

    propvar.vt = VT_LPWSTR;
    propvar.u.pwszVal = NULL;
    result = PropVariantToStringWithDefault(&propvar, default_value);
    ok(result == default_value, "Unexpected value %s\n", wine_dbgstr_w(result));

    propvar.vt = VT_LPWSTR;
    propvar.u.pwszVal = wstr_empty;
    result = PropVariantToStringWithDefault(&propvar, default_value);
    ok(result == wstr_empty, "Unexpected value %s\n", wine_dbgstr_w(result));

    propvar.vt = VT_LPWSTR;
    propvar.u.pwszVal = wstr_space;
    result = PropVariantToStringWithDefault(&propvar, default_value);
    ok(result == wstr_space, "Unexpected value %s\n", wine_dbgstr_w(result));

    propvar.vt = VT_LPWSTR;
    propvar.u.pwszVal = wstr_test2;
    result = PropVariantToStringWithDefault(&propvar, default_value);
    ok(result == wstr_test2, "Unexpected value %s\n", wine_dbgstr_w(result));

    /* VT_LPSTR */

    propvar.vt = VT_LPSTR;
    propvar.u.pszVal = NULL;
    result = PropVariantToStringWithDefault(&propvar, default_value);
    ok(result == default_value, "Unexpected value %s\n", wine_dbgstr_w(result));

    propvar.vt = VT_LPSTR;
    propvar.u.pszVal = str_empty;
    result = PropVariantToStringWithDefault(&propvar, default_value);
    ok(result == default_value, "Unexpected value %s\n", wine_dbgstr_w(result));

    propvar.vt = VT_LPSTR;
    propvar.u.pszVal = str_space;
    result = PropVariantToStringWithDefault(&propvar, default_value);
    ok(result == default_value, "Unexpected value %s\n", wine_dbgstr_w(result));

    propvar.vt = VT_LPSTR;
    propvar.u.pszVal = str_test2;
    result = PropVariantToStringWithDefault(&propvar, default_value);
    ok(result == default_value, "Unexpected value %s\n", wine_dbgstr_w(result));

    /* VT_BSTR */

    propvar.vt = VT_BSTR;
    propvar.u.bstrVal = NULL;
    result = PropVariantToStringWithDefault(&propvar, default_value);
    ok(!lstrcmpW(result, wstr_empty), "Unexpected value %s\n", wine_dbgstr_w(result));

    propvar.vt = VT_BSTR;
    propvar.u.bstrVal = SysAllocString(wstr_empty);
    result = PropVariantToStringWithDefault(&propvar, default_value);
    ok(!lstrcmpW(result, wstr_empty), "Unexpected value %s\n", wine_dbgstr_w(result));
    SysFreeString(propvar.u.bstrVal);

    propvar.vt = VT_BSTR;
    propvar.u.bstrVal = SysAllocString(wstr_space);
    result = PropVariantToStringWithDefault(&propvar, default_value);
    ok(!lstrcmpW(result, wstr_space), "Unexpected value %s\n", wine_dbgstr_w(result));
    SysFreeString(propvar.u.bstrVal);

    propvar.vt = VT_BSTR;
    propvar.u.bstrVal = SysAllocString(wstr_test2);
    result = PropVariantToStringWithDefault(&propvar, default_value);
    ok(!lstrcmpW(result, wstr_test2), "Unexpected value %s\n", wine_dbgstr_w(result));
    SysFreeString(propvar.u.bstrVal);
}