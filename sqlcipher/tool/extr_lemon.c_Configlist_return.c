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
 struct config* current ; 
 scalar_t__ currentend ; 

struct config *Configlist_return(void){
  struct config *old;
  old = current;
  current = 0;
  currentend = 0;
  return old;
}