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
struct parser {int dummy; } ;
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  EOL_BACKSLASH ; 
 int /*<<< orphan*/  is_eol (struct parser*,char const*) ; 
 int /*<<< orphan*/  isspaceW (char const) ; 
 int /*<<< orphan*/  pop_state (struct parser*) ; 
 int /*<<< orphan*/  set_state (struct parser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const WCHAR *trailing_spaces_state( struct parser *parser, const WCHAR *pos )
{
  const WCHAR *p;

  for (p = pos; !is_eol( parser, p ); p++)
    {
      if (*p == '\\')
        {
          set_state( parser, EOL_BACKSLASH );
          return p;
        }
      if (!isspaceW(*p))
        break;
    }
  pop_state( parser );
  return p;
}