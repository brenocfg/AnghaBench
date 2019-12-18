#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int i_buffer_size; int i_buffer_pos; int i_buffer_last_pos; int b_has_keyframes; int /*<<< orphan*/  url; int /*<<< orphan*/ * p_http_headers; scalar_t__ i_http_headers; scalar_t__ i_last_keyframe_seen_pos; int /*<<< orphan*/  p_buffer; int /*<<< orphan*/ * p_header; scalar_t__ i_header; int /*<<< orphan*/  psz_mime; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ httpd_stream_t ;
typedef  int /*<<< orphan*/  httpd_host_t ;
typedef  int /*<<< orphan*/  httpd_callback_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  HTTPD_MSG_GET ; 
 int /*<<< orphan*/  HTTPD_MSG_HEAD ; 
 int /*<<< orphan*/  HTTPD_MSG_POST ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  httpd_StreamCallBack ; 
 int /*<<< orphan*/  httpd_UrlCatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  httpd_UrlNew (int /*<<< orphan*/ *,char const*,char const*,char const*) ; 
 TYPE_1__* malloc (int) ; 
 char* vlc_mime_Ext2Mime (char const*) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmalloc (int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

httpd_stream_t *httpd_StreamNew(httpd_host_t *host,
                                 const char *psz_url, const char *psz_mime,
                                 const char *psz_user, const char *psz_password)
{
    httpd_stream_t *stream = malloc(sizeof(*stream));
    if (!stream)
        return NULL;

    stream->url = httpd_UrlNew(host, psz_url, psz_user, psz_password);
    if (!stream->url) {
        free(stream);
        return NULL;
    }

    vlc_mutex_init(&stream->lock);
    if (psz_mime == NULL || psz_mime[0] == '\0')
        psz_mime = vlc_mime_Ext2Mime(psz_url);
    stream->psz_mime = xstrdup(psz_mime);

    stream->i_header = 0;
    stream->p_header = NULL;
    stream->i_buffer_size = 5000000;    /* 5 Mo per stream */
    stream->p_buffer = xmalloc(stream->i_buffer_size);
    /* We set to 1 to make life simpler
     * (this way i_body_offset can never be 0) */
    stream->i_buffer_pos = 1;
    stream->i_buffer_last_pos = 1;
    stream->b_has_keyframes = false;
    stream->i_last_keyframe_seen_pos = 0;
    stream->i_http_headers = 0;
    stream->p_http_headers = NULL;

    httpd_UrlCatch(stream->url, HTTPD_MSG_HEAD, httpd_StreamCallBack,
                    (httpd_callback_sys_t*)stream);
    httpd_UrlCatch(stream->url, HTTPD_MSG_GET, httpd_StreamCallBack,
                    (httpd_callback_sys_t*)stream);
    httpd_UrlCatch(stream->url, HTTPD_MSG_POST, httpd_StreamCallBack,
                    (httpd_callback_sys_t*)stream);

    return stream;
}