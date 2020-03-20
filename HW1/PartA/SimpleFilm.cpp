#include "SimpleFilm.h"

Film::Film(const string fTitle, const string fDirector,
                 const unsigned int fYear,
                 const unsigned int fDuration) {

    title = fTitle;
    director = fDirector;
    year = fYear;
    duration = fDuration;
}

Film::Film(const Film &fToCopy) {
    title = fToCopy.title;
    director = fToCopy.director;
    year = fToCopy.year;
    duration = fToCopy.duration;
}

Film::~Film() {

}

void Film::operator=(const Film &right) {
    if (&right != this) {
        if ((right.director != director) && (right.title != title) &&
        (right.year != year) && (right.duration != duration)) {
        title = right.title;
        director = right.director;
        year = right.year;
        duration = right.duration;
        }
    }
}

string Film::getTitle() const {
    return title;
}

string Film::getDirector() const {
    return director;
}

unsigned int Film::getYear() const {
    return year;
}

unsigned int Film::getDuration() const {
    return duration;
}

ostream& operator<<(ostream& out, const Film& f) {
    out << f.getTitle() << ", " << f.getYear() << ", "
        << f.getDirector() << ", " << f.getDuration() << " min" << endl;
    return out;
}
