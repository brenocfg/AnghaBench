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
typedef  int /*<<< orphan*/  result_t ;

/* Variables and functions */
#define  result_error_compression_error 133 
#define  result_error_decompression_error 132 
#define  result_error_ok 131 
#define  result_error_round_trip_error 130 
#define  result_error_skip 129 
#define  result_error_system_error 128 
 int result_get_error (int /*<<< orphan*/ ) ; 

char const* result_get_error_string(result_t result) {
    switch (result_get_error(result)) {
        case result_error_ok:
            return "okay";
        case result_error_skip:
            return "skip";
        case result_error_system_error:
            return "system error";
        case result_error_compression_error:
            return "compression error";
        case result_error_decompression_error:
            return "decompression error";
        case result_error_round_trip_error:
            return "round trip error";
    }
}