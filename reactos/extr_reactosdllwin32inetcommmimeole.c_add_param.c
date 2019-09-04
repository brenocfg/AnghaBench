#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* name; int /*<<< orphan*/  entry; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ param_t ;
struct TYPE_5__ {int /*<<< orphan*/  params; } ;
typedef  TYPE_2__ header_t ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE (char*,char const*) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  unquote_string (char const*) ; 

__attribute__((used)) static void add_param(header_t *header, const char *p)
{
    const char *key = p, *value, *cp = p;
    param_t *param;
    char *name;

    TRACE("got param %s\n", p);

    while (*key == ' ' || *key == '\t' ) key++;

    cp = strchr(key, '=');
    if(!cp)
    {
        WARN("malformed parameter - skipping\n");
        return;
    }

    name = HeapAlloc(GetProcessHeap(), 0, cp - key + 1);
    memcpy(name, key, cp - key);
    name[cp - key] = '\0';

    value = cp + 1;

    param = HeapAlloc(GetProcessHeap(), 0, sizeof(*param));
    param->name = name;
    param->value = unquote_string(value);
    list_add_tail(&header->params, &param->entry);
}