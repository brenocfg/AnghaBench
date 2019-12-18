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
typedef  int /*<<< orphan*/  vlc_tls_server_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tls_server_load ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_custom_create (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/ * vlc_module_load (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  vlc_object_delete (int /*<<< orphan*/ *) ; 

vlc_tls_server_t *
vlc_tls_ServerCreate (vlc_object_t *obj, const char *cert_path,
                      const char *key_path)
{
    vlc_tls_server_t *srv = vlc_custom_create(obj, sizeof (*srv),
                                              "tls server");
    if (unlikely(srv == NULL))
        return NULL;

    if (key_path == NULL)
        key_path = cert_path;

    if (vlc_module_load(srv, "tls server", NULL, false,
                        tls_server_load, srv, cert_path, key_path) == NULL)
    {
        msg_Err (srv, "TLS server plugin not available");
        vlc_object_delete(srv);
        return NULL;
    }

    return srv;
}