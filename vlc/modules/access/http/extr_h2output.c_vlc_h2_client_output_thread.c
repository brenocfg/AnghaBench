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
struct vlc_h2_output {int failed; int /*<<< orphan*/  lock; int /*<<< orphan*/  tls; } ;

/* Variables and functions */
 void* vlc_h2_output_thread (void*) ; 
 int vlc_https_send (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *vlc_h2_client_output_thread(void *data)
{
    static const char http2_hello[] = "PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n";
    struct vlc_h2_output *out = data;

    if (vlc_https_send(out->tls, http2_hello, 24) < 24)
    {
        vlc_mutex_lock(&out->lock);
        out->failed = true;
        vlc_mutex_unlock(&out->lock);
        return NULL;
    }

    return vlc_h2_output_thread(data);
}