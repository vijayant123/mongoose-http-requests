// mongoose wrapper for http requests

#include <stddef.h>

#define HEADER_HTTP_WRAPPER_C


// header for this wrapper


typedef struct http_output {
    int response_code;
    const char *response_message;
    size_t response_length;
} response;


// global state variables

response *response_ptr;


#ifndef HEADER_LIBS_INCLUDED

#include "../libs/mongoose.c"

#define HEADER_LIBS_INCLUDED
#endif


void connect(
        char * output_buffer,
        void ** success_callback,
        struct mg_mgr *mgr,
        mg_event_handler_t ev_callback
        const char *url,
        const char *extra_headers,
        const char *post_data
) {
    mg_mgr_init(mgr, NULL);
    mg_connect_http(mgr, ev_callback, url, extra_headers, post_data);
}

void handle_return(){
    if()
}

static void ev_callback(
        struct mg_connection *conn,
        int ev,
        void *p
){
    if(ev == MG_EV_HTTP_REPLY){
        struct http_message *hm = (struct http_message *) p;

        response_ptr->response_code = hm->resp_code;
        response_ptr->response_message = hm->resp_status_msg.p;
        response_ptr->response_length = hm->resp_status_msg.len;

        handle_return();
    }
}

