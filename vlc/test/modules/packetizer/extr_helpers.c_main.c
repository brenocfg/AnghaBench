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
typedef  int /*<<< orphan*/  test1_annexbdata ;
struct results_s {int member_0; int member_1; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct results_s const*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int run_annexb_sets (int const*,int const*,struct results_s const*,int /*<<< orphan*/ ,size_t const) ; 

int main( void )
{
    const uint8_t test1_annexbdata[] = { 0, 0, 0, 1, 0x55, 0x55, 0x55, 0x55, 0x55, // 9
                                         0, 0, 1, 0x22, 0x22, //14
                                         0, 0, 1, 0x0, 0x0, //19
                                         0, 0, 1, //22
                                         0, 0, 1, 0, //26
                                         0, 0, 1, 0x11, //30
                                         0, 0, 1,
                                       };
    const struct results_s test1_results[] = {
                                        { 1,  3 + 5 },
                                        { 9,  3 + 2 },
                                        { 14, 3 + 2 },
                                        { 19, 3 + 0 },
                                        { 22, 3 + 1 },
                                        { 26, 3 + 1 },
                                        { 30, 3 + 0 },
                                       };

    printf("* Running tests on set 1:\n");
    int i_ret = run_annexb_sets( test1_annexbdata,
                                 test1_annexbdata + sizeof(test1_annexbdata),
                                 test1_results, ARRAY_SIZE(test1_results), 0 );
    if( i_ret != 0 )
        return i_ret;

    uint8_t *p_data = malloc( 4096 );
    if( p_data )
    {
        const ssize_t i_dataoffset = 4096 - sizeof(test1_annexbdata) - 111;
        memset( p_data, 0x42, 4096 );
        memcpy( &p_data[i_dataoffset],
                test1_annexbdata, sizeof(test1_annexbdata) );
        printf("* Running tests on extended set 1:\n");
        i_ret = run_annexb_sets( p_data,
                                 p_data + 4096,
                                 test1_results, ARRAY_SIZE(test1_results),
                                 i_dataoffset );
        free( p_data );
        if( i_ret != 0 )
            return i_ret;
    }

    return 0;
}