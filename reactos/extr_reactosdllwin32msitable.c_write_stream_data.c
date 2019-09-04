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
typedef  scalar_t__ ULONG ;
struct TYPE_5__ {scalar_t__ QuadPart; } ;
typedef  TYPE_1__ ULARGE_INTEGER ;
typedef  scalar_t__ UINT ;
struct TYPE_6__ {scalar_t__ QuadPart; } ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  LPCVOID ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStorage_CreateStream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStorage_OpenStream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ *,TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_SetSize (int /*<<< orphan*/ *,TYPE_1__) ; 
 int /*<<< orphan*/  IStream_Write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int STGM_SHARE_EXCLUSIVE ; 
 int STGM_WRITE ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  encode_streamname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ ) ; 

UINT write_stream_data( IStorage *stg, LPCWSTR stname,
                        LPCVOID data, UINT sz, BOOL bTable )
{
    HRESULT r;
    UINT ret = ERROR_FUNCTION_FAILED;
    ULONG count;
    IStream *stm = NULL;
    ULARGE_INTEGER size;
    LARGE_INTEGER pos;
    LPWSTR encname;

    encname = encode_streamname(bTable, stname );
    r = IStorage_OpenStream( stg, encname, NULL, 
            STGM_WRITE | STGM_SHARE_EXCLUSIVE, 0, &stm);
    if( FAILED(r) )
    {
        r = IStorage_CreateStream( stg, encname,
                STGM_WRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stm);
    }
    msi_free( encname );
    if( FAILED( r ) )
    {
        WARN("open stream failed r = %08x\n", r);
        return ret;
    }

    size.QuadPart = sz;
    r = IStream_SetSize( stm, size );
    if( FAILED( r ) )
    {
        WARN("Failed to SetSize\n");
        goto end;
    }

    pos.QuadPart = 0;
    r = IStream_Seek( stm, pos, STREAM_SEEK_SET, NULL );
    if( FAILED( r ) )
    {
        WARN("Failed to Seek\n");
        goto end;
    }

    if (sz)
    {
        r = IStream_Write(stm, data, sz, &count );
        if( FAILED( r ) || ( count != sz ) )
        {
            WARN("Failed to Write\n");
            goto end;
        }
    }

    ret = ERROR_SUCCESS;

end:
    IStream_Release( stm );

    return ret;
}