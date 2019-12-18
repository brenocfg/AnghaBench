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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IHlink ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ CreateFileMoniker (char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  HLINKGETREF_RELATIVE ; 
 int HLINKSETF_LOCATION ; 
 int HLINKSETF_TARGET ; 
 scalar_t__ HlinkCreateFromString (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHlink_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IHlink ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * getMonikerRef (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getStringRef (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  setMonikerRef (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  setStringRef (int /*<<< orphan*/ *,int,char const*,char const*) ; 
 scalar_t__ wine_dbgstr_w (char const*) ; 

__attribute__((used)) static void test_HlinkMoniker(void)
{
    IHlink *hlink;
    IMoniker *aMon, *file_mon;
    static const WCHAR emptyW[] = {0};
    static const WCHAR wordsW[] = {'w','o','r','d','s',0};
    static const WCHAR aW[] = {'a',0};
    static const WCHAR bW[] = {'b',0};
    HRESULT hres;

    hres = HlinkCreateFromString(NULL, NULL, NULL, NULL, 0, NULL, &IID_IHlink, (void**)&hlink);
    ok(hres == S_OK, "HlinkCreateFromString failed: 0x%08x\n", hres);
    getStringRef(hlink, NULL, NULL);
    getMonikerRef(hlink, NULL, NULL, HLINKGETREF_RELATIVE);

    /* setting a string target creates a moniker reference */
    setStringRef(hlink, HLINKSETF_TARGET | HLINKSETF_LOCATION, aW, wordsW);
    getStringRef(hlink, aW, wordsW);
    aMon = getMonikerRef(hlink, (IMoniker*)0xFFFFFFFF, wordsW, HLINKGETREF_RELATIVE);
    ok(aMon != NULL, "Moniker from %s target should not be NULL\n", wine_dbgstr_w(aW));
    if(aMon)
        IMoniker_Release(aMon);

    /* setting target & location to the empty string deletes the moniker
     * reference */
    setStringRef(hlink, HLINKSETF_TARGET | HLINKSETF_LOCATION, emptyW, emptyW);
    getStringRef(hlink, NULL, NULL);
    getMonikerRef(hlink, NULL, NULL, HLINKGETREF_RELATIVE);

    /* setting a moniker target also sets the target string to that moniker's
     * display name */
    hres = CreateFileMoniker(bW, &file_mon);
    ok(hres == S_OK, "CreateFileMoniker failed: 0x%08x\n", hres);

    setMonikerRef(hlink, HLINKSETF_TARGET | HLINKSETF_LOCATION, file_mon, wordsW);
    getStringRef(hlink, bW, wordsW);
    getMonikerRef(hlink, file_mon, wordsW, HLINKGETREF_RELATIVE);

    IMoniker_Release(file_mon);

    IHlink_Release(hlink);
}