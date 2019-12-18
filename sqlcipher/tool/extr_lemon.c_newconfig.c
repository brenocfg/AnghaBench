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
struct config {struct config* next; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 struct config* freelist ; 
 int /*<<< orphan*/  stderr ; 

struct config *newconfig(void){
  struct config *newcfg;
  if( freelist==0 ){
    int i;
    int amt = 3;
    freelist = (struct config *)calloc( amt, sizeof(struct config) );
    if( freelist==0 ){
      fprintf(stderr,"Unable to allocate memory for a new configuration.");
      exit(1);
    }
    for(i=0; i<amt-1; i++) freelist[i].next = &freelist[i+1];
    freelist[amt-1].next = 0;
  }
  newcfg = freelist;
  freelist = freelist->next;
  return newcfg;
}