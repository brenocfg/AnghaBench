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
struct TYPE_3__ {int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 int /*<<< orphan*/  OPCODE_END_OF_LIST ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static Node *make_empty_list( void )
{
   Node *n = (Node *) malloc( sizeof(Node) );
   n[0].opcode = OPCODE_END_OF_LIST;
   return n;
}