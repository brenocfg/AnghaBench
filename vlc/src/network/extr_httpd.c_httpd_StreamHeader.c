#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int i_header; int /*<<< orphan*/  lock; int /*<<< orphan*/ * p_header; } ;
typedef  TYPE_1__ httpd_stream_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmalloc (int) ; 

int httpd_StreamHeader(httpd_stream_t *stream, uint8_t *p_data, int i_data)
{
    vlc_mutex_lock(&stream->lock);
    free(stream->p_header);
    stream->p_header = NULL;

    stream->i_header = i_data;
    if (i_data > 0) {
        stream->p_header = xmalloc(i_data);
        memcpy(stream->p_header, p_data, i_data);
    }
    vlc_mutex_unlock(&stream->lock);

    return VLC_SUCCESS;
}