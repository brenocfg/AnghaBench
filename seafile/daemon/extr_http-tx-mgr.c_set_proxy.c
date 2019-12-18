#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gboolean ;
struct TYPE_2__ {int http_proxy_addr; int http_proxy_port; int http_proxy_username; int http_proxy_password; int /*<<< orphan*/  http_proxy_type; int /*<<< orphan*/  use_http_proxy; } ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int CURLAUTH_BASIC ; 
 int CURLAUTH_DIGEST ; 
 int CURLAUTH_DIGEST_IE ; 
 int CURLAUTH_GSSNEGOTIATE ; 
 int CURLAUTH_NTLM ; 
 int /*<<< orphan*/  CURLOPT_HTTPPROXYTUNNEL ; 
 int /*<<< orphan*/  CURLOPT_PROXY ; 
 int /*<<< orphan*/  CURLOPT_PROXYAUTH ; 
 int /*<<< orphan*/  CURLOPT_PROXYPASSWORD ; 
 int /*<<< orphan*/  CURLOPT_PROXYPORT ; 
 int /*<<< orphan*/  CURLOPT_PROXYTYPE ; 
 int /*<<< orphan*/  CURLOPT_PROXYUSERNAME ; 
 int CURLPROXY_HTTP ; 
 int CURLPROXY_SOCKS5 ; 
 int /*<<< orphan*/  PROXY_TYPE_HTTP ; 
 int /*<<< orphan*/  PROXY_TYPE_SOCKS ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ g_strcmp0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* seaf ; 

__attribute__((used)) static void
set_proxy (CURL *curl, gboolean is_https)
{
    /* Disable proxy if proxy options are not set properly. */
    if (!seaf->use_http_proxy || !seaf->http_proxy_type || !seaf->http_proxy_addr) {
        curl_easy_setopt (curl, CURLOPT_PROXY, NULL);
        return;
    }

    if (g_strcmp0(seaf->http_proxy_type, PROXY_TYPE_HTTP) == 0) {
        curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);
        /* Use CONNECT method create a SSL tunnel if https is used. */
        if (is_https)
            curl_easy_setopt(curl, CURLOPT_HTTPPROXYTUNNEL, 1L);
        curl_easy_setopt(curl, CURLOPT_PROXY, seaf->http_proxy_addr);
        curl_easy_setopt(curl, CURLOPT_PROXYPORT,
                         seaf->http_proxy_port > 0 ? seaf->http_proxy_port : 80);
        if (seaf->http_proxy_username && seaf->http_proxy_password) {
            curl_easy_setopt(curl, CURLOPT_PROXYAUTH,
                             CURLAUTH_BASIC |
                             CURLAUTH_DIGEST |
                             CURLAUTH_DIGEST_IE |
                             CURLAUTH_GSSNEGOTIATE |
                             CURLAUTH_NTLM);
            curl_easy_setopt(curl, CURLOPT_PROXYUSERNAME, seaf->http_proxy_username);
            curl_easy_setopt(curl, CURLOPT_PROXYPASSWORD, seaf->http_proxy_password);
        }
    } else if (g_strcmp0(seaf->http_proxy_type, PROXY_TYPE_SOCKS) == 0) {
        if (seaf->http_proxy_port < 0)
            return;
        curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
        curl_easy_setopt(curl, CURLOPT_PROXY, seaf->http_proxy_addr);
        curl_easy_setopt(curl, CURLOPT_PROXYPORT, seaf->http_proxy_port);
    }
}