struct json_obj_head {
    //linked list of json_node structure
    struct json_node *head;
    struct json_node *tail;
};

//we must implement array head to enable accessing to the wanted node by indexing... 
struct json_arr_head {
    //linked list
    int len;
    struct json_arr_node *head;
    struct json_arr_node *tail;
};

struct json_arr_node {
    int                     index;
    unsigned char           val_type;
    //there are what kinds of data type? -> number, string, null, obj? array?...
    int                     *val_num_int;
    float                   *val_num_float;
    double                  *val_num_double;
    unsigned char           val_bool;
    unsigned char           val_null;
    struct json_str_head    *val_str;
    struct json_obj_head    *val_obj;
    struct json_arr_head    *val_arr;
    struct json_arr_node    *next;
    struct json_arr_node    *prev;
};

struct json_str_head {
    int len;
    char *str;
};

struct json_node {
    unsigned char           *key;
    unsigned char           val_type;       //srting, number, object, boolean, null
    int                     *val_num_int;
    float                   *val_num_float;
    double                  *val_num_double;
    unsigned char           val_bool;
    unsigned char           val_null;
    struct json_str_head    *val_str;
    struct json_obj_head    *val_obj;
    struct json_arr_head    *val_arr;
    struct json_node        *next, *prev;
};

//get value of json by passing js command string... (parse js command internally)
void* get_value(struct json_obj_head, char js_command[]);