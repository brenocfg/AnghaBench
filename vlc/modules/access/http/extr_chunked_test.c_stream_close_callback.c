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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int stream_bad ; 

__attribute__((used)) static void stream_close_callback(struct vlc_http_stream *stream, bool bad)
{
    (void) stream;
    assert(bad == stream_bad);
}