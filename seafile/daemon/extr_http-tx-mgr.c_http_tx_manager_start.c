#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  reset_bytes_timer; int /*<<< orphan*/  ca_bundle_path; } ;
typedef  TYPE_2__ HttpTxManager ;

/* Variables and functions */
 int /*<<< orphan*/  RESET_BYTES_INTERVAL_MSEC ; 
 int /*<<< orphan*/  g_unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_bytes ; 
 int /*<<< orphan*/  seaf_timer_new (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

int
http_tx_manager_start (HttpTxManager *mgr)
{
#ifdef WIN32
    /* Remove existing ca-bundle file on start. */
    g_unlink (mgr->priv->ca_bundle_path);
#endif

    /* TODO: add a timer to clean up unused Http connections. */

    mgr->priv->reset_bytes_timer = seaf_timer_new (reset_bytes,
                                                   mgr,
                                                   RESET_BYTES_INTERVAL_MSEC);

    return 0;
}