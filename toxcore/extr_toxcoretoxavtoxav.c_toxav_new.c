#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int interval; TYPE_4__* msi; int /*<<< orphan*/  mutex; TYPE_2__* m; } ;
typedef  TYPE_1__ ToxAV ;
typedef  int /*<<< orphan*/  Tox ;
struct TYPE_11__ {TYPE_1__* av; } ;
struct TYPE_10__ {scalar_t__ msi_packet; } ;
typedef  scalar_t__ TOXAV_ERR_NEW ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_WARNING (char*) ; 
 scalar_t__ TOXAV_ERR_NEW_MALLOC ; 
 scalar_t__ TOXAV_ERR_NEW_MULTIPLE ; 
 scalar_t__ TOXAV_ERR_NEW_NULL ; 
 scalar_t__ TOXAV_ERR_NEW_OK ; 
 int /*<<< orphan*/  callback_capabilites ; 
 int /*<<< orphan*/  callback_end ; 
 int /*<<< orphan*/  callback_error ; 
 int /*<<< orphan*/  callback_invite ; 
 int /*<<< orphan*/  callback_start ; 
 TYPE_1__* calloc (int,int) ; 
 scalar_t__ create_recursive_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  msi_OnCapabilities ; 
 int /*<<< orphan*/  msi_OnEnd ; 
 int /*<<< orphan*/  msi_OnError ; 
 int /*<<< orphan*/  msi_OnInvite ; 
 int /*<<< orphan*/  msi_OnPeerTimeout ; 
 int /*<<< orphan*/  msi_OnStart ; 
 TYPE_4__* msi_new (TYPE_2__*) ; 
 int /*<<< orphan*/  msi_register_callback (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ ) ; 

ToxAV *toxav_new(Tox *tox, TOXAV_ERR_NEW *error)
{
    TOXAV_ERR_NEW rc = TOXAV_ERR_NEW_OK;
    ToxAV *av = NULL;

    if (tox == NULL) {
        rc = TOXAV_ERR_NEW_NULL;
        goto END;
    }

    if (((Messenger *)tox)->msi_packet) {
        rc = TOXAV_ERR_NEW_MULTIPLE;
        goto END;
    }

    av = calloc (sizeof(ToxAV), 1);

    if (av == NULL) {
        LOGGER_WARNING("Allocation failed!");
        rc = TOXAV_ERR_NEW_MALLOC;
        goto END;
    }

    if (create_recursive_mutex(av->mutex) != 0) {
        LOGGER_WARNING("Mutex creation failed!");
        rc = TOXAV_ERR_NEW_MALLOC;
        goto END;
    }

    av->m = (Messenger *)tox;
    av->msi = msi_new(av->m);

    if (av->msi == NULL) {
        pthread_mutex_destroy(av->mutex);
        rc = TOXAV_ERR_NEW_MALLOC;
        goto END;
    }

    av->interval = 200;
    av->msi->av = av;

    msi_register_callback(av->msi, callback_invite, msi_OnInvite);
    msi_register_callback(av->msi, callback_start, msi_OnStart);
    msi_register_callback(av->msi, callback_end, msi_OnEnd);
    msi_register_callback(av->msi, callback_error, msi_OnError);
    msi_register_callback(av->msi, callback_error, msi_OnPeerTimeout);
    msi_register_callback(av->msi, callback_capabilites, msi_OnCapabilities);

END:

    if (error)
        *error = rc;

    if (rc != TOXAV_ERR_NEW_OK) {
        free(av);
        av = NULL;
    }

    return av;
}