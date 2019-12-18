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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_7__ {struct TYPE_7__* data; struct TYPE_7__* next; } ;
typedef  TYPE_1__ session_descriptor_t ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; int /*<<< orphan*/  session_count; TYPE_1__* first; struct TYPE_8__* next; } ;
typedef  TYPE_2__ sap_address_t ;

/* Variables and functions */
 int /*<<< orphan*/  AddressDestroy (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* sap_addrs ; 
 int /*<<< orphan*/  sap_mutex ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void sout_AnnounceUnRegister (vlc_object_t *obj, session_descriptor_t *session)
{
    sap_address_t *addr, **paddr;
    session_descriptor_t **psession;

    msg_Dbg (obj, "removing SAP session");
    vlc_mutex_lock (&sap_mutex);
    paddr = &sap_addrs;
    for (;;)
    {
        addr = *paddr;
        assert (addr != NULL);

        psession = &addr->first;
        vlc_mutex_lock (&addr->lock);
        while (*psession != NULL)
        {
            if (*psession == session)
                goto found;
            psession = &(*psession)->next;
        }
        vlc_mutex_unlock (&addr->lock);
        paddr = &addr->next;
    }

found:
    *psession = session->next;

    if (addr->first == NULL)
        /* Last session for this address -> unlink the address */
        *paddr = addr->next;
    vlc_mutex_unlock (&sap_mutex);

    if (addr->first == NULL)
    {
        /* Last session for this address -> unlink the address */
        vlc_mutex_unlock (&addr->lock);
        AddressDestroy (addr);
    }
    else
    {
        addr->session_count--;
        vlc_cond_signal (&addr->wait);
        vlc_mutex_unlock (&addr->lock);
    }

    free(session->data);
    free(session);
}