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
struct config {int dummy; } ;

/* Variables and functions */
 struct config* basis ; 
 scalar_t__ basisend ; 

struct config *Configlist_basis(void){
  struct config *old;
  old = basis;
  basis = 0;
  basisend = 0;
  return old;
}