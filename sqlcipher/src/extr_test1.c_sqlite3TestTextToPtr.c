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
typedef  int /*<<< orphan*/  v2 ;
typedef  int /*<<< orphan*/  v ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  p ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (void**,int*,int) ; 
 int testHexToInt (char const) ; 

void *sqlite3TestTextToPtr(const char *z){
  void *p;
  u64 v;
  u32 v2;
  if( z[0]=='0' && z[1]=='x' ){
    z += 2;
  }
  v = 0;
  while( *z ){
    v = (v<<4) + testHexToInt(*z);
    z++;
  }
  if( sizeof(p)==sizeof(v) ){
    memcpy(&p, &v, sizeof(p));
  }else{
    assert( sizeof(p)==sizeof(v2) );
    v2 = (u32)v;
    memcpy(&p, &v2, sizeof(p));
  }
  return p;
}