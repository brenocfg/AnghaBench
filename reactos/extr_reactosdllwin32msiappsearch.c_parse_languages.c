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
typedef  scalar_t__ WCHAR ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  LANGID ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  atoiW (scalar_t__*) ; 
 int /*<<< orphan*/ * msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (scalar_t__*) ; 
 scalar_t__* strchrW (scalar_t__*,char) ; 
 scalar_t__* strdupW (scalar_t__ const*) ; 

__attribute__((used)) static LANGID *parse_languages( const WCHAR *languages, DWORD *num_ids )
{
    UINT i, count = 1;
    WCHAR *str = strdupW( languages ), *p, *q;
    LANGID *ret;

    if (!str) return NULL;
    for (p = q = str; (q = strchrW( q, ',' )); q++) count++;

    if (!(ret = msi_alloc( count * sizeof(LANGID) )))
    {
        msi_free( str );
        return NULL;
    }
    i = 0;
    while (*p)
    {
        q = strchrW( p, ',' );
        if (q) *q = 0;
        ret[i] = atoiW( p );
        if (!q) break;
        p = q + 1;
        i++;
    }
    msi_free( str );
    *num_ids = count;
    return ret;
}