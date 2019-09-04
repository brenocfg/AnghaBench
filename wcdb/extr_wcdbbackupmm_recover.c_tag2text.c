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
typedef  int uint8_t ;

/* Variables and functions */
 char const** BIND_TAG_TEXT ; 
 char const** FUNC_TAG_TEXT ; 

__attribute__((used)) static const char *tag2text(uint8_t tag)
{
    return (tag & 0x80) ? FUNC_TAG_TEXT[tag & 0x7F] : BIND_TAG_TEXT[tag];
}