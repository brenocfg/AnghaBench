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
typedef  int /*<<< orphan*/  vlc_tls_t ;

/* Variables and functions */
 int /*<<< orphan*/  PF_LOCAL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * conn ; 
 int /*<<< orphan*/ * external_tls ; 
 int /*<<< orphan*/ * vlc_h1_conn_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ vlc_tls_SocketPair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void conn_create(void)
{
    vlc_tls_t *tlsv[2];

    if (vlc_tls_SocketPair(PF_LOCAL, 0, tlsv))
        assert(!"vlc_tls_SocketPair");

    external_tls = tlsv[0];

    conn = vlc_h1_conn_create(NULL, tlsv[1], false);
    assert(conn != NULL);
}