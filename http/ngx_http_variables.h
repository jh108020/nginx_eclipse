
/*
 * Copyright (C) Igor Sysoev
 */


#ifndef _NGX_HTTP_VARIABLES_H_INCLUDED_
#define _NGX_HTTP_VARIABLES_H_INCLUDED_


#include "../core/ngx_config.h"
#include "../core/ngx_core.h"
#include "ngx_http.h"


typedef ngx_variable_value_t  ngx_http_variable_value_t;

#define ngx_http_variable(v)     { sizeof(v) - 1, 1, 0, 0, 0, (u_char *) v }

typedef struct ngx_http_variable_s  ngx_http_variable_t;

typedef void (*ngx_http_set_variable_pt) (ngx_http_request_t *r,
    ngx_http_variable_value_t *v, uintptr_t data);
typedef ngx_int_t (*ngx_http_get_variable_pt) (ngx_http_request_t *r,
    ngx_http_variable_value_t *v, uintptr_t data);


#define NGX_HTTP_VAR_CHANGEABLE   1
#define NGX_HTTP_VAR_NOCACHEABLE  2
#define NGX_HTTP_VAR_INDEXED      4
#define NGX_HTTP_VAR_NOHASH       8

//参考资料：
//http://blog.csdn.net/dingyujie/article/details/7515904
struct ngx_http_variable_s {
    ngx_str_t                     name;         /* must be first to build the hash */ //变量的字符串值
    ngx_http_set_variable_pt      set_handler;  //使用变量中的值设置request的某个成员的值
    ngx_http_get_variable_pt      get_handler;  //根据request中成员(如uri，args等)的值来设置，r->variables中对应变量的内容
    uintptr_t                     data;         //在set和get操作中使用，一般是r中某个成员在request结构中的offset
    ngx_uint_t                    flags;        //一些在set和get中控制特定动作的标志
    ngx_uint_t                    index;        //某个变量在r->variabels或者cmcf->variabels中数组中的下标
};


ngx_http_variable_t *ngx_http_add_variable(ngx_conf_t *cf, ngx_str_t *name,
    ngx_uint_t flags);
ngx_int_t ngx_http_get_variable_index(ngx_conf_t *cf, ngx_str_t *name);
ngx_http_variable_value_t *ngx_http_get_indexed_variable(ngx_http_request_t *r,
    ngx_uint_t index);
ngx_http_variable_value_t *ngx_http_get_flushed_variable(ngx_http_request_t *r,
    ngx_uint_t index);

ngx_http_variable_value_t *ngx_http_get_variable(ngx_http_request_t *r,
    ngx_str_t *name, ngx_uint_t key);

ngx_int_t ngx_http_variable_unknown_header(ngx_http_variable_value_t *v,
    ngx_str_t *var, ngx_list_part_t *part, size_t prefix);


#define ngx_http_clear_variable(r, index) r->variables0[index].text.data = NULL;


#if (NGX_PCRE)

typedef struct {
    ngx_uint_t                    capture;
    ngx_int_t                     index;
} ngx_http_regex_variable_t;


typedef struct {
    ngx_regex_t                  *regex;
    ngx_uint_t                    ncaptures;
    ngx_http_regex_variable_t    *variables;
    ngx_uint_t                    nvariables;
    ngx_str_t                     name;
} ngx_http_regex_t;


typedef struct {
    ngx_http_regex_t             *regex;
    void                         *value;
} ngx_http_map_regex_t;


ngx_http_regex_t *ngx_http_regex_compile(ngx_conf_t *cf,
    ngx_regex_compile_t *rc);
ngx_int_t ngx_http_regex_exec(ngx_http_request_t *r, ngx_http_regex_t *re,
    ngx_str_t *s);

#endif


typedef struct {
    ngx_hash_combined_t           hash;
#if (NGX_PCRE)
    ngx_http_map_regex_t         *regex;
    ngx_uint_t                    nregex;
#endif
} ngx_http_map_t;


void *ngx_http_map_find(ngx_http_request_t *r, ngx_http_map_t *map,
    ngx_str_t *match);


ngx_int_t ngx_http_variables_add_core_vars(ngx_conf_t *cf);
ngx_int_t ngx_http_variables_init_vars(ngx_conf_t *cf);


extern ngx_http_variable_value_t  ngx_http_variable_null_value;
extern ngx_http_variable_value_t  ngx_http_variable_true_value;


#endif /* _NGX_HTTP_VARIABLES_H_INCLUDED_ */