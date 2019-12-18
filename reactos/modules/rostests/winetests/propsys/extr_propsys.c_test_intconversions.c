#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int USHORT ;
typedef  int ULONGLONG ;
typedef  int ULONG ;
struct TYPE_13__ {int QuadPart; } ;
struct TYPE_12__ {int QuadPart; } ;
struct TYPE_14__ {int ulVal; int lVal; int uiVal; int iVal; TYPE_2__ hVal; TYPE_1__ uhVal; } ;
struct TYPE_15__ {int vt; TYPE_3__ u; } ;
typedef  int SHORT ;
typedef  TYPE_4__ PROPVARIANT ;
typedef  int LONGLONG ;
typedef  int LONG ;
typedef  int HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_ARITHMETIC_OVERFLOW ; 
 int /*<<< orphan*/  FAILED (int) ; 
 int HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int PropVariantClear (TYPE_4__*) ; 
 int PropVariantToInt16 (TYPE_4__*,int*) ; 
 int PropVariantToInt32 (TYPE_4__*,int*) ; 
 int PropVariantToInt64 (TYPE_4__*,int*) ; 
 int PropVariantToUInt16 (TYPE_4__*,int*) ; 
 int PropVariantToUInt32 (TYPE_4__*,int*) ; 
 int PropVariantToUInt64 (TYPE_4__*,int*) ; 
 int S_OK ; 
 int VT_I2 ; 
 int VT_I4 ; 
 void* VT_I8 ; 
 int VT_UI2 ; 
 int VT_UI4 ; 
 int VT_UI8 ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int wine_dbgstr_longlong (int) ; 

__attribute__((used)) static void test_intconversions(void)
{
    PROPVARIANT propvar;
    SHORT sval;
    USHORT usval;
    LONG lval;
    ULONG ulval;
    LONGLONG llval;
    ULONGLONG ullval;
    HRESULT hr;

    propvar.vt = 0xdead;
    hr = PropVariantClear(&propvar);
    ok (FAILED(hr), "PropVariantClear fails on invalid vt.\n");

    propvar.vt = VT_I8;
    PropVariantClear(&propvar);

    propvar.vt = VT_I8;
    propvar.u.hVal.QuadPart = (ULONGLONG)1 << 63;

    hr = PropVariantToInt64(&propvar, &llval);
    ok(hr == S_OK, "hr=%x\n", hr);
    ok(llval == (ULONGLONG)1 << 63, "got wrong value %s\n", wine_dbgstr_longlong(llval));

    hr = PropVariantToUInt64(&propvar, &ullval);
    ok(hr == HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW), "hr=%x\n", hr);

    hr = PropVariantToInt32(&propvar, &lval);
    ok(hr == HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW), "hr=%x\n", hr);

    hr = PropVariantToUInt32(&propvar, &ulval);
    ok(hr == HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW), "hr=%x\n", hr);

    hr = PropVariantToInt16(&propvar, &sval);
    ok(hr == HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW), "hr=%x\n", hr);

    hr = PropVariantToUInt16(&propvar, &usval);
    ok(hr == HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW), "hr=%x\n", hr);

    propvar.vt = VT_UI8;
    propvar.u.uhVal.QuadPart = 5;

    hr = PropVariantToInt64(&propvar, &llval);
    ok(hr == S_OK, "hr=%x\n", hr);
    ok(llval == 5, "got wrong value %s\n", wine_dbgstr_longlong(llval));

    hr = PropVariantToUInt64(&propvar, &ullval);
    ok(hr == S_OK, "hr=%x\n", hr);
    ok(ullval == 5, "got wrong value %s\n", wine_dbgstr_longlong(ullval));

    hr = PropVariantToInt32(&propvar, &lval);
    ok(hr == S_OK, "hr=%x\n", hr);
    ok(lval == 5, "got wrong value %d\n", lval);

    hr = PropVariantToUInt32(&propvar, &ulval);
    ok(hr == S_OK, "hr=%x\n", hr);
    ok(ulval == 5, "got wrong value %d\n", ulval);

    hr = PropVariantToInt16(&propvar, &sval);
    ok(hr == S_OK, "hr=%x\n", hr);
    ok(sval == 5, "got wrong value %d\n", sval);

    hr = PropVariantToUInt16(&propvar, &usval);
    ok(hr == S_OK, "hr=%x\n", hr);
    ok(usval == 5, "got wrong value %d\n", usval);

    propvar.vt = VT_I8;
    propvar.u.hVal.QuadPart = -5;

    hr = PropVariantToInt64(&propvar, &llval);
    ok(hr == S_OK, "hr=%x\n", hr);
    ok(llval == -5, "got wrong value %s\n", wine_dbgstr_longlong(llval));

    hr = PropVariantToUInt64(&propvar, &ullval);
    ok(hr == HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW), "hr=%x\n", hr);

    hr = PropVariantToInt32(&propvar, &lval);
    ok(hr == S_OK, "hr=%x\n", hr);
    ok(lval == -5, "got wrong value %d\n", lval);

    hr = PropVariantToUInt32(&propvar, &ulval);
    ok(hr == HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW), "hr=%x\n", hr);

    hr = PropVariantToInt16(&propvar, &sval);
    ok(hr == S_OK, "hr=%x\n", hr);
    ok(sval == -5, "got wrong value %d\n", sval);

    hr = PropVariantToUInt16(&propvar, &usval);
    ok(hr == HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW), "hr=%x\n", hr);

    propvar.vt = VT_UI4;
    propvar.u.ulVal = 6;

    hr = PropVariantToInt64(&propvar, &llval);
    ok(hr == S_OK, "hr=%x\n", hr);
    ok(llval == 6, "got wrong value %s\n", wine_dbgstr_longlong(llval));

    propvar.vt = VT_I4;
    propvar.u.lVal = -6;

    hr = PropVariantToInt64(&propvar, &llval);
    ok(hr == S_OK, "hr=%x\n", hr);
    ok(llval == -6, "got wrong value %s\n", wine_dbgstr_longlong(llval));

    propvar.vt = VT_UI2;
    propvar.u.uiVal = 7;

    hr = PropVariantToInt64(&propvar, &llval);
    ok(hr == S_OK, "hr=%x\n", hr);
    ok(llval == 7, "got wrong value %s\n", wine_dbgstr_longlong(llval));

    propvar.vt = VT_I2;
    propvar.u.iVal = -7;

    hr = PropVariantToInt64(&propvar, &llval);
    ok(hr == S_OK, "hr=%x\n", hr);
    ok(llval == -7, "got wrong value %s\n", wine_dbgstr_longlong(llval));
}