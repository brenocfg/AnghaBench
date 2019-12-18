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
typedef  int /*<<< orphan*/  hb_test_data_func_t ;
typedef  int /*<<< orphan*/  gconstpointer ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_test_add_data_func (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* hb_test_normalize_path (char const*) ; 

__attribute__((used)) static inline void
hb_test_add_data_func (const char          *test_path,
		       gconstpointer        test_data,
		       hb_test_data_func_t  test_func)
{
  char *normal_path = hb_test_normalize_path (test_path);
  g_test_add_data_func (normal_path, test_data, test_func);
  g_free (normal_path);
}