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
typedef  int /*<<< orphan*/  strm_int ;
struct TYPE_3__ {int /*<<< orphan*/  value; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ node_str ;
typedef  int /*<<< orphan*/  node ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_STR ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  node_str_new (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_escape (char*,int /*<<< orphan*/ ) ; 

node*
node_string_new(const char* s, strm_int len)
{
  node_str* ns = malloc(sizeof(node_str));

  ns->type = NODE_STR;
  len = string_escape((char*)s, len);
  ns->value = node_str_new(s, len);
  return (node*)ns;
}