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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int O_BINARY ; 
 int O_CREAT ; 
 int O_RDONLY ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int _S_IREAD ; 
 int _S_IWRITE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lseek (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int open (char*,int,...) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  write (int,char const*,int) ; 

__attribute__((used)) static void test_fdopen( void )
{
    static const char buffer[] = {0,1,2,3,4,5,6,7,8,9};
    char ibuf[10];
    int fd;
    FILE *file;

    fd = open ("fdopen.tst", O_WRONLY | O_CREAT | O_BINARY, _S_IREAD |_S_IWRITE);
    write (fd, buffer, sizeof (buffer));
    close (fd);

    fd = open ("fdopen.tst", O_RDONLY | O_BINARY);
    lseek (fd, 5, SEEK_SET);
    file = fdopen (fd, "rb");
    ok (fread (ibuf, 1, sizeof (buffer), file) == 5, "read wrong byte count\n");
    ok (memcmp (ibuf, buffer + 5, 5) == 0, "read wrong bytes\n");
    fclose (file);
    unlink ("fdopen.tst");
}