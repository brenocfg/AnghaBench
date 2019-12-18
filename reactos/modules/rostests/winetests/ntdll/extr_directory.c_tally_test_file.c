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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {int attr; int /*<<< orphan*/  nfound; scalar_t__ attr_done; int /*<<< orphan*/  description; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int FileAttributes; int FileNameLength; int /*<<< orphan*/ * FileName; } ;
typedef  TYPE_1__ FILE_BOTH_DIRECTORY_INFORMATION ;
typedef  int DWORD ;

/* Variables and functions */
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int FILE_ATTRIBUTE_HIDDEN ; 
 int FILE_ATTRIBUTE_REPARSE_POINT ; 
 int FILE_ATTRIBUTE_SYSTEM ; 
 scalar_t__ TRUE ; 
 int lstrlenW (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,...) ; 
 int test_dir_count ; 
 TYPE_2__* testfiles ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_wn (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void tally_test_file(FILE_BOTH_DIRECTORY_INFORMATION *dir_info)
{
    int i;
    DWORD attribmask =
      (FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_DIRECTORY|FILE_ATTRIBUTE_REPARSE_POINT);
    DWORD attrib = dir_info->FileAttributes & attribmask;
    WCHAR *nameW = dir_info->FileName;
    int namelen = dir_info->FileNameLength / sizeof(WCHAR);

    for (i = 0; i < test_dir_count; i++) {
        int len = lstrlenW(testfiles[i].name);
        if (namelen != len || memcmp(nameW, testfiles[i].name, len*sizeof(WCHAR)))
            continue;
        if (!testfiles[i].attr_done) {
            ok (attrib == (testfiles[i].attr & attribmask), "file %s: expected %s (%x), got %x (is your linux new enough?)\n", wine_dbgstr_w(testfiles[i].name), testfiles[i].description, testfiles[i].attr, attrib);
            testfiles[i].attr_done = TRUE;
        }
        testfiles[i].nfound++;
        break;
    }
    ok(i < test_dir_count, "unexpected file found %s\n", wine_dbgstr_wn(dir_info->FileName, namelen));
}