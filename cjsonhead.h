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

//return type int is for notification of operation success or fail(error).

//get value of json by passing js command string... (parse js command internally)
void* cjson_get(struct json_obj_head *json, char *js_command);
//change value of target. value is passed by void pointer
int cjson_change(struct json_obj_head *json, char *target, void *value);
//open json file, parse and convert json to C data structure.
struct json_obj_head* cjson_open(char *path);
//convert C sturct to json file.
int cjson_cvrt_to_json(struct json_obj_head *json, char *filename);
//push operation
int cjson_push(struct json_obj_head *json, void *value);
//pop operation. this operation just remove value. it does not return value.
int cjson_pop(struct json_obj_head *json);
