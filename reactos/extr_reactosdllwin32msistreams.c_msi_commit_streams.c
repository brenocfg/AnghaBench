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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t UINT ;
struct TYPE_5__ {size_t num_streams; TYPE_1__* streams; int /*<<< orphan*/  storage; int /*<<< orphan*/  strings; } ;
struct TYPE_4__ {int /*<<< orphan*/  stream; int /*<<< orphan*/  str_index; } ;
typedef  TYPE_2__ MSIDATABASE ;
typedef  int /*<<< orphan*/  IStream ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 size_t ERROR_FUNCTION_FAILED ; 
 size_t ERROR_OUTOFMEMORY ; 
 size_t ERROR_SUCCESS ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IStorage_CreateStream (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IStream_Commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int STGM_SHARE_EXCLUSIVE ; 
 int STGM_WRITE ; 
 scalar_t__ STG_E_FILEALREADYEXISTS ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,size_t) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * encode_streamname (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msi_string_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ write_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

UINT msi_commit_streams( MSIDATABASE *db )
{
    UINT i;
    const WCHAR *name;
    WCHAR *encname;
    IStream *stream;
    HRESULT hr;

    TRACE("got %u streams\n", db->num_streams);

    for (i = 0; i < db->num_streams; i++)
    {
        name = msi_string_lookup( db->strings, db->streams[i].str_index, NULL );
        if (!(encname = encode_streamname( FALSE, name ))) return ERROR_OUTOFMEMORY;

        hr = IStorage_CreateStream( db->storage, encname, STGM_WRITE|STGM_SHARE_EXCLUSIVE, 0, 0, &stream );
        if (SUCCEEDED( hr ))
        {
            hr = write_stream( stream, db->streams[i].stream );
            if (FAILED( hr ))
            {
                ERR("failed to write stream %s (hr = %08x)\n", debugstr_w(encname), hr);
                msi_free( encname );
                IStream_Release( stream );
                return ERROR_FUNCTION_FAILED;
            }
            hr = IStream_Commit( stream, 0 );
            IStream_Release( stream );
            if (FAILED( hr ))
            {
                ERR("failed to commit stream %s (hr = %08x)\n", debugstr_w(encname), hr);
                msi_free( encname );
                return ERROR_FUNCTION_FAILED;
            }
        }
        else if (hr != STG_E_FILEALREADYEXISTS)
        {
            ERR("failed to create stream %s (hr = %08x)\n", debugstr_w(encname), hr);
            msi_free( encname );
            return ERROR_FUNCTION_FAILED;
        }
        msi_free( encname );
    }

    return ERROR_SUCCESS;
}