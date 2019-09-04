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
typedef  int /*<<< orphan*/  parse_buffer ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ TOKEN_CBRACKET ; 
 scalar_t__ TOKEN_OBRACKET ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ check_TOKEN (int /*<<< orphan*/ *) ; 
 scalar_t__ get_TOKEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_template_members_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_template_option_info (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL parse_template_parts(parse_buffer * buf)
{
  if (!parse_template_members_list(buf))
    return FALSE;
  if (check_TOKEN(buf) == TOKEN_OBRACKET)
  {
    get_TOKEN(buf);
    if (!parse_template_option_info(buf))
      return FALSE;
    if (get_TOKEN(buf) != TOKEN_CBRACKET)
     return FALSE;
  }

  return TRUE;
}