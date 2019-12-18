#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int i64 ;
struct TYPE_2__ {int pagesize; } ;

/* Variables and functions */
 TYPE_1__ g ; 

__attribute__((used)) static i64 localPayload(i64 nPayload, char cType){
  i64 maxLocal;
  i64 minLocal;
  i64 surplus;
  i64 nLocal;
  if( cType==13 ){
    /* Table leaf */
    maxLocal = g.pagesize-35;
    minLocal = (g.pagesize-12)*32/255-23;
  }else{
    maxLocal = (g.pagesize-12)*64/255-23;
    minLocal = (g.pagesize-12)*32/255-23;
  }
  if( nPayload>maxLocal ){
    surplus = minLocal + (nPayload-minLocal)%(g.pagesize-4);
    if( surplus<=maxLocal ){
      nLocal = surplus;
    }else{
      nLocal = minLocal;
    }
  }else{
    nLocal = nPayload;
  }
  return nLocal;
}