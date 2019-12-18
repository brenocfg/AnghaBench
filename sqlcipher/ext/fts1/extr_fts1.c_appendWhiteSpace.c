#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int len; int /*<<< orphan*/ * s; } ;
typedef  TYPE_1__ StringBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  append (TYPE_1__*,char*) ; 
 scalar_t__ safe_isspace (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void appendWhiteSpace(StringBuffer *p){
  if( p->len==0 ) return;
  if( safe_isspace(p->s[p->len-1]) ) return;
  append(p, " ");
}