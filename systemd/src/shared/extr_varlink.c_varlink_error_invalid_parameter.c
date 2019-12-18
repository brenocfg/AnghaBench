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
typedef  int /*<<< orphan*/  Varlink ;
typedef  int /*<<< orphan*/  JsonVariant ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VARLINK_ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  assert_return (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * json_variant_by_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ json_variant_elements (int /*<<< orphan*/ *) ; 
 scalar_t__ json_variant_is_object (int /*<<< orphan*/ *) ; 
 scalar_t__ json_variant_is_string (int /*<<< orphan*/ *) ; 
 int varlink_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int varlink_error_invalid_parameter(Varlink *v, JsonVariant *parameters) {

        assert_return(v, -EINVAL);
        assert_return(parameters, -EINVAL);

        /* We expect to be called in one of two ways: the 'parameters' argument is a string variant in which
         * case it is the parameter key name that is invalid. Or the 'parameters' argument is an object
         * variant in which case we'll pull out the first key. The latter mode is useful in functions that
         * don't expect any arguments. */

        if (json_variant_is_string(parameters))
                return varlink_error(v, VARLINK_ERROR_INVALID_PARAMETER, parameters);

        if (json_variant_is_object(parameters) &&
            json_variant_elements(parameters) > 0)
                return varlink_error(v, VARLINK_ERROR_INVALID_PARAMETER,
                                     json_variant_by_index(parameters, 0));

        return -EINVAL;
}