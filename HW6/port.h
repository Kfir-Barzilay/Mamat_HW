#include "string.h"
#include "generic-field.h"

class port : public GenericField
{
    String type;
    int min_value;
    int max_value;
public:
    port(const String &type);
    bool match(String packet); 
    bool set_value(String value);
};