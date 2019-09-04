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
struct stub_manager {int /*<<< orphan*/  lock; scalar_t__ norm_refs; } ;
struct ifstub {int flags; } ;
typedef  int /*<<< orphan*/  IPID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int MSHLFLAGS_NORMAL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/  const*) ; 
 struct ifstub* stub_manager_ipid_to_ifstub (struct stub_manager*,int /*<<< orphan*/  const*) ; 

BOOL stub_manager_notify_unmarshal(struct stub_manager *m, const IPID *ipid)
{
    BOOL ret = TRUE;
    struct ifstub *ifstub;

    if (!(ifstub = stub_manager_ipid_to_ifstub(m, ipid)))
    {
        ERR("attempted unmarshal of unknown IPID %s\n", debugstr_guid(ipid));
        return FALSE;
    }

    EnterCriticalSection(&m->lock);

    /* track normal marshals so we can enforce rules whilst in-process */
    if (ifstub->flags & MSHLFLAGS_NORMAL)
    {
        if (m->norm_refs)
            m->norm_refs--;
        else
        {
            ERR("attempted invalid normal unmarshal, norm_refs is zero\n");
            ret = FALSE;
        }
    }

    LeaveCriticalSection(&m->lock);

    return ret;
}