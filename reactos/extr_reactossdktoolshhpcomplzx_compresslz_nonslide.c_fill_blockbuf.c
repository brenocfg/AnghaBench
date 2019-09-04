#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {int block_buf_size; int chars_in_buf; int (* get_chars ) (TYPE_1__*,int,int /*<<< orphan*/ *) ;scalar_t__ eofcount; int /*<<< orphan*/ * block_buf; } ;
typedef  TYPE_1__ lz_info ;

/* Variables and functions */
 scalar_t__ lz_left_to_process (TYPE_1__*) ; 
 int stub1 (TYPE_1__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fill_blockbuf(lz_info *lzi, int maxchars)
{
  int toread;
  u_char *readhere;
  int nread;

  if (lzi->eofcount) return;
  maxchars -= lz_left_to_process(lzi);
  toread = lzi->block_buf_size - lzi->chars_in_buf;
  if (toread > maxchars) toread = maxchars;
  readhere = lzi->block_buf + lzi->chars_in_buf;
  nread = lzi->get_chars(lzi, toread, readhere);
  lzi->chars_in_buf += nread;
  if (nread != toread)
    lzi->eofcount++;
}