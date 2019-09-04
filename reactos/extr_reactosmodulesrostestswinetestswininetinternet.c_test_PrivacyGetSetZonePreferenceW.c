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
typedef  int /*<<< orphan*/  pref ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int PRIVACY_TEMPLATE_ADVANCED ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int pPrivacyGetZonePreferenceW (int,int,int*,int /*<<< orphan*/ *,int*) ; 
 int pPrivacySetZonePreferenceW (int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (char*,int) ; 

__attribute__((used)) static void test_PrivacyGetSetZonePreferenceW(void)
{
    DWORD ret, zone, type, template, old_template, pref_size = 0;
    WCHAR pref[256];

    zone = 3;
    type = 0;
    ret = pPrivacyGetZonePreferenceW(zone, type, NULL, NULL, NULL);
    ok(ret == 0, "expected ret == 0, got %u\n", ret);

    old_template = 0;
    ret = pPrivacyGetZonePreferenceW(zone, type, &old_template, NULL, NULL);
    ok(ret == 0, "expected ret == 0, got %u\n", ret);

    trace("template %u\n", old_template);

    if(old_template == PRIVACY_TEMPLATE_ADVANCED) {
        pref_size = sizeof(pref)/sizeof(WCHAR);
        ret = pPrivacyGetZonePreferenceW(zone, type, &old_template, pref, &pref_size);
        ok(ret == 0, "expected ret == 0, got %u\n", ret);
    }

    template = 5;
    ret = pPrivacySetZonePreferenceW(zone, type, template, NULL);
    ok(ret == 0, "expected ret == 0, got %u\n", ret);

    template = 0;
    ret = pPrivacyGetZonePreferenceW(zone, type, &template, NULL, NULL);
    ok(ret == 0, "expected ret == 0, got %u\n", ret);
    ok(template == 5, "expected template == 5, got %u\n", template);

    template = 5;
    ret = pPrivacySetZonePreferenceW(zone, type, old_template, pref_size ? pref : NULL);
    ok(ret == 0, "expected ret == 0, got %u\n", ret);
}