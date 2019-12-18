#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* e_ident; } ;
typedef  TYPE_1__ Elf32_Ehdr ;

/* Variables and functions */
 size_t EI_CLASS ; 
 size_t EI_DATA ; 
 size_t EI_MAG0 ; 
 size_t EI_MAG1 ; 
 size_t EI_MAG2 ; 
 size_t EI_MAG3 ; 
 scalar_t__ EI_NIDENT ; 
 scalar_t__ ELFDATA2LSB ; 
 scalar_t__ ELFDATA2MSB ; 
 scalar_t__ ELFMAG0 ; 
 scalar_t__ ELFMAG1 ; 
 scalar_t__ ELFMAG2 ; 
 scalar_t__ ELFMAG3 ; 
 int do_reverse_endian ; 
 int /*<<< orphan*/  err (char*) ; 
 scalar_t__ errno ; 
 int ferr (char*) ; 
 scalar_t__ read (int,TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int readelfheaderident(int fd, Elf32_Ehdr *ehdr)
{
    errno = 0;
    if (read(fd, ehdr, EI_NIDENT) != EI_NIDENT)
        return ferr("missing or incomplete ELF header.");

    /* Check the ELF signature.
     */
    if (!(ehdr->e_ident[EI_MAG0] == ELFMAG0 &&
          ehdr->e_ident[EI_MAG1] == ELFMAG1 &&
          ehdr->e_ident[EI_MAG2] == ELFMAG2 &&
          ehdr->e_ident[EI_MAG3] == ELFMAG3))
    {
        err("missing ELF signature.");
        return -1;
    }

    /* Compare the file's class and endianness with the program's.
     */
#if __BYTE_ORDER == __LITTLE_ENDIAN
    if (ehdr->e_ident[EI_DATA] == ELFDATA2LSB) {
        do_reverse_endian = 0;
    } else if (ehdr->e_ident[EI_DATA] == ELFDATA2MSB) {
/*      fprintf(stderr, "ELF file has different endianness.\n"); */
        do_reverse_endian = 1;
    }
#elif __BYTE_ORDER == __BIG_ENDIAN
    if (ehdr->e_ident[EI_DATA] == ELFDATA2LSB) {
/*      fprintf(stderr, "ELF file has different endianness.\n"); */
        do_reverse_endian = 1;
    } else if (ehdr->e_ident[EI_DATA] == ELFDATA2MSB) {
        do_reverse_endian = 0;
    }
#else
#error unknown endianness
#endif
    else {
        err("Unsupported endianness");
        return -1;
    }

    /* Check the target architecture.
     */
/*   if (EGET(ehdr->e_machine) != ELF_ARCH) { */
/*      /\* return err("ELF file created for different architecture."); *\/ */
/*      fprintf(stderr, "ELF file created for different architecture.\n"); */
/*  } */
    return ehdr->e_ident[EI_CLASS];
}