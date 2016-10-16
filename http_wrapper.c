/**
 *
 * created by vijayant saini @vijayant123
 *
 * mongoose wrapper for http requests
 *
 * todo make this wrapper MT-safe
*/

#include <stddef.h>

#define HEADER_HTTP_WRAPPER_C


// header for this wrapper


typedef struct http_response {
    int response_code;
    const char *response_message;
    size_t response_length;
} res;

typedef struct http_request {
    const char *url;
    const char *extra_headers;
    const char *post_data;
} req;


// global state variables

res *response_ptr;
void (*response_callback)();

// global mg_ structures

struct mg_mgr request_mgr;


#ifndef HEADER_LIBS_INCLUDED

#include "../../libs/mongoose.c"

#define HEADER_LIBS_INCLUDED
#endif


void connect(
        struct mg_mgr *mgr,
        mg_event_handler_t ev_callback,
        const char *url,
        const char *extra_headers,
        const char *post_data
) {
    mg_mgr_init(mgr, NULL);
    mg_connect_http(mgr, ev_callback, url, extra_headers, post_data);
}

void handle_return() {
    response_callback();
}

static void ev_callback(
        struct mg_connection *conn,
        int ev,
        void *p
) {
    if (ev == MG_EV_HTTP_REPLY) {
        struct http_message *hm = (struct http_message *) p;

        response_ptr->response_code = hm->resp_code;
        response_ptr->response_message = hm->resp_status_msg.p;
        response_ptr->response_length = hm->resp_status_msg.len;

        handle_return();
    }
}

void get(
        req *request,
        void (*callback(void)),
        res *response
) {
    response_callback = callback;
    response_ptr =  response;

    connect(&request_mgr, ev_callback, request->url, request->extra_headers, request->post_data);
}
