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
typedef  int /*<<< orphan*/  JsonVariant ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int JSON_FORMAT_COLOR_AUTO ; 
 int JSON_FORMAT_NEWLINE ; 
 int JSON_FORMAT_PRETTY ; 
 scalar_t__ JSON_PRETTY ; 
 scalar_t__ arg_json ; 
 int /*<<< orphan*/  json_variant_dump (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void json_dump_with_flags(JsonVariant *v, FILE *f) {

        json_variant_dump(v,
                          (arg_json == JSON_PRETTY ? JSON_FORMAT_PRETTY : JSON_FORMAT_NEWLINE) |
                          JSON_FORMAT_COLOR_AUTO,
                          f, NULL);
}