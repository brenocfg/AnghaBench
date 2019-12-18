#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  module_t ;
struct TYPE_10__ {int /*<<< orphan*/ * psz_file; TYPE_2__* p_item; } ;
typedef  TYPE_1__ meta_export_t ;
struct TYPE_11__ {int i_type; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ input_item_t ;
typedef  enum input_item_type_e { ____Placeholder_input_item_type_e } input_item_type_e ;

/* Variables and functions */
 int ITEM_TYPE_FILE ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 char* input_item_GetURI (TYPE_2__*) ; 
 int /*<<< orphan*/ * module_need (TYPE_1__*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  module_unneed (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,char*) ; 
 TYPE_1__* vlc_custom_create (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 
 int /*<<< orphan*/ * vlc_uri2path (char*) ; 

int input_item_WriteMeta( vlc_object_t *obj, input_item_t *p_item )
{
    meta_export_t *p_export =
        vlc_custom_create( obj, sizeof( *p_export ), "meta writer" );
    if( p_export == NULL )
        return VLC_ENOMEM;
    p_export->p_item = p_item;

    enum input_item_type_e type;
    vlc_mutex_lock( &p_item->lock );
    type = p_item->i_type;
    vlc_mutex_unlock( &p_item->lock );
    if( type != ITEM_TYPE_FILE )
        goto error;

    char *psz_uri = input_item_GetURI( p_item );
    p_export->psz_file = vlc_uri2path( psz_uri );
    if( p_export->psz_file == NULL )
        msg_Err( p_export, "cannot write meta to remote media %s", psz_uri );
    free( psz_uri );
    if( p_export->psz_file == NULL )
        goto error;

    module_t *p_mod = module_need( p_export, "meta writer", NULL, false );
    if( p_mod )
        module_unneed( p_export, p_mod );
    vlc_object_delete(p_export);
    return VLC_SUCCESS;

error:
    vlc_object_delete(p_export);
    return VLC_EGENERIC;
}