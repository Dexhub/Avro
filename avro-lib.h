
#include <stdio.h>
#include <avro.h>
#include <avro/generic.h>
#include "avro_private.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "schema.h"

#ifdef DEFLATE_CODEC
#define AVRO_CODEC  "deflate"
#else
#define AVRO_CODEC  "null"
#endif

#define bool int
#define true 1
#define false 0


// Internal functions ----
void init_schema(const char *schema_file);
    


// External Functions for use --    
int setup_record_structure(const char  *schema_file);
int set_null_value(); // TODO Ujjwal - datavalue
int set_boolean(bool data_value);
int set_int_value(uint32_t data_value);
int set_long_value(uint64_t data_value);
int set_float_value(float data_value);
int set_double_value(double data_value);
int set_byte_value(void *data_value, int size); //TODO Ujjwal - datavalue
int set_string_value(const char* data_value);
int reset_record_structure(void);
int cleanup_record_structure(void);
//----
