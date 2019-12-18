#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* z; TYPE_1__* a; } ;
struct TYPE_4__ {int nByte; } ;
typedef  TYPE_2__ EditDist3FromString ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

__attribute__((used)) static int matchFromTo(
  EditDist3FromString *pStr,  /* Left hand string */
  int n1,                     /* Index of comparison character on the left */
  const char *z2,             /* Right-handl comparison character */
  int n2                      /* Bytes remaining in z2[] */
){
  int b1 = pStr->a[n1].nByte;
  if( b1>n2 ) return 0;
  assert( b1>0 );
  if( pStr->z[n1]!=z2[0] ) return 0;
  if( strncmp(pStr->z+n1, z2, b1)!=0 ) return 0;
  return 1;
}