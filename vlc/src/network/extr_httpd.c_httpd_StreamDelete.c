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
struct TYPE_4__ {size_t i_http_headers; struct TYPE_4__* p_buffer; struct TYPE_4__* p_header; struct TYPE_4__* psz_mime; int /*<<< orphan*/  lock; struct TYPE_4__* p_http_headers; struct TYPE_4__* value; struct TYPE_4__* name; int /*<<< orphan*/  url; } ;
typedef  TYPE_1__ httpd_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  httpd_UrlDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

void httpd_StreamDelete(httpd_stream_t *stream)
{
    httpd_UrlDelete(stream->url);
    for (size_t i = 0; i < stream->i_http_headers; i++) {
        free(stream->p_http_headers[i].name);
        free(stream->p_http_headers[i].value);
    }
    free(stream->p_http_headers);
    vlc_mutex_destroy(&stream->lock);
    free(stream->psz_mime);
    free(stream->p_header);
    free(stream->p_buffer);
    free(stream);
}