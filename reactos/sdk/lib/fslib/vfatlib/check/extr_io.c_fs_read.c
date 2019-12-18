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
typedef  int off_t ;
struct TYPE_3__ {int pos; int size; scalar_t__ data; struct TYPE_3__* next; } ;
typedef  TYPE_1__ CHANGE ;

/* Variables and functions */
 char* alloc (size_t const) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* changes ; 
 int /*<<< orphan*/  die (char*,int,int,long long) ; 
 int /*<<< orphan*/  fd ; 
 int /*<<< orphan*/  free (char*) ; 
 int lseek (int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  pdie (char*,int,...) ; 
 int read (int /*<<< orphan*/ ,void*,size_t const) ; 

void fs_read(off_t pos, int size, void *data)
{
    CHANGE *walk;
    int got;

#ifdef __REACTOS__
	const size_t readsize_aligned = (size % 512) ? (size + (512 - (size % 512))) : size;
 	const off_t seekpos_aligned = pos - (pos % 512);
 	const size_t seek_delta = (size_t)(pos - seekpos_aligned);
#if DBG
	const size_t readsize = (size_t)(pos - seekpos_aligned) + readsize_aligned;
#endif
	char* tmpBuf = alloc(readsize_aligned);
    if (lseek(fd, seekpos_aligned, 0) != seekpos_aligned) pdie("Seek to %lld",pos);
    if ((got = read(fd, tmpBuf, readsize_aligned)) < 0) pdie("Read %d bytes at %lld",size,pos);
	assert(got >= size);
	got = size;
	assert(seek_delta + size <= readsize);
	memcpy(data, tmpBuf+seek_delta, size);
	free(tmpBuf);
#else
    if (lseek(fd, pos, 0) != pos)
	pdie("Seek to %lld", (long long)pos);
    if ((got = read(fd, data, size)) < 0)
	pdie("Read %d bytes at %lld", size, (long long)pos);
#endif
    if (got != size)
	die("Got %d bytes instead of %d at %lld", got, size, (long long)pos);
    for (walk = changes; walk; walk = walk->next) {
	if (walk->pos < pos + size && walk->pos + walk->size > pos) {
	    if (walk->pos < pos)
		memcpy(data, (char *)walk->data + pos - walk->pos,
		       min(size, walk->size - pos + walk->pos));
	    else
		memcpy((char *)data + walk->pos - pos, walk->data,
		       min(walk->size, size + pos - walk->pos));
	}
    }
}