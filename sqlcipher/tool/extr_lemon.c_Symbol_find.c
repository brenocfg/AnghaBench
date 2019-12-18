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
struct TYPE_3__ {struct symbol* data; struct TYPE_3__* next; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ x2node ;
struct symbol {int dummy; } ;
struct TYPE_4__ {int size; TYPE_1__** ht; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int strhash (char const*) ; 
 TYPE_2__* x2a ; 

struct symbol *Symbol_find(const char *key)
{
  unsigned h;
  x2node *np;

  if( x2a==0 ) return 0;
  h = strhash(key) & (x2a->size-1);
  np = x2a->ht[h];
  while( np ){
    if( strcmp(np->key,key)==0 ) break;
    np = np->next;
  }
  return np ? np->data : 0;
}