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

/* Variables and functions */
 int /*<<< orphan*/  write_big_endian_word (char) ; 
 int /*<<< orphan*/  write_byte (char) ; 

__attribute__((used)) static void write_bytecounted_string_as_big_endian_unicode(unsigned bytecount, char *s, char padding)
{
    unsigned wordcount = bytecount / 2;

    while (*s != 0 && wordcount != 0)
    {
        write_big_endian_word(*s++);
        wordcount--;
    }
    while (wordcount != 0)
    {
        write_big_endian_word(padding);
        wordcount--;
    }

    if (bytecount % 2 != 0)
        write_byte(padding);
}