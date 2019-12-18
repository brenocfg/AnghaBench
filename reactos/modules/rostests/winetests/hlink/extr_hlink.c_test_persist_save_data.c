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
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IPersistStream ;
typedef  int /*<<< orphan*/  IHlink ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  unsigned int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ CreateStreamOnHGlobal (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int FALSE ; 
 scalar_t__ GetHGlobalFromStream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned char* GlobalLock (int /*<<< orphan*/ ) ; 
 unsigned int GlobalSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 scalar_t__ IHlink_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IPersistStream ; 
 int /*<<< orphan*/  IPersistStream_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IPersistStream_Save (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int TRUE ; 
 scalar_t__ broken (int) ; 
 unsigned char const* expected_hlink_data2 ; 
 unsigned char const* expected_hlink_data2_ie7 ; 
 unsigned char const* expected_hlink_data3 ; 
 unsigned char const* expected_hlink_data3_ie7 ; 
 unsigned char const* expected_hlink_data5_ie7 ; 
 unsigned char const* expected_hlink_data_ie7 ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void test_persist_save_data(const char *testname, IHlink *lnk,
                                   const unsigned char *expected_data,
                                   unsigned int expected_data_size,
                                   const unsigned char *expected_data_alt,
                                   unsigned int expected_data_alt_size)
{
    HRESULT hr;
    IStream *stream;
    IPersistStream *ps;
    HGLOBAL hglobal;
    DWORD data_size;
    const unsigned char *data;
    DWORD i;
    BOOL same;

    hr = IHlink_QueryInterface(lnk, &IID_IPersistStream, (void **)&ps);
    ok(hr == S_OK, "IHlink_QueryInterface failed with error 0x%08x\n", hr);

    hr = CreateStreamOnHGlobal(NULL, TRUE, &stream);
    ok(hr == S_OK, "CreateStreamOnHGlobal failed with error 0x%08x\n", hr);

    hr = IPersistStream_Save(ps, stream, TRUE);
    ok(hr == S_OK, "IPersistStream_Save failed with error 0x%08x\n", hr);

    hr = GetHGlobalFromStream(stream, &hglobal);
    ok(hr == S_OK, "GetHGlobalFromStream failed with error 0x%08x\n", hr);

    data_size = GlobalSize(hglobal);

    data = GlobalLock(hglobal);

    /* first check we have the right amount of data */
    ok((data_size == expected_data_size) ||
       (data_size == expected_data_alt_size),
       "%s: Size of saved data differs (expected %d or %d, actual %d)\n",
       testname, expected_data_size, expected_data_alt_size, data_size);

    same = TRUE;
    /* then do a byte-by-byte comparison */
    for (i = 0; i < min(data_size, expected_data_size); i++)
    {
        if ((expected_data[i] != data[i]) &&
            (((expected_data != expected_hlink_data2) &&
              (expected_data != expected_hlink_data3)) ||
             ((i < 52 || i >= 56) && (i < 80 || i >= 84))))
        {
            same = FALSE;
            break;
        }
    }

    if (!same && (expected_data_alt != expected_data))
    {
        /* then try the alternate data */
        same = TRUE;
        for (i = 0; i < min(data_size, expected_data_alt_size); i++)
        {
            if ((expected_data_alt == expected_hlink_data_ie7  && i == 89)  /* Win10 */ ||
                (expected_data_alt == expected_hlink_data2_ie7 && i == 109) /* Win10 */ ||
                (expected_data_alt == expected_hlink_data3_ie7 && i == 109) /* Win10 */ ||
                (expected_data_alt == expected_hlink_data5_ie7 && i == 107) /* Win10 */)
            {
                ok(data[i] == 0 || broken(data[i] == 1) || broken(data[i] == 3),
                   "Expected 0 or 1, got %d\n", data[i]);
                continue;
            }
            if ((expected_data_alt[i] != data[i]) &&
                (((expected_data_alt != expected_hlink_data2) &&
                  (expected_data_alt != expected_hlink_data3)) ||
                 ((i < 52 || i >= 56) && (i < 80 || i >= 84))))
            {
                same = FALSE;
                break;
            }
        }
    }

    ok(same, "%s: Saved data differs\n", testname);
    if (!same)
    {
        for (i = 0; i < data_size; i++)
        {
            if (i % 8 == 0) printf("    ");
            printf("0x%02x,", data[i]);
            if (i % 8 == 7) printf("\n");
        }
        printf("\n");
    }

    GlobalUnlock(hglobal);

    IStream_Release(stream);
    IPersistStream_Release(ps);
}