#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8 ;
struct TYPE_7__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {TYPE_3__* textcache; } ;
struct TYPE_6__ {TYPE_1__ cache; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  TYPE_3__ DATABLOB ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 

void
cache_put_text(RDPCLIENT * This, uint8 cache_id, void *data, int length)
{
	DATABLOB *text;
	void * p = malloc(length);

	if(p == NULL)
		return;

	text = &This->cache.textcache[cache_id];
	if (text->data != NULL)
		free(text->data);
	text->data = p;
	text->size = length;
	memcpy(text->data, data, length);
}