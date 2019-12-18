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

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,char const*) ; 
 int /*<<< orphan*/  UTIL_isRegularFile (char const*) ; 
 int /*<<< orphan*/  _S_IWRITE ; 
 int /*<<< orphan*/  chmod (char const*,int /*<<< orphan*/ ) ; 
 int remove (char const*) ; 

__attribute__((used)) static int FIO_remove(const char* path)
{
    if (!UTIL_isRegularFile(path)) {
        DISPLAYLEVEL(2, "zstd: Refusing to remove non-regular file %s \n", path);
        return 0;
    }
#if defined(_WIN32) || defined(WIN32)
    /* windows doesn't allow remove read-only files,
     * so try to make it writable first */
    chmod(path, _S_IWRITE);
#endif
    return remove(path);
}