
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_CORE_H_INCLUDED_
#define _NGX_CORE_H_INCLUDED_


typedef struct ngx_module_s      ngx_module_t;
typedef struct ngx_conf_s        ngx_conf_t;
typedef struct ngx_cycle_s       ngx_cycle_t;
typedef struct ngx_pool_s        ngx_pool_t;
typedef struct ngx_chain_s       ngx_chain_t;
typedef struct ngx_log_s         ngx_log_t;
typedef struct ngx_array_s       ngx_array_t;
typedef struct ngx_open_file_s   ngx_open_file_t;
typedef struct ngx_command_s     ngx_command_t;
typedef struct ngx_file_s        ngx_file_t;
typedef struct ngx_event_s       ngx_event_t;
typedef struct ngx_event_aio_s   ngx_event_aio_t;
typedef struct ngx_connection_s  ngx_connection_t;

typedef void (*ngx_event_handler_pt)(ngx_event_t *ev);
typedef void (*ngx_connection_handler_pt)(ngx_connection_t *c);


#define  NGX_OK          0	//表示成功，nginx会继续执行该请求的后续动作
#define  NGX_ERROR      -1	//表示错误，此时nginx会中止请求
#define  NGX_AGAIN      -2
#define  NGX_BUSY       -3
#define  NGX_DONE       -4	//表示到此为止，NGINX的HTTP框架将暂停不再执行这个请求的后续部分
#define  NGX_DECLINED   -5	//继续在NGX_HTTP_CONTENT_PHASE阶段寻找下一个对于该请求感兴趣的HTTP模块来处理这个请求
#define  NGX_ABORT      -6


#include "../os_win32/ngx_errno.h"
#include "../os_win32/ngx_atomic.h"
#include "../os_win32/ngx_thread.h"
#include "ngx_rbtree.h"
#include "../os_win32/ngx_time.h"
#include "../os_win32/ngx_socket.h"
#include "ngx_string.h"
#include "../os_win32/ngx_files.h"
#include "../os_win32/ngx_shmem.h"
#include "../os_win32/ngx_process.h"
#include "../os_win32/ngx_user.h"
#include "ngx_parse.h"
#include "ngx_log.h"
#include "../os_win32/ngx_alloc.h"
#include "ngx_palloc.h"
#include "ngx_buf.h"
#include "ngx_queue.h"
#include "ngx_array.h"
#include "ngx_list.h"
#include "ngx_hash.h"
#include "ngx_file.h"
#include "ngx_crc.h"
#include "ngx_crc32.h"
#include "ngx_murmurhash.h"
#if (NGX_PCRE)
	#include "ngx_regex.h"
#endif
#include "ngx_radix_tree.h"
#include "ngx_times.h"
#include "ngx_shmtx.h"
#include "ngx_slab.h"
#include "ngx_inet.h"
#include "ngx_cycle.h"
//#if (NGX_OPENSSL)
//	#include "../event/ngx_event_openssl.h"
//#endif
#include "../os_win32/ngx_process_cycle.h"
#include "ngx_conf_file.h"
#include "ngx_resolver.h"
#include "ngx_open_file_cache.h"
#include "../os_win32/ngx_os.h"
#include "ngx_connection.h"


#define LF     (u_char) 10
#define CR     (u_char) 13
#define CRLF   "\x0d\x0a"


#define ngx_abs(value)       (((value) >= 0) ? (value) : - (value))
#define ngx_max(val1, val2)  ((val1 < val2) ? (val2) : (val1))
#define ngx_min(val1, val2)  ((val1 > val2) ? (val2) : (val1))

void ngx_cpuinfo(void);


#endif /* _NGX_CORE_H_INCLUDED_ */
