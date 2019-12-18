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
 int /*<<< orphan*/  fatalError (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 TYPE_2__ g ; 

__attribute__((used)) static void reformatVfs(void){
  int i;
  for(i=0; i<MX_FILE; i++){
    if( g.aFile[i].sz<0 ) continue;
    if( g.aFile[i].zFilename ){
      free(g.aFile[i].zFilename);
      g.aFile[i].zFilename = 0;
    }
    if( g.aFile[i].nRef>0 ){
      fatalError("file %d still open.  nRef=%d", i, g.aFile[i].nRef);
    }
    g.aFile[i].sz = -1;
    free(g.aFile[i].a);
    g.aFile[i].a = 0;
    g.aFile[i].nRef = 0;
  }
}