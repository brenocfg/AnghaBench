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
struct shellExpectedValues {int numTypes; int* types; int /*<<< orphan*/  folder; } ;
typedef  int BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
#define  PT_DRIVE 131 
#define  PT_DRIVE2 130 
#define  PT_FOLDER 129 
#define  PT_IESPECIAL2 128 
 scalar_t__ TRUE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  getFolderName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ pSHGetFolderLocation ; 
 int testSHGetFolderLocation (int /*<<< orphan*/ ) ; 
 int testSHGetSpecialFolderLocation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_SHGetFolderPath (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_SHGetSpecialFolderPath (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_ShellValues(const struct shellExpectedValues testEntries[],
 int numEntries, BOOL optional)
{
    int i;

    for (i = 0; i < numEntries; i++)
    {
        BYTE type;
        int j;
        BOOL foundTypeMatch = FALSE;

        if (pSHGetFolderLocation)
        {
            type = testSHGetFolderLocation(testEntries[i].folder);
            for (j = 0; !foundTypeMatch && j < testEntries[i].numTypes; j++)
                if (testEntries[i].types[j] == type)
                    foundTypeMatch = TRUE;
            ok(foundTypeMatch || optional || broken(type == 0xff) /* Win9x */,
             "%s has unexpected type %d (0x%02x)\n",
             getFolderName(testEntries[i].folder), type, type);
        }
        type = testSHGetSpecialFolderLocation(testEntries[i].folder);
        for (j = 0, foundTypeMatch = FALSE; !foundTypeMatch &&
         j < testEntries[i].numTypes; j++)
            if (testEntries[i].types[j] == type)
                foundTypeMatch = TRUE;
        ok(foundTypeMatch || optional || broken(type == 0xff) /* Win9x */,
         "%s has unexpected type %d (0x%02x)\n",
         getFolderName(testEntries[i].folder), type, type);
        switch (type)
        {
            case PT_FOLDER:
            case PT_DRIVE:
            case PT_DRIVE2:
            case PT_IESPECIAL2:
                test_SHGetFolderPath(optional, testEntries[i].folder);
                test_SHGetSpecialFolderPath(optional, testEntries[i].folder);
                break;
        }
    }
}