#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * fh; } ;
typedef  int /*<<< orphan*/  PAVIFILE ;
typedef  TYPE_1__ COMMON_AVI_HEADERS ;

/* Variables and functions */
 int AVIFileOpenA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,long) ; 
 scalar_t__ DeleteFileA (char*) ; 
 int /*<<< orphan*/  GetTempPathA (int,char*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  OF_SHARE_DENY_WRITE ; 
 int /*<<< orphan*/  create_avi_file (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  init_test_struct (TYPE_1__*) ; 
 int /*<<< orphan*/  mmioFOURCC (char,char,char,char) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  testfilename ; 

__attribute__((used)) static void test_amh_corruption(void)
{
    COMMON_AVI_HEADERS cah;
    char filename[MAX_PATH];
    PAVIFILE pFile;
    int res;

    GetTempPathA(MAX_PATH, filename);
    strcpy(filename+strlen(filename), testfilename);

    /* Make sure only AVI files with the proper headers will be loaded */
    init_test_struct(&cah);
    cah.fh[3] = mmioFOURCC('A', 'V', 'i', ' ');

    create_avi_file(&cah, filename);
    res = AVIFileOpenA(&pFile, filename, OF_SHARE_DENY_WRITE, 0L);
    ok(res != 0, "Able to open file: error=%u\n", res);

    ok(DeleteFileA(filename) !=0, "Deleting file %s failed\n", filename);
}