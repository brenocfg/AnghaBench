#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nLang; TYPE_1__ const* a; } ;
struct TYPE_6__ {int iLang; } ;
typedef  TYPE_1__ EditDist3Lang ;
typedef  TYPE_2__ EditDist3Config ;

/* Variables and functions */
 TYPE_1__ const editDist3Lang ; 

__attribute__((used)) static const EditDist3Lang *editDist3FindLang(
  EditDist3Config *pConfig,
  int iLang
){
  int i;
  for(i=0; i<pConfig->nLang; i++){
    if( pConfig->a[i].iLang==iLang ) return &pConfig->a[i];
  }
  return &editDist3Lang;
}