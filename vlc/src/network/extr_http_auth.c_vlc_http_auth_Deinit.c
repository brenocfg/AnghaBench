#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  psz_HA1; int /*<<< orphan*/  psz_cnonce; int /*<<< orphan*/  psz_qop; int /*<<< orphan*/  psz_algorithm; int /*<<< orphan*/  psz_stale; int /*<<< orphan*/  psz_opaque; int /*<<< orphan*/  psz_nonce; int /*<<< orphan*/  psz_domain; int /*<<< orphan*/  psz_realm; } ;
typedef  TYPE_1__ vlc_http_auth_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void vlc_http_auth_Deinit( vlc_http_auth_t *p_auth )
{
    free( p_auth->psz_realm );
    free( p_auth->psz_domain );
    free( p_auth->psz_nonce );
    free( p_auth->psz_opaque );
    free( p_auth->psz_stale );
    free( p_auth->psz_algorithm );
    free( p_auth->psz_qop );
    free( p_auth->psz_cnonce );
    free( p_auth->psz_HA1 );
}