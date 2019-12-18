#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * storage; } ;
typedef  TYPE_1__ THMemoryFile ;
typedef  int /*<<< orphan*/  THFile ;

/* Variables and functions */
 int /*<<< orphan*/  THArgCheck (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  THCharStorage_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void THMemoryFile_close(THFile *self)
{
  THMemoryFile *mfself = (THMemoryFile*)self;
  THArgCheck(mfself->storage != NULL, 1, "attempt to use a closed file");
  THCharStorage_free(mfself->storage);
  mfself->storage = NULL;
}