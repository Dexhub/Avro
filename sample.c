#include <stdio.h>
#include <avro.h>
#include <avro/generic.h>
#include "avro_private.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef DEFLATE_CODEC
#define AVRO_CODEC  "deflate"
#else
#define AVRO_CODEC  "null"
#endif
/*
    Data Type
      0         AVRO_STRING,
      1         AVRO_BYTES,
      2         AVRO_INT32,
      3         AVRO_INT64,
      4         AVRO_FLOAT,
      5         AVRO_DOUBLE,
      6         AVRO_BOOLEAN,
      7         AVRO_NULL,
      8         AVRO_RECORD,
      9         AVRO_ENUM,
     10         AVRO_FIXED,
     11         AVRO_MAP,
     12         AVRO_ARRAY,
     13         AVRO_UNION,
     14         AVRO_LINK
     15 };
*/


avro_schema_t person_schema;
int64_t id = 0;

const char  DATA_SCHEMA[] =
"{\"type\":\"record\",\
  \"name\":\"Person\",\
  \"fields\":[\
  {\"name\": \"ID\", \"type\": \"long\"},\
  {\"name\": \"First\", \"type\": \"string\"},\
  {\"name\": \"Last\", \"type\": \"string\"},\
  {\"name\": \"Phone\", \"type\": \"string\"},\
  {\"name\": \"Age\", \"type\": \"int\"}]}";

/* Parse schema into a schema data structure */
void init_schema(void)
{
    //Read the Schema file into buffer
    FILE * pFile;
    long lSize;
    char * buffer;
    size_t result;
  
    pFile = fopen ( "myfile.bin" , "rb" ); //TODO Specify the file name from user
    if (pFile==NULL) {fputs ("File error",stderr); exit (1);}
  
    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);
  
    // allocate memory to contain the whole file:
    buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}
  
    // copy the file into the buffer:
    result = fread (buffer,1,lSize,pFile);
    if (result != lSize) {fputs ("Reading error",stderr); exit (3);}
  
    /* the whole file is now loaded in the memory buffer. */
  
    // terminate
    fclose (pFile);
    free (buffer);




	if (avro_schema_from_json_literal(DATA_SCHEMA, &person_schema)) {
		fprintf(stderr, "Unable to parse person schema\n");
		exit(EXIT_FAILURE);
	}
}


void write_avro(const char* avro_output)
{

    /************************************************************************
     *      STEP I : Create a Generic record                                *
     *                                                                      *
     *      STEP II : Read the data from a file                             *
     *              - Based on the schema get data type for each field      *
     *              - Accordingly populate the fields in generic record.    *
     *                                                                      *
     *      STEP III : Save the records and write it out to a file.         *
     *                                                                      *
     ************************************************************************/
    
        //TODO avro_file_writer_create_with_codec_fp
        //TODO avro_datum_t record_data = avro_record(person_schema);
        //TODO int num_fields= get_num_fields_schema();
        //TODO run a for loop to get the number of fields


    int i, j, k;
    int rval;
    char *field_data;
    char *saveptr;
    
    int num_records = 4;
    int num_fields = 5;
    
    
    avro_file_writer_t writer = NULL;
    avro_value_t value, field;
    avro_type_t val_type;
    
    char *CSVData[num_records][num_fields];
    
    CSVData[0][0] = "ID"; 
    CSVData[0][1] = "First";
    CSVData[0][2] = "Last";
    CSVData[0][3] = "Phone";
    CSVData[0][4] = "Age";


    CSVData[1][0] = "1"; 
    CSVData[1][1] = "Alexander";
    CSVData[1][2] = "Zimmerman";
    CSVData[1][3] = "2017725487";
    CSVData[1][4] = "38";


    CSVData[2][0] = "2"; 
    CSVData[2][1] = "Shaun";
    CSVData[2][2] = "Paul";
    CSVData[2][3] = "6096475898";
    CSVData[2][4] = "23";

    
    CSVData[3][0] = "3"; 
    CSVData[3][1] = "Steve";
    CSVData[3][2] = "Shaw";
    CSVData[3][3] = "609654398";
    CSVData[3][4] = "21";
    
    rval = avro_file_writer_create_with_codec(avro_output, person_schema, &writer, AVRO_CODEC, 0); 
  
    if (rval)
    {
        printf("There was an error creating %s\n",avro_output);
    }

    avro_value_iface_t *iface = avro_generic_class_from_schema(person_schema);
    avro_generic_value_new(iface, &value);


    for ( j = 1; j < num_records ; j++ ) // J=0 is the field title record
    {
        for ( i = 0; i < num_fields ; i++ ) // For each field perform
        {
            avro_value_get_by_index(&value, i, &field, NULL);
            val_type = avro_value_get_type(&field);
            printf("Field Type:%d\n",val_type);

            //TODO use function pointers
            switch(val_type)
            {
                case 0: 
                    // AVRO_STRING
                    avro_value_set_string(&field, CSVData[j][i]/*Data Value*/);
                    break;
                case 2: 
                    // AVRO_INT32
                    avro_value_set_int(&field, atoi(CSVData[j][i]) /*atoi(DataValue)*/);
                    break;
                case 3:
                    // AVRO_INT64
                    avro_value_set_long(&field, atol(CSVData[j][i])/*atol(DataValue)*/);
                    break;
                case 4:
                    // AVRO_FLOAT
                    avro_value_set_float(&field, atof(CSVData[j][i])/*atof(DataValue)*/);
                    break;
                default:
                    // We don't handle this format yet
                    printf("Unknown Format!");
                    break;
            }// End Switch statement
        } // End for i: Num_fields

       // Write the value to avro file 
        avro_file_writer_append_value(writer, &value); 
    } // End for j : Num_records


    //Cleanup Code
    avro_file_writer_close(writer);
    avro_value_decref(&value);
    avro_value_iface_decref(iface);
    avro_schema_decref(person_schema);

    printf("So far Good!\n");
    return;
}



void read_avro(const char* avro_input)
{
    avro_file_reader_t reader;
    avro_datum_t person;
    avro_schema_t reader_schema = NULL;
    int64_t i64;
    int32_t i32;
    char *p;
    
    if (avro_file_reader(avro_input, &reader))
    {
        printf("Error opening File for reading");
    }

    avro_file_reader_read(reader, reader_schema, &person); 
    avro_datum_t id_datum, first_datum, last_datum, phone_datum,
        age_datum;
 
    if (avro_record_get(person, "ID", &id_datum) == 0) {
            avro_int64_get(id_datum, &i64);
            fprintf(stdout, "%"PRId64" | ", i64);
    }
    if (avro_record_get(person, "First", &first_datum) == 0) {
            avro_string_get(first_datum, &p);
            fprintf(stdout, "%15s | ", p);
    }
    if (avro_record_get(person, "Last", &last_datum) == 0) {
            avro_string_get(last_datum, &p);
            fprintf(stdout, "%15s | ", p);
    }
    if (avro_record_get(person, "Phone", &phone_datum) == 0) {
            avro_string_get(phone_datum, &p);
            fprintf(stdout, "%15s | ", p);
    }
    if (avro_record_get(person, "Age", &age_datum) == 0) {
            avro_int32_get(age_datum, &i32);
            fprintf(stdout, "%d", i32);
    }
    fprintf(stdout, "\n");
 
    /* We no longer need this memory */
    avro_datum_decref(person);


    return;
}


int main(void)
{

    int rval;    
    const char *avro_file="Avrooutput.avro";
    /* Step I : Initialize the schema structure from JSON */
    init_schema();

    write_avro(avro_file);

    read_avro(avro_file);

    return 0;
    }
