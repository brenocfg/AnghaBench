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
struct vlc_http_resource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct vlc_http_resource*) ; 
 int /*<<< orphan*/  vlc_http_res_deinit (struct vlc_http_resource*) ; 

void vlc_http_res_destroy(struct vlc_http_resource *res)
{
    vlc_http_res_deinit(res);
    free(res);
}