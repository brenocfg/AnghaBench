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
typedef  TYPE_1__* node_string ;
struct TYPE_3__ {int len; char* buf; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 

__attribute__((used)) static int
pattern_placeholder_p(node_string name){
  if (name->len == 1 && name->buf[0] == '_')
    return TRUE;
  return FALSE;
}