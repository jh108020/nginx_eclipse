#include "../core/ngx_config.h"
#include "../core/ngx_core.h"
#include "../http/ngx_http.h"

static ngx_int_t ngx_http_mytest_handler(ngx_http_request_t *r);
static char* ngx_http_mytest(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

//配置项
static ngx_command_t ngx_http_mytest_commands[] = {
    {
        ngx_string("mytest"),//指令名称，在配置文件中使用
        NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_HTTP_LMT_CONF|NGX_CONF_NOARGS,
        ngx_http_mytest, //回调函数
        NGX_HTTP_LOC_CONF_OFFSET, //位置
        0, //指令的值保存的位置
        NULL
    },
    ngx_null_command
};
//模块上下文
static ngx_http_module_t ngx_http_mytest_module_ctx = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};
//新的模块
ngx_module_t ngx_http_mytest_module = {
    NGX_MODULE_V1,
    &ngx_http_mytest_module_ctx,
    ngx_http_mytest_commands,
    NGX_HTTP_MODULE,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NGX_MODULE_V1_PADDING
};
//配置回调函数
static char* ngx_http_mytest(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t *clcf;
    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_mytest_handler;
    return NGX_CONF_OK;
}

//回调函数
static ngx_int_t ngx_http_mytest_handler(ngx_http_request_t *r)
{
    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http mytest handler start");
    if(!(r->method & (NGX_HTTP_GET | NGX_HTTP_HEAD)))
        return NGX_HTTP_NOT_ALLOWED;

    ngx_int_t rc = ngx_http_discard_request_body(r);
    if(rc != NGX_OK)
        return rc;

    ngx_str_t type = ngx_string("text/plain");
    ngx_str_t response = ngx_string("Hello, this is nginx world!");
    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = response.len;
    r->headers_out.content_type = type;

    rc = ngx_http_send_header(r);
    if(rc == NGX_ERROR || rc > NGX_OK || r->header_only)
        return rc;

    ngx_buf_t *b;
    b = ngx_create_temp_buf(r->pool, response.len);
    if(b == NULL)
        return NGX_HTTP_INTERNAL_SERVER_ERROR;

    ngx_memcpy(b->pos, response.data, response.len);
    b->last = b->pos + response.len;
    b->last_buf = 1;

    ngx_chain_t out; //构造输出链表
    out.buf = b;
    out.next = NULL;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http mytest handler end");
    return ngx_http_output_filter(r, &out);
}
