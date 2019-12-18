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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  IMimeInternational ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int IMimeInternational_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ MimeOleGetInternat (int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_create(void)
{
    IMimeInternational *internat, *internat2;
    HRESULT hr;
    ULONG ref;

    hr = MimeOleGetInternat(&internat);
    ok(hr == S_OK, "ret %08x\n", hr);
    hr = MimeOleGetInternat(&internat2);
    ok(hr == S_OK, "ret %08x\n", hr);

    /* Under w2k8 it's no longer a singleton */
    if(internat == internat2)
    {
        /* test to show that the object is a singleton with
           a reference held by the dll. */
        ref = IMimeInternational_Release(internat2);
        ok(ref == 2 ||
           ref == 1, /* win95 - object is a static singleton */
           "got %d\n", ref);

        ref = IMimeInternational_Release(internat);
        ok(ref == 1, "got %d\n", ref);
    }
    else
    {
        ref = IMimeInternational_Release(internat2);
        ok(ref == 0, "got %d\n", ref);

        ref = IMimeInternational_Release(internat);
        ok(ref == 0, "got %d\n", ref);
    }

}