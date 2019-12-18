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
struct vlc_chunked_stream {int error; } ;

/* Variables and functions */
 void* vlc_http_error ; 

__attribute__((used)) static void *vlc_chunked_fatal(struct vlc_chunked_stream *s)
{
    s->error = true;
    return vlc_http_error;
}