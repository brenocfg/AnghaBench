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
typedef  int u16 ;
struct TYPE_3__ {int* z; size_t i; int a; int b; } ;
typedef  TYPE_1__ hash ;

/* Variables and functions */
 int NHASH ; 

__attribute__((used)) static void hash_next(hash *pHash, int c){
  u16 old = pHash->z[pHash->i];
  pHash->z[pHash->i] = c;
  pHash->i = (pHash->i+1)&(NHASH-1);
  pHash->a = pHash->a - old + c;
  pHash->b = pHash->b - NHASH*old + pHash->a;
}