#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {int /*<<< orphan*/  pszVal; } ;
struct TYPE_6__ {TYPE_1__ u; int /*<<< orphan*/  vt; } ;
typedef  TYPE_2__ PROPVARIANT ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemAlloc (scalar_t__) ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PropVariantClear (TYPE_2__*) ; 
 scalar_t__ PropVariantToStringAlloc (TYPE_2__*,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  VT_LPSTR ; 
 int /*<<< orphan*/  VT_NULL ; 
 int /*<<< orphan*/  emptyW ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  topic ; 
 int /*<<< orphan*/  topicW ; 
 scalar_t__ wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_PropVariantToStringAlloc(void)
{
    PROPVARIANT prop;
    WCHAR *str;
    HRESULT hres;

    prop.vt = VT_NULL;
    hres = PropVariantToStringAlloc(&prop, &str);
    ok(hres == S_OK, "returned %x\n", hres);
    ok(!lstrcmpW(str, emptyW), "got %s\n", wine_dbgstr_w(str));
    CoTaskMemFree(str);

    prop.vt = VT_LPSTR;
    prop.u.pszVal = CoTaskMemAlloc(strlen(topic)+1);
    strcpy(prop.u.pszVal, topic);
    hres = PropVariantToStringAlloc(&prop, &str);
    ok(hres == S_OK, "returned %x\n", hres);
    ok(!lstrcmpW(str, topicW), "got %s\n", wine_dbgstr_w(str));
    CoTaskMemFree(str);
    PropVariantClear(&prop);
}