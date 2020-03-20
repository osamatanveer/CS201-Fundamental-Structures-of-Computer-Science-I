#include "Author.h"

Author::Author() {
    name = "";
    id = 0;
}

Author::Author(const int id, const string name) {
    Author::name = name;
    Author::id = id;
}

int Author::getID() const {
    return id;
}

void Author::setID(const int id) {
    Author::id = id;
}

string Author::getName() const {
    return name;
}

void Author::setName(const string name) {
    Author::name = name;
}