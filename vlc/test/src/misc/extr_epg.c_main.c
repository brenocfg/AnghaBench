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
typedef  int /*<<< orphan*/  vlc_epg_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPG_ADD (int /*<<< orphan*/ *,int,int,char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert_current (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  assert_events (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  print_order (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_init () ; 
 int /*<<< orphan*/  vlc_epg_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_epg_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_epg_SetCurrent (int /*<<< orphan*/ *,int) ; 

int main( void )
{
    test_init();

    int i=1;

    /* Simple insert/current test */
    printf("--test %d\n", i++);
    vlc_epg_t *p_epg = vlc_epg_New( 0, 0 );
    assert(p_epg);
    EPG_ADD( p_epg,  42, 20, "A" );
    EPG_ADD( p_epg,  62, 20, "B" );
    EPG_ADD( p_epg,  82, 20, "C" );
    EPG_ADD( p_epg, 102, 20, "D" );
    print_order( p_epg );
    assert_events( p_epg, "ABCD", 4 );
    assert_current( p_epg, NULL );

    vlc_epg_SetCurrent( p_epg, 82 );
    assert_current( p_epg, "C" );

    vlc_epg_Delete( p_epg );


    /* Test reordering / head/tail inserts */
    printf("--test %d\n", i++);
    p_epg = vlc_epg_New( 0, 0 );
    assert(p_epg);
    EPG_ADD( p_epg,  82, 20, "C" );
    EPG_ADD( p_epg,  62, 20, "B" );
    EPG_ADD( p_epg, 102, 20, "D" );
    EPG_ADD( p_epg,  42, 20, "A" );
    print_order( p_epg );
    assert_events( p_epg, "ABCD", 4 );
    vlc_epg_Delete( p_epg );

    /* Test reordering/bisect lookup on insert */
    printf("--test %d\n", i++);
    p_epg = vlc_epg_New( 0, 0 );
    assert(p_epg);
    EPG_ADD( p_epg, 142, 20, "F" );
    EPG_ADD( p_epg, 122, 20, "E" );
    EPG_ADD( p_epg, 102, 20, "D" );
    EPG_ADD( p_epg,  82, 20, "C" );
    EPG_ADD( p_epg,  42, 20, "A" );
    EPG_ADD( p_epg,  62, 20, "B" );
    print_order( p_epg );
    assert_events( p_epg, "ABCDEF", 6 );
    vlc_epg_Delete( p_epg );

    /* Test deduplication and current pointer rebasing on insert */
    printf("--test %d\n", i++);
    p_epg = vlc_epg_New( 0, 0 );
    assert(p_epg);
    EPG_ADD( p_epg,  62, 20, "E" );
    EPG_ADD( p_epg,  62, 20, "F" );
    EPG_ADD( p_epg,  42, 20, "A" );
    vlc_epg_SetCurrent( p_epg, 62 );
    EPG_ADD( p_epg,  82, 20, "C" );
    EPG_ADD( p_epg,  62, 20, "B" );
    EPG_ADD( p_epg, 102, 20, "D" );
    print_order( p_epg );
    assert_events( p_epg, "ABCD", 4 );
    assert_current( p_epg, "B" );
    vlc_epg_Delete( p_epg );

    return 0;
}