#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  module_t ;
struct TYPE_8__ {int e_scope; int /*<<< orphan*/ * p_item; } ;
typedef  TYPE_1__ meta_fetcher_t ;
typedef  int /*<<< orphan*/  input_item_t ;
struct TYPE_9__ {int /*<<< orphan*/  owner; } ;
typedef  TYPE_2__ input_fetcher_t ;

/* Variables and functions */
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/ * module_need (TYPE_1__*,char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  module_unneed (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 TYPE_1__* vlc_custom_create (int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 

__attribute__((used)) static int InvokeModule( input_fetcher_t* fetcher, input_item_t* item,
                         int scope, char const* type )
{
    meta_fetcher_t* mf = vlc_custom_create( fetcher->owner,
                                            sizeof( *mf ), type );
    if( unlikely( !mf ) )
        return VLC_ENOMEM;

    mf->e_scope = scope;
    mf->p_item = item;

    module_t* mf_module = module_need( mf, type, NULL, false );

    if( mf_module )
        module_unneed( mf, mf_module );

    vlc_object_delete(mf);

    return VLC_SUCCESS;
}