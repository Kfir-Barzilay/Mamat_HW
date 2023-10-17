#include "port.h"


#define BIT_IN_NUM 8
#define NUMS_IN_ADD 4

//------------------------helpers----------------------------//

bool get_value_port(String type, String packet, String &value) { 
    const char *delimeters = ",=#";
    String *arr = nullptr;
    size_t arr_len = 0;
    packet.split(delimeters , &arr , &arr_len);
    for (size_t i = 0; i < (arr_len/2) ; i++) { //for each rule thers a type and val
        if (type.equals(arr[2*i].trim())) {
            value = arr[2*i + 1].trim();
            delete[] arr;
            return true;
        }
    }
    //shouldnt happen
    delete[] arr;
    value= String();
    return false;
}
//--------------------------constructor-----------------------------//
port::port(const String &type) {
    this->type = type;
    this->min_value = 0;
    this->max_value = 0; 
}

//takes  XXXXXX-XXXXXX
bool port::set_value(String value) {
    const char *delimeter = "-";
    String *arr =nullptr;
    size_t arr_len = 0;
    value.split(delimeter, &arr, &arr_len);
    String str1 = arr[0].trim();
    String str2 = arr[1].trim();
    this->min_value = str1.to_integer();
    this->max_value = str2.to_integer(); 
    //std::cout << "min / nax" << min_value << " / " << max_value << std::endl;
    if ((this->min_value >> 16) || (this->max_value >> 16)) {
        delete[] arr;
        return false;
    }
    //std::cout << "min / nax" << min_value << " / " << max_value << std::endl;
    delete[] arr;
    return true;
}

//takes  XXXXXX
bool port::match(String packet) {
    String value;
    if (get_value_port(this->type, packet , value) == false)
        return false;
    int packet_port = value.to_integer();
    //std::cout << "challenger port is: " << packet_port << std::endl;
    int answer = (this->min_value <= packet_port) && 
                 (packet_port <= this->max_value);
    //std::cout << "answer for match: " << answer << std::endl;
    return (answer );
} 