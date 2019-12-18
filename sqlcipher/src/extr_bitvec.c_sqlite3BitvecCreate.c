#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  iSize; } ;
typedef  TYPE_1__ Bitvec ;

/* Variables and functions */
 int BITVEC_SZ ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* sqlite3MallocZero (int) ; 

Bitvec *sqlite3BitvecCreate(u32 iSize){
  Bitvec *p;
  assert( sizeof(*p)==BITVEC_SZ );
  p = sqlite3MallocZero( sizeof(*p) );
  if( p ){
    p->iSize = iSize;
  }
  return p;
}