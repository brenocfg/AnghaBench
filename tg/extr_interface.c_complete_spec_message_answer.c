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
struct tgl_message {TYPE_1__* reply_markup; } ;
struct TYPE_2__ {size_t rows; int* row_start; int /*<<< orphan*/ * buttons; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int) ; 

int complete_spec_message_answer (struct tgl_message *M, int index, const char *text, int len, char **R) {
  if (!M || !M->reply_markup || !M->reply_markup->rows) {
    *R = NULL;
    return -1;
  }
  index ++;

  int total = M->reply_markup->row_start[M->reply_markup->rows];
  while (index < total && strncmp (M->reply_markup->buttons[index], text, len)) {
    index ++;
  }
  
  if (index < total) {
    *R = strdup (M->reply_markup->buttons[index]);
    assert (*R);
    return index;
  } else {
    *R = NULL;
    return -1;
  }
}