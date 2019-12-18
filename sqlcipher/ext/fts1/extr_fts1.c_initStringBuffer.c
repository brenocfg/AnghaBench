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
struct TYPE_3__ {int alloced; char* s; scalar_t__ len; } ;
typedef  TYPE_1__ StringBuffer ;

/* Variables and functions */
 char* malloc (int) ; 

__attribute__((used)) static void initStringBuffer(StringBuffer *sb){
  sb->len = 0;
  sb->alloced = 100;
  sb->s = malloc(100);
  sb->s[0] = '\0';
}