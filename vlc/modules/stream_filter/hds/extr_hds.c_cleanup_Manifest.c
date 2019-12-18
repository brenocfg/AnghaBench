#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ vlc_reader; TYPE_2__* bootstraps; TYPE_1__* medias; int /*<<< orphan*/ * element_stack; } ;
typedef  TYPE_3__ manifest_t ;
struct TYPE_6__ {int /*<<< orphan*/  profile; int /*<<< orphan*/  url; int /*<<< orphan*/  id; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int /*<<< orphan*/  metadata; int /*<<< orphan*/  bootstrap_id; int /*<<< orphan*/  media_url; int /*<<< orphan*/  stream_id; } ;

/* Variables and functions */
 unsigned int MAX_BOOTSTRAP_INFO ; 
 unsigned int MAX_MEDIA_ELEMENTS ; 
 unsigned int MAX_XML_DEPTH ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xml_ReaderDelete (scalar_t__) ; 

__attribute__((used)) static void cleanup_Manifest( manifest_t *m )
{
    for (unsigned i = 0; i < MAX_XML_DEPTH; i++)
        free( m->element_stack[i] );

    for( unsigned i = 0; i < MAX_MEDIA_ELEMENTS; i++ )
    {
        free( m->medias[i].stream_id );
        free( m->medias[i].media_url );
        free( m->medias[i].bootstrap_id );
        free( m->medias[i].metadata );
    }

    for( unsigned i = 0; i < MAX_BOOTSTRAP_INFO; i++ )
    {
        free( m->bootstraps[i].data );
        free( m->bootstraps[i].id );
        free( m->bootstraps[i].url );
        free( m->bootstraps[i].profile );
    }

    if( m->vlc_reader )
        xml_ReaderDelete( m->vlc_reader );
}