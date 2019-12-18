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
typedef  int LexToken ;

/* Variables and functions */
#define  TK_else 132 
#define  TK_elseif 131 
#define  TK_end 130 
#define  TK_eof 129 
#define  TK_until 128 

__attribute__((used)) static int parse_isend(LexToken tok)
{
  switch (tok) {
  case TK_else: case TK_elseif: case TK_end: case TK_until: case TK_eof:
    return 1;
  default:
    return 0;
  }
}