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
struct TYPE_3__ {char* z; } ;
typedef  TYPE_1__ GeoParse ;

/* Variables and functions */
 scalar_t__ safe_isspace (char) ; 

__attribute__((used)) static char geopolySkipSpace(GeoParse *p){
  while( safe_isspace(p->z[0]) ) p->z++;
  return p->z[0];
}