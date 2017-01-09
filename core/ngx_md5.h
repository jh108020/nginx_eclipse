
/*
 * Copyright (C) Igor Sysoev
 */


#ifndef _NGX_MD5_H_INCLUDED_
#define _NGX_MD5_H_INCLUDED_


#include "ngx_config.h"
#include "ngx_core.h"


#if (NGX_HAVE_MD5)

#include "md5.h"

#define MD5_LONG unsigned int

#define MD5_CBLOCK	64
#define MD5_LBLOCK	(MD5_CBLOCK/4)
#define MD5_DIGEST_LENGTH 16


typedef MD5_CTX  ngx_md5_t;


#if (NGX_OPENSSL_MD5)

#define ngx_md5_init    MD5_Init
#define ngx_md5_update  MD5_Update
#define ngx_md5_final   MD5_Final

#else

#define ngx_md5_init    MD5Init
#define ngx_md5_update  MD5Update
#define ngx_md5_final   MD5Final

#endif


#else /* !NGX_HAVE_MD5 */


typedef struct {
    uint64_t  bytes;
    uint32_t  a, b, c, d;
    u_char    buffer[64];
} ngx_md5_t;


void ngx_md5_init(ngx_md5_t *ctx);										//初始化ngx_md5_t变量
void ngx_md5_update(ngx_md5_t *ctx, const void *data, size_t size);		//输入数据"data",和长度"size"
void ngx_md5_final(u_char result[16], ngx_md5_t *ctx);					//输出MD5值


#endif

#endif /* _NGX_MD5_H_INCLUDED_ */
