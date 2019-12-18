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
struct TYPE_3__ {char const* data; struct TYPE_3__* next; } ;
typedef  TYPE_1__ x1node ;
struct TYPE_4__ {int size; TYPE_1__** ht; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,char const*) ; 
 int strhash (char const*) ; 
 TYPE_2__* x1a ; 

const char *Strsafe_find(const char *key)
{
  unsigned h;
  x1node *np;

  if( x1a==0 ) return 0;
  h = strhash(key) & (x1a->size-1);
  np = x1a->ht[h];
  while( np ){
    if( strcmp(np->data,key)==0 ) break;
    np = np->next;
  }
  return np ? np->data : 0;
}