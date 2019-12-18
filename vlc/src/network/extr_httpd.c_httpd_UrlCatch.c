#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; TYPE_1__* catch; } ;
typedef  TYPE_2__ httpd_url_t ;
typedef  int /*<<< orphan*/  httpd_callback_t ;
typedef  int /*<<< orphan*/  httpd_callback_sys_t ;
struct TYPE_4__ {int /*<<< orphan*/ * p_sys; int /*<<< orphan*/  cb; } ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

int httpd_UrlCatch(httpd_url_t *url, int i_msg, httpd_callback_t cb,
                    httpd_callback_sys_t *p_sys)
{
    vlc_mutex_lock(&url->lock);
    url->catch[i_msg].cb   = cb;
    url->catch[i_msg].p_sys= p_sys;
    vlc_mutex_unlock(&url->lock);

    return VLC_SUCCESS;
}