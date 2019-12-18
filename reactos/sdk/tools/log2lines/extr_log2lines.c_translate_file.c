#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* path; size_t ImageBase; } ;
typedef  TYPE_1__ LIST_MEMBER ;

/* Variables and functions */
 size_t INVALID_BASE ; 
 int /*<<< orphan*/  cache ; 
 char* convert_path (char const*) ; 
 TYPE_1__* entry_lookup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_ImageBase (char*,size_t*) ; 
 int /*<<< orphan*/  l2l_dbg (int,char*,char*) ; 
 int process_file (char*,size_t,char*) ; 

__attribute__((used)) static int
translate_file(const char *cpath, size_t offset, char *toString)
{
    size_t base = 0;
    LIST_MEMBER *pentry = NULL;
    int res = 0;
    char *path, *dpath;

    dpath = path = convert_path(cpath);
    if (!path)
        return 1;

    // The path could be absolute:
    if (get_ImageBase(path, &base))
    {
        pentry = entry_lookup(&cache, path);
        if (pentry)
        {
            path = pentry->path;
            base = pentry->ImageBase;
            if (base == INVALID_BASE)
            {
                l2l_dbg(1, "No, or invalid base address: %s\n", path);
                res = 2;
            }
        }
        else
        {
            l2l_dbg(1, "Not found in cache: %s\n", path);
            res = 3;
        }
    }

    if (!res)
    {
        res = process_file(path, offset, toString);
    }

    free(dpath);
    return res;
}