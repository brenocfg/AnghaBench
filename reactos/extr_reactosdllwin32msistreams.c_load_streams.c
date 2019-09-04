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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/  num_streams; int /*<<< orphan*/  storage; } ;
struct TYPE_8__ {scalar_t__ type; int* pwcsName; } ;
typedef  TYPE_1__ STATSTG ;
typedef  TYPE_2__ MSIDATABASE ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IEnumSTATSTG ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (int*) ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEnumSTATSTG_Next (int /*<<< orphan*/ *,int,TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  IEnumSTATSTG_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStorage_EnumElements (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  MAX_STREAM_NAME_LEN ; 
 scalar_t__ STGTY_STREAM ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ append_stream (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decode_streamname (int*,int /*<<< orphan*/ *) ; 
 scalar_t__ find_stream (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_stream (TYPE_2__*,int*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static UINT load_streams( MSIDATABASE *db )
{
    WCHAR decoded[MAX_STREAM_NAME_LEN + 1];
    IEnumSTATSTG *stgenum;
    STATSTG stat;
    HRESULT hr;
    UINT count, r = ERROR_SUCCESS;
    IStream *stream;

    hr = IStorage_EnumElements( db->storage, 0, NULL, 0, &stgenum );
    if (FAILED( hr ))
        return ERROR_FUNCTION_FAILED;

    for (;;)
    {
        count = 0;
        hr = IEnumSTATSTG_Next( stgenum, 1, &stat, &count );
        if (FAILED( hr ) || !count)
            break;

        /* table streams are not in the _Streams table */
        if (stat.type != STGTY_STREAM || *stat.pwcsName == 0x4840)
        {
            CoTaskMemFree( stat.pwcsName );
            continue;
        }
        decode_streamname( stat.pwcsName, decoded );
        if (find_stream( db, decoded ))
        {
            CoTaskMemFree( stat.pwcsName );
            continue;
        }
        TRACE("found new stream %s\n", debugstr_w( decoded ));

        hr = open_stream( db, stat.pwcsName, &stream );
        CoTaskMemFree( stat.pwcsName );
        if (FAILED( hr ))
        {
            ERR("unable to open stream %08x\n", hr);
            r = ERROR_FUNCTION_FAILED;
            break;
        }

        r = append_stream( db, decoded, stream );
        if (r != ERROR_SUCCESS)
            break;
    }

    TRACE("loaded %u streams\n", db->num_streams);
    IEnumSTATSTG_Release( stgenum );
    return r;
}