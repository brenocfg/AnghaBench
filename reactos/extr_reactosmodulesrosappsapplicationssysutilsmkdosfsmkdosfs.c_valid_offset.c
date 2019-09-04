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
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int TRUE ; 
 scalar_t__ llseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 

__attribute__((used)) static int
valid_offset (int fd, loff_t offset)
{
  char ch;

  if (llseek (fd, offset, SEEK_SET) < 0)
    return FALSE;
  if (read (fd, &ch, 1) < 1)
    return FALSE;
  return TRUE;
}