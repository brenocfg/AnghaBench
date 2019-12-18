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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BasicTest (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DataCreate () ; 
 int /*<<< orphan*/  DataSharedMem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,char*,int) ; 
 int /*<<< orphan*/  DeleteImage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ EEXIST ; 
 int GenImage (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int HEIGHT ; 
 int /*<<< orphan*/  IPC_PRIVATE ; 
 int /*<<< orphan*/  IPC_RMID ; 
 int /*<<< orphan*/  S_IRWXU ; 
 int TEXTSIZE ; 
 int /*<<< orphan*/  TextTest (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int WIDTH ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ mkfifo (char*,int /*<<< orphan*/ ) ; 
 void* p_imageRGBA ; 
 void* p_text ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 void* shmat (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int shmctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int shmget (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int main( int i_argc, char *ppsz_argv[] ) {
    if( i_argc != 3 ) {
        printf( "Incorrect number of parameters.\n"
                "Usage is: %s command-fifo response-fifo\n", ppsz_argv[0] );
        exit( -2 );
    }

    printf( "Creating shared memory for RGBA..." );
    int i_shmRGBA = shmget( IPC_PRIVATE, WIDTH * HEIGHT * 4, S_IRWXU );
    if( i_shmRGBA == -1 ) {
        printf( " failed\n" );
        exit( -1 );
    }
    printf( " done, ID is %d. Text...", i_shmRGBA );
    int i_shmText = shmget( IPC_PRIVATE, TEXTSIZE, S_IRWXU );
    if( i_shmText == -1 ) {
        printf( " failed\n" );
        exit( -1 );
    }
    printf( " done, ID is %d\n", i_shmText );

    printf( "Attaching shared memory for RGBA..." );
    p_imageRGBA = shmat( i_shmRGBA, NULL, 0 );
    if( p_imageRGBA == (void*)-1 ) {
        printf( " failed\n" );
        exit( -1 );
    }
    printf( " done. Text..." );
    p_text = shmat( i_shmText, NULL, 0 );
    if( p_text == (void*)-1 ) {
        printf( " failed\n" );
        exit( -1 );
    }
    printf( " done\n" );

    printf( "Queueing shared memory for destruction, RGBA..." );
    if( shmctl( i_shmRGBA, IPC_RMID, 0 ) == -1 ) {
        printf( " failed\n" );
        exit( -1 );
    }
    printf( " done. Text..." );
    if( shmctl( i_shmText, IPC_RMID, 0 ) == -1 ) {
        printf( " failed\n" );
        exit( -1 );
    }
    printf( " done\n" );

    printf( "Generating data..." );
    DataCreate();
    printf( " done\n" );

    printf( "Making FIFOs..." );
    if( mkfifo( ppsz_argv[1], S_IRWXU ) ) {
        if( errno != EEXIST ) {
            printf( " failed\n" );
            exit( -1 );
        }
        printf( " input already exists..." );
    }
    if( mkfifo( ppsz_argv[2], S_IRWXU ) ) {
        if( errno != EEXIST ) {
            printf( " failed\n" );
            exit( -1 );
        }
        printf( " output already exists..." );
    }
    printf( " done\n" );

    printf( "Please make sure vlc is running.\n"
            "You should append parameters similar to the following:\n"
            "--sub-source overlay{input=%s,output=%s}\n",
            ppsz_argv[1], ppsz_argv[2] );

    printf( "Opening FIFOs..." );
    FILE *p_cmd = fopen( ppsz_argv[1], "w" );
    if( p_cmd == NULL ) {
        printf( " failed\n" );
        exit( -1 );
    }
    FILE *p_res = fopen( ppsz_argv[2], "r" );
    if( p_res == NULL ) {
        printf( " failed\n" );
        exit( -1 );
    }
    printf( " done\n" );

    int i_overlay_image = GenImage( p_cmd, p_res );
    int i_overlay_text = GenImage( p_cmd, p_res );
    DataSharedMem( p_cmd, p_res, i_overlay_image, WIDTH, HEIGHT, "RGBA",
                   i_shmRGBA );
    DataSharedMem( p_cmd, p_res, i_overlay_text, TEXTSIZE, 1, "TEXT",
                   i_shmText );

    BasicTest( p_cmd, p_res, i_overlay_image );
    BasicTest( p_cmd, p_res, i_overlay_text );
    TextTest( p_cmd, p_res, i_overlay_text );

    DeleteImage( p_cmd, p_res, i_overlay_image );
    DeleteImage( p_cmd, p_res, i_overlay_text );
}