#ifndef USER_H
#define USER_H

#include <string>

#include <boost/json.hpp>

class User // profile info
{
public:
    User();
    User(const User &other);

    std::string id;
    std::string name;
    std::string email;
    std::string country;
    std::string user_image;
};

#endif // USER_H
