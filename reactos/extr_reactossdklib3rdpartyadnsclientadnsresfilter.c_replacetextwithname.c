#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct outqueuenode {char* buffer; char* textp; int textlen; TYPE_3__* addr; } ;
struct TYPE_6__ {TYPE_2__* ans; } ;
struct TYPE_4__ {char** str; } ;
struct TYPE_5__ {TYPE_1__ rrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  address ; 
 scalar_t__ bracket ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int,char*) ; 
 int strlen (char*) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static void replacetextwithname(struct outqueuenode *entry) {
  char *name, *newbuf;
  int namelen, newlen;

  name= entry->addr->ans->rrs.str[0];
  namelen= strlen(name);
  if (!address) {
    free(entry->buffer);
    entry->buffer= 0;
    entry->textp= name;
    entry->textlen= namelen;
  } else {
    newlen= entry->textlen + namelen + (bracket ? 0 : 2);
    newbuf= xmalloc(newlen + 1);
    sprintf(newbuf, bracket ? "%s%.*s" : "%s[%.*s]", name, entry->textlen, entry->textp);
    free(entry->buffer);
    entry->buffer= entry->textp= newbuf;
    entry->textlen= newlen;
  }
}