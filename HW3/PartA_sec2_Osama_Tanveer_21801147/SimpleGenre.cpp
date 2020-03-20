#include "SimpleGenre.h"

Genre::Genre(const string gname) {
    genreName = gname;
}

Genre::~Genre() {

}

Genre::Genre (const Genre &genreToCopy) {
    if (genreToCopy.genreName != genreName) {
        genreName = genreToCopy.genreName;
    }
}

void Genre::operator=(const Genre &right) {
    if (&right != this) {
        genreName = right.genreName;
    }
}

string Genre::getGenreName() const {
    return genreName;
}

void Genre::setGenreName(const string gName) {
    genreName = gName;
}
