#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  result; } ;
struct TYPE_7__ {struct TYPE_7__* next; TYPE_2__ res; } ;
typedef  TYPE_1__ winner_ll_node ;
typedef  TYPE_2__ winnerInfo_t ;
typedef  int /*<<< orphan*/  constraint_t ;
typedef  int /*<<< orphan*/  BMK_benchResult_t ;

/* Variables and functions */
#define  BETTER_RESULT 131 
#define  SIZE_RESULT 130 
#define  SPEED_RESULT 129 
#define  WORSE_RESULT 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  feasible (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* g_winners ; 
 TYPE_1__* malloc (int) ; 
 int speedSizeCompare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
insertWinner(const winnerInfo_t w, const constraint_t targetConstraints)
{
    BMK_benchResult_t r = w.result;
    winner_ll_node* cur_node = g_winners;
    /* first node to insert */
    if(!feasible(r, targetConstraints)) {
        return 1;
    }

    if(g_winners == NULL) {
        winner_ll_node* first_node = malloc(sizeof(winner_ll_node));
        if(first_node == NULL) {
            return 1;
        }
        first_node->next = NULL;
        first_node->res = w;
        g_winners = first_node;
        return 0;
    }

    while(cur_node->next != NULL) {
        switch(speedSizeCompare(cur_node->res.result, r)) {
            case WORSE_RESULT:
            {
                return 1; /* never insert if better */
            }
            case BETTER_RESULT:
            {
                winner_ll_node* tmp;
                cur_node->res = cur_node->next->res;
                tmp = cur_node->next;
                cur_node->next = cur_node->next->next;
                free(tmp);
                break;
            }
            case SIZE_RESULT:
            {
                cur_node = cur_node->next;
                break;
            }
            case SPEED_RESULT: /* insert after first size result, then return */
            {
                winner_ll_node* newnode = malloc(sizeof(winner_ll_node));
                if(newnode == NULL) {
                    return 1;
                }
                newnode->res = cur_node->res;
                cur_node->res = w;
                newnode->next = cur_node->next;
                cur_node->next = newnode;
                return 0;
            }
        }

    }

    assert(cur_node->next == NULL);
    switch(speedSizeCompare(cur_node->res.result, r)) {
        case WORSE_RESULT:
        {
            return 1; /* never insert if better */
        }
        case BETTER_RESULT:
        {
            cur_node->res = w;
            return 0;
        }
        case SIZE_RESULT:
        {
            winner_ll_node* newnode = malloc(sizeof(winner_ll_node));
            if(newnode == NULL) {
                return 1;
            }
            newnode->res = w;
            newnode->next = NULL;
            cur_node->next = newnode;
            return 0;
        }
        case SPEED_RESULT: /* insert before first size result, then return */
        {
            winner_ll_node* newnode = malloc(sizeof(winner_ll_node));
            if(newnode == NULL) {
                return 1;
            }
            newnode->res = cur_node->res;
            cur_node->res = w;
            newnode->next = cur_node->next;
            cur_node->next = newnode;
            return 0;
        }
        default:
            return 1;
    }
}