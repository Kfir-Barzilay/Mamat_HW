#include "string.h"
#include "generic-field.h"

class ip : public GenericField
{
private:
    String type;
    int address;
    int mask;
public:
    ip(const String &type);
    bool match(String packet); 
    bool set_value(String value);
};
