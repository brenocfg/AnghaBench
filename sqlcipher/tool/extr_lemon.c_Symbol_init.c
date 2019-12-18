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
typedef  int /*<<< orphan*/  x2node ;
struct s_x2 {int size; int /*<<< orphan*/ ** ht; int /*<<< orphan*/ * tbl; scalar_t__ count; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (struct s_x2*) ; 
 scalar_t__ malloc (int) ; 
 struct s_x2* x2a ; 

void Symbol_init(void){
  if( x2a ) return;
  x2a = (struct s_x2*)malloc( sizeof(struct s_x2) );
  if( x2a ){
    x2a->size = 128;
    x2a->count = 0;
    x2a->tbl = (x2node*)calloc(128, sizeof(x2node) + sizeof(x2node*));
    if( x2a->tbl==0 ){
      free(x2a);
      x2a = 0;
    }else{
      int i;
      x2a->ht = (x2node**)&(x2a->tbl[128]);
      for(i=0; i<128; i++) x2a->ht[i] = 0;
    }
  }
}