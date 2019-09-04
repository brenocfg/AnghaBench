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
struct TYPE_8__ {int /*<<< orphan*/  codepage; TYPE_1__* strings; } ;
typedef  TYPE_2__ string_table ;
typedef  enum StringPersistence { ____Placeholder_StringPersistence } StringPersistence ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  USHORT ;
typedef  size_t UINT ;
struct TYPE_7__ {scalar_t__ nonpersistent_refcount; scalar_t__ persistent_refcount; } ;
typedef  scalar_t__* LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,size_t,scalar_t__*,int) ; 
 int StringPersistent ; 
 int /*<<< orphan*/  debugstr_a (char const*) ; 
 scalar_t__* msi_alloc (int) ; 
 int /*<<< orphan*/  set_st_entry (TYPE_2__*,size_t,scalar_t__*,int,int /*<<< orphan*/ ,int) ; 
 size_t st_find_free_entry (TYPE_2__*) ; 
 scalar_t__ string2id (TYPE_2__*,char const*,size_t*) ; 

__attribute__((used)) static int add_string( string_table *st, UINT n, const char *data, UINT len, USHORT refcount, enum StringPersistence persistence )
{
    LPWSTR str;
    int sz;

    if( !data || !len )
        return 0;
    if( n > 0 )
    {
        if( st->strings[n].persistent_refcount ||
            st->strings[n].nonpersistent_refcount )
            return -1;
    }
    else
    {
        if (string2id( st, data, &n ) == ERROR_SUCCESS)
        {
            if (persistence == StringPersistent)
                st->strings[n].persistent_refcount += refcount;
            else
                st->strings[n].nonpersistent_refcount += refcount;
            return n;
        }
        n = st_find_free_entry( st );
        if( n == -1 )
            return -1;
    }

    if( n < 1 )
    {
        ERR("invalid index adding %s (%d)\n", debugstr_a( data ), n );
        return -1;
    }

    /* allocate a new string */
    sz = MultiByteToWideChar( st->codepage, 0, data, len, NULL, 0 );
    str = msi_alloc( (sz+1)*sizeof(WCHAR) );
    if( !str )
        return -1;
    MultiByteToWideChar( st->codepage, 0, data, len, str, sz );
    str[sz] = 0;

    set_st_entry( st, n, str, sz, refcount, persistence );
    return n;
}