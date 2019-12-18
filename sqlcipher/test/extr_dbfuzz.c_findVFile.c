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
struct TYPE_4__ {scalar_t__ zFilename; } ;
typedef  TYPE_1__ VFile ;
struct TYPE_5__ {TYPE_1__* aFile; } ;

/* Variables and functions */
 int MX_FILE ; 
 TYPE_2__ g ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static VFile *findVFile(const char *zName){
  int i;
  if( zName==0 ) return 0;
  for(i=0; i<MX_FILE; i++){
    if( g.aFile[i].zFilename==0 ) continue;   
    if( strcmp(g.aFile[i].zFilename, zName)==0 ) return &g.aFile[i];
  }
  return 0;
}