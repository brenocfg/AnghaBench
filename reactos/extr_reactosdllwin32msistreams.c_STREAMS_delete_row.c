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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t UINT ;
struct TYPE_6__ {size_t num_streams; TYPE_1__* streams; int /*<<< orphan*/  storage; int /*<<< orphan*/  strings; } ;
struct TYPE_5__ {TYPE_3__* db; } ;
struct TYPE_4__ {int /*<<< orphan*/  stream; int /*<<< orphan*/  str_index; } ;
typedef  TYPE_2__ MSISTREAMSVIEW ;
typedef  TYPE_3__ MSIDATABASE ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 size_t ERROR_FUNCTION_FAILED ; 
 size_t ERROR_OUTOFMEMORY ; 
 size_t ERROR_SUCCESS ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IStorage_DestroyElement (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,struct tagMSIVIEW*,size_t) ; 
 int /*<<< orphan*/ * encode_streamname (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msi_string_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT STREAMS_delete_row(struct tagMSIVIEW *view, UINT row)
{
    MSIDATABASE *db = ((MSISTREAMSVIEW *)view)->db;
    UINT i, num_rows = db->num_streams - 1;
    const WCHAR *name;
    WCHAR *encname;
    HRESULT hr;

    TRACE("(%p %d)!\n", view, row);

    name = msi_string_lookup( db->strings, db->streams[row].str_index, NULL );
    if (!(encname = encode_streamname( FALSE, name ))) return ERROR_OUTOFMEMORY;
    hr = IStorage_DestroyElement( db->storage, encname );
    msi_free( encname );
    if (FAILED( hr ))
        return ERROR_FUNCTION_FAILED;
    hr = IStream_Release( db->streams[row].stream );
    if (FAILED( hr ))
        return ERROR_FUNCTION_FAILED;

    for (i = row; i < num_rows; i++)
        db->streams[i] = db->streams[i + 1];
    db->num_streams = num_rows;

    return ERROR_SUCCESS;
}