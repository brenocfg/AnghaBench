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
struct outqueuenode {int textlen; int textp; struct outqueuenode* buffer; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  LIST_UNLINK (int /*<<< orphan*/ ,struct outqueuenode*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (struct outqueuenode*) ; 
 int outblocked ; 
 int /*<<< orphan*/  outqueue ; 
 int /*<<< orphan*/  outqueuelen ; 
 int /*<<< orphan*/  sysfail (char*) ; 
 int write (int,int,int) ; 

__attribute__((used)) static void writestdout(struct outqueuenode *entry) {
  int r;

  while (entry->textlen) {
    r= write(1, entry->textp, entry->textlen);
    if (r < 0) {
      if (errno == EINTR) continue;
      if (errno == EAGAIN) { outblocked= 1; break; }
      sysfail("write stdout");
    }
    assert(r <= entry->textlen);
    entry->textp += r;
    entry->textlen -= r;
  }
  if (!entry->textlen) {
    LIST_UNLINK(outqueue,entry);
    free(entry->buffer);
    free(entry);
    outqueuelen--;
  }
}