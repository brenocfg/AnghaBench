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
struct buffy {scalar_t__ size; scalar_t__ data; struct buffy* next; } ;
struct bufferchain {scalar_t__ pos; scalar_t__ fileoff; scalar_t__ size; scalar_t__ firstpos; struct buffy* first; int /*<<< orphan*/ * last; } ;

/* Variables and functions */
 int /*<<< orphan*/  bc_free (struct bufferchain*,struct buffy*) ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  debug2 (char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  debug5 (char*,void*,long,long,long,long) ; 

__attribute__((used)) static void bc_forget(struct bufferchain *bc)
{
	struct buffy *b = bc->first;
	/* free all buffers that are def'n'tly outdated */
	/* we have buffers until filepos... delete all buffers fully below it */
	if(b) debug2("bc_forget: block %lu pos %lu", (unsigned long)b->size, (unsigned long)bc->pos);
	else debug("forget with nothing there!");

	while(b != NULL && bc->pos >= b->size)
	{
		struct buffy *n = b->next; /* != NULL or this is indeed the end and the last cycle anyway */
		if(n == NULL) bc->last = NULL; /* Going to delete the last buffy... */
		bc->fileoff += b->size;
		bc->pos  -= b->size;
		bc->size -= b->size;

		debug5("bc_forget: forgot %p with %lu, pos=%li, size=%li, fileoff=%li", (void*)b->data, (long)b->size, (long)bc->pos,  (long)bc->size, (long)bc->fileoff);

		bc_free(bc, b);
		b = n;
	}
	bc->first = b;
	bc->firstpos = bc->pos;
}