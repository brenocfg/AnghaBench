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
typedef  int /*<<< orphan*/  OutputMode ;

/* Variables and functions */
 int IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTPUT_JSON ; 
 int /*<<< orphan*/  OUTPUT_JSON_PRETTY ; 
 int /*<<< orphan*/  OUTPUT_JSON_SEQ ; 
 int /*<<< orphan*/  OUTPUT_JSON_SSE ; 

__attribute__((used)) static inline bool OUTPUT_MODE_IS_JSON(OutputMode m) {
        return IN_SET(m, OUTPUT_JSON, OUTPUT_JSON_PRETTY, OUTPUT_JSON_SSE, OUTPUT_JSON_SEQ);
}