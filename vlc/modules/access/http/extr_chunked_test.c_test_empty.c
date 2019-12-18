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
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunked_stream ; 
 int /*<<< orphan*/  chunked_tls ; 
 int stream_bad ; 
 char* stream_content ; 
 int stream_length ; 
 struct vlc_http_stream* vlc_chunked_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_http_stream_close (struct vlc_http_stream*,int) ; 
 int /*<<< orphan*/ * vlc_http_stream_read (struct vlc_http_stream*) ; 

__attribute__((used)) static void test_empty(void)
{
    struct vlc_http_stream *s;
    block_t *b;

    stream_content = "0\r\n";
    stream_length = 3;
    stream_bad = true;

    s = vlc_chunked_open(&chunked_stream, &chunked_tls);
    assert(s != NULL);

    b = vlc_http_stream_read(s);
    assert(b == NULL);
    b = vlc_http_stream_read(s);
    assert(b == NULL);
    vlc_http_stream_close(s, false);
}