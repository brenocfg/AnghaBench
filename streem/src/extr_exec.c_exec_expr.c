#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_51__   TYPE_9__ ;
typedef  struct TYPE_50__   TYPE_8__ ;
typedef  struct TYPE_49__   TYPE_7__ ;
typedef  struct TYPE_48__   TYPE_6__ ;
typedef  struct TYPE_47__   TYPE_5__ ;
typedef  struct TYPE_46__   TYPE_4__ ;
typedef  struct TYPE_45__   TYPE_3__ ;
typedef  struct TYPE_44__   TYPE_2__ ;
typedef  struct TYPE_43__   TYPE_22__ ;
typedef  struct TYPE_42__   TYPE_21__ ;
typedef  struct TYPE_41__   TYPE_20__ ;
typedef  struct TYPE_40__   TYPE_1__ ;
typedef  struct TYPE_39__   TYPE_19__ ;
typedef  struct TYPE_38__   TYPE_18__ ;
typedef  struct TYPE_37__   TYPE_17__ ;
typedef  struct TYPE_36__   TYPE_16__ ;
typedef  struct TYPE_35__   TYPE_15__ ;
typedef  struct TYPE_34__   TYPE_14__ ;
typedef  struct TYPE_33__   TYPE_13__ ;
typedef  struct TYPE_32__   TYPE_12__ ;
typedef  struct TYPE_31__   TYPE_11__ ;
typedef  struct TYPE_30__   TYPE_10__ ;

/* Type definitions */
struct strm_lambda {int /*<<< orphan*/ * body; int /*<<< orphan*/  type; int /*<<< orphan*/ * state; } ;
struct strm_genfunc {int /*<<< orphan*/ * body; int /*<<< orphan*/  type; int /*<<< orphan*/ * state; } ;
typedef  void* strm_value ;
typedef  int /*<<< orphan*/  strm_string ;
struct TYPE_40__ {TYPE_17__* exc; } ;
typedef  TYPE_1__ strm_stream ;
typedef  int /*<<< orphan*/  strm_state ;
typedef  size_t strm_int ;
typedef  int /*<<< orphan*/ * strm_ary_ns ;
typedef  int /*<<< orphan*/  strm_ary_headers ;
typedef  void* strm_array ;
struct TYPE_44__ {int /*<<< orphan*/  utc_offset; int /*<<< orphan*/  usec; int /*<<< orphan*/  sec; } ;
typedef  TYPE_2__ node_time ;
struct TYPE_45__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_3__ node_str ;
struct TYPE_46__ {TYPE_22__* node; } ;
typedef  TYPE_4__ node_splat ;
struct TYPE_47__ {scalar_t__ rv; } ;
typedef  TYPE_5__ node_return ;
struct TYPE_48__ {int /*<<< orphan*/  op; TYPE_22__* rhs; TYPE_22__* lhs; } ;
typedef  TYPE_6__ node_op ;
struct TYPE_49__ {TYPE_22__* body; int /*<<< orphan*/  name; } ;
typedef  TYPE_7__ node_ns ;
struct TYPE_50__ {int len; TYPE_22__** data; } ;
typedef  TYPE_8__ node_nodes ;
struct TYPE_51__ {int /*<<< orphan*/  lhs; TYPE_22__* rhs; } ;
typedef  TYPE_9__ node_let ;
typedef  int /*<<< orphan*/  node_lambda ;
struct TYPE_30__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_10__ node_int ;
struct TYPE_31__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_11__ node_import ;
struct TYPE_32__ {TYPE_22__* opt_else; TYPE_22__* then; TYPE_22__* cond; } ;
typedef  TYPE_12__ node_if ;
struct TYPE_33__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_13__ node_ident ;
struct TYPE_34__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_14__ node_genfunc ;
struct TYPE_35__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_15__ node_float ;
struct TYPE_36__ {TYPE_22__* args; TYPE_22__* func; } ;
typedef  TYPE_16__ node_fcall ;
struct TYPE_37__ {int /*<<< orphan*/  lineno; int /*<<< orphan*/  fname; } ;
typedef  TYPE_17__ node_error ;
struct TYPE_38__ {scalar_t__ emit; } ;
typedef  TYPE_18__ node_emit ;
struct TYPE_39__ {int /*<<< orphan*/  ident; TYPE_22__* args; } ;
typedef  TYPE_19__ node_call ;
struct TYPE_41__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_20__ node_bool ;
struct TYPE_42__ {int len; int /*<<< orphan*/  ns; int /*<<< orphan*/  headers; TYPE_22__** data; } ;
typedef  TYPE_21__ node_array ;
struct TYPE_43__ {int type; int /*<<< orphan*/  lineno; int /*<<< orphan*/  fname; } ;
typedef  TYPE_22__ node ;

