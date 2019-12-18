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
struct vlc_http_mgr {int /*<<< orphan*/ * creds; int /*<<< orphan*/ * conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct vlc_http_mgr*) ; 
 int /*<<< orphan*/  vlc_http_mgr_release (struct vlc_http_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_tls_ClientDelete (int /*<<< orphan*/ *) ; 

void vlc_http_mgr_destroy(struct vlc_http_mgr *mgr)
{
    if (mgr->conn != NULL)
        vlc_http_mgr_release(mgr, mgr->conn);
    if (mgr->creds != NULL)
        vlc_tls_ClientDelete(mgr->creds);
    free(mgr);
}