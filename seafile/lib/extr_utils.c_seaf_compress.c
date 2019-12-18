#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int avail_in; int avail_out; int /*<<< orphan*/ * next_out; int /*<<< orphan*/ * next_in; void* opaque; void* zfree; void* zalloc; } ;
typedef  TYPE_1__ z_stream ;
typedef  int /*<<< orphan*/  guint8 ;
struct TYPE_10__ {int len; } ;
typedef  TYPE_2__ GByteArray ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int ZLIB_BUF_SIZE ; 
 int /*<<< orphan*/  Z_DEFAULT_COMPRESSION ; 
 int /*<<< orphan*/  Z_FINISH ; 
 void* Z_NULL ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int deflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deflateEnd (TYPE_1__*) ; 
 int deflateInit (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_byte_array_append (TYPE_2__*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * g_byte_array_free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* g_byte_array_new () ; 
 int /*<<< orphan*/  g_warning (char*) ; 

int
seaf_compress (guint8 *input, int inlen, guint8 **output, int *outlen)
{
    int ret;
    unsigned have;
    z_stream strm;
    guint8 out[ZLIB_BUF_SIZE];
    GByteArray *barray;

    if (inlen == 0)
        return -1;

    /* allocate deflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    ret = deflateInit(&strm, Z_DEFAULT_COMPRESSION);
    if (ret != Z_OK) {
        g_warning ("deflateInit failed.\n");
        return -1;
    }

    strm.avail_in = inlen;
    strm.next_in = input;
    barray = g_byte_array_new ();

    do {
        strm.avail_out = ZLIB_BUF_SIZE;
        strm.next_out = out;
        ret = deflate(&strm, Z_FINISH);    /* no bad return value */
        have = ZLIB_BUF_SIZE - strm.avail_out;
        g_byte_array_append (barray, out, have);
    } while (ret != Z_STREAM_END);

    *outlen = barray->len;
    *output = g_byte_array_free (barray, FALSE);

    /* clean up and return */
    (void)deflateEnd(&strm);
    return 0;
}