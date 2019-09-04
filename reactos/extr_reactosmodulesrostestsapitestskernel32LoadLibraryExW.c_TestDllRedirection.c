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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LoadLibraryExW (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ActivateCtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * _CreateActCtxFromFile (char*,int) ; 
 int /*<<< orphan*/  _DeactivateCtx (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _TestVesion (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

VOID TestDllRedirection()
{
    HANDLE dll1, dll2, h;
    ULONG_PTR cookie;

    /* Try to load the libraries without sxs */
    dll1 = LoadLibraryExW(L"kernel32test_versioned.dll",0 , 0);
    ok (dll1 != NULL, "LoadLibraryExW failed\n");
    dll2 = LoadLibraryExW(L"testdata\\kernel32test_versioned.dll",0 , 0);
    ok (dll2 != NULL, "LoadLibraryExW failed\n");

    ok (dll1 != dll2, "\n");
    _TestVesion(dll1, 1, __LINE__);
    _TestVesion(dll2, 2, __LINE__);

    FreeLibrary(dll1);
    FreeLibrary(dll2);

    dll1 = LoadLibraryExW(L"kernel32test_versioned.dll",0 , 0);
    ok (dll1 != NULL, "LoadLibraryExW failed\n");

    /* redir2dep.manifest defines an assembly with nothing but a dependency on redirtest2 assembly */
    /* redirtest2.manifest defines an assembly that contains kernel32test_versioned.dll */
    /* In win10 it is enought to load and activate redirtest2 */
    /* In win2k3 however the only way to trigger the redirection is to load and activate redir2dep */
    h = _CreateActCtxFromFile(L"testdata\\redir2dep.manifest", __LINE__);
    _ActivateCtx(h, &cookie, __LINE__);
    dll2 = LoadLibraryExW(L"kernel32test_versioned.dll",0 , 0);
    _DeactivateCtx(cookie, __LINE__);
    ok (dll2 != NULL, "LoadLibraryExW failed\n");

    ok (dll1 != dll2, "\n");
    _TestVesion(dll1, 1, __LINE__);
    _TestVesion(dll2, 2, __LINE__);

    FreeLibrary(dll1);
    FreeLibrary(dll2);

    dll1 = LoadLibraryExW(L"comctl32.dll",0 ,0);
    ok (dll1 != NULL, "LoadLibraryExW failed\n");

    h = _CreateActCtxFromFile(L"comctl32dep.manifest", __LINE__);
    _ActivateCtx(h, &cookie, __LINE__);
    dll2 = LoadLibraryExW(L"comctl32.dll",0 , 0);
    _DeactivateCtx(cookie, __LINE__);
    ok (dll2 != NULL, "LoadLibraryExW failed\n");

    ok (dll1 != dll2, "\n");

}