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
typedef  int /*<<< orphan*/  dictionary_t ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_ALLOC () ; 
 int /*<<< orphan*/ * calloc (int,int) ; 

dictionary_t* create_dictionary() {
    dictionary_t* dict = calloc(1, sizeof(dictionary_t));
    if (!dict) {
        BAD_ALLOC();
    }
    return dict;
}