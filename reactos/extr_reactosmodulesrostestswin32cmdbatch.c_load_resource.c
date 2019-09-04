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
typedef  int /*<<< orphan*/ * HRSRC ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/ * FindResourceA (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 char* LoadResource (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SizeofResource (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD load_resource(const char *name, const char *type, const char **ret)
{
    const char *res;
    HRSRC src;
    DWORD size;

    src = FindResourceA(NULL, name, type);
    ok(src != NULL, "Could not find resource %s: %u\n", name, GetLastError());
    if(!src)
        return 0;

    res = LoadResource(NULL, src);
    size = SizeofResource(NULL, src);
    while(size && !res[size-1])
        size--;

    *ret = res;
    return size;
}