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
struct treething {scalar_t__ qu; int /*<<< orphan*/ * bytes; scalar_t__ ans; } ;
struct sockaddr {int dummy; } ;
struct outqueuenode {int textlen; int /*<<< orphan*/  printbefore; struct treething* addr; int /*<<< orphan*/ * textp; int /*<<< orphan*/ * buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/  sin_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_LINK_TAIL (int /*<<< orphan*/ ,struct outqueuenode*) ; 
 int /*<<< orphan*/  addrtextbuf ; 
 int adns_submit_reverse (int /*<<< orphan*/ ,struct sockaddr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct treething*,scalar_t__*) ; 
 int /*<<< orphan*/  adnsfail (char*,int) ; 
 int /*<<< orphan*/  ads ; 
 int /*<<< orphan*/  bytes ; 
 int cbyte ; 
 int /*<<< orphan*/  comparer ; 
 int inbuf ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct treething* newthing ; 
 int /*<<< orphan*/  outqueue ; 
 int /*<<< orphan*/  outqueuelen ; 
 int /*<<< orphan*/  printbefore ; 
 int /*<<< orphan*/  rrt ; 
 TYPE_1__ sa ; 
 int /*<<< orphan*/  sysfail (char*) ; 
 int /*<<< orphan*/  treeroot ; 
 void** tsearch (struct treething*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* xmalloc (int) ; 

__attribute__((used)) static void procaddr(void) {
  struct treething *foundthing;
  void **searchfound;
  struct outqueuenode *entry;
  int r;

  if (!newthing) {
    newthing= xmalloc(sizeof(struct treething));
    newthing->qu= 0;
    newthing->ans= 0;
  }

  memcpy(newthing->bytes,bytes,4);
  searchfound= tsearch(newthing,&treeroot,comparer);
  if (!searchfound) sysfail("tsearch");
  foundthing= *searchfound;

  if (foundthing == newthing) {
    newthing= 0;
    memcpy(&sa.sin_addr,bytes,4);
    r= adns_submit_reverse(ads, (const struct sockaddr*)&sa,
			   rrt,0,foundthing,&foundthing->qu);
    if (r) adnsfail("submit",r);
  }
  entry= xmalloc(sizeof(*entry));
  entry->buffer= xmalloc(inbuf);
  entry->textp= entry->buffer;
  memcpy(entry->textp,addrtextbuf,inbuf);
  entry->textlen= inbuf;
  entry->addr= foundthing;
  entry->printbefore= printbefore;
  LIST_LINK_TAIL(outqueue,entry);
  outqueuelen++;
  inbuf= 0;
  cbyte= -1;
}