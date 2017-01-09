
/*
 * Copyright (C) Igor Sysoev
 */


#ifndef _NGX_SHA1_H_INCLUDED_
#define _NGX_SHA1_H_INCLUDED_


#include "ngx_config.h"
#include "ngx_core.h"

#define SHA_LONG unsigned int
#define SHA_LBLOCK	16
#define SHA_CBLOCK	(SHA_LBLOCK*4)	/* SHA treats input data as a
					 * contiguous array of 32 bit
					 * wide big-endian values. */
#define SHA_LAST_BLOCK  (SHA_CBLOCK-8)
#define SHA_DIGEST_LENGTH 20

typedef struct SHAstate_st
	{
	SHA_LONG h0,h1,h2,h3,h4;
	SHA_LONG Nl,Nh;
	SHA_LONG data[SHA_LBLOCK];
	unsigned int num;
	} SHA_CTX;


typedef SHA_CTX  ngx_sha1_t;


#define ngx_sha1_init    SHA1_Init	//初始化
#define ngx_sha1_update  SHA1_Update//输入数据
#define ngx_sha1_final   SHA1_Final //输出SHA1值


#endif /* _NGX_SHA1_H_INCLUDED_ */
