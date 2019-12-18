#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  extra_tags; scalar_t__ i_status; int /*<<< orphan*/  ppsz_meta; } ;
typedef  TYPE_1__ vlc_meta_t ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_dictionary_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

vlc_meta_t *vlc_meta_New( void )
{
    vlc_meta_t *m = (vlc_meta_t*)malloc( sizeof(*m) );
    if( !m )
        return NULL;
    memset( m->ppsz_meta, 0, sizeof(m->ppsz_meta) );
    m->i_status = 0;
    vlc_dictionary_init( &m->extra_tags, 0 );
    return m;
}