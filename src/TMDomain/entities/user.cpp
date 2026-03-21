#include "user.h"

User::User() {}

User::User(const User &other)
    : id{other.id}
    , name{other.name}
    , email{other.email}
    , country{other.country}
    , user_image{other.user_image}
{}
