#include "Actor.h"

Actor::Actor(const string aName, const string aBirthPlace,
      const unsigned int aBirthYear) {

    name = aName;
    birthPlace = aBirthPlace;
    birthYear = aBirthYear;
}

Actor::Actor(const Actor &actorToCopy) {
    name = actorToCopy.name;
    birthPlace = actorToCopy.birthPlace;
    birthYear = actorToCopy.birthYear;
}

Actor::~Actor() {

}

void Actor::operator=(const Actor &right) {
    if (&right != this) {
        name = right.name;
        birthPlace = right.birthPlace;
        birthYear = right.birthYear;
    }

}

string Actor::getName() const {
    return name;
}

string Actor::getBirthPlace() const {
    return birthPlace;
}

unsigned int Actor::getBirthYear() const {
    return birthYear;
}

ostream& operator<<(ostream& out, const Actor& a) {
    out << a.getName() << ", " << a.getBirthPlace() << ", " << a.getBirthYear() << endl;
    return out;
}
