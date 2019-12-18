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
typedef  int /*<<< orphan*/  x1node ;
struct s_x1 {int size; int /*<<< orphan*/ ** ht; int /*<<< orphan*/ * tbl; scalar_t__ count; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (struct s_x1*) ; 
 scalar_t__ malloc (int) ; 
 struct s_x1* x1a ; 

void Strsafe_init(void){
  if( x1a ) return;
  x1a = (struct s_x1*)malloc( sizeof(struct s_x1) );
  if( x1a ){
    x1a->size = 1024;
    x1a->count = 0;
    x1a->tbl = (x1node*)calloc(1024, sizeof(x1node) + sizeof(x1node*));
    if( x1a->tbl==0 ){
      free(x1a);
      x1a = 0;
    }else{
      int i;
      x1a->ht = (x1node**)&(x1a->tbl[1024]);
      for(i=0; i<1024; i++) x1a->ht[i] = 0;
    }
  }
}