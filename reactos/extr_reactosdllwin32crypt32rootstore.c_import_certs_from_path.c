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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  debugstr_a (int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ import_certs_from_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ import_certs_from_file (int,int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL import_certs_from_path(LPCSTR path, HCERTSTORE store,
 BOOL allow_dir)
{
    BOOL ret = FALSE;
    int fd;

    TRACE("(%s, %p, %d)\n", debugstr_a(path), store, allow_dir);

    fd = open(path, O_RDONLY);
    if (fd != -1)
    {
        struct stat st;

        if (fstat(fd, &st) == 0)
        {
            if (S_ISREG(st.st_mode))
                ret = import_certs_from_file(fd, store);
            else if (S_ISDIR(st.st_mode))
            {
                if (allow_dir)
                    ret = import_certs_from_dir(path, store);
                else
                    WARN("%s is a directory and directories are disallowed\n",
                     debugstr_a(path));
            }
            else
                ERR("%s: invalid file type\n", path);
        }
        close(fd);
    }
    return ret;
}