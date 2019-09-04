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
struct parser {char* cmd; size_t idx; int len; } ;
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 

__attribute__((used)) static int get_int( struct parser *parser )
{
    const WCHAR *p = &parser->cmd[parser->idx];
    int i, ret = 0;

    for (i = 0; i < parser->len; i++)
    {
        if (p[i] < '0' || p[i] > '9')
        {
            ERR("should only be numbers here!\n");
            break;
        }
        ret = (p[i] - '0') + ret * 10;
    }
    return ret;
}