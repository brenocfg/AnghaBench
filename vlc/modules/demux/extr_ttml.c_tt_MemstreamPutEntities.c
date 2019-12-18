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
struct vlc_memstream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  vlc_memstream_puts (struct vlc_memstream*,char*) ; 
 char* vlc_xml_encode (char const*) ; 

__attribute__((used)) static void tt_MemstreamPutEntities( struct vlc_memstream *p_stream, const char *psz )
{
    char *psz_entities = vlc_xml_encode( psz );
    if( psz_entities )
    {
        vlc_memstream_puts( p_stream, psz_entities );
        free( psz_entities );
    }
}