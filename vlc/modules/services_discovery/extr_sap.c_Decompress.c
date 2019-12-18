#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int avail_in; int avail_out; int total_out; int /*<<< orphan*/ * next_out; int /*<<< orphan*/ * next_in; } ;
typedef  TYPE_1__ z_stream ;
typedef  int /*<<< orphan*/  d_stream ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inflateEnd (TYPE_1__*) ; 
 int inflateInit (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 unsigned char* xrealloc (unsigned char*,int) ; 

__attribute__((used)) static int Decompress( const unsigned char *psz_src, unsigned char **_dst, int i_len )
{
#ifdef HAVE_ZLIB_H
    int i_result, i_dstsize, n = 0;
    unsigned char *psz_dst = NULL;
    z_stream d_stream;

    memset (&d_stream, 0, sizeof (d_stream));

    i_result = inflateInit(&d_stream);
    if( i_result != Z_OK )
        return( -1 );

    d_stream.next_in = (Bytef *)psz_src;
    d_stream.avail_in = i_len;

    do
    {
        n++;
        psz_dst = xrealloc( psz_dst, n * 1000 );
        d_stream.next_out = (Bytef *)&psz_dst[(n - 1) * 1000];
        d_stream.avail_out = 1000;

        i_result = inflate(&d_stream, Z_NO_FLUSH);
        if( ( i_result != Z_OK ) && ( i_result != Z_STREAM_END ) )
        {
            inflateEnd( &d_stream );
            free( psz_dst );
            return( -1 );
        }
    }
    while( ( d_stream.avail_out == 0 ) && ( d_stream.avail_in != 0 ) &&
           ( i_result != Z_STREAM_END ) );

    i_dstsize = d_stream.total_out;
    inflateEnd( &d_stream );

    *_dst = xrealloc( psz_dst, i_dstsize );

    return i_dstsize;
#else
    (void)psz_src;
    (void)_dst;
    (void)i_len;
    return -1;
#endif
}