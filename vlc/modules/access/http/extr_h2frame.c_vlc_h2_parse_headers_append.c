#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {scalar_t__ sid; size_t len; int /*<<< orphan*/ * buf; } ;
struct vlc_h2_parser {TYPE_1__ headers; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_H2_INTERNAL_ERROR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int vlc_h2_parse_error (struct vlc_h2_parser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlc_h2_parse_headers_append(struct vlc_h2_parser *p,
                                       const uint8_t *data, size_t len)
{
    assert(p->headers.sid != 0);

    if (p->headers.len + len > 65536)
        return vlc_h2_parse_error(p, VLC_H2_INTERNAL_ERROR);

    uint8_t *buf = realloc(p->headers.buf, p->headers.len + len);
    if (unlikely(buf == NULL))
        return vlc_h2_parse_error(p, VLC_H2_INTERNAL_ERROR);

    p->headers.buf = buf;
    memcpy(p->headers.buf + p->headers.len, data, len);
    p->headers.len += len;
    return 0;
}