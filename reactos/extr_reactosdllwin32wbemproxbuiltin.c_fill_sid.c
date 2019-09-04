#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct table {int num_rows; scalar_t__ data; } ;
struct record_sid {int /*<<< orphan*/  sidlength; int /*<<< orphan*/  sid; int /*<<< orphan*/  referenceddomainname; int /*<<< orphan*/  binaryrepresentation; int /*<<< orphan*/  accountname; } ;
struct expr {int dummy; } ;
typedef  enum fill_status { ____Placeholder_fill_status } fill_status ;
typedef  int /*<<< orphan*/  attrs ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int Length; } ;
typedef  int /*<<< orphan*/  PSID ;
typedef  int /*<<< orphan*/  LSA_TRANSLATED_NAME ;
typedef  int /*<<< orphan*/  LSA_REFERENCED_DOMAIN_LIST ;
typedef  TYPE_1__ LSA_OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  LSA_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertStringSidToSidW (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int FILL_STATUS_FAILED ; 
 int FILL_STATUS_FILTERED ; 
 int /*<<< orphan*/  GetLengthSid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LsaClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LsaFreeMemory (int /*<<< orphan*/ *) ; 
 scalar_t__ LsaLookupSids (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ LsaOpenPolicy (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  POLICY_ALL_ACCESS ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/ * find_sid_str (struct expr const*) ; 
 int /*<<< orphan*/  get_accountname (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_binaryrepresentation (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_referenceddomainname (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_strdupW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resize_table (struct table*,int,int) ; 

__attribute__((used)) static enum fill_status fill_sid( struct table *table, const struct expr *cond )
{
    PSID sid;
    LSA_REFERENCED_DOMAIN_LIST *domain;
    LSA_TRANSLATED_NAME *name;
    LSA_HANDLE handle;
    LSA_OBJECT_ATTRIBUTES attrs;
    const WCHAR *str;
    struct record_sid *rec;
    UINT len;

    if (!(str = find_sid_str( cond ))) return FILL_STATUS_FAILED;
    if (!resize_table( table, 1, sizeof(*rec) )) return FILL_STATUS_FAILED;

    if (!ConvertStringSidToSidW( str, &sid )) return FILL_STATUS_FAILED;
    len = GetLengthSid( sid );

    memset( &attrs, 0, sizeof(attrs) );
    attrs.Length = sizeof(attrs);
    if (LsaOpenPolicy( NULL, &attrs, POLICY_ALL_ACCESS, &handle ))
    {
        LocalFree( sid );
        return FILL_STATUS_FAILED;
    }
    if (LsaLookupSids( handle, 1, &sid, &domain, &name ))
    {
        LocalFree( sid );
        LsaClose( handle );
        return FILL_STATUS_FAILED;
    }

    rec = (struct record_sid *)table->data;
    rec->accountname            = get_accountname( name );
    rec->binaryrepresentation   = get_binaryrepresentation( sid, len );
    rec->referenceddomainname   = get_referenceddomainname( domain );
    rec->sid                    = heap_strdupW( str );
    rec->sidlength              = len;

    TRACE("created 1 row\n");
    table->num_rows = 1;

    LsaFreeMemory( domain );
    LsaFreeMemory( name );
    LocalFree( sid );
    LsaClose( handle );
    return FILL_STATUS_FILTERED;
}