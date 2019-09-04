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
struct inf_value {char* key; char* value; int /*<<< orphan*/  entry; struct inf_section* section; } ;
struct inf_section {int /*<<< orphan*/  values; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 struct inf_value* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 char* trim (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT inf_value_parse(struct inf_section *sec, char *line)
{
    struct inf_value *key_val;
    char *key, *value, *del;

    del = strchr(line, '=');
    if (!del) return S_OK;

    *del = 0;
    key = line;
    value = del + 1;

    key = trim(key, NULL, FALSE);
    value = trim(value, NULL, TRUE);

    key_val = heap_alloc_zero(sizeof(*key_val));
    if (!key_val) return E_OUTOFMEMORY;

    key_val->key = key;
    key_val->value = value;
    key_val->section = sec;

    list_add_tail(&sec->values, &key_val->entry);
    return S_OK;
}