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
 int O_BINARY ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  output_buffer ; 
 scalar_t__ output_buffer_pos ; 
 scalar_t__ write (int,int /*<<< orphan*/ ,scalar_t__) ; 

void flush_output_buffer( const char *name )
{
    int fd = open( name, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, 0666 );
    if (fd == -1) error( "Error creating %s\n", name );
    if (write( fd, output_buffer, output_buffer_pos ) != output_buffer_pos)
        error( "Error writing to %s\n", name );
    close( fd );
    free( output_buffer );
}