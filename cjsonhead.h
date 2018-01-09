struct json_head {
    //linked list of json_node structure
    int len;
    struct json_node *head;
    struct json_node *tail;
};

struct json_str_head {
    int len;
    char *str;
};

struct json_node {
    char                    *key;
    int                     index;          //use only in array
    unsigned char           val_type;       //srting, number, object, boolean, null
    int                     val_num_int;
    double                  val_num_double;
    unsigned char           val_bool;
    struct json_str_head    *val_str;
    struct json_head        *val_obj;
    struct json_head        *val_arr;
    struct json_node        *next, *prev;
};

//return type int is for notification of operation success or fail(error).

//minor functions
//check validity of json file.
int cjson_invalid(char *json, int size);
struct json_head* __parse(char *json, int size);
//parsing functions
void cjson_make_obj(char *json, struct json_head *cjson, int *index, int size);
void cjson_make_json_node(char *json, struct json_head *cjson, int *index, int node_type);
void cjson_check_val_type(char *json, int *index, unsigned char *type);
void cjson_make_numval(char *json, struct json_node *key, int *index);
void cjson_make_strval(char *json, struct json_node *key, int *index);
void cjson_make_nulval(char *json, struct json_node *key, int *index);
void cjson_make_arrval(char *json, struct json_node *key, int *index, int size);
void cjson_make_boolval(char *json, struct json_node *key, int *index);

//get value of json by passing key.
void* cjson_get(struct json_head *json, char *key);
//change value of target. value is passed by void pointer
int cjson_change(struct json_head *json, char *target, void *value);
//open json file, parse and convert json to C data structure.
struct json_head* cjson_parse(char *path);
//convert C sturct to json file.
int cjson_stringfy(struct json_head *json, char *filename);
//push operation
int cjson_push(struct json_head *json, void *value);
//pop operation. this operation just remove value. it does not return value.
int cjson_rm(struct json_head *json, char *key);
