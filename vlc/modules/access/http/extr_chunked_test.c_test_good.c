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
struct vlc_http_stream {int dummy; } ;
struct TYPE_4__ {int i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  block_Release (TYPE_1__*) ; 
 int /*<<< orphan*/  chunked_stream ; 
 int /*<<< orphan*/  chunked_tls ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int stream_bad ; 
 char* stream_content ; 
 int /*<<< orphan*/  stream_length ; 
 int /*<<< orphan*/  strlen (char*) ; 
 struct vlc_http_stream* vlc_chunked_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_http_stream_close (struct vlc_http_stream*,int) ; 
 TYPE_1__* vlc_http_stream_read (struct vlc_http_stream*) ; 
 int /*<<< orphan*/ * vlc_http_stream_read_headers (struct vlc_http_stream*) ; 

__attribute__((used)) static void test_good(void)
{
    struct vlc_http_stream *s;
    block_t *b;

    /* Simple good payload */
    stream_content =
        "A\r\n" "1234567890\r\n"
        "1A; ext-foo=1\r\n" "abcdefghijklmnopqrstuvwxyz\r\n"
        "0\r\n" "\r\n";
    stream_length = strlen(stream_content);
    stream_bad = false;

    s = vlc_chunked_open(&chunked_stream, &chunked_tls);
    assert(s != NULL);
    assert(vlc_http_stream_read_headers(s) == NULL);

    b = vlc_http_stream_read(s);
    assert(b != NULL);
    assert(b->i_buffer == 10);
    assert(!memcmp(b->p_buffer, "1234567890", 10));
    block_Release(b);

    b = vlc_http_stream_read(s);
    assert(b != NULL);
    assert(b->i_buffer == 26);
    assert(!memcmp(b->p_buffer, "abcdefghijklmnopqrstuvwxyz", 26));
    block_Release(b);

    b = vlc_http_stream_read(s);
    assert(b == NULL);
    b = vlc_http_stream_read(s);
    assert(b == NULL);

    vlc_http_stream_close(s, false);
}