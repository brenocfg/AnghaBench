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

__attribute__((used)) static char *THMemoryFile_strnextspace(char *str_, char *c_)
{
  char c;

  while( (c = *str_) )
  {
    if( (c != ' ') && (c != '\n') && (c != ':') && (c != ';') )
      break;
    str_++;
  }

  while( (c = *str_) )
  {
    if( (c == ' ') || (c == '\n') || (c == ':') || (c == ';') )
    {
      *c_ = c;
      *str_ = '\0';
      return(str_);
    }
    str_++;
  }
  return NULL;
}