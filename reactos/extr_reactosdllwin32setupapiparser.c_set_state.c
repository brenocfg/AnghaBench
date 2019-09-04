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
struct parser {int state; } ;
typedef  enum parser_state { ____Placeholder_parser_state } parser_state ;

/* Variables and functions */

__attribute__((used)) static inline enum parser_state set_state( struct parser *parser, enum parser_state state )
{
    enum parser_state ret = parser->state;
    parser->state = state;
    return ret;
}