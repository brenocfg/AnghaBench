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
struct vlc_http_msg {int /*<<< orphan*/ * payload; } ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/ * vlc_http_stream_read (int /*<<< orphan*/ *) ; 

block_t *vlc_http_msg_read(struct vlc_http_msg *m)
{
    if (m->payload == NULL)
        return NULL;

    return vlc_http_stream_read(m->payload);
}