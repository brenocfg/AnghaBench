#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int O_BINARY ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 unsigned int nb_resources ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  output_buffer ; 
 scalar_t__ output_buffer_pos ; 
 int /*<<< orphan*/  put_dword (int) ; 
 int /*<<< orphan*/  put_word (int) ; 
 TYPE_1__* resources ; 
 scalar_t__ write (int,int /*<<< orphan*/ ,scalar_t__) ; 

void flush_output_resources( const char *name )
{
    int fd;
    unsigned int i;

    /* all output must have been saved with add_output_to_resources() first */
    assert( !output_buffer_pos );

    put_dword( 0 );      /* ResSize */
    put_dword( 32 );     /* HeaderSize */
    put_word( 0xffff );  /* ResType */
    put_word( 0x0000 );
    put_word( 0xffff );  /* ResName */
    put_word( 0x0000 );
    put_dword( 0 );      /* DataVersion */
    put_word( 0 );       /* Memory options */
    put_word( 0 );       /* Language */
    put_dword( 0 );      /* Version */
    put_dword( 0 );      /* Characteristics */

    fd = open( name, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, 0666 );
    if (fd == -1) error( "Error creating %s\n", name );
    if (write( fd, output_buffer, output_buffer_pos ) != output_buffer_pos)
        error( "Error writing to %s\n", name );
    for (i = 0; i < nb_resources; i++)
    {
        if (write( fd, resources[i].data, resources[i].size ) != resources[i].size)
            error( "Error writing to %s\n", name );
        free( resources[i].data );
    }
    close( fd );
    nb_resources = 0;
    free( output_buffer );
}