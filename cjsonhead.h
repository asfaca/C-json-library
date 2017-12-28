struct json_obj_head {
    //linked list of json_node structure
    struct json_node *head;
    struct json_node *tail;
};

struct json_arr_head {
    //linked list
    struct json_arr_node *head;
    struct json_arr_node *tail;
};

struct json_node {
    unsigned char           val_type;       //srting, number, object, boolean, null
    unsigned char           *key;
    unsigned char           *val_string;
    int                     *val_num;
    unsigned char           val_bool;
    unsigned char           val_null;
    struct json_obj_head    *val_obj;
    struct json_arr_head    *val_arr;
    struct json_node    *next, *prev;
};