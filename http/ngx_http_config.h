
/*
 * Copyright (C) Igor Sysoev
 */


#ifndef _NGX_HTTP_CONFIG_H_INCLUDED_
#define _NGX_HTTP_CONFIG_H_INCLUDED_


#include "../core/ngx_config.h"
#include "../core/ngx_core.h"
#include "ngx_http.h"

// 使用三个数组的原因是，nginx把http配置设为http/server/location三个层次
typedef struct {
    void        **main_conf;//数组，数组成员是void*，指向http模块的mainconf
    void        **srv_conf; //server域的存储数组
    void        **loc_conf;// localtion域的存储数组
} ngx_http_conf_ctx_t;

//HTTP框架在读取,重载配置文件时定义了由ngx_http_module_t接口描述的8个阶段
//这8个阶段的调用顺序应该是：
/*
create_main_conf
create_srv_conf
create_loc_conf
preconfiguration
init_main_conf
merge_srv_conf
merge_loc_conf
postconfiguration
*/
typedef struct {
    ngx_int_t   (*preconfiguration)(ngx_conf_t *cf);  //在创建和读取该模块的配置信息之前被调用。
    ngx_int_t   (*postconfiguration)(ngx_conf_t *cf); //在创建和读取该模块的配置信息之后被调用。

    void       *(*create_main_conf)(ngx_conf_t *cf);  //	调用该函数创建本模块位于http block的配置信息存储结构。该函数成功的时候，返回创建的配置对象。失败的话，返回NULL。
    char       *(*init_main_conf)(ngx_conf_t *cf, void *conf); //调用该函数初始化本模块位于http block的配置信息存储结构。该函数成功的时候，返回NGX_CONF_OK。失败的话，返回NGX_CONF_ERROR或错误字符串。

    void       *(*create_srv_conf)(ngx_conf_t *cf); //调用该函数创建本模块位于http server block的配置信息存储结构，每个server block会创建一个。该函数成功的时候，返回创建的配置对象。失败的话，返回NULL。
    char       *(*merge_srv_conf)(ngx_conf_t *cf, void *prev, void *conf); //因为有些配置指令既可以出现在http block，也可以出现在http server block中。那么遇到这种情况，每个server都会有自己存储结构来存储该server的配置，但是在这种情况下http block中的配置与server block中的配置信息发生冲突的时候，就需要调用此函数进行合并，该函数并非必须提供，当预计到绝对不会发生需要合并的情况的时候，就无需提供。当然为了安全起见还是建议提供。该函数执行成功的时候，返回NGX_CONF_OK。失败的话，返回NGX_CONF_ERROR或错误字符串。

    void       *(*create_loc_conf)(ngx_conf_t *cf); //	调用该函数创建本模块位于location block的配置信息存储结构。每个在配置中指明的location创建一个。该函数执行成功，返回创建的配置对象。失败的话，返回NULL。
    char       *(*merge_loc_conf)(ngx_conf_t *cf, void *prev, void *conf); //与merge_srv_conf类似，这个也是进行配置值合并的地方。该函数成功的时候，返回NGX_CONF_OK。失败的话，返回NGX_CONF_ERROR或错误字符串。
} ngx_http_module_t;


#define NGX_HTTP_MODULE           0x50545448   /* "HTTP" */

#define NGX_HTTP_MAIN_CONF        0x02000000 //可以直接出现在http配置指令里。
#define NGX_HTTP_SRV_CONF         0x04000000 //可以出现在http里面的server配置指令里。
#define NGX_HTTP_LOC_CONF         0x08000000 //可以出现在http server块里面的location配置指令里
#define NGX_HTTP_UPS_CONF         0x10000000 //可以出现在http里面的upstream配置指令里。
#define NGX_HTTP_SIF_CONF         0x20000000 //可以出现在http里面的server配置指令里的if语句所在的block中。
#define NGX_HTTP_LIF_CONF         0x40000000 //可以出现在http server块里面的location配置指令里的if语句所在的block中。
#define NGX_HTTP_LMT_CONF         0x80000000 //可以出现在http里面的limit_except指令的block中。


#define NGX_HTTP_MAIN_CONF_OFFSET  offsetof(ngx_http_conf_ctx_t, main_conf)
#define NGX_HTTP_SRV_CONF_OFFSET   offsetof(ngx_http_conf_ctx_t, srv_conf)
#define NGX_HTTP_LOC_CONF_OFFSET   offsetof(ngx_http_conf_ctx_t, loc_conf)


#define ngx_http_get_module_main_conf(r, module)                             \
    (r)->main_conf[module.ctx_index]
#define ngx_http_get_module_srv_conf(r, module)  (r)->srv_conf[module.ctx_index]
#define ngx_http_get_module_loc_conf(r, module)  (r)->loc_conf[module.ctx_index]


#define ngx_http_conf_get_module_main_conf(cf, module)                        \
    ((ngx_http_conf_ctx_t *) cf->ctx)->main_conf[module.ctx_index]
#define ngx_http_conf_get_module_srv_conf(cf, module)                         \
    ((ngx_http_conf_ctx_t *) cf->ctx)->srv_conf[module.ctx_index]
#define ngx_http_conf_get_module_loc_conf(cf, module)                         \
    ((ngx_http_conf_ctx_t *) cf->ctx)->loc_conf[module.ctx_index]

#define ngx_http_cycle_get_module_main_conf(cycle, module)                    \
    (cycle->conf_ctx[ngx_http_module.index] ?                                 \
        ((ngx_http_conf_ctx_t *) cycle->conf_ctx[ngx_http_module.index])      \
            ->main_conf[module.ctx_index]:                                    \
        NULL)


#endif /* _NGX_HTTP_CONFIG_H_INCLUDED_ */