/* Variables and functions */
 int FALSE ; 
#define  NODE_ARRAY 149 
#define  NODE_BOOL 148 
#define  NODE_CALL 147 
#define  NODE_EMIT 146 
 int /*<<< orphan*/  NODE_ERROR_RETURN ; 
 int /*<<< orphan*/  NODE_ERROR_SKIP ; 
#define  NODE_FCALL 145 
#define  NODE_FLOAT 144 
#define  NODE_GENFUNC 143 
#define  NODE_IDENT 142 
#define  NODE_IF 141 
#define  NODE_IMPORT 140 
#define  NODE_INT 139 
#define  NODE_LAMBDA 138 
#define  NODE_LET 137 
#define  NODE_NIL 136 
#define  NODE_NODES 135 
#define  NODE_NS 134 
#define  NODE_OP 133 
#define  NODE_PLAMBDA 132 
#define  NODE_RETURN 131 
#define  NODE_SKIP 130 
 int NODE_SPLAT ; 
#define  NODE_STR 129 
#define  NODE_TIME 128 
 int STRM_NG ; 
 int /*<<< orphan*/  STRM_NS_UDEF_GET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STRM_NS_UDEF_SET (int /*<<< orphan*/ *) ; 
 int STRM_OK ; 
 int /*<<< orphan*/  STRM_PTR_LAMBDA ; 
 int TRUE ; 
 int /*<<< orphan*/  ary_headers (int /*<<< orphan*/ ,int) ; 
 int exec_call (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,void**,void**) ; 
 int /*<<< orphan*/  free (void**) ; 
 struct strm_lambda* genfunc_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  node_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_to_sym (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_array_p (void*) ; 
 int strm_ary_len (void*) ; 
 void* strm_ary_new (int /*<<< orphan*/ *,int) ; 
 void** strm_ary_ptr (void*) ; 
 void* strm_ary_value (void*) ; 
 int /*<<< orphan*/  strm_bool_p (void*) ; 
 void* strm_bool_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_emit (TYPE_1__*,void*,int /*<<< orphan*/ *) ; 
 int strm_env_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* strm_float_value (int /*<<< orphan*/ ) ; 
 int strm_funcall (TYPE_1__*,void*,int,void**,void**) ; 
 void* strm_int_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_nil_p (void*) ; 
 void* strm_nil_value () ; 
 int /*<<< orphan*/ * strm_ns_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strm_ns_get (int /*<<< orphan*/ ) ; 
 void* strm_ptr_value (struct strm_lambda*) ; 
 int /*<<< orphan*/  strm_raise (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  strm_set_exc (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * strm_str_null ; 
 void* strm_str_value (int /*<<< orphan*/ ) ; 
 void* strm_time_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* strm_value_ary (void*) ; 
 int /*<<< orphan*/  strm_value_bool (void*) ; 
 int strm_var_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 int strm_var_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
exec_expr(strm_stream* strm, strm_state* state, node* np, strm_value* val)
{
  int n;

  if (np == NULL) {
    return STRM_NG;
  }

  switch (np->type) {
/*
  case NODE_ARGS:
    break;
*/
  case NODE_NS:
    {
      node_ns* ns = (node_ns*)np;
      strm_string name = node_to_sym(ns->name);
      strm_state* s = strm_ns_create(state, name);

      if (!s) {
        if (strm_ns_get(name)) {
          strm_raise(strm, "namespace already exists");
        }
        else {
          strm_raise(strm, "failed to create namespace");
        }
        return STRM_NG;
      }
      STRM_NS_UDEF_SET(s);
      if (ns->body)
        return exec_expr(strm, s, ns->body, val);
      return STRM_OK;
    }

  case NODE_IMPORT:
    {
      node_import *ns = (node_import*)np;
      strm_state* s = strm_ns_get(node_to_sym(ns->name));
      if (!s) {
        strm_raise(strm, "no such namespace");
        return STRM_NG;
      }
      n = strm_env_copy(state, s);
      if (n) {
        strm_raise(strm, "failed to import");
        return n;
      }
      return STRM_OK;
    }
    break;

  case NODE_SKIP:
    strm_set_exc(strm, NODE_ERROR_SKIP, strm_nil_value());
    return STRM_NG;
  case NODE_EMIT:
    {
      int i, n;
      node_array* v0;

      v0 = (node_array*)((node_emit*)np)->emit;
      if (!v0) {
        strm_emit(strm, strm_nil_value(), NULL);
      }
      else {
        for (i = 0; i < v0->len; i++) {
          n = exec_expr(strm, state, v0->data[i], val);
          if (n) return n;
          strm_emit(strm, *val, NULL);
        }
      }
      return STRM_OK;
    }
    break;
  case NODE_LET:
    {
      node_let *nlet = (node_let*)np;
      n = exec_expr(strm, state, nlet->rhs, val);
      if (n) {
        strm_raise(strm, "failed to assign");
        return n;
      }
      return strm_var_set(state, node_to_sym(nlet->lhs), *val);
    }
  case NODE_ARRAY:
    {
      node_array* v0 = (node_array*)np;
      strm_array arr = strm_ary_new(NULL, v0->len);
      strm_value *ptr = strm_ary_ptr(arr);
      int splat = FALSE;

      for (int i = 0; i < v0->len; i++) {
        if (v0->data[i]->type == NODE_SPLAT) {
          node_splat* s = (node_splat*)v0->data[i];
          n = exec_expr(strm, state, s->node, &ptr[i]);
          if (n) return n;
          if (!strm_array_p(ptr[i])) {
            strm_raise(strm, "splat requires array");
            return STRM_NG;
          }
          splat = TRUE;
        }
        else {
          n = exec_expr(strm, state, v0->data[i], &ptr[i]);
          if (n) return n;
        }
      }
      if (splat) {
        int len = v0->len;

        if (v0->headers) {
          strm_raise(strm, "label(s) and splat(s) in an array");
          return STRM_NG;
        }
        for (int i = 0; i < v0->len; i++) {
          if (v0->data[i]->type == NODE_SPLAT) {
            strm_array a = strm_value_ary(ptr[i]);
            len += strm_ary_len(a)-1;
          }
        }
        if (len > v0->len) {
          strm_value* nptr;

          arr = strm_ary_new(NULL, len);
          nptr = strm_ary_ptr(arr);
          for (int i = 0; i < v0->len; i++) {
            if (v0->data[i]->type == NODE_SPLAT) {
              strm_array a = strm_value_ary(ptr[i]);
              int alen = strm_ary_len(a);
              strm_value* aptr = strm_ary_ptr(a);
              for (int j=0; j<alen; j++) {
                *nptr++ = aptr[j];
              }
            }
            else {
              *nptr++ = ptr[i];
            }
          }
        }
      }
      else if (v0->headers) {
        strm_ary_headers(arr) = ary_headers(v0->headers, v0->len);
      }
      if (v0->ns) {
        strm_state* ns = strm_ns_get(node_to_sym(v0->ns));
        if (!STRM_NS_UDEF_GET(ns)) {
          strm_raise(strm, "instantiating primitive class");
          return STRM_NG;
        }
        strm_ary_ns(arr) = ns;
      }
      else {
        strm_ary_ns(arr) = strm_str_null;
      }
      *val = strm_ary_value(arr);
      return STRM_OK;
    }
  case NODE_IDENT:
    {
      node_ident* ni = (node_ident*)np;
      n = strm_var_get(state, node_to_sym(ni->name), val);
      if (n) {
        strm_raise(strm, "failed to reference variable");
      }
      return n;
    }
  case NODE_IF:
    {
      strm_value v;
      node_if* nif = (node_if*)np;
      n = exec_expr(strm, state, nif->cond, &v);
      if (n) return n;
      if (strm_bool_p(v) && strm_value_bool(v)) {
        return exec_expr(strm, state, nif->then, val);
      }
      else if (nif->opt_else != NULL) {
        return exec_expr(strm, state, nif->opt_else, val);
      }
      else {
        *val = strm_nil_value();
        return STRM_OK;
      }
    }
    break;
  case NODE_OP:
    {
      node_op* nop = (node_op*)np;
      strm_value args[2];
      int i=0;

      if (nop->lhs) {
        n = exec_expr(strm, state, nop->lhs, &args[i++]);
        if (n) return n;
      }
      if (nop->rhs) {
        n = exec_expr(strm, state, nop->rhs, &args[i++]);
        if (n) return n;
      }
      return exec_call(strm, state, node_to_sym(nop->op), i, args, val);
    }
    break;
  case NODE_LAMBDA:
  case NODE_PLAMBDA:
    {
      struct strm_lambda* lambda = malloc(sizeof(struct strm_lambda));

      if (!lambda) return STRM_NG;
      lambda->state = malloc(sizeof(strm_state));
      if (!lambda->state) return STRM_NG;
      *lambda->state = *state;
      lambda->type = STRM_PTR_LAMBDA;
      lambda->body = (node_lambda*)np;
      *val = strm_ptr_value(lambda);
      return STRM_OK;
    }
    break;
  case NODE_CALL:
    {
      /* TODO: wip code of ident */
      node_call* ncall = (node_call*)np;
      int i;
      node_nodes* v0 = (node_nodes*)ncall->args;
      strm_value *args;
      int splat = FALSE;

      for (i = 0; i < v0->len; i++) {
        if (v0->data[i]->type == NODE_SPLAT) {
          splat = TRUE;
          break;
        }
      }
      if (splat) {
        strm_value aary;
        n = exec_expr(strm, state, ncall->args, &aary);
        args = strm_ary_ptr(aary);
        i = strm_ary_len(aary);
      }
      else {
        args = malloc(sizeof(strm_value)*v0->len);
        for (i = 0; i < v0->len; i++) {
          n = exec_expr(strm, state, v0->data[i], &args[i]);
          if (n == STRM_NG) {
            free(args);
            return n;
          }
        }
      }
      n = exec_call(strm, state, node_to_sym(ncall->ident), i, args, val);
      if (!splat) free(args);
      return n;
    }
    break;
  case NODE_FCALL:
    {
      node_fcall* ncall = (node_fcall*)np;
      int i;
      strm_value func;
      node_nodes* v0 = (node_nodes*)ncall->args;
      strm_value *args;
      int splat = FALSE;

      if (exec_expr(strm, state, ncall->func, &func) == STRM_NG) {
        return STRM_NG;
      }
      for (i = 0; i < v0->len; i++) {
        if (v0->data[i]->type == NODE_SPLAT) {
          splat = TRUE;
          break;
        }
      }
      if (splat) {
        strm_value aary;
        n = exec_expr(strm, state, ncall->args, &aary);
        args = strm_ary_ptr(aary);
        i = strm_ary_len(aary);
      }
      else {
        args = malloc(sizeof(strm_value)*v0->len);
        for (i = 0; i < v0->len; i++) {
          n = exec_expr(strm, state, v0->data[i], &args[i]);
          if (n == STRM_NG) {
            free(args);
            return n;
          }
        }
      }
      n = strm_funcall(strm, func, i, args, val);
      if (!splat) free(args);
      return n;
    }
    break;
  case NODE_GENFUNC:
    {
      node_genfunc* ngf = (node_genfunc*)np;
      struct strm_genfunc *gf;

      gf = genfunc_new(state, node_to_str(ngf->id));
      if (!gf) return STRM_NG;
      *val = strm_ptr_value(gf);
      return STRM_OK;
    }
    break;
  case NODE_RETURN:
    {
      node_return* nreturn = (node_return*)np;
      node_nodes* args = (node_nodes*)nreturn->rv;
      strm_value arg;

      if (!args) {
        arg = strm_nil_value();
      }
      else {
        switch (args->len) {
        case 0:
          arg = strm_nil_value();
          break;
        case 1:
          n = exec_expr(strm, state, args->data[0], &arg);
          if (n) return n;
          break;
        default:
          {
            strm_array ary = strm_ary_new(NULL, args->len);
            strm_int i;

            for (i=0; i<args->len; i++) {
              n = exec_expr(strm, state, args->data[i], (strm_value*)&strm_ary_ptr(ary)[i]);
              if (n) return n;
            }
            arg = strm_ary_value(ary);
          }
          break;
        }
      }
      strm_set_exc(strm, NODE_ERROR_RETURN, arg);
      return STRM_NG;
    }
    break;
  case NODE_NODES:
    {
      int i;
      node_nodes* v = (node_nodes*)np;
      for (i = 0; i < v->len; i++) {
        n = exec_expr(strm, state, v->data[i], val);
        if (n) {
          if (strm) {
            node_error* exc = strm->exc;
            if (exc != NULL) {
              node* n = v->data[i];

              exc->fname = n->fname;
              exc->lineno = n->lineno;
            }
          }
          return n;
        }
      }
    }
    return STRM_OK;
  case NODE_INT:
    *val = strm_int_value(((node_int*)np)->value);
    return STRM_OK;
  case NODE_FLOAT:
    *val = strm_float_value(((node_float*)np)->value);
    return STRM_OK;
  case NODE_TIME:
    {
      node_time* nt = (node_time*)np;
      *val = strm_time_new(nt->sec, nt->usec, nt->utc_offset);
      if (strm_nil_p(*val)) return STRM_NG;
    }
    return STRM_OK;
  case NODE_BOOL:
    *val = strm_bool_value(((node_bool*)np)->value);
    return STRM_OK;
  case NODE_NIL:
    *val = strm_nil_value();
    return STRM_OK;
  case NODE_STR:
    *val = strm_str_value(node_to_str(((node_str*)np)->value));
    return STRM_OK;
  default:
    strm_raise(strm, "unknown node");
    break;
  }
  return STRM_NG;
}