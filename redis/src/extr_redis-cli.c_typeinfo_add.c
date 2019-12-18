#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ typeinfo ;
typedef  int /*<<< orphan*/  dict ;

/* Variables and functions */
 int /*<<< orphan*/  dictAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 TYPE_1__* zmalloc (int) ; 

__attribute__((used)) static typeinfo* typeinfo_add(dict *types, char* name, typeinfo* type_template) {
    typeinfo *info = zmalloc(sizeof(typeinfo));
    *info = *type_template;
    info->name = sdsnew(name);
    dictAdd(types, info->name, info);
    return info;
}