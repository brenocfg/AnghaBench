#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int hasError; int /*<<< orphan*/  isQuiet; } ;
struct TYPE_4__ {size_t size; size_t position; TYPE_1__ file; int /*<<< orphan*/ * storage; } ;
typedef  TYPE_2__ THMemoryFile ;
typedef  int /*<<< orphan*/  THFile ;

/* Variables and functions */
 int /*<<< orphan*/  THArgCheck (int,int,char*) ; 
 int /*<<< orphan*/  THError (char*,size_t) ; 

__attribute__((used)) static void THMemoryFile_seek(THFile *self, size_t position)
{
  THMemoryFile *mfself = (THMemoryFile*)self;

  THArgCheck(mfself->storage != NULL, 1, "attempt to use a closed file");
  THArgCheck(position >= 0, 2, "position must be positive");

  if(position <= mfself->size)
    mfself->position = position;
  else
  {
    mfself->file.hasError = 1;
    if(!mfself->file.isQuiet)
      THError("unable to seek at position %zu", position);
  }
}