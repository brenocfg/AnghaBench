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
typedef  int /*<<< orphan*/  httpd_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * httpd_HostCreate (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,...) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * vlc_tls_ServerCreate (int /*<<< orphan*/ *,char*,char*) ; 

httpd_host_t *vlc_https_HostNew(vlc_object_t *obj)
{
    char *cert = var_InheritString(obj, "http-cert");
    if (!cert) {
        msg_Err(obj, "HTTP/TLS certificate not specified!");
        return NULL;
    }

    char *key = var_InheritString(obj, "http-key");
    vlc_tls_server_t *tls = vlc_tls_ServerCreate(obj, cert, key);

    if (!tls) {
        msg_Err(obj, "HTTP/TLS certificate error (%s and %s)",
                 cert, key ? key : cert);
        free(key);
        free(cert);
        return NULL;
    }
    free(key);
    free(cert);

    return httpd_HostCreate(obj, "http-host", "https-port", tls);
}