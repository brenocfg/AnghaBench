#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  revision; int /*<<< orphan*/  build; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct assembly_identity {char const* arch; char const* public_key; char const* language; char const* name; TYPE_1__ version; } ;
typedef  int /*<<< orphan*/  mskeyW ;
typedef  char WCHAR ;
typedef  int SIZE_T ;

/* Variables and functions */
 char* RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  sprintfW (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcatW (char*,char const*) ; 
 int /*<<< orphan*/  strcpyW (char*,char const*) ; 
 int strlenW (char const*) ; 
 int /*<<< orphan*/  version_formatW ; 

__attribute__((used)) static WCHAR *build_assembly_dir(struct assembly_identity* ai)
{
    static const WCHAR undW[] = {'_',0};
    static const WCHAR noneW[] = {'n','o','n','e',0};
    static const WCHAR mskeyW[] = {'d','e','a','d','b','e','e','f',0};

    const WCHAR *arch = ai->arch ? ai->arch : noneW;
    const WCHAR *key = ai->public_key ? ai->public_key : noneW;
    const WCHAR *lang = ai->language ? ai->language : noneW;
    const WCHAR *name = ai->name ? ai->name : noneW;
    SIZE_T size = (strlenW(arch) + 1 + strlenW(name) + 1 + strlenW(key) + 24 + 1 +
		    strlenW(lang) + 1) * sizeof(WCHAR) + sizeof(mskeyW);
    WCHAR *ret;

    if (!(ret = RtlAllocateHeap( RtlGetProcessHeap(), 0, size ))) return NULL;

    strcpyW( ret, arch );
    strcatW( ret, undW );
    strcatW( ret, name );
    strcatW( ret, undW );
    strcatW( ret, key );
    strcatW( ret, undW );
    sprintfW( ret + strlenW(ret), version_formatW,
              ai->version.major, ai->version.minor, ai->version.build, ai->version.revision );
    strcatW( ret, undW );
    strcatW( ret, lang );
    strcatW( ret, undW );
    strcatW( ret, mskeyW );
    return ret;
}