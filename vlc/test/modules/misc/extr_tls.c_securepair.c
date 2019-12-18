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
typedef  int /*<<< orphan*/  vlc_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  PF_LOCAL ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_LOW ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  client_creds ; 
 int /*<<< orphan*/  server_creds ; 
 int /*<<< orphan*/  tls_echo ; 
 int vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_tls_ClientSessionCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,char const* const*,char**) ; 
 int /*<<< orphan*/ * vlc_tls_ServerSessionCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const* const*) ; 
 int /*<<< orphan*/  vlc_tls_SessionDelete (int /*<<< orphan*/ *) ; 
 int vlc_tls_SocketPair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static vlc_tls_t *securepair(vlc_thread_t *th,
                             const char *const salpnv[],
                             const char *const calpnv[],
                             char **restrict alp)
{
    vlc_tls_t *socks[2];
    vlc_tls_t *server, *client;
    int val;

    val = vlc_tls_SocketPair(PF_LOCAL, 0, socks);
    assert(val == 0);

    server = vlc_tls_ServerSessionCreate(server_creds, socks[0], salpnv);
    assert(server != NULL);

    val = vlc_clone(th, tls_echo, server, VLC_THREAD_PRIORITY_LOW);
    assert(val == 0);

    client = vlc_tls_ClientSessionCreate(client_creds, socks[1],
                                         "localhost", "vlc-tls-test",
                                         calpnv, alp);
    if (client == NULL)
    {
        vlc_tls_SessionDelete(socks[1]);
        vlc_join(*th, NULL);
        return NULL;
    }
    return client;
}