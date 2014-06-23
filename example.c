#include "avro-lib.h"

int main(){

    //Testing the avro-lib functions
    const char *avro_input="data.avsc";
    setup_record_structure(avro_input);

    set_long_value(223);
    set_string_value("Bryan");
    set_string_value("Adams");
    set_string_value("6589896564");
    set_int_value(32);
    reset_record_structure();
    cleanup_record_structure();
    return(0);

}

