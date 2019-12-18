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
struct TYPE_4__ {struct TYPE_4__* p_buffer; int /*<<< orphan*/  query; int /*<<< orphan*/  answer; int /*<<< orphan*/  sock; int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ httpd_client_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  httpd_MsgClean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_tls_Close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void httpd_ClientDestroy(httpd_client_t *cl)
{
    vlc_list_remove(&cl->node);
    vlc_tls_Close(cl->sock);
    httpd_MsgClean(&cl->answer);
    httpd_MsgClean(&cl->query);

    free(cl->p_buffer);
    free(cl);
}