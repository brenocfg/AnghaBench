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
struct assembly_version {int /*<<< orphan*/  revision; int /*<<< orphan*/  build; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct TYPE_2__ {struct assembly_version version; } ;
struct assembly {TYPE_1__ id; } ;
typedef  char WCHAR ;

/* Variables and functions */
 int sprintfW (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_assembly_version(struct assembly *assembly, WCHAR *ret)
{
    static const WCHAR fmtW[] = {'%','u','.','%','u','.','%','u','.','%','u',0};
    struct assembly_version *ver = &assembly->id.version;
    WCHAR buff[25];

    if (!ret) ret = buff;
    return sprintfW(ret, fmtW, ver->major, ver->minor, ver->build, ver->revision);
}