#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int (* xToken ) (void*,int,char const*,int,int,int) ;int /*<<< orphan*/  aBuf; void* pCtx; } ;
struct TYPE_4__ {int (* xTokenize ) (int /*<<< orphan*/ ,void*,int,char const*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  pTokenizer; TYPE_1__ tokenizer; int /*<<< orphan*/  aBuf; } ;
typedef  TYPE_2__ PorterTokenizer ;
typedef  TYPE_3__ PorterContext ;
typedef  int /*<<< orphan*/  Fts5Tokenizer ;

/* Variables and functions */
 int /*<<< orphan*/  fts5PorterCb ; 
 int stub1 (int /*<<< orphan*/ ,void*,int,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts5PorterTokenize(
  Fts5Tokenizer *pTokenizer,
  void *pCtx,
  int flags,
  const char *pText, int nText,
  int (*xToken)(void*, int, const char*, int nToken, int iStart, int iEnd)
){
  PorterTokenizer *p = (PorterTokenizer*)pTokenizer;
  PorterContext sCtx;
  sCtx.xToken = xToken;
  sCtx.pCtx = pCtx;
  sCtx.aBuf = p->aBuf;
  return p->tokenizer.xTokenize(
      p->pTokenizer, (void*)&sCtx, flags, pText, nText, fts5PorterCb
  );
}