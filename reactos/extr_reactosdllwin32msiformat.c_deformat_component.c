#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_11__ {int /*<<< orphan*/  package; } ;
struct TYPE_10__ {int len; } ;
struct TYPE_9__ {scalar_t__ Action; int /*<<< orphan*/  Directory; } ;
typedef  TYPE_1__ MSICOMPONENT ;
typedef  TYPE_2__ FORMSTR ;
typedef  TYPE_3__ FORMAT ;

/* Variables and functions */
 scalar_t__ INSTALLSTATE_SOURCE ; 
 int /*<<< orphan*/  get_formstr_data (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  lstrcpynW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* msi_get_loaded_component (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msi_get_target_folder (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * msi_resolve_source_folder (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strdupW (int /*<<< orphan*/ ) ; 
 int strlenW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static WCHAR *deformat_component( FORMAT *format, FORMSTR *str, int *ret_len )
{
    WCHAR *key, *ret;
    MSICOMPONENT *comp;

    if (!(key = msi_alloc( (str->len + 1) * sizeof(WCHAR) ))) return NULL;
    lstrcpynW(key, get_formstr_data(format, str), str->len + 1);

    if (!(comp = msi_get_loaded_component( format->package, key )))
    {
        msi_free( key );
        return NULL;
    }
    if (comp->Action == INSTALLSTATE_SOURCE)
        ret = msi_resolve_source_folder( format->package, comp->Directory, NULL );
    else
        ret = strdupW( msi_get_target_folder( format->package, comp->Directory ) );

    if (ret) *ret_len = strlenW( ret );
    else *ret_len = 0;
    msi_free( key );
    return ret;
}