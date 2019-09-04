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
typedef  int /*<<< orphan*/  adns_query ;

/* Variables and functions */
 char* adns__alloc_final (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int strlen (char*) ; 

void adns__makefinal_str(adns_query qu, char **strp) {
  int l;
  char *before, *after;

  before= *strp;
  if (!before) return;
  l= strlen(before)+1;
  after= adns__alloc_final(qu, (size_t) l);
  memcpy(after,before,(size_t) l);
  *strp= after;
}