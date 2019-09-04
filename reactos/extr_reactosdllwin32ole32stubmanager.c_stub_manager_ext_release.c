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
struct stub_manager {scalar_t__ extrefs; scalar_t__ weakrefs; scalar_t__ extern_conn; int /*<<< orphan*/  oid; int /*<<< orphan*/  lock; } ;
typedef  scalar_t__ ULONG ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EXTCONN_STRONG ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IExternalConnection_ReleaseConnection (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,struct stub_manager*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub_manager_int_release (struct stub_manager*) ; 
 int /*<<< orphan*/  wine_dbgstr_longlong (int /*<<< orphan*/ ) ; 

ULONG stub_manager_ext_release(struct stub_manager *m, ULONG refs, BOOL tableweak, BOOL last_unlock_releases)
{
    BOOL last_extern_ref;
    ULONG rc;

    EnterCriticalSection(&m->lock);

    /* make sure we don't underflow extrefs */
    refs = min(refs, m->extrefs);
    rc = (m->extrefs -= refs);

    if (tableweak)
        --m->weakrefs;
    if (!last_unlock_releases)
        rc += m->weakrefs;

    last_extern_ref = refs && !m->extrefs;

    LeaveCriticalSection(&m->lock);
    
    TRACE("removed %u refs from %p (oid %s), rc is now %u\n", refs, m, wine_dbgstr_longlong(m->oid), rc);

    if (last_extern_ref && m->extern_conn)
        IExternalConnection_ReleaseConnection(m->extern_conn, EXTCONN_STRONG, 0, last_unlock_releases);

    if (rc == 0)
        if (!(m->extern_conn && last_unlock_releases && m->weakrefs))
            stub_manager_int_release(m);

    return rc;
}