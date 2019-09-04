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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  TAGREF ;
typedef  int TAGID ;
typedef  int TAG ;
typedef  int /*<<< orphan*/ * PDB ;
typedef  int /*<<< orphan*/ * HSDB ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  SDB_DATABASE_MAIN_SHIM ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  mbstowcs (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pSdbGetTagFromTagID (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pSdbInitDatabase (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pSdbReleaseDatabase (int /*<<< orphan*/ *) ; 
 scalar_t__ pSdbTagRefToTagID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void ValidateShim(TAGREF trLayer, const char* name)
{
    HSDB hsdb = pSdbInitDatabase(SDB_DATABASE_MAIN_SHIM, NULL);
    ok(hsdb != NULL, "Expected a valid handle\n");
    if (hsdb)
    {
        PDB pdb = NULL;
        TAGID tagid = 0xdeadbeef;
        WCHAR nameW[256] = { 0 };
        BOOL ret;

        mbstowcs(nameW, name, strlen(name));

        ret = pSdbTagRefToTagID(hsdb, trLayer, &pdb, &tagid);
        ok(ret == TRUE, "Expected pSdbTagRefToTagID to succeed\n");
        if (ret)
        {
            TAG tag;
            ok(pdb != NULL, "Expected pdb to be a valid pointer\n");
            ok(tagid != 0 && tagid != 0xdeadbeef, "Expected tagid to be a valid tag id, was: 0x%x\n", tagid);
            tag = pSdbGetTagFromTagID(pdb, tagid);
            ok(tag == 0x700b, "Expected tag to be 0x700b, was 0x%x\n", (DWORD)tag);
        }

        pSdbReleaseDatabase(hsdb);
    }
}