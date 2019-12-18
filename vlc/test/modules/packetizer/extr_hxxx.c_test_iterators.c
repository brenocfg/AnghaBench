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
typedef  int /*<<< orphan*/  hxxx_iterator_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int hxxx_annexb_iterate_next (int /*<<< orphan*/ *,int const**,size_t*) ; 
 int hxxx_iterate_next (int /*<<< orphan*/ *,int const**,size_t*) ; 
 int /*<<< orphan*/  hxxx_iterator_init (int /*<<< orphan*/ *,int const*,size_t,int) ; 
 scalar_t__ memcmp (int const*,int const*,size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void test_iterators( const uint8_t *p_ab, size_t i_ab, /* AnnexB */
                            const uint8_t **pp_prefix, size_t *pi_prefix /* Prefixed */ )
{
    printf("INPUT SET    : ");
    for(size_t j=0; j<i_ab; j++)
        printf("0x%.2x, ", p_ab[j] );
    printf("\n");

    for( unsigned int i=0; i<3; i++)
    {
        const uint8_t *p_prefix = pp_prefix[i];
        size_t i_prefix = pi_prefix[i];

        printf("Test with prefix len %d:\n", 1 << i);

        hxxx_iterator_ctx_t it_ab;
        hxxx_iterator_init( &it_ab, p_ab, i_ab, 0 );

        hxxx_iterator_ctx_t it_prefix;
        hxxx_iterator_init( &it_prefix, p_prefix, i_prefix, 1 << i );

        const uint8_t *p_start_ab; size_t i_size_ab;
        const uint8_t *p_start_prefix; size_t i_size_prefix;

        bool b1 = true;
        bool b2 = true;

        int i_nal = 0;
        while(b1 && b2)
        {
            /* hxxx_*_iterate_next can potentially not set these pointers. */
            p_start_ab = NULL;
            p_start_prefix = NULL;

            b1 = hxxx_annexb_iterate_next( &it_ab, &p_start_ab, &i_size_ab );
            b2 = hxxx_iterate_next( &it_prefix, &p_start_prefix, &i_size_prefix );
            printf("NAL %d ", i_nal++);
            if( b1 != b2 )
                printf(", returns %d != %d\n", b1, b2);
            assert(b1 == b2);
            if( b1 && b2 )
            {
                assert(i_size_ab == i_size_prefix);
                assert(memcmp(p_start_ab, p_start_prefix, i_size_ab) == 0);
                for(size_t j=0; j<i_size_ab; j++)
                    printf("0x%.2x, ", p_start_ab[j] );
                printf("\n");
            }
        }
        printf("\n");

    }
}