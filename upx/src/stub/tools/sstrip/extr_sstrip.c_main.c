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
typedef  int /*<<< orphan*/  Elf64_Phdr ;
typedef  int /*<<< orphan*/  Elf64_Ehdr ;
typedef  int /*<<< orphan*/  Elf32_Phdr ;
typedef  int /*<<< orphan*/  Elf32_Ehdr ;

/* Variables and functions */
#define  ELFCLASS32 129 
#define  ELFCLASS64 128 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  commitchanges32 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  commitchanges64 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ferr (char*) ; 
 char* filename ; 
 int /*<<< orphan*/  getmemorysize32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  getmemorysize64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  modifyheaders32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  modifyheaders64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 char* progname ; 
 int /*<<< orphan*/  readelfheader32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readelfheader64 (int,int /*<<< orphan*/ *) ; 
 int readelfheaderident (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readphdrtable32 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  readphdrtable64 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  truncatezeros (int,unsigned long*) ; 

int main(int argc, char *argv[])
{
    int             fd;
    union {
        Elf32_Ehdr  ehdr32;
        Elf64_Ehdr  ehdr64;
    } e;
    union {
        Elf32_Phdr  *phdrs32;
        Elf64_Phdr  *phdrs64;
    } p;
    unsigned long   newsize;
    char            **arg;
    int             failures = 0;

    if (argc < 2 || argv[1][0] == '-') {
        printf("Usage: sstrip FILE...\n"
               "sstrip discards all nonessential bytes from an executable.\n\n"
               "Version 2.0-X Copyright (C) 2000,2001 Brian Raiter.\n"
               "Cross-devel hacks Copyright (C) 2004 Manuel Novoa III.\n"
               "This program is free software, licensed under the GNU\n"
               "General Public License. There is absolutely no warranty.\n");
        return EXIT_SUCCESS;
    }

    progname = argv[0];

    for (arg = argv + 1 ; *arg != NULL ; ++arg) {
        filename = *arg;

        fd = open(*arg, O_RDWR);
        if (fd < 0) {
            ferr("can't open");
            ++failures;
            continue;
        }

        switch (readelfheaderident(fd, &e.ehdr32)) {
            case ELFCLASS32:
                if (!(readelfheader32(fd, &e.ehdr32)                    &&
                      readphdrtable32(fd, &e.ehdr32, &p.phdrs32)        &&
                      getmemorysize32(&e.ehdr32, p.phdrs32, &newsize)   &&
                      truncatezeros(fd, &newsize)                       &&
                      modifyheaders32(&e.ehdr32, p.phdrs32, newsize)    &&
                      commitchanges32(fd, &e.ehdr32, p.phdrs32, newsize)))
                    ++failures;
                break;
            case ELFCLASS64:
                if (!(readelfheader64(fd, &e.ehdr64)                    &&
                      readphdrtable64(fd, &e.ehdr64, &p.phdrs64)        &&
                      getmemorysize64(&e.ehdr64, p.phdrs64, &newsize)   &&
                      truncatezeros(fd, &newsize)                       &&
                      modifyheaders64(&e.ehdr64, p.phdrs64, newsize)    &&
                      commitchanges64(fd, &e.ehdr64, p.phdrs64, newsize)))
                    ++failures;
                break;
            default:
                ++failures;
                break;
        }
        close(fd);
    }

    return failures ? EXIT_FAILURE : EXIT_SUCCESS;
}