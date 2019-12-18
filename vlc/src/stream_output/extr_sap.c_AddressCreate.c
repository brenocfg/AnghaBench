#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct sockaddr {int dummy; } ;
struct TYPE_6__ {int fd; int origlen; int /*<<< orphan*/  thread; int /*<<< orphan*/ * first; scalar_t__ session_count; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  interval; int /*<<< orphan*/  orig; int /*<<< orphan*/  group; } ;
typedef  TYPE_1__ sap_address_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPPORT_SAP ; 
 int /*<<< orphan*/  RunThread ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_LOW ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  getsockname (int,struct sockaddr*,int*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  net_Close (int) ; 
 int net_ConnectUDP (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  var_CreateGetInteger (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static sap_address_t *AddressCreate (vlc_object_t *obj, const char *group)
{
    int fd = net_ConnectUDP (obj, group, IPPORT_SAP, 255);
    if (fd == -1)
        return NULL;

    sap_address_t *addr = malloc (sizeof (*addr));
    if (addr == NULL)
    {
        net_Close (fd);
        return NULL;
    }

    strlcpy (addr->group, group, sizeof (addr->group));
    addr->fd = fd;
    addr->origlen = sizeof (addr->orig);
    getsockname (fd, (struct sockaddr *)&addr->orig, &addr->origlen);

    addr->interval = var_CreateGetInteger (obj, "sap-interval");
    vlc_mutex_init (&addr->lock);
    vlc_cond_init (&addr->wait);
    addr->session_count = 0;
    addr->first = NULL;

    if (vlc_clone (&addr->thread, RunThread, addr, VLC_THREAD_PRIORITY_LOW))
    {
        msg_Err (obj, "unable to spawn SAP announce thread");
        net_Close (fd);
        free (addr);
        return NULL;
    }
    return addr;
}