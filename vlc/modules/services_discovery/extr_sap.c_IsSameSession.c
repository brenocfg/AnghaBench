#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ session_id; scalar_t__ orig_ip_version; int /*<<< orphan*/  orig_host; int /*<<< orphan*/  username; } ;
typedef  TYPE_1__ sdp_t ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool IsSameSession( sdp_t *p_sdp1, sdp_t *p_sdp2 )
{
    /* A session is identified by
     * - username,
     * - session_id,
     * - network type (which is always IN),
     * - address type (currently, this means IP version),
     * - and hostname.
     */
    if (strcmp (p_sdp1->username, p_sdp2->username)
     || (p_sdp1->session_id != p_sdp2->session_id)
     || (p_sdp1->orig_ip_version != p_sdp2->orig_ip_version)
     || strcmp (p_sdp1->orig_host, p_sdp2->orig_host))
        return false;

    return true;
}