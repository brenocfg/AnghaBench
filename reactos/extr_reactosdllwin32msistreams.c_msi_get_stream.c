#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_6__ {scalar_t__ QuadPart; } ;
struct TYPE_5__ {int /*<<< orphan*/ * stream; } ;
typedef  TYPE_1__ MSISTREAM ;
typedef  int /*<<< orphan*/  MSIDATABASE ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_OUTOFMEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IStream_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ *,TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 scalar_t__ append_stream (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * encode_streamname (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 TYPE_1__* find_stream (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

UINT msi_get_stream( MSIDATABASE *db, const WCHAR *name, IStream **ret )
{
    MSISTREAM *stream;
    WCHAR *encname;
    HRESULT hr;
    UINT r;

    if ((stream = find_stream( db, name )))
    {
        LARGE_INTEGER pos;

        pos.QuadPart = 0;
        hr = IStream_Seek( stream->stream, pos, STREAM_SEEK_SET, NULL );
        if (FAILED( hr ))
            return ERROR_FUNCTION_FAILED;

        *ret = stream->stream;
        IStream_AddRef( *ret );
        return ERROR_SUCCESS;
    }

    if (!(encname = encode_streamname( FALSE, name )))
        return ERROR_OUTOFMEMORY;

    hr = open_stream( db, encname, ret );
    msi_free( encname );
    if (FAILED( hr ))
        return ERROR_FUNCTION_FAILED;

    r = append_stream( db, name, *ret );
    if (r != ERROR_SUCCESS)
    {
        IStream_Release( *ret );
        return r;
    }

    IStream_AddRef( *ret );
    return ERROR_SUCCESS;
}