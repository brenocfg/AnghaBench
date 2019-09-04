#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct table_data {size_t size; int /*<<< orphan*/  data; int /*<<< orphan*/  name; } ;
typedef  size_t UINT ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  size_t DWORD ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStorage_CreateStream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,size_t*) ; 
 int STGM_SHARE_EXCLUSIVE ; 
 int STGM_WRITE ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void write_tables( IStorage *stg, const struct table_data *tables, UINT num_tables )
{
    IStream *stm;
    DWORD i, count;
    HRESULT r;

    for (i = 0; i < num_tables; i++)
    {
        r = IStorage_CreateStream( stg, tables[i].name, STGM_WRITE|STGM_SHARE_EXCLUSIVE, 0, 0, &stm );
        if (FAILED( r ))
        {
            ok( 0, "failed to create stream 0x%08x\n", r );
            continue;
        }

        r = IStream_Write( stm, tables[i].data, tables[i].size, &count );
        if (FAILED( r ) || count != tables[i].size)
            ok( 0, "failed to write stream\n" );
        IStream_Release( stm );
    }
}