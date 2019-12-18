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
struct buffy {size_t realsize; int /*<<< orphan*/ * next; scalar_t__ size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct buffy*) ; 
 void* malloc (int) ; 

__attribute__((used)) static struct buffy* buffy_new(size_t size, size_t minsize)
{
	struct buffy *newbuf;
	newbuf = malloc(sizeof(struct buffy));
	if(newbuf == NULL) return NULL;

	newbuf->realsize = size > minsize ? size : minsize;
	newbuf->data = malloc(newbuf->realsize);
	if(newbuf->data == NULL)
	{
		free(newbuf);
		return NULL;
	}
	newbuf->size = 0;
	newbuf->next = NULL;
	return newbuf;
}