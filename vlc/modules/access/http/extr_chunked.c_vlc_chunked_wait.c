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
struct vlc_http_stream {int dummy; } ;
struct vlc_http_msg {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct vlc_http_msg *vlc_chunked_wait(struct vlc_http_stream *stream)
{
    /* Request trailers are not supported so far.
     * There cannot be headers during chunked encoding. */
    (void) stream;
    return NULL;
}