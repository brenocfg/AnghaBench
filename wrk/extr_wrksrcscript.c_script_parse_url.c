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
struct http_parser_url {int field_set; } ;

/* Variables and functions */
 int UF_HOST ; 
 int UF_SCHEMA ; 
 int /*<<< orphan*/  http_parser_parse_url (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct http_parser_url*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int script_parse_url(char *url, struct http_parser_url *parts) {
    if (!http_parser_parse_url(url, strlen(url), 0, parts)) {
        if (!(parts->field_set & (1 << UF_SCHEMA))) return 0;
        if (!(parts->field_set & (1 << UF_HOST)))   return 0;
        return 1;
    }
    return 0;
}