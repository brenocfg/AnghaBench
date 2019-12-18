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
typedef  int off_t ;

/* Variables and functions */
 void* alloc (size_t const) ; 
 int /*<<< orphan*/  fd ; 
 int /*<<< orphan*/  free (void*) ; 
 int lseek (int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdie (char*,long long) ; 
 int read (int /*<<< orphan*/ ,void*,size_t const) ; 

int fs_test(off_t pos, int size)
{
    void *scratch;
    int okay;

#ifdef __REACTOS__
	const size_t readsize_aligned = (size % 512) ? (size + (512 - (size % 512))) : size;        // TMN:
	const off_t seekpos_aligned = pos - (pos % 512);                   // TMN:
    scratch = alloc(readsize_aligned);
    if (lseek(fd, seekpos_aligned, 0) != seekpos_aligned) pdie("Seek to %lld",pos);
    okay = read(fd, scratch, readsize_aligned) == (int)readsize_aligned;
    free(scratch);
#else
    if (lseek(fd, pos, 0) != pos)
	pdie("Seek to %lld", (long long)pos);
    scratch = alloc(size);
    okay = read(fd, scratch, size) == size;
    free(scratch);
#endif
    return okay;
}