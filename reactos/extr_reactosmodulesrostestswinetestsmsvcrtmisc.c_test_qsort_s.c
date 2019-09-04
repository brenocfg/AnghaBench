#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_70__   TYPE_9__ ;
typedef  struct TYPE_69__   TYPE_8__ ;
typedef  struct TYPE_68__   TYPE_7__ ;
typedef  struct TYPE_67__   TYPE_6__ ;
typedef  struct TYPE_66__   TYPE_5__ ;
typedef  struct TYPE_65__   TYPE_4__ ;
typedef  struct TYPE_64__   TYPE_3__ ;
typedef  struct TYPE_63__   TYPE_35__ ;
typedef  struct TYPE_62__   TYPE_34__ ;
typedef  struct TYPE_61__   TYPE_33__ ;
typedef  struct TYPE_60__   TYPE_32__ ;
typedef  struct TYPE_59__   TYPE_31__ ;
typedef  struct TYPE_58__   TYPE_30__ ;
typedef  struct TYPE_57__   TYPE_2__ ;
typedef  struct TYPE_56__   TYPE_29__ ;
typedef  struct TYPE_55__   TYPE_28__ ;
typedef  struct TYPE_54__   TYPE_27__ ;
typedef  struct TYPE_53__   TYPE_26__ ;
typedef  struct TYPE_52__   TYPE_25__ ;
typedef  struct TYPE_51__   TYPE_24__ ;
typedef  struct TYPE_50__   TYPE_23__ ;
typedef  struct TYPE_49__   TYPE_22__ ;
typedef  struct TYPE_48__   TYPE_21__ ;
typedef  struct TYPE_47__   TYPE_20__ ;
typedef  struct TYPE_46__   TYPE_1__ ;
typedef  struct TYPE_45__   TYPE_19__ ;
typedef  struct TYPE_44__   TYPE_18__ ;
typedef  struct TYPE_43__   TYPE_17__ ;
typedef  struct TYPE_42__   TYPE_16__ ;
typedef  struct TYPE_41__   TYPE_15__ ;
typedef  struct TYPE_40__   TYPE_14__ ;
typedef  struct TYPE_39__   TYPE_13__ ;
typedef  struct TYPE_38__   TYPE_12__ ;
typedef  struct TYPE_37__   TYPE_11__ ;
typedef  struct TYPE_36__   TYPE_10__ ;

/* Type definitions */
struct TYPE_67__ {int member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_66__ {int member_0; int member_1; } ;
struct TYPE_65__ {int member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_64__ {int member_0; int member_1; } ;
struct TYPE_57__ {int member_0; int member_1; } ;
struct TYPE_46__ {int member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_44__ {int member_0; int member_1; } ;
struct TYPE_43__ {int member_0; int member_1; } ;
struct TYPE_42__ {int member_0; int member_1; } ;
struct TYPE_41__ {int member_0; int member_1; } ;
struct TYPE_40__ {int member_0; int member_1; } ;
struct TYPE_39__ {int member_0; int member_1; } ;
struct TYPE_38__ {int member_0; int member_1; } ;
struct TYPE_37__ {int member_0; int member_1; } ;
struct TYPE_36__ {int member_0; int member_1; } ;
struct TYPE_70__ {int member_0; int member_1; } ;
struct TYPE_69__ {int member_0; int member_1; } ;
struct TYPE_68__ {int member_0; int member_1; } ;
struct TYPE_63__ {int member_0; int member_1; } ;
struct TYPE_62__ {int member_0; int member_1; } ;
struct TYPE_61__ {int member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_60__ {int member_0; int member_1; } ;
struct TYPE_59__ {int member_0; int member_1; } ;
struct TYPE_58__ {int member_0; int member_1; } ;
struct TYPE_56__ {int member_0; int member_1; } ;
struct TYPE_55__ {int member_0; int member_1; } ;
struct TYPE_54__ {int member_0; int member_1; } ;
struct TYPE_53__ {int member_0; int member_1; } ;
struct TYPE_52__ {int member_0; int member_1; } ;
struct TYPE_51__ {int member_0; int member_1; } ;
struct TYPE_50__ {int member_0; int member_1; } ;
struct TYPE_49__ {int member_0; int member_1; } ;
struct TYPE_48__ {int member_0; int member_1; } ;
struct TYPE_47__ {int member_0; int member_1; } ;
struct TYPE_45__ {TYPE_6__ member_33; TYPE_5__ member_32; TYPE_4__ member_31; TYPE_3__ member_30; TYPE_2__ member_29; TYPE_1__ member_28; TYPE_18__ member_27; TYPE_17__ member_26; TYPE_16__ member_25; TYPE_15__ member_24; TYPE_14__ member_23; TYPE_13__ member_22; TYPE_12__ member_21; TYPE_11__ member_20; TYPE_10__ member_19; TYPE_9__ member_18; TYPE_8__ member_17; TYPE_7__ member_16; TYPE_35__ member_15; TYPE_34__ member_14; TYPE_33__ member_13; TYPE_32__ member_12; TYPE_31__ member_11; TYPE_30__ member_10; TYPE_29__ member_9; TYPE_28__ member_8; TYPE_27__ member_7; TYPE_26__ member_6; TYPE_25__ member_5; TYPE_24__ member_4; TYPE_23__ member_3; TYPE_22__ member_2; TYPE_21__ member_1; TYPE_20__ member_0; } ;
struct qsort_test {int* member_1; int pos; TYPE_19__ member_2; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  p_qsort_s (int*,int,int,int /*<<< orphan*/ ,struct qsort_test*) ; 
 int /*<<< orphan*/  qsort_comp ; 
 int rand () ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_qsort_s(void)
{
    static const int nonstable_test[] = {9000, 8001, 7002, 6003, 1003, 5004, 4005, 3006, 2007};
    int tab[100], i;

    struct qsort_test small_sort = {
        0, tab, {
            {1, 0}, {2, 1}, {3, 2}, {4, 3}, {5, 4}, {6, 5}, {7, 6},
            {1, 0}, {2, 1}, {3, 2}, {4, 3}, {5, 4}, {6, 5},
            {1, 0}, {2, 1}, {3, 2}, {4, 3}, {5, 4},
            {1, 0}, {2, 1}, {3, 2}, {4, 3},
            {1, 0}, {2, 1}, {3, 2},
            {1, 0}, {2, 1},
            {1, 0}
        }
    }, small_sort2 = {
        0, tab, {
            {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0},
            {1, 0}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1},
            {1, 0}, {2, 1}, {3, 2}, {4, 2}, {5, 2},
            {1, 0}, {2, 1}, {3, 2}, {4, 3},
            {1, 0}, {2, 1}, {3, 2},
            {1, 0}, {2, 1},
            {1, 0}
        }
    }, quick_sort = {
        0, tab, {
            {0, 4}, {0, 8}, {4, 8},
            {1, 4}, {2, 4}, {3, 4}, {5, 4}, {6, 4}, {7, 4}, {7, 4}, {6, 4},
            {6, 4},
            {8, 7},
            {1, 0}, {2, 1}, {3, 2}, {4, 3}, {5, 4}, {6, 4},
            {1, 0}, {2, 1}, {3, 2}, {4, 3}, {5, 3},
            {1, 0}, {2, 1}, {3, 2}, {4, 2},
            {1, 0}, {2, 1}, {3, 2},
            {1, 0}, {2, 1},
            {1, 0}
        }
    };

    if(!p_qsort_s) {
        win_skip("qsort_s not available\n");
        return;
    }

    for(i=0; i<8; i++) tab[i] = i;
    p_qsort_s(tab, 8, sizeof(int), qsort_comp, &small_sort);
    ok(small_sort.pos == 28, "small_sort.pos = %d\n", small_sort.pos);
    for(i=0; i<8; i++)
        ok(tab[i] == i, "tab[%d] = %d\n", i, tab[i]);

    for(i=0; i<8; i++) tab[i] = 7-i;
    p_qsort_s(tab, 8, sizeof(int), qsort_comp, &small_sort2);
    ok(small_sort2.pos == 28, "small_sort2.pos = %d\n", small_sort2.pos);
    for(i=0; i<8; i++)
        ok(tab[i] == i, "tab[%d] = %d\n", i, tab[i]);

    for(i=0; i<9; i++) tab[i] = i;
    tab[5] = 1;
    tab[6] = 2;
    p_qsort_s(tab, 9, sizeof(int), qsort_comp, &quick_sort);
    ok(quick_sort.pos == 34, "quick_sort.pos = %d\n", quick_sort.pos);

    /* show that qsort is not stable */
    for(i=0; i<9; i++) tab[i] = 8-i + 1000*(i+1);
    tab[0] = 1003;
    p_qsort_s(tab, 9, sizeof(int), qsort_comp, NULL);
    for(i=0; i<9; i++)
        ok(tab[i] == nonstable_test[i], "tab[%d] = %d, expected %d\n", i, tab[i], nonstable_test[i]);

    /* check if random data is sorted */
    srand(0);
    for(i=0; i<100; i++) tab[i] = rand()%1000;
    p_qsort_s(tab, 100, sizeof(int), qsort_comp, NULL);
    for(i=1; i<100; i++)
        ok(tab[i-1] <= tab[i], "data sorted incorrectly on position %d: %d <= %d\n", i, tab[i-1], tab[i]);

    /* test if random permutation is sorted correctly */
    for(i=0; i<100; i++) tab[i] = i;
    for(i=0; i<100; i++) {
        int b = rand()%100;
        int e = rand()%100;

        if(b == e) continue;
        tab[b] ^= tab[e];
        tab[e] ^= tab[b];
        tab[b] ^= tab[e];
    }
    p_qsort_s(tab, 100, sizeof(int), qsort_comp, NULL);
    for(i=0; i<100; i++)
        ok(tab[i] == i, "data sorted incorrectly on position %d: %d\n", i, tab[i]);
}