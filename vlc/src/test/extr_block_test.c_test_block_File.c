#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_1__ block_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* block_File (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  block_Release (TYPE_1__*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,scalar_t__) ; 
 int /*<<< orphan*/  remove (char*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  text ; 

__attribute__((used)) static void test_block_File(bool write)
{
    FILE *stream;
    int res;

    stream = fopen ("testfile.txt", "wb+e");
    assert (stream != NULL);

    res = fputs (text, stream);
    assert (res != EOF);
    res = fflush (stream);
    assert (res != EOF);

    block_t *block = block_File(fileno(stream), write);
    fclose (stream);

    assert (block != NULL);
    assert (block->i_buffer == strlen (text));
    assert (!memcmp (block->p_buffer, text, block->i_buffer));
    if (write)
        memset(block->p_buffer, 'A', block->i_buffer);
    block_Release (block);

    remove ("testfile.txt");
}