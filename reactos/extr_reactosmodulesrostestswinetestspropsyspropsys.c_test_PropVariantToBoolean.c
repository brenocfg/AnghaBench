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
struct TYPE_4__ {int boolVal; int lVal; char* pwszVal; char* pszVal; } ;
struct TYPE_5__ {TYPE_1__ u; void* vt; } ;
typedef  TYPE_2__ PROPVARIANT ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ DISP_E_TYPEMISMATCH ; 
 scalar_t__ FALSE ; 
 scalar_t__ PropVariantToBoolean (TYPE_2__*,scalar_t__*) ; 
 scalar_t__ S_OK ; 
 scalar_t__ TRUE ; 
 int VARIANT_FALSE ; 
 void* VARIANT_TRUE ; 
 void* VT_BOOL ; 
 void* VT_EMPTY ; 
 void* VT_I4 ; 
 void* VT_LPSTR ; 
 void* VT_LPWSTR ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_PropVariantToBoolean(void)
{
    static WCHAR str_0[] = {'0',0};
    static WCHAR str_1[] = {'1',0};
    static WCHAR str_7[] = {'7',0};
    static WCHAR str_n7[] = {'-','7',0};
    static WCHAR str_true[] = {'t','r','u','e',0};
    static WCHAR str_true2[] = {'#','T','R','U','E','#',0};
    static WCHAR str_true_case[] = {'t','R','U','e',0};
    static WCHAR str_false[] = {'f','a','l','s','e',0};
    static WCHAR str_false2[] = {'#','F','A','L','S','E','#',0};
    static WCHAR str_true_space[] = {'t','r','u','e',' ',0};
    static WCHAR str_yes[] = {'y','e','s',0};
    PROPVARIANT propvar;
    HRESULT hr;
    BOOL val;

    /* VT_BOOL */
    propvar.vt = VT_BOOL;
    propvar.u.boolVal = VARIANT_FALSE;
    val = TRUE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    ok(val == FALSE, "Unexpected value %d\n", val);

    propvar.vt = VT_BOOL;
    propvar.u.boolVal = 1;
    val = TRUE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    ok(val == FALSE, "Unexpected value %d\n", val);

    propvar.vt = VT_BOOL;
    propvar.u.boolVal = VARIANT_TRUE;
    val = FALSE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    ok(val == TRUE, "Unexpected value %d\n", val);

    /* VT_EMPTY */
    propvar.vt = VT_EMPTY;
    propvar.u.boolVal = VARIANT_TRUE;
    val = TRUE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    ok(val == FALSE, "Unexpected value %d\n", val);

    /* test integer conversion */
    propvar.vt = VT_I4;
    propvar.u.lVal = 0;
    val = TRUE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    ok(val == FALSE, "Unexpected value %d\n", val);

    propvar.vt = VT_I4;
    propvar.u.lVal = 1;
    val = FALSE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    ok(val == TRUE, "Unexpected value %d\n", val);

    propvar.vt = VT_I4;
    propvar.u.lVal = 67;
    val = FALSE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    ok(val == TRUE, "Unexpected value %d\n", val);

    propvar.vt = VT_I4;
    propvar.u.lVal = -67;
    val = FALSE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    ok(val == TRUE, "Unexpected value %d\n", val);

    /* test string conversion */
    propvar.vt = VT_LPWSTR;
    propvar.u.pwszVal = str_0;
    val = TRUE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    ok(val == FALSE, "Unexpected value %d\n", val);

    propvar.vt = VT_LPWSTR;
    propvar.u.pwszVal = str_1;
    val = FALSE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    ok(val == TRUE, "Unexpected value %d\n", val);

    propvar.vt = VT_LPWSTR;
    propvar.u.pwszVal = str_7;
    val = FALSE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    ok(val == TRUE, "Unexpected value %d\n", val);

    propvar.vt = VT_LPWSTR;
    propvar.u.pwszVal = str_n7;
    val = FALSE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    ok(val == TRUE, "Unexpected value %d\n", val);

    propvar.vt = VT_LPWSTR;
    propvar.u.pwszVal = str_true;
    val = FALSE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    ok(val == TRUE, "Unexpected value %d\n", val);

    propvar.vt = VT_LPWSTR;
    propvar.u.pwszVal = str_true_case;
    val = FALSE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    ok(val == TRUE, "Unexpected value %d\n", val);

    propvar.vt = VT_LPWSTR;
    propvar.u.pwszVal = str_true2;
    val = FALSE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    ok(val == TRUE, "Unexpected value %d\n", val);

    propvar.vt = VT_LPWSTR;
    propvar.u.pwszVal = str_false;
    val = TRUE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    ok(val == FALSE, "Unexpected value %d\n", val);

    propvar.vt = VT_LPWSTR;
    propvar.u.pwszVal = str_false2;
    val = TRUE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    ok(val == FALSE, "Unexpected value %d\n", val);

    propvar.vt = VT_LPWSTR;
    propvar.u.pwszVal = str_true_space;
    val = TRUE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == DISP_E_TYPEMISMATCH, "Unexpected hr %#x.\n", hr);
    ok(val == FALSE, "Unexpected value %d\n", val);

    propvar.vt = VT_LPWSTR;
    propvar.u.pwszVal = str_yes;
    val = TRUE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == DISP_E_TYPEMISMATCH, "Unexpected hr %#x.\n", hr);
    ok(val == FALSE, "Unexpected value %d\n", val);

    propvar.vt = VT_LPWSTR;
    propvar.u.pwszVal = NULL;
    val = TRUE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == DISP_E_TYPEMISMATCH, "Unexpected hr %#x.\n", hr);
    ok(val == FALSE, "Unexpected value %d\n", val);

    /* VT_LPSTR */
    propvar.vt = VT_LPSTR;
    propvar.u.pszVal = (char *)"#TruE#";
    val = TRUE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == DISP_E_TYPEMISMATCH, "Unexpected hr %#x.\n", hr);
    ok(val == FALSE, "Unexpected value %d\n", val);

    propvar.vt = VT_LPSTR;
    propvar.u.pszVal = (char *)"#TRUE#";
    val = FALSE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    ok(val == TRUE, "Unexpected value %d\n", val);

    propvar.vt = VT_LPSTR;
    propvar.u.pszVal = (char *)"tRUe";
    val = FALSE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    ok(val == TRUE, "Unexpected value %d\n", val);

    propvar.vt = VT_LPSTR;
    propvar.u.pszVal = (char *)"#FALSE#";
    val = TRUE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    ok(val == FALSE, "Unexpected value %d\n", val);

    propvar.vt = VT_LPSTR;
    propvar.u.pszVal = (char *)"fALSe";
    val = TRUE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    ok(val == FALSE, "Unexpected value %d\n", val);

    propvar.vt = VT_LPSTR;
    propvar.u.pszVal = (char *)"1";
    val = FALSE;
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    ok(val == TRUE, "Unexpected value %d\n", val);

    propvar.vt = VT_LPSTR;
    propvar.u.pszVal = (char *)"-1";
    hr = PropVariantToBoolean(&propvar, &val);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    ok(val == TRUE, "Unexpected value %d\n", val);
}