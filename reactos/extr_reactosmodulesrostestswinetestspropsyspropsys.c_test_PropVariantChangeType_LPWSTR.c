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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_7__ {void* pwszVal; void* pszVal; } ;
struct TYPE_8__ {scalar_t__ vt; TYPE_1__ u; } ;
typedef  TYPE_2__ PROPVARIANT ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 void* CoTaskMemAlloc (int) ; 
 scalar_t__ PropVariantChangeType (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PropVariantClear (TYPE_2__*) ; 
 int /*<<< orphan*/  PropVariantInit (TYPE_2__*) ; 
 scalar_t__ S_OK ; 
 scalar_t__ VT_LPSTR ; 
 scalar_t__ VT_LPWSTR ; 
 scalar_t__ VT_NULL ; 
 int /*<<< orphan*/  emptyW ; 
 int /*<<< orphan*/  lstrcmpW (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyW (void*,int /*<<< orphan*/ ) ; 
 int lstrlenW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (void*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  topic ; 
 int /*<<< orphan*/  topicW ; 
 scalar_t__ wine_dbgstr_w (void*) ; 

__attribute__((used)) static void test_PropVariantChangeType_LPWSTR(void)
{
    PROPVARIANT dest, src;
    HRESULT hr;

    PropVariantInit(&dest);

    src.vt = VT_NULL;
    hr = PropVariantChangeType(&dest, &src, 0, VT_LPWSTR);
    ok(hr == S_OK, "hr=%x\n", hr);
    ok(dest.vt == VT_LPWSTR, "got %d\n", dest.vt);
    ok(!lstrcmpW(dest.u.pwszVal, emptyW), "got %s\n", wine_dbgstr_w(dest.u.pwszVal));
    PropVariantClear(&dest);
    PropVariantClear(&src);

    src.vt = VT_LPSTR;
    src.u.pszVal = CoTaskMemAlloc(strlen(topic)+1);
    strcpy(src.u.pszVal, topic);
    hr = PropVariantChangeType(&dest, &src, 0, VT_LPWSTR);
    ok(hr == S_OK, "hr=%x\n", hr);
    ok(dest.vt == VT_LPWSTR, "got %d\n", dest.vt);
    ok(!lstrcmpW(dest.u.pwszVal, topicW), "got %s\n", wine_dbgstr_w(dest.u.pwszVal));
    PropVariantClear(&dest);
    PropVariantClear(&src);

    src.vt = VT_LPWSTR;
    src.u.pwszVal = CoTaskMemAlloc( (lstrlenW(topicW)+1) * sizeof(WCHAR));
    lstrcpyW(src.u.pwszVal, topicW);
    hr = PropVariantChangeType(&dest, &src, 0, VT_LPWSTR);
    ok(hr == S_OK, "hr=%x\n", hr);
    ok(dest.vt == VT_LPWSTR, "got %d\n", dest.vt);
    ok(!lstrcmpW(dest.u.pwszVal, topicW), "got %s\n", wine_dbgstr_w(dest.u.pwszVal));
    PropVariantClear(&dest);
    PropVariantClear(&src);
}