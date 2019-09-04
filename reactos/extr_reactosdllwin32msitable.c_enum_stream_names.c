#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ ULONG ;
struct TYPE_3__ {int /*<<< orphan*/ * pwcsName; } ;
typedef  TYPE_1__ STATSTG ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  IEnumSTATSTG ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEnumSTATSTG_Next (int /*<<< orphan*/ *,int,TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  IEnumSTATSTG_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStorage_EnumElements (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decode_streamname (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void enum_stream_names( IStorage *stg )
{
    IEnumSTATSTG *stgenum = NULL;
    HRESULT r;
    STATSTG stat;
    ULONG n, count;
    WCHAR name[0x40];

    r = IStorage_EnumElements( stg, 0, NULL, 0, &stgenum );
    if( FAILED( r ) )
        return;

    n = 0;
    while( 1 )
    {
        count = 0;
        r = IEnumSTATSTG_Next( stgenum, 1, &stat, &count );
        if( FAILED( r ) || !count )
            break;
        decode_streamname( stat.pwcsName, name );
        TRACE("stream %2d -> %s %s\n", n,
              debugstr_w(stat.pwcsName), debugstr_w(name) );
        CoTaskMemFree( stat.pwcsName );
        n++;
    }

    IEnumSTATSTG_Release( stgenum );
}