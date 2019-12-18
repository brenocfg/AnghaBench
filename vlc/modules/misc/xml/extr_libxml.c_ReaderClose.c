#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ xml_reader_t ;
struct TYPE_5__ {struct TYPE_5__* node; int /*<<< orphan*/  xml; } ;
typedef  TYPE_2__ xml_reader_sys_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlCleanupParser () ; 
 int /*<<< orphan*/  xmlFreeTextReader (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ReaderClose( vlc_object_t *p_this )
{
    xml_reader_t *p_reader = (xml_reader_t *)p_this;
    xml_reader_sys_t *p_sys = p_reader->p_sys;

    xmlFreeTextReader( p_sys->xml );
#ifdef LIBXML_GETS_A_CLUE_ABOUT_REENTRANCY_AND_MEMORY_LEAKS
    vlc_mutex_lock( &lock );
    xmlCleanupParser();
    vlc_mutex_unlock( &lock );
#endif
    free( p_sys->node );
    free( p_sys );
}