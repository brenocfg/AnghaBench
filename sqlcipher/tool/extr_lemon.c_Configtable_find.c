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
struct TYPE_3__ {struct config* data; struct TYPE_3__* next; } ;
typedef  TYPE_1__ x4node ;
struct config {int dummy; } ;
struct TYPE_4__ {int size; TYPE_1__** ht; } ;

/* Variables and functions */
 scalar_t__ Configcmp (char const*,char const*) ; 
 int confighash (struct config*) ; 
 TYPE_2__* x4a ; 

struct config *Configtable_find(struct config *key)
{
  int h;
  x4node *np;

  if( x4a==0 ) return 0;
  h = confighash(key) & (x4a->size-1);
  np = x4a->ht[h];
  while( np ){
    if( Configcmp((const char *) np->data,(const char *) key)==0 ) break;
    np = np->next;
  }
  return np ? np->data : 0;
}