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
struct parser {int const* start; int cur_section; int /*<<< orphan*/  line_pos; int /*<<< orphan*/  broken_line; } ;
typedef  int WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  COMMENT ; 
 int /*<<< orphan*/  KEY_NAME ; 
 int /*<<< orphan*/  LINE_START ; 
 int /*<<< orphan*/  SECTION_NAME ; 
 int /*<<< orphan*/  close_current_line (struct parser*) ; 
 int /*<<< orphan*/  is_eof (struct parser*,int const*) ; 
 int /*<<< orphan*/  isspaceW (int const) ; 
 int /*<<< orphan*/  push_state (struct parser*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_state (struct parser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const WCHAR *line_start_state( struct parser *parser, const WCHAR *pos )
{
    const WCHAR *p;

    for (p = pos; !is_eof( parser, p ); p++)
    {
        switch(*p)
        {
        case '\n':
            parser->line_pos++;
            close_current_line( parser );
            break;
        case ';':
            push_state( parser, LINE_START );
            set_state( parser, COMMENT );
            return p + 1;
        case '[':
            parser->start = p + 1;
            set_state( parser, SECTION_NAME );
            return p + 1;
        default:
            if (isspaceW(*p)) break;
            if (parser->cur_section != -1)
            {
                parser->start = p;
                set_state( parser, KEY_NAME );
                return p;
            }
            if (!parser->broken_line)
                parser->broken_line = parser->line_pos;
            break;
        }
    }
    close_current_line( parser );
    return NULL;
}