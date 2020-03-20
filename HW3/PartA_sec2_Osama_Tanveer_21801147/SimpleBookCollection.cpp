#include "SimpleBookCollection.h"
#include <iostream>
#include<bits/stdc++.h>

BookCollection::BookCollection() {
    name = "";
    genreCount = 0;
    head = NULL;
}

BookCollection::~BookCollection() {
    if (head != NULL) {
        GenreNode* current = head;
        GenreNode* next;

        while (current != NULL) {
            next = current->next;
            delete current;
            current = next;
        }
    }
}

BookCollection::BookCollection(const BookCollection& bcToCopy) {
    name = bcToCopy.name;
    genreCount = bcToCopy.genreCount;
    if (bcToCopy.head == NULL) {
        head = NULL;
    }
    else {
        head = new GenreNode;
        head->g = bcToCopy.head->g;
        GenreNode *newPtr = head;
        for (GenreNode *origPtr = bcToCopy.head->next; origPtr != NULL; origPtr = origPtr->next) {
            newPtr->next = new GenreNode;
            newPtr = newPtr->next;
            newPtr->g = origPtr->g;
        }
        newPtr->next = NULL;
    }
}

void BookCollection::operator=(const BookCollection& right) {
    if (&right != this) {
        name = right.name;
        genreCount = right.genreCount;

        if (right.head == NULL) {
            head = NULL;
        }
        else {
            if (head != NULL) {
                GenreNode* current = head;
                GenreNode* next;

                while (current != NULL) {
                    next = current->next;
                    delete current;
                    current = next;
                }
            }
            head = new GenreNode;
            head->g = right.head->g;
            GenreNode *newPtr = head;
            for (GenreNode *origPtr = right.head->next; origPtr != NULL; origPtr = origPtr->next) {
                newPtr->next = new GenreNode;
                newPtr = newPtr->next;
                newPtr->g = origPtr->g;
            }
            newPtr->next = NULL;
        }
    }
}

void BookCollection::displayGenres() const {
    if (head == NULL) {
        cout << "--EMPTY--" << endl;
    }

    else {
        for (GenreNode *curr = head; curr != NULL; curr = curr->next) {
            cout << curr->g.getGenreName() << endl;
        }
    }
}

bool BookCollection::addGenre(const string genreName) {
    if (findGenre(genreName) != NULL) {
        cout << "Genre " << genreName << " already exists in collection." << endl;
        return false;
    }

    if (head == NULL) {
        head = new GenreNode;
        head->g.setGenreName(genreName);
        head->next = NULL;
        genreCount++;
    }

    else {
        GenreNode* curr = head;
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next = new GenreNode;
        curr = curr->next;
        curr->g.setGenreName(genreName);
        curr->next = NULL;
        genreCount++;
    }

    return true;
}

bool BookCollection::removeGenre(const string genreName) {
    if (findGenre(genreName) == NULL) {
        cout << "Genre " << genreName << " does not exist in collection." << endl;
        return false;
    }
    else {
        GenreNode* ptrToRemove = findGenre(genreName);
        GenreNode* prev = head;
        if ((prev->next == NULL) && (prev == ptrToRemove)) {
            delete prev;
            head = NULL;
            return true;
        }
        else {
            for (GenreNode *curr = head->next; curr != NULL; curr = curr->next) {
                if (curr == ptrToRemove) {
                    GenreNode* temp = curr->next;
                    prev->next = temp;
                    delete curr;
                    genreCount--;
                    return true;
                }

                else if (prev == ptrToRemove) {
                    GenreNode* temp = prev->next;
                    head = temp;
                    delete prev;
                    genreCount--;
                    return true;
                }
                prev = prev->next;
            }
        }
    }
    return true;
}

string BookCollection::getName() const {
    return name;
}

void BookCollection::setName(const string bcName) {
    name = bcName;
}

BookCollection::GenreNode* BookCollection::findGenre(string genreName) {
    string genreNameToFind = genreName;
    string currentGenreName = "";
    string temp = "";
    transform(genreNameToFind.begin(), genreNameToFind.end(), genreNameToFind.begin(), ::tolower);
    for (GenreNode *curr = head; curr != NULL; curr = curr->next) {
        currentGenreName = curr->g.getGenreName();
        transform(currentGenreName.begin(), currentGenreName.end(), currentGenreName.begin(), ::tolower);
        if (currentGenreName == genreNameToFind) {
            return curr;
        }
    }
    return NULL;
}