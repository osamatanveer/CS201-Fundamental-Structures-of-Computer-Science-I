#include "Film.h"

Film::Film(const string fTitle, const string fDirector,
           const unsigned int fYear, const unsigned int fDuration) {
    title = fTitle;
    director = fDirector;
    year = fYear;
    duration = fDuration;
    actors = NULL;
    noOfActors = 0;
    size = 0;
}

Film::Film(const Film &fToCopy) {
    title = fToCopy.title;
    director = fToCopy.director;
    year = fToCopy.year;
    duration = fToCopy.duration;
    noOfActors = fToCopy.noOfActors;
    size = fToCopy.size;
    if (noOfActors == 0) {
        actors = NULL;
    }
    else {
        actors = new Actor[noOfActors];
        for (int i = 0; i < noOfActors; i++) {
            actors[i] = fToCopy.actors[i];
        }
    }
}
Film::~Film() {
    if (actors) {
        delete [] actors;
    }
}
void Film::operator=(const Film &right) {
    if (&right != this) {
        title = right.title;
        director = right.director;
        year = right.year;
        duration = right.duration;
        noOfActors = right.noOfActors;
        size = right.size;
        delete [] actors;
        if (noOfActors == 0) {
            actors = NULL;
        }
        else {
            actors = new Actor[noOfActors];
            for (int i = 0; i < noOfActors; i++) {
                actors[i] = right.actors[i];
            }
        }
    }
}

string Film::getFilmTitle() const {
    return title;
}

string Film::getFilmDirector() const {
    return director;
}

unsigned int Film::getFilmYear() const {
    return year;
}

unsigned int Film::getFilmDuration() const {
    return duration;
}

unsigned int Film::calculateAverageActorAge() const {
    if (noOfActors == 0) {
        return 0;
    }

    int sum = 0;
    for (int i = 0; i < noOfActors; i++) {
        sum = sum + (year - actors[i].getBirthYear());
    }
    return sum / noOfActors;
}

bool Film::addActorToFilm(const string aName, const string aBirthPlace,
                    const unsigned int aBirthYear) {

    for (int i = 0; i < noOfActors; i++) {
        if ((actors[i].getName() == aName) && (actors[i].getBirthPlace() == aBirthPlace) && (actors[i].getBirthYear() == aBirthYear)) {
            return false;
        }
    }

    Actor actorToAdd(aName, aBirthPlace, aBirthYear);
    Actor* temp = new Actor[noOfActors + 1];
    for (int i = 0; i < noOfActors; i++) {
        temp[i] = actors[i];
    }
    delete [] actors;
    actors = new Actor[noOfActors + 1];

    for (int i = 0; i < noOfActors + 1; i++) {
        actors[i] = temp[i];
    }
    actors[noOfActors] = actorToAdd;
    delete[] temp;
    noOfActors++;
    size++;
    return true;
}

bool Film::removeFilmActors() {
    if (actors == NULL) {
        return false;
    }
    delete [] actors;
    actors = NULL;
    noOfActors = 0;
    size = 0;
    return true;
}

ostream& operator<<(ostream& out, const Film& f) {
    out << f.title << ", " << f.director << ", " << f.year << ", " << f.duration << endl;
    if (f.actors != NULL) {
        for (int i = 0; i < f.noOfActors; i++) {
            out << "\t" << f.actors[i].getName() << ", " << f.actors[i].getBirthPlace() << ", " << f.actors[i].getBirthYear() << endl;
        }
    }
    return out;
}


