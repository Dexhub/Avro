#include "avro-lib.h"


avro_schema_t avro_schema;
avro_file_writer_t writer = NULL;
avro_value_t value, field;
avro_value_iface_t *iface;

int32_t field_counter = 0;



/* Parse schema into a schema data structure */
void init_schema(const char *schema_file)
{
    //Read the Schema file into buffer
    FILE * pFile;
    long lSize;
    char * buffer;
    size_t result;
  
    pFile = fopen ( schema_file, "rb" ); 
    if (pFile==NULL) 
    {
        fputs ("File error",stderr); 
        exit (1);
    }
  
    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);
  
    // allocate memory to contain the whole file:
    buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) 
    {
        fputs ("Memory error",stderr); 
        exit (2);
    }
  
    // copy the file into the buffer:
    result = fread (buffer,1,lSize,pFile);
    if (result != lSize) 
    {
        fputs ("Reading error",stderr); 
        exit (3);
    }
  
    /* the whole file is now loaded in the memory buffer. */
  
    //printf("Schema: %s\n", buffer);

    if(avro_schema_from_json_length(buffer, result, &avro_schema))
    {
        fprintf(stderr, "Unable to parse the schema\n");
	exit(EXIT_FAILURE);
    }
    
    // terminate
    fclose (pFile);
   // free (buffer);
}

int setup_record_structure(const char  *schema_file) //TODO Error Checking
{
    FILE *fp = stdout; 
    
    init_schema(schema_file);
    avro_file_writer_create_with_codec_fp(fp, "", 0, avro_schema, &writer, AVRO_CODEC, 0); 
  
    iface = avro_generic_class_from_schema(avro_schema);
    avro_generic_value_new(iface, &value);
    return 0;
}

int reset_record_structure(void)
{
    avro_file_writer_append_value(writer, &value); 
    field_counter = 0 ;
}


int cleanup_record_structure(void)
{
    avro_file_writer_close(writer);
    avro_value_decref(&value);
    avro_value_iface_decref(iface);
    avro_schema_decref(avro_schema);
}

int set_null_value() // TODO Test
{
    avro_value_get_by_index(&value, field_counter, &field, NULL);
    int rval = avro_value_set_null(&field);
    if (rval)
    {
        printf("Error: Unable to set string value correctly.");
        return 1;
    }
    else
    {
        field_counter++;
    }
    return 0;
}

int set_boolean_value(bool data_value)
{
    avro_value_get_by_index(&value, field_counter, &field, NULL);
    int rval = avro_value_set_boolean(&field, data_value);
    if (rval)
    {
        printf("Error: Unable to set boolean value correctly.");
        return 1;
    }
    else
    {
        field_counter++;
    }
    return 0;
}

int set_int_value(uint32_t data_value)
{
    avro_value_get_by_index(&value, field_counter, &field, NULL);
    int rval = avro_value_set_int(&field, data_value);
    if (rval)
    {
        printf("Error: Unable to set integer value correctly.");
        return 1;
    }
    else
    {
        field_counter++;
    }
    return 0;
}

int set_long_value(uint64_t data_value)
{
    avro_value_get_by_index(&value, field_counter, &field, NULL);
    int rval = avro_value_set_long(&field, data_value);
    if (rval)
    {
        printf("Error: Unable to set long value correctly.");
        return 1;
    }
    else
    {
        field_counter++;
    }
    return 0;
}

int set_float_value(float data_value)
{
    avro_value_get_by_index(&value, field_counter, &field, NULL);
    int rval = avro_value_set_float(&field, data_value);
    if (rval)
    {
        printf("Error: Unable to set float value correctly.");
        return 1;
    }
    else
    {
        field_counter++;
    }
    return 0;
}

int set_double_value(double data_value)
{
    avro_value_get_by_index(&value, field_counter, &field, NULL);
    int rval = avro_value_set_double(&field, data_value);
    if (rval)
    {
        printf("Error: Unable to set double value correctly.");
        return 1;
    }
    else
    {
        field_counter++;
    }
    return 0;
}
int set_byte_value(void *data_value, int size) //TODO Test
{
    avro_value_get_by_index(&value, field_counter, &field, NULL);
    int rval = avro_value_set_bytes(&field, data_value, size);
    if (rval)
    {
        printf("Error: Unable to set byte value correctly.");
        return 1;
    }
    else
    {
        field_counter++;
    }
    return 0;
}
int set_string_value(const char* data_value)
{
    avro_value_get_by_index(&value, field_counter, &field, NULL);
    int rval = avro_value_set_string(&field, data_value);
    if (rval)
    {
        printf("Error: Unable to set string value correctly.");
        return 1;
    }
    else
    {
        field_counter++;
    }
    return 0;
}
