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
typedef  int cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _cmsMalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreateLab4Profile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cmsGetPostScriptCSA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cmsOpenProfileFromFile (int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove (char const*) ; 

__attribute__((used)) static
void GenerateCSA(const char* cInProf, const char* FileName)
{
    cmsHPROFILE hProfile;
    cmsUInt32Number n;
    char* Buffer;
    cmsContext BuffThread = DbgThread();
    FILE* o;


    if (cInProf == NULL)
        hProfile = cmsCreateLab4Profile(DbgThread(), NULL);
    else
        hProfile = cmsOpenProfileFromFile(DbgThread(), cInProf, "r");

    n = cmsGetPostScriptCSA(DbgThread(), hProfile, 0, 0, NULL, 0);
    if (n == 0) return;

    Buffer = (char*) _cmsMalloc(BuffThread, n + 1);
    cmsGetPostScriptCSA(DbgThread(), hProfile, 0, 0, Buffer, n);
    Buffer[n] = 0;

    if (FileName != NULL) {
        o = fopen(FileName, "wb");
        fwrite(Buffer, n, 1, o);
        fclose(o);
    }

    _cmsFree(BuffThread, Buffer);
    cmsCloseProfile(DbgThread(), hProfile);
    if (FileName != NULL)
        remove(FileName);
}