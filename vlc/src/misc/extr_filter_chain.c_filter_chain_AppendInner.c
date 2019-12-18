#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_mouse_t ;
struct TYPE_18__ {scalar_t__ i_cat; } ;
struct TYPE_15__ {int /*<<< orphan*/ * sub; TYPE_3__* sys; int /*<<< orphan*/ * video; } ;
struct TYPE_16__ {char const* psz_name; TYPE_4__ fmt_in; TYPE_4__ fmt_out; int /*<<< orphan*/ * p_module; TYPE_1__ owner; int /*<<< orphan*/ * p_cfg; scalar_t__ b_allow_fmt_out_change; } ;
typedef  TYPE_2__ filter_t ;
struct TYPE_17__ {int /*<<< orphan*/  obj; TYPE_5__* last; TYPE_5__* first; scalar_t__ b_allow_fmt_out_change; TYPE_4__ fmt_out; TYPE_4__ fmt_in; } ;
typedef  TYPE_3__ filter_chain_t ;
typedef  TYPE_4__ es_format_t ;
typedef  int /*<<< orphan*/  config_chain_t ;
struct TYPE_19__ {int /*<<< orphan*/ * pending; int /*<<< orphan*/ * mouse; struct TYPE_19__* next; struct TYPE_19__* prev; TYPE_2__ filter; } ;
typedef  TYPE_5__ chained_filter_t ;

/* Variables and functions */
 scalar_t__ VIDEO_ES ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_format_Clean (TYPE_4__*) ; 
 int /*<<< orphan*/  es_format_Copy (TYPE_4__*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  filter_chain_video_cbs ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 char const* module_get_name (int /*<<< orphan*/ *,int) ; 
 void* module_need (TYPE_2__*,char const*,char const*,int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*,char const*,void*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 TYPE_5__* vlc_custom_create (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  vlc_mouse_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_2__*) ; 

__attribute__((used)) static filter_t *filter_chain_AppendInner( filter_chain_t *chain,
    const char *name, const char *capability, config_chain_t *cfg,
    const es_format_t *fmt_out )
{
    chained_filter_t *chained =
        vlc_custom_create( chain->obj, sizeof(*chained), "filter" );
    if( unlikely(chained == NULL) )
        return NULL;

    filter_t *filter = &chained->filter;

    const es_format_t *fmt_in;
    if( chain->last != NULL )
        fmt_in = &chain->last->filter.fmt_out;
    else
        fmt_in = &chain->fmt_in;

    if( fmt_out == NULL )
        fmt_out = &chain->fmt_out;

    es_format_Copy( &filter->fmt_in, fmt_in );
    es_format_Copy( &filter->fmt_out, fmt_out );
    filter->b_allow_fmt_out_change = chain->b_allow_fmt_out_change;
    filter->p_cfg = cfg;
    filter->psz_name = name;

    if (fmt_in->i_cat == VIDEO_ES)
    {
        filter->owner.video = &filter_chain_video_cbs;
        filter->owner.sys = chain;
    }
    else
        filter->owner.sub = NULL;

    assert( capability != NULL );
    if( name != NULL && chain->b_allow_fmt_out_change )
    {
        /* Append the "chain" video filter to the current list.
         * This filter will be used if the requested filter fails to load.
         * It will then try to add a video converter before. */
        char name_chained[strlen(name) + sizeof(",chain")];
        sprintf( name_chained, "%s,chain", name );
        filter->p_module = module_need( filter, capability, name_chained, true );
    }
    else
        filter->p_module = module_need( filter, capability, name, name != NULL );

    if( filter->p_module == NULL )
        goto error;

    if( chain->last == NULL )
    {
        assert( chain->first == NULL );
        chain->first = chained;
    }
    else
        chain->last->next = chained;
    chained->prev = chain->last;
    chain->last = chained;
    chained->next = NULL;

    vlc_mouse_t *mouse = malloc( sizeof(*mouse) );
    if( likely(mouse != NULL) )
        vlc_mouse_Init( mouse );
    chained->mouse = mouse;
    chained->pending = NULL;

    msg_Dbg( chain->obj, "Filter '%s' (%p) appended to chain",
             (name != NULL) ? name : module_get_name(filter->p_module, false),
             (void *)filter );
    return filter;

error:
    if( name != NULL )
        msg_Err( chain->obj, "Failed to create %s '%s'", capability, name );
    else
        msg_Err( chain->obj, "Failed to create %s", capability );
    es_format_Clean( &filter->fmt_out );
    es_format_Clean( &filter->fmt_in );
    vlc_object_delete(filter);
    return NULL;
}