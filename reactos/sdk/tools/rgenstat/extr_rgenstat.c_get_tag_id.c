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

/* Variables and functions */
 int TAG_IMPLEMENTED ; 
 int TAG_UNIMPLEMENTED ; 
 int TAG_UNKNOWN ; 
 scalar_t__ strcasecmp (char*,char*) ; 

__attribute__((used)) static int
get_tag_id(char *tag)
{
  if (strcasecmp(tag, "implemented") == 0)
    {
      return TAG_IMPLEMENTED;
    }
  if (strcasecmp(tag, "unimplemented") == 0)
    {
      return TAG_UNIMPLEMENTED;
    }
  return TAG_UNKNOWN;
}