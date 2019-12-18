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
struct TYPE_2__ {scalar_t__ bRaw; int dbfd; scalar_t__ pFd; scalar_t__ pDb; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 TYPE_1__ g ; 
 int /*<<< orphan*/  sqlite3_close (scalar_t__) ; 

__attribute__((used)) static void fileClose(){
  if( g.bRaw==0 ){
    sqlite3_close(g.pDb);
    g.pDb = 0;
    g.pFd = 0;
  }else{
    close(g.dbfd);
    g.dbfd = -1;
  }
}