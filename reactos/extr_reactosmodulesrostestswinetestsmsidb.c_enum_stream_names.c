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
typedef  size_t ULONG ;
struct TYPE_5__ {size_t size; int /*<<< orphan*/ * data; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  pwcsName; } ;
typedef  TYPE_1__ STATSTG ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  IEnumSTATSTG ;
typedef  size_t HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (size_t) ; 
 size_t IEnumSTATSTG_Next (int /*<<< orphan*/ *,int,TYPE_1__*,size_t*) ; 
 int /*<<< orphan*/  IEnumSTATSTG_Release (int /*<<< orphan*/ *) ; 
 size_t IStorage_EnumElements (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 size_t IStorage_OpenStream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 size_t IStream_Read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int STGM_READ ; 
 int STGM_SHARE_EXCLUSIVE ; 
 size_t S_OK ; 
 scalar_t__ TRUE ; 
 TYPE_2__* database_table_data ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void enum_stream_names(IStorage *stg)
{
    IEnumSTATSTG *stgenum = NULL;
    IStream *stm;
    HRESULT hr;
    STATSTG stat;
    ULONG n, count;
    BYTE data[MAX_PATH];
    BYTE check[MAX_PATH];
    DWORD sz;

    memset(check, 'a', MAX_PATH);

    hr = IStorage_EnumElements(stg, 0, NULL, 0, &stgenum);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    n = 0;
    while(TRUE)
    {
        count = 0;
        hr = IEnumSTATSTG_Next(stgenum, 1, &stat, &count);
        if(FAILED(hr) || !count)
            break;

        ok(!lstrcmpW(stat.pwcsName, database_table_data[n].name),
           "Expected table %d name to match\n", n);

        stm = NULL;
        hr = IStorage_OpenStream(stg, stat.pwcsName, NULL,
                                 STGM_READ | STGM_SHARE_EXCLUSIVE, 0, &stm);
        ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
        ok(stm != NULL, "Expected non-NULL stream\n");

        CoTaskMemFree(stat.pwcsName);

        sz = MAX_PATH;
        memset(data, 'a', MAX_PATH);
        hr = IStream_Read(stm, data, sz, &count);
        ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

        ok(count == database_table_data[n].size,
           "Expected %d, got %d\n", database_table_data[n].size, count);

        if (!database_table_data[n].size)
            ok(!memcmp(data, check, MAX_PATH), "data should not be changed\n");
        else
            ok(!memcmp(data, database_table_data[n].data, database_table_data[n].size),
               "Expected table %d data to match\n", n);

        IStream_Release(stm);
        n++;
    }

    ok(n == 3, "Expected 3, got %d\n", n);

    IEnumSTATSTG_Release(stgenum);
}