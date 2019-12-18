#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t size; char* data; } ;
struct TYPE_4__ {size_t size; TYPE_3__* storage; } ;
typedef  TYPE_1__ THMemoryFile ;

/* Variables and functions */
 int /*<<< orphan*/  THCharStorage_resize (TYPE_3__*,int) ; 

__attribute__((used)) static void THMemoryFile_grow(THMemoryFile *self, size_t size)
{
  size_t missingSpace;

  if(size <= self->size)
    return;
  else
  {
    if(size < self->storage->size) /* note the "<" and not "<=" */
    {
      self->size = size;
      self->storage->data[self->size] = '\0';
      return;
    }
  }

  missingSpace = size-self->storage->size+1; /* +1 for the '\0' */
  THCharStorage_resize(self->storage, (self->storage->size/2 > missingSpace ?
                                       self->storage->size + (self->storage->size/2)
                                       : self->storage->size + missingSpace));
}