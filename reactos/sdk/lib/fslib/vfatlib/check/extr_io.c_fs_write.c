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
typedef  int off_t ;
struct TYPE_4__ {int pos; char* data; int size; struct TYPE_4__* next; } ;
typedef  TYPE_1__ CHANGE ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int FSCHECK_IMMEDIATE_WRITE ; 
 int FsCheckFlags ; 
 void* alloc (size_t const) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* changes ; 
 int did_change ; 
 int /*<<< orphan*/  die (char*,int,int,long long) ; 
 int /*<<< orphan*/  fd ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ interactive ; 
 TYPE_1__* last ; 
 int lseek (int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,void*,int) ; 
 int /*<<< orphan*/  pdie (char*,int const,...) ; 
 scalar_t__ read (int /*<<< orphan*/ ,void*,size_t const) ; 
 scalar_t__ rw ; 
 int write (int /*<<< orphan*/ ,void*,size_t const) ; 
 scalar_t__ write_immed ; 

void fs_write(off_t pos, int size, void *data)
{
    CHANGE *new;
    int did;

#ifdef __REACTOS__
    assert(interactive || rw);

    if (FsCheckFlags & FSCHECK_IMMEDIATE_WRITE) {
        void *scratch;
        const size_t readsize_aligned = (size % 512) ? (size + (512 - (size % 512))) : size;
        const off_t seekpos_aligned = pos - (pos % 512);
        const size_t seek_delta = (size_t)(pos - seekpos_aligned);
        BOOLEAN use_read = (seek_delta != 0) || ((readsize_aligned-size) != 0);

        /* Aloc temp buffer if write is not aligned */
        if (use_read)
            scratch = alloc(readsize_aligned);
        else
            scratch = data;

        did_change = 1;
        if (lseek(fd, seekpos_aligned, 0) != seekpos_aligned) pdie("Seek to %lld",seekpos_aligned);

        if (use_read)
        {
            /* Read aligned data */
            if (read(fd, scratch, readsize_aligned) < 0) pdie("Read %d bytes at %lld",size,pos);

            /* Patch data in memory */
            memcpy((char *)scratch + seek_delta, data, size);
        }

        /* Write it back */
        if ((did = write(fd, scratch, readsize_aligned)) == (int)readsize_aligned)
        {
            if (use_read) free(scratch);
            return;
        }
        if (did < 0) pdie("Write %d bytes at %lld", size, pos);
        die("Wrote %d bytes instead of %d at %lld", did, size, pos);
    }
#else
    if (write_immed) {
	did_change = 1;
	if (lseek(fd, pos, 0) != pos)
	    pdie("Seek to %lld", (long long)pos);
	if ((did = write(fd, data, size)) == size)
	    return;
	if (did < 0)
	    pdie("Write %d bytes at %lld", size, (long long)pos);
	die("Wrote %d bytes instead of %d at %lld", did, size, (long long)pos);
    }
#endif
    new = alloc(sizeof(CHANGE));
    new->pos = pos;
    memcpy(new->data = alloc(new->size = size), data, size);
    new->next = NULL;
    if (last)
	last->next = new;
    else
	changes = new;
    last = new;
}