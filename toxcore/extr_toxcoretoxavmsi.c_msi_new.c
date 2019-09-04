#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * messenger; int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  Messenger ;
typedef  TYPE_1__ MSISession ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_DEBUG (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  LOGGER_ERROR (char*) ; 
 TYPE_1__* calloc (int,int) ; 
 scalar_t__ create_recursive_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  handle_msi_packet ; 
 int /*<<< orphan*/  m_callback_connectionstatus_internal_av (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  m_callback_msi_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  on_peer_status ; 

MSISession *msi_new (Messenger *m)
{
    if (m == NULL) {
        LOGGER_ERROR("Could not init session on empty messenger!");
        return NULL;
    }

    MSISession *retu = calloc (sizeof (MSISession), 1);

    if (retu == NULL) {
        LOGGER_ERROR("Allocation failed! Program might misbehave!");
        return NULL;
    }

    if (create_recursive_mutex(retu->mutex) != 0) {
        LOGGER_ERROR("Failed to init mutex! Program might misbehave");
        free(retu);
        return NULL;
    }

    retu->messenger = m;

    m_callback_msi_packet(m, handle_msi_packet, retu);

    /* This is called when remote terminates session */
    m_callback_connectionstatus_internal_av(m, on_peer_status, retu);

    LOGGER_DEBUG("New msi session: %p ", retu);
    return retu;
}