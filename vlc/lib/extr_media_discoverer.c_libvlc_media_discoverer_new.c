#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; int /*<<< orphan*/  catname_to_submedialist; int /*<<< orphan*/ * p_sd; TYPE_3__* p_mlist; int /*<<< orphan*/ * p_libvlc_instance; } ;
typedef  TYPE_1__ libvlc_media_discoverer_t ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;
struct TYPE_6__ {int b_read_only; } ;

/* Variables and functions */
 TYPE_3__* libvlc_media_list_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_printerr (char*) ; 
 int /*<<< orphan*/  libvlc_retain (int /*<<< orphan*/ *) ; 
 TYPE_1__* malloc (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncasecmp (char const*,char*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_dictionary_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

libvlc_media_discoverer_t *
libvlc_media_discoverer_new( libvlc_instance_t * p_inst, const char * psz_name )
{
    /* podcast SD is a hack and only works with custom playlist callbacks. */
    if( !strncasecmp( psz_name, "podcast", 7 ) )
        return NULL;

    libvlc_media_discoverer_t *p_mdis;

    p_mdis = malloc(sizeof(*p_mdis) + strlen(psz_name) + 1);
    if( unlikely(p_mdis == NULL) )
    {
        libvlc_printerr( "Not enough memory" );
        return NULL;
    }

    p_mdis->p_libvlc_instance = p_inst;
    p_mdis->p_mlist = libvlc_media_list_new( p_inst );
    p_mdis->p_mlist->b_read_only = true;
    p_mdis->p_sd = NULL;

    vlc_dictionary_init( &p_mdis->catname_to_submedialist, 0 );

    libvlc_retain( p_inst );
    strcpy( p_mdis->name, psz_name );
    return p_mdis;
}