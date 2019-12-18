#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* aFile; } ;
struct TYPE_3__ {int sz; scalar_t__ nRef; scalar_t__ a; scalar_t__ zFilename; } ;

/* Variables and functions */
 int MX_FILE ; 
 TYPE_2__ g ; 

__attribute__((used)) static void formatVfs(void){
  int i;
  for(i=0; i<MX_FILE; i++){
    g.aFile[i].sz = -1;
    g.aFile[i].zFilename = 0;
    g.aFile[i].a = 0;
    g.aFile[i].nRef = 0;
  }
}