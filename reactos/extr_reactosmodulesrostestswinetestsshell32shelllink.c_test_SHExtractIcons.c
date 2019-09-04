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
typedef  unsigned int UINT ;
typedef  scalar_t__ HICON ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyIcon (scalar_t__) ; 
 int MAKELONG (int,int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 unsigned int pSHExtractIconsW (char const*,int,int,int,scalar_t__*,unsigned int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_SHExtractIcons(void)
{
    static const WCHAR notepadW[] = {'n','o','t','e','p','a','d','.','e','x','e',0};
    static const WCHAR shell32W[] = {'s','h','e','l','l','3','2','.','d','l','l',0};
    static const WCHAR emptyW[] = {0};
    UINT ret, ret2;
    HICON icons[256];
    UINT ids[256], i;

    if (!pSHExtractIconsW)
    {
        win_skip("SHExtractIconsW not available\n");
        return;
    }

    ret = pSHExtractIconsW(emptyW, 0, 16, 16, icons, ids, 1, 0);
    ok(ret == ~0u, "got %u\n", ret);

    ret = pSHExtractIconsW(notepadW, 0, 16, 16, NULL, NULL, 1, 0);
    ok(ret == 1 || broken(ret == 2) /* win2k */, "got %u\n", ret);

    icons[0] = (HICON)0xdeadbeef;
    ret = pSHExtractIconsW(notepadW, 0, 16, 16, icons, NULL, 1, 0);
    ok(ret == 1, "got %u\n", ret);
    ok(icons[0] != (HICON)0xdeadbeef, "icon not set\n");
    DestroyIcon(icons[0]);

    icons[0] = (HICON)0xdeadbeef;
    ids[0] = 0xdeadbeef;
    ret = pSHExtractIconsW(notepadW, 0, 16, 16, icons, ids, 1, 0);
    ok(ret == 1, "got %u\n", ret);
    ok(icons[0] != (HICON)0xdeadbeef, "icon not set\n");
    ok(ids[0] != 0xdeadbeef, "id not set\n");
    DestroyIcon(icons[0]);

    ret = pSHExtractIconsW(shell32W, 0, 16, 16, NULL, NULL, 0, 0);
    ret2 = pSHExtractIconsW(shell32W, 4, MAKELONG(32,16), MAKELONG(32,16), NULL, NULL, 256, 0);
    ok(ret && ret == ret2,
       "icon count should be independent of requested icon sizes and base icon index\n");

    ret = pSHExtractIconsW(shell32W, 0, 16, 16, icons, ids, 0, 0);
    ok(ret == ~0u || !ret /* < vista */, "got %u\n", ret);

    ret = pSHExtractIconsW(shell32W, 0, 16, 16, icons, ids, 3, 0);
    ok(ret == 3, "got %u\n", ret);
    for (i = 0; i < ret; i++) DestroyIcon(icons[i]);

    /* count must be a multiple of two when getting two sizes */
    ret = pSHExtractIconsW(shell32W, 0, MAKELONG(16,32), MAKELONG(16,32), icons, ids, 3, 0);
    ok(!ret /* vista */ || ret == 4, "got %u\n", ret);
    for (i = 0; i < ret; i++) DestroyIcon(icons[i]);

    ret = pSHExtractIconsW(shell32W, 0, MAKELONG(16,32), MAKELONG(16,32), icons, ids, 4, 0);
    ok(ret == 4, "got %u\n", ret);
    for (i = 0; i < ret; i++) DestroyIcon(icons[i]);
}