#include "FC.h"
#include "Film.h"

FC::FC() {
    films = NULL;
    noOfFilms = 0;
    size = 0;
}

FC::FC(const FC &fcToCopy) {
    noOfFilms = fcToCopy.noOfFilms;
    size = fcToCopy.size;
    if (noOfFilms == 0) {
        films = NULL;
    }
    else {
        films = new Film[noOfFilms];
        for (int i = 0; i < noOfFilms; i++) {
            films[i] = fcToCopy.films[i];
        }
    }
}

FC::~FC() {
    if (films) {
        delete [] films;
    }
}

void FC::operator=(const FC &right) {
    if (&right != this) {
        noOfFilms = right.noOfFilms;
        size = right.noOfFilms;
        if (noOfFilms == 0) {
            films = NULL;
        }
        else {
            films = new Film[noOfFilms];
            for (int i = 0; i < noOfFilms; i++) {
                films[i] = right.films[i];
            }
        }
    }
}

bool FC::addFilm(const string fTitle, const string fDirector,
                 const unsigned int fYear,
                 const unsigned int fDuration) {

    for (int i = 0; i < noOfFilms; i++) {
        if ((films[i].getFilmTitle() == fTitle) && (films[i].getFilmDirector() == fDirector)) {
        return false;
        }
    }

    Film filmToAdd(fTitle, fDirector, fYear, fDuration);
    Film* temp = new Film[noOfFilms + 1];

    for (int i = 0; i < noOfFilms; i++) {
        temp[i] = films[i];
    }
    delete [] films;
    films = new Film[noOfFilms + 1];

    for (int i = 0; i < noOfFilms; i++) {
        films[i] = temp[i];
    }
    films[size] = filmToAdd;
    delete [] temp;
    noOfFilms++;
    size++;

    return true;
}
bool FC::removeFilm(const string fTitle, const string fDirector) {
    int indexOfFilmToRemove = -1;
    for (int i = 0; i < noOfFilms; i++) {
        if ((films[i].getFilmTitle() == fTitle) && (films[i].getFilmDirector() == fDirector)) {
            indexOfFilmToRemove = i;
        }
    }

    if (indexOfFilmToRemove == -1) {
        return false;
    }

    Film* temp = new Film[noOfFilms - 1];
    for (int i = 0; i < indexOfFilmToRemove; i++) {
			temp[i] = films[i];
		}
    for (int i = indexOfFilmToRemove + 1; i < noOfFilms; i++) {
			temp[i-1] = films[i];
    }
    delete[] films;
	films = new Film[noOfFilms - 1];
    for (int i = 0; i < noOfFilms - 1; i++) {
     films[i] = temp[i];
    }
    delete [] temp;
    noOfFilms--;
    size--;
    return true;
}

unsigned int FC::getFilms(Film *&allFilms) const {
    allFilms = new Film[noOfFilms];
	for (int i = 0; i < noOfFilms; i++) {
		allFilms[i] = films[i];
	}
	return noOfFilms;
}

bool FC::addActor(const string fTitle, const string fDirector,
                  const string aName, const string aBirthPlace,
                  const unsigned int aBirthYear) {

    int indexOfFilm = -1;
    for (int i = 0; i < noOfFilms; i++) {
        if ((films[i].getFilmTitle() == fTitle) && (films[i].getFilmDirector() == fDirector)) {
            indexOfFilm = i;
        }
    }

    if (indexOfFilm == -1) {
        return false;
    }

    if ((films[indexOfFilm]).addActorToFilm(aName, aBirthPlace, aBirthYear)) {
        return true;
    }
    else {
        return false;
    }
}

bool FC::removeActors(const string fTitle, const string fDirector) {
    int indexOfFilm = -1;
    for (int i = 0; i < noOfFilms; i++) {
        if ((films[i].getFilmTitle() == fTitle) && (films[i].getFilmDirector() == fDirector)) {
            indexOfFilm = i;
        }
    }
    if (indexOfFilm == -1) {
        return false;
    }

    if (films[indexOfFilm].removeFilmActors()) {
        return true;
    }
    else {
        return false;
    }
}

unsigned int FC::calculateAverageDuration() const {
    int sum = 0;
    for (int i = 0; i < noOfFilms; i++) {
        sum = sum + films[i].getFilmDuration();
    }
    return sum / noOfFilms;
}

