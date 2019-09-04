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
struct tagMSIVIEW {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int /*<<< orphan*/  db; } ;
struct TYPE_4__ {int /*<<< orphan*/  fetch_int; } ;
typedef  TYPE_2__ MSITABLEVIEW ;
typedef  int /*<<< orphan*/  IStream ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__,...) ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 scalar_t__ get_stream_name (TYPE_2__*,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 scalar_t__ msi_get_stream (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static UINT TABLE_fetch_stream( struct tagMSIVIEW *view, UINT row, UINT col, IStream **stm )
{
    MSITABLEVIEW *tv = (MSITABLEVIEW*)view;
    UINT r;
    WCHAR *name;

    if( !view->ops->fetch_int )
        return ERROR_INVALID_PARAMETER;

    r = get_stream_name( tv, row, &name );
    if (r != ERROR_SUCCESS)
    {
        ERR("fetching stream, error = %u\n", r);
        return r;
    }

    r = msi_get_stream( tv->db, name, stm );
    if (r != ERROR_SUCCESS)
        ERR("fetching stream %s, error = %u\n", debugstr_w(name), r);

    msi_free( name );
    return r;
}