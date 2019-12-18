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
struct bufferchain {scalar_t__ size; scalar_t__ pos; struct buffy* first; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ bc_need_more (struct bufferchain*) ; 
 int /*<<< orphan*/  debug2 (char*,long,long) ; 
 int /*<<< orphan*/  debug3 (char*,long,scalar_t__,long) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static ssize_t bc_give(struct bufferchain *bc, unsigned char *out, ssize_t size)
{
	struct buffy *b = bc->first;
	ssize_t gotcount = 0;
	ssize_t offset = 0;
	if(bc->size - bc->pos < size) return bc_need_more(bc);

	/* find the current buffer */
	while(b != NULL && (offset + b->size) <= bc->pos)
	{
		offset += b->size;
		b = b->next;
	}
	/* now start copying from there */
	while(gotcount < size && (b != NULL))
	{
		ssize_t loff = bc->pos - offset;
		ssize_t chunk = size - gotcount; /* amount of bytes to get from here... */
		if(chunk > b->size - loff) chunk = b->size - loff;

#ifdef EXTRA_DEBUG
		debug3("copying %liB from %p+%li",(long)chunk, b->data, (long)loff);
#endif

		memcpy(out+gotcount, b->data+loff, chunk);
		gotcount += chunk;
		bc->pos  += chunk;
		offset += b->size;
		b = b->next;
	}
#ifdef EXTRA_DEBUG
	debug2("got %li bytes, pos advanced to %li", (long)gotcount, (long)bc->pos);
#endif

	return gotcount;
}