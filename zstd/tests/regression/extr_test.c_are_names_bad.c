#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* name; } ;
struct TYPE_5__ {char* name; } ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
 TYPE_3__** configs ; 
 TYPE_2__** data ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ is_name_bad (char*) ; 
 TYPE_1__** methods ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int are_names_bad() {
    for (size_t method = 0; methods[method] != NULL; ++method)
        if (is_name_bad(methods[method]->name)) {
            fprintf(stderr, "method name %s is bad\n", methods[method]->name);
            return 1;
        }
    for (size_t datum = 0; data[datum] != NULL; ++datum)
        if (is_name_bad(data[datum]->name)) {
            fprintf(stderr, "data name %s is bad\n", data[datum]->name);
            return 1;
        }
    for (size_t config = 0; configs[config] != NULL; ++config)
        if (is_name_bad(configs[config]->name)) {
            fprintf(stderr, "config name %s is bad\n", configs[config]->name);
            return 1;
        }
    return 0;
}