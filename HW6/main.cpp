#include "ip.h"
#include "generic-field.h"
#include "port.h"
#include "string.h"
#include "input.h"
#include <stddef.h>
#include <iostream>
#include <cstring>

const String FIELDS[] = {String("src-ip"),
                             String("dst-ip"),
		                     String("src-port"),
                             String("dst-port")
};

GenericField* setGenericRule(const String &rule) {
    //std::cout << "getting field" << std::endl;
    GenericField *field = nullptr;
    const char *delimeters ="=";
    String *arr = nullptr;
    size_t arr_len = 0;
    rule.split(delimeters , &arr , &arr_len);
    if(arr == nullptr){ 
        std::cout << "fuck" << std::endl;
        delete[] arr;
        return field;
    }
    String type = arr[0].trim();
    String value= arr[1].trim();
    
    //std::cout << "lets compare" << std::endl;
    if (type.equals(FIELDS[0])) {
        field = new ip(FIELDS[0]);
        //std::cout << "match 0 " << std::endl;
    }
    else if (type.equals(FIELDS[1])) {
        field = new ip(FIELDS[1]);
        //std::cout << "match 1 " << std::endl;
    }
    else if (type.equals(FIELDS[2])){
        field = new port(FIELDS[2]);
       // std::cout << "match 2 " << std::endl;
    }
    else if (type.equals(FIELDS[3])) {
        field = new port(FIELDS[3]);
       // std::cout << "match 3 " << std::endl;
    }
    else {
        std::cout << "something wrong with rule name" << std::endl;
    } // something wrong -shouldnt happen
    //std::cout << "got field" << std::endl;
    (*field).set_value(value);
    delete[] arr;
    return field;
}

int main(int argc, char** argv){
    //std::cout << "start main" << std::endl;
    if(check_args(argc, argv)){
        return 1;
    }
    String rule = argv[1];
    //std::cout << "get field" << std::endl;
    GenericField *field = setGenericRule(rule);
    parse_input(*field); //should print all valid packets
    delete (field);
    //std::cout << "finish main" << std::endl;
    return 0;
}