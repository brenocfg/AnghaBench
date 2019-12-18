#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct command {scalar_t__ name; } ;

/* Variables and functions */
 int MAX_COMMANDS_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 struct command* commands ; 

void register_new_command (struct command *cmd) {
  int i = 0;
  while (commands[i].name) {
    i ++;
  }
  assert (i < MAX_COMMANDS_SIZE - 1);
  commands[i] = *cmd;
}