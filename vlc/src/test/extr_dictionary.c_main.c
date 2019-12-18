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
typedef  int /*<<< orphan*/  vlc_dictionary_t ;
typedef  int /*<<< orphan*/  our_keys ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  test_dictionary_validity (int /*<<< orphan*/ *,char const**,int const) ; 
 char** vlc_dictionary_all_keys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_dictionary_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vlc_dictionary_has_key (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  vlc_dictionary_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_dictionary_insert (int /*<<< orphan*/ *,char const*,void*) ; 
 int vlc_dictionary_is_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_dictionary_keys_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_dictionary_remove_value_for_key (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int main (void)
{
    static const char * our_keys[] = {
        "Hello", "Hella", "flowmeter", "Frostnipped", "frostnipped", "remiform", "quadrifoliolate", "singularity", "unafflicted"
    };
    const int size = sizeof(our_keys)/sizeof(our_keys[0]);
    char ** keys;
    intptr_t i = 0;

    vlc_dictionary_t dict;
    vlc_dictionary_init( &dict, 0 );

    assert( vlc_dictionary_keys_count( &dict ) == 0 );
    assert( vlc_dictionary_is_empty( &dict ) );

    keys = vlc_dictionary_all_keys( &dict );
    assert( keys && !keys[0] );
    free(keys);


    /* Insert some values */
    for( i = 0; i < size; i++ )
    {
        vlc_dictionary_insert( &dict, our_keys[i], (void *)i );
        assert( vlc_dictionary_has_key(&dict, our_keys[i]) );
        for( int j = i + 1; j < size; j++ )
            assert( !vlc_dictionary_has_key(&dict, our_keys[j]) );
    }

    assert( !vlc_dictionary_is_empty( &dict ) );
    test_dictionary_validity( &dict, our_keys, size );

    vlc_dictionary_remove_value_for_key( &dict, our_keys[size-1], NULL, NULL );

    test_dictionary_validity( &dict, our_keys, size-1 );

    vlc_dictionary_clear( &dict, NULL, NULL );

    assert( vlc_dictionary_keys_count( &dict ) == 0 );
    assert( vlc_dictionary_is_empty( &dict ) );
    return 0;
}