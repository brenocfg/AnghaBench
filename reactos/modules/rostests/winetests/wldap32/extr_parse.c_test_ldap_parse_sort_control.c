#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct l_timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  unsigned int ULONG ;
struct TYPE_3__ {char* sk_attrtype; int /*<<< orphan*/  sk_reverseorder; int /*<<< orphan*/ * sk_matchruleoid; } ;
typedef  TYPE_1__ LDAPSortKeyA ;
typedef  int /*<<< orphan*/  LDAPMessage ;
typedef  int /*<<< orphan*/  LDAPControlA ;
typedef  int /*<<< orphan*/  LDAP ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 unsigned int LDAP_CONTROL_NOT_FOUND ; 
 unsigned int LDAP_PARAM_ERROR ; 
 int /*<<< orphan*/  LDAP_SCOPE_ONELEVEL ; 
 unsigned int LDAP_SERVER_DOWN ; 
 unsigned int LDAP_TIMEOUT ; 
 int /*<<< orphan*/  ldap_control_freeA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldap_controls_freeA (int /*<<< orphan*/ **) ; 
 unsigned int ldap_create_sort_controlA (int /*<<< orphan*/ *,TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 unsigned int ldap_parse_resultA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ***,int) ; 
 unsigned int ldap_parse_sort_controlA (int /*<<< orphan*/ *,int /*<<< orphan*/ **,unsigned int*,int /*<<< orphan*/ *) ; 
 unsigned int ldap_search_ext_sA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,struct l_timeval*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_ldap_parse_sort_control( LDAP *ld )
{
    ULONG ret, result;
    LDAPSortKeyA *sortkeys[2], key;
    LDAPControlA *sort, *ctrls[2], **server_ctrls;
    LDAPMessage *res = NULL;
    struct l_timeval timeout;

    key.sk_attrtype = (char *)"ou";
    key.sk_matchruleoid = NULL;
    key.sk_reverseorder = FALSE;

    sortkeys[0] = &key;
    sortkeys[1] = NULL;
    ret = ldap_create_sort_controlA( ld, sortkeys, 0, &sort );
    ok( !ret, "ldap_create_sort_controlA failed 0x%x\n", ret );

    ctrls[0] = sort;
    ctrls[1] = NULL;
    timeout.tv_sec = 20;
    timeout.tv_usec = 0;
    ret = ldap_search_ext_sA( ld, (char *)"", LDAP_SCOPE_ONELEVEL, (char *)"(ou=*)", NULL, 0, ctrls, NULL, &timeout, 10, &res );
    if (ret == LDAP_SERVER_DOWN || ret == LDAP_TIMEOUT)
    {
        skip("test server can't be reached\n");
        ldap_control_freeA( sort );
        return;
    }
    ok( !ret, "ldap_search_ext_sA failed 0x%x\n", ret );
    ok( res != NULL, "expected res != NULL\n" );

    if (GetProcAddress(GetModuleHandleA("wldap32.dll"), "ber_init"))
    {
        ret = ldap_parse_resultA( NULL, res, &result, NULL, NULL, NULL, &server_ctrls, 1 );
        ok( ret == LDAP_PARAM_ERROR, "ldap_parse_resultA failed 0x%x\n", ret );
    }
    else
        win_skip("Test would crash on older wldap32 versions\n");

    result = ~0u;
    ret = ldap_parse_resultA( ld, res, &result, NULL, NULL, NULL, &server_ctrls, 1 );
    ok( !ret, "ldap_parse_resultA failed 0x%x\n", ret );
    ok( !result, "got 0x%x expected 0\n", result );

    ret = ldap_parse_sort_controlA( NULL, NULL, NULL, NULL );
    ok( ret == LDAP_PARAM_ERROR, "ldap_parse_sort_controlA failed 0x%d\n", ret );

    ret = ldap_parse_sort_controlA( ld, NULL, NULL, NULL );
    ok( ret == LDAP_CONTROL_NOT_FOUND, "ldap_parse_sort_controlA failed 0x%x\n", ret );

    ret = ldap_parse_sort_controlA( ld, NULL, &result, NULL );
    ok( ret == LDAP_CONTROL_NOT_FOUND, "ldap_parse_sort_controlA failed 0x%x\n", ret );

    ret = ldap_parse_sort_controlA( ld, server_ctrls, &result, NULL );
    ok( ret == LDAP_CONTROL_NOT_FOUND, "ldap_parse_sort_controlA failed 0x%x\n", ret );

    ldap_control_freeA( sort );
    ldap_controls_freeA( server_ctrls );
}