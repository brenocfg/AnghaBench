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
typedef  int /*<<< orphan*/  buf ;
typedef  void* ULONG ;
typedef  void IUnknown ;
typedef  int /*<<< orphan*/  IOleContainer ;
typedef  int /*<<< orphan*/  IEnumUnknown ;
typedef  void* HRESULT ;

/* Variables and functions */
 void* IEnumUnknown_Next (int /*<<< orphan*/ *,int,void**,void**) ; 
 int /*<<< orphan*/  IEnumUnknown_Release (int /*<<< orphan*/ *) ; 
 void* IOleContainer_EnumObjects (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  OLECONTF_EMBEDDINGS ; 
 void* S_FALSE ; 
 void* S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_enum_objects(IOleContainer *container)
{
    IEnumUnknown *enum_unknown;
    IUnknown *buf[100] = {(void*)0xdeadbeef};
    ULONG fetched;
    HRESULT hres;

    enum_unknown = NULL;
    hres = IOleContainer_EnumObjects(container, OLECONTF_EMBEDDINGS, &enum_unknown);
    ok(hres == S_OK, "EnumObjects failed: %08x\n", hres);
    ok(enum_unknown != NULL, "enum_unknown == NULL\n");

    fetched = 0xdeadbeef;
    hres = IEnumUnknown_Next(enum_unknown, sizeof(buf)/sizeof(*buf), buf, &fetched);
    ok(hres == S_FALSE, "Next returned %08x\n", hres);
    ok(!fetched, "fetched = %d\n", fetched);
    ok(buf[0] == (void*)0xdeadbeef, "buf[0] = %p\n", buf[0]);

    fetched = 0xdeadbeef;
    hres = IEnumUnknown_Next(enum_unknown, 1, buf, &fetched);
    ok(hres == S_FALSE, "Next returned %08x\n", hres);
    ok(!fetched, "fetched = %d\n", fetched);

    hres = IEnumUnknown_Next(enum_unknown, 1, buf, NULL);
    ok(hres == S_FALSE, "Next returned %08x\n", hres);

    IEnumUnknown_Release(enum_unknown);
}