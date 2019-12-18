#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  s; } ;
struct reader {char* psz_name; TYPE_2__* p_data; int /*<<< orphan*/  pf_seek; int /*<<< orphan*/  pf_tell; int /*<<< orphan*/  pf_peek; int /*<<< orphan*/  pf_read; int /*<<< orphan*/  pf_getsize; int /*<<< orphan*/  pf_close; TYPE_1__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  p_libvlc_int; } ;
typedef  TYPE_2__ libvlc_instance_t ;
typedef  int /*<<< orphan*/  argv ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct reader*) ; 
 struct reader* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct reader*) ; 
 TYPE_2__* libvlc_new (int,char const**) ; 
 int /*<<< orphan*/  libvlc_release (TYPE_2__*) ; 
 int /*<<< orphan*/  stream_close ; 
 int /*<<< orphan*/  stream_getsize ; 
 int /*<<< orphan*/  stream_peek ; 
 int /*<<< orphan*/  stream_read ; 
 int /*<<< orphan*/  stream_seek ; 
 int /*<<< orphan*/  stream_tell ; 
 int /*<<< orphan*/  vlc_stream_NewURL (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct reader *
stream_open( const char *psz_url )
{
    libvlc_instance_t *p_vlc;
    struct reader *p_reader;
    const char * argv[] = {
        "-v",
        "--ignore-config",
        "-I",
        "dummy",
        "--no-media-library",
        "--vout=dummy",
        "--aout=dummy",
    };

    p_reader = calloc( 1, sizeof(struct reader) );
    assert( p_reader );

    p_vlc = libvlc_new( sizeof(argv) / sizeof(argv[0]), argv );
    assert( p_vlc != NULL );

    p_reader->u.s = vlc_stream_NewURL( p_vlc->p_libvlc_int, psz_url );
    if( !p_reader->u.s )
    {
        libvlc_release( p_vlc );
        free( p_reader );
        return NULL;
    }
    p_reader->pf_close = stream_close;
    p_reader->pf_getsize = stream_getsize;
    p_reader->pf_read = stream_read;
    p_reader->pf_peek = stream_peek;
    p_reader->pf_tell = stream_tell;
    p_reader->pf_seek = stream_seek;
    p_reader->p_data = p_vlc;
    p_reader->psz_name = "stream";
    return p_reader;
}