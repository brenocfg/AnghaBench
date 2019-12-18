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
struct TYPE_2__ {int iTotal; int /*<<< orphan*/  bSqlOnly; } ;

/* Variables and functions */
 char* NAMEWIDTH ; 
 TYPE_1__ g ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int) ; 
 int zDots ; 

void speedtest1_final(void){
  if( !g.bSqlOnly ){
    printf("       TOTAL%.*s %4d.%03ds\n", NAMEWIDTH-5, zDots,
           (int)(g.iTotal/1000), (int)(g.iTotal%1000));
  }
}