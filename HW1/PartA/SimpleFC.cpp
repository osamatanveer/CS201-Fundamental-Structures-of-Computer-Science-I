#include "SimpleFC.h"

FC::FC() {
    films = NULL;
    noOfFilms = 0;
    size = 0;
}

FC::FC(const FC &fcToCopy) {
    if ((fcToCopy.films != NULL) && (fcToCopy.size > 0) && (fcToCopy.noOfFilms > 0)) {
        films = fcToCopy.films;
        size = fcToCopy.size;
        noOfFilms = fcToCopy.noOfFilms;
        delete [] films;
        films = new Film[noOfFilms];

        for (int i = 0; i < size; i++) {
            films[i] = fcToCopy.films[i];
        }

     }
    else {
        films = NULL;
        noOfFilms = 0;
        size = 0;
    }
}

FC::~FC(){
    if (films) {
        delete [] films;
    }
}

void FC::operator=(const FC &right) {
    if (&right != this) {
        if ((right.films != NULL) && (right.size > 0) && (right.noOfFilms > 0)) {
            films = right.films;
            size = right.size;
            noOfFilms = right.noOfFilms;
            delete [] films;
            films = new Film[noOfFilms];

            for (int i = 0; i < size; i++) {
                films[i] = right.films[i];
            }
         }
     }
}

bool FC::addFilm(const string fTitle, const string fDirector,
                 const unsigned int fYear, const unsigned int fDuration) {

    // Checking if films already exists in the collection
    for (int i = 0; i < size; i++) {
        if ((films[i].getTitle() == fTitle) && (films[i].getDirector() == fDirector)) {
            return false;
        }
    }

    Film filmToAdd(fTitle, fDirector, fYear, fDuration);
    Film* temp = new Film[noOfFilms + 1];
    for (int i = 0; i < size; i++) {
        temp[i] = films[i];
    }
    delete [] films;
    films = new Film[noOfFilms + 1];
    for (int i = 0; i < size; i++) {
        films[i] = temp[i];
    }
    delete [] temp;
    films[size] = filmToAdd;
    noOfFilms++;
    size++;
}


bool FC::removeFilm(const string fTitle, const string fDirector) {
    int indexToRemove = -1;
    for (int i = 0; i < size; i++) {
        if ((films[i].getTitle() == fTitle) && (films[i].getDirector() == fDirector)) {
            indexToRemove = i;
        }
    }
    if (indexToRemove == -1) {
        return false;
    }

    Film* temp = new Film[noOfFilms - 1];
    for (int i = 0; i < size; i++) {
        if (i != indexToRemove) {
            temp[i] = films[i];
        }
    }
    delete [] films;
    films = new Film[noOfFilms - 1];
    for (int i = 0; i < size - 1; i++) {
        films[i] = temp [i];
    }
    delete [] temp;
    noOfFilms--;
    size--;
}

unsigned int FC::getFilms(Film *&allFilms) const {
    allFilms = new Film[noOfFilms];
	for (int i = 0; i < size; i++) {
		allFilms[i] = films[i];
	}
	return noOfFilms;
}

