#include "ip.h"

#define BIT_IN_NUM 8
#define NUMS_IN_ADD 4

//-------------------helpers----------------------------//
//
bool get_value_ip(String type, String packet, String &value) { 
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

//-------------------constructor------------------------//
ip::ip(const String &type) { //address/mask
    this->type = type;
    this->address = 0;
    this->mask = 0;
}

//this function get string in this form only! "XXX.XXX.XXX.XXX/X"
bool ip::set_value(String value) {
    const char *delimeters = "./";
    String *arr = nullptr; 
    size_t arr_len;
    value.split(delimeters, &arr , &arr_len);
    //set address 
    int temp_address = 0 , temp;
    for (size_t i=0 ; i < 4 ; i++) { //4 nums in ip
        temp  = arr[i].to_integer();
        if (temp < 0 || temp > 255) {
            delete[] arr;
            return false;
        }
        temp_address += temp << (8* (3 - i));
    }
    this->address = temp_address;
    //set mask
   int temp_mask =  arr[4].to_integer();
    if(temp_mask <0 || temp_mask > 32) { 
        delete[] arr;
        return false;
    }
    this->mask = (-1 << (32-temp_mask)) ;
    delete[] arr;
    return true;
}

//works for packets 
bool ip::match(String packet) {
    String value;
    if (get_value_ip(this->type, packet, value) == false)
        return false;
    const char *delimeters = ".";
    String *arr = nullptr;  
    size_t arr_len = 0;
    value.split(delimeters, &arr , &arr_len);
    int temp_address = 0;
    for (size_t i=0 ; i < (arr_len) ; i++) { 
        int temp  = arr[i].to_integer();
        if (temp < 0 || temp > 255) {
            delete[] arr;
            return false;
        }
        temp_address += temp << (8* (3 - i));
    }
    delete[] arr;
    int answer = (temp_address & this->mask)==(this->address & this->mask);
   // std::cout << "answer for match: " << answer << std::endl;
    return answer;
}