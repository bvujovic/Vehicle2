#include "Status.h"
#include <UtilsCommon.h>

ulong Status::idGenerator = 0;

Status::Status(String message, String source, ulong ms)
{
    this->id = ++idGenerator;
    this->message = message;
    this->source = source;
    this->ms = ms;
}

Status::Status(String message, String source)
    : Status(message, source, millis())
{
}

String Status::ToString()
{
    String res = source;
    res.concat('\t');
    res.concat(message);
    res.concat('\t');
    res.concat(ms);
    res.concat('\t');
    res.concat(id);
    return res;
}