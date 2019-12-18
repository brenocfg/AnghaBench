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
typedef  int /*<<< orphan*/  uint_fast32_t ;
struct vlc_http_msg {unsigned int count; int status; char* method; char* scheme; char* authority; char* path; int /*<<< orphan*/ ** headers; } ;
struct vlc_h2_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_H2_DEFAULT_MAX_FRAME ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char const***) ; 
 int /*<<< orphan*/  memcpy (char const***,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int strcasecmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 char*** vlc_alloc (int,int) ; 
 struct vlc_h2_frame* vlc_h2_frame_headers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int,char const***) ; 

struct vlc_h2_frame *vlc_http_msg_h2_frame(const struct vlc_http_msg *m,
                                           uint_fast32_t stream_id, bool eos)
{
    for (unsigned j = 0; j < m->count; j++)
    {   /* No HTTP 1 specific headers */
        assert(strcasecmp(m->headers[j][0], "Connection"));
        assert(strcasecmp(m->headers[j][0], "Upgrade"));
        assert(strcasecmp(m->headers[j][0], "HTTP2-Settings"));
    }

    const char *(*headers)[2] = vlc_alloc(m->count + 5, sizeof (char *[2]));
    if (unlikely(headers == NULL))
        return NULL;

    struct vlc_h2_frame *f;
    unsigned i = 0;
    char status[4];

    if (m->status >= 0)
    {
        assert(m->status < 1000);
        sprintf(status, "%hd", m->status);
        headers[i][0] = ":status";
        headers[i][1] = status;
        i++;
    }
    if (m->method != NULL)
    {
        headers[i][0] = ":method";
        headers[i][1] = m->method;
        i++;
    }
    if (m->scheme != NULL)
    {
        headers[i][0] = ":scheme";
        headers[i][1] = m->scheme;
        i++;
    }
    if (m->authority != NULL)
    {
        headers[i][0] = ":authority";
        headers[i][1] = m->authority;
        i++;
    }
    if (m->path != NULL)
    {
        headers[i][0] = ":path";
        headers[i][1] = m->path;
        i++;
    }
    if (m->count > 0)
    {
        memcpy(headers + i, m->headers, m->count * sizeof (*headers));
        i += m->count;
    }

    f = vlc_h2_frame_headers(stream_id, VLC_H2_DEFAULT_MAX_FRAME, eos,
                             i, headers);
    free(headers);
    return f;
}