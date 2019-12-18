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
typedef  int int32_t ;
typedef  int /*<<< orphan*/  UChar ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static char *generate_token_printable_code(const UChar *buf, int32_t length)
{
    char *out = (char *) malloc(length * 5 + 1);
    char *pc = out;
    if (!out)
        return "";

    while (length > 0) {
        snprintf(pc, 6, "%04hX ", *buf);
        length--;
        buf++;
        pc += 5;
    }

    return out;
}