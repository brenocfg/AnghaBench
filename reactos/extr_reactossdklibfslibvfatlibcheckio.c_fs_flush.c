#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ pos; long long size; struct TYPE_5__* data; struct TYPE_5__* next; } ;
typedef  TYPE_1__ CHANGE ;

/* Variables and functions */
 TYPE_1__* changes ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fd ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,long long,long long) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 long long strerror (int /*<<< orphan*/ ) ; 
 int write (int /*<<< orphan*/ ,TYPE_1__*,long long) ; 

__attribute__((used)) static void fs_flush(void)
{
#ifdef __REACTOS__

    CHANGE *this;
    int old_write_immed = (FsCheckFlags & FSCHECK_IMMEDIATE_WRITE);

    /* Disable writes to the list now */
    FsCheckFlags |= FSCHECK_IMMEDIATE_WRITE;

    while (changes) {
	this = changes;
	changes = changes->next;

    fs_write(this->pos, this->size, this->data);

	free(this->data);
	free(this);
    }

    /* Restore values */
    if (!old_write_immed) FsCheckFlags ^= FSCHECK_IMMEDIATE_WRITE;

#else
    CHANGE *this;
    int size;

    while (changes) {
	this = changes;
	changes = changes->next;
	if (lseek(fd, this->pos, 0) != this->pos)
	    fprintf(stderr,
		    "Seek to %lld failed: %s\n  Did not write %d bytes.\n",
		    (long long)this->pos, strerror(errno), this->size);
	else if ((size = write(fd, this->data, this->size)) < 0)
	    fprintf(stderr, "Writing %d bytes at %lld failed: %s\n", this->size,
		    (long long)this->pos, strerror(errno));
	else if (size != this->size)
	    fprintf(stderr, "Wrote %d bytes instead of %d bytes at %lld."
		    "\n", size, this->size, (long long)this->pos);
	free(this->data);
	free(this);
    }
#endif
}