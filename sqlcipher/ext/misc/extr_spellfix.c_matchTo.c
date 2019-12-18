#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* a; size_t nFrom; int nTo; } ;
typedef  TYPE_1__ EditDist3Cost ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

__attribute__((used)) static int matchTo(EditDist3Cost *p, const char *z, int n){
  assert( n>0 );
  if( p->a[p->nFrom]!=z[0] ) return 0;
  if( p->nTo>n ) return 0;
  if( strncmp(p->a+p->nFrom, z, p->nTo)!=0 ) return 0;
  return 1;
}