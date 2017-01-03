
/*
 * Copyright (C) Igor Sysoev
 */


#ifndef _NGX_ALLOC_H_INCLUDED_
#define _NGX_ALLOC_H_INCLUDED_


#include "../core/ngx_config.h"
#include "../core/ngx_core.h"


void *ngx_alloc(size_t size, ngx_log_t *log);
void *ngx_calloc(size_t size, ngx_log_t *log);

#define ngx_free          free
#define ngx_memalign(alignment, size, log)  ngx_alloc(size, log)

extern ngx_uint_t  ngx_pagesize;
extern ngx_uint_t  ngx_pagesize_shift;
extern ngx_uint_t  ngx_cacheline_size;


#endif /* _NGX_ALLOC_H_INCLUDED_ */