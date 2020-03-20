#include "BookCollection.h"
#include<bits/stdc++.h>

BookCollection::BookCollection() {
    genreCount = 0;
    head = NULL;
}

BookCollection::~BookCollection() {
    if (head != NULL) {
        GenreNode *current = head;
        GenreNode *next;
        while (current != NULL) {
            next = current->next;
            delete current;
            current = next;
        }
    }
}

BookCollection::BookCollection(const BookCollection& bcToCopy) {
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
        genreCount = right.genreCount;
        if (right.head == NULL) {
            head = NULL;
        }
        else {
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

void BookCollection::addGenre(string genreName) {
    if (findGenre(genreName) != NULL) {
        cout << "Genre " << genreName << " already exists in this genre." << endl;
    }

    if (head == NULL){
        head = new GenreNode;
        head->g.setGenreName(genreName);
        head->next = NULL;
        genreCount++;
    }
    else {
        GenreNode *curr = head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = new GenreNode;
        curr = curr->next;
        curr->g.setGenreName(genreName);
        curr->next = NULL;
        genreCount++;
    }
}

void BookCollection::removeGenre (string genreName){
    GenreNode *genreToRemove = findGenre(genreName);
    if (genreToRemove == NULL) {
        cout << "Genre " << genreName << " does not exist in this genre." << endl;
        return;
    } 
    GenreNode *prev = head;
    if ((prev->next == NULL) && (prev == genreToRemove)) {
            delete prev;
            head = NULL;
            return;
    }
    for (GenreNode *curr = head->next; curr != NULL; curr = curr->next) {
        if (curr == genreToRemove) {
            prev->next = curr->next;
            delete curr;
        }
        else if (prev == genreToRemove) {
            head = prev->next;
            delete prev;
        }
        prev = prev->next;
    }
}

void BookCollection::displayAllGenres() const {
    if (head == NULL) {
        cout << "--EMPTY--";
        return;
    }
    for (GenreNode *curr = head; curr != NULL; curr = curr->next) {
        cout << curr->g.getGenreName() << endl;
        
    }
}
void BookCollection::addBook(string genreName, string bookName) {
    GenreNode *genreToAddBookTo = findGenre(genreName);
    if (genreToAddBookTo == NULL) {
        cout << "Genre " << genreName << " does not exist in collection." << endl;
    }
    else {
        genreToAddBookTo->g.addBook(bookName);
    }
}

void BookCollection::removeBook(string genreName, string bookName) {
    GenreNode *genreToAddBookTo = findGenre(genreName);
    if (genreToAddBookTo == NULL) {
        cout << "Genre " << genreName << " does not exist in collection." << endl;
    }
    else {
        genreToAddBookTo->g.removeBook(bookName);
    }
}

void BookCollection::addAuthor(string genreName, string bookName, int authorID, string authorName) {
    GenreNode *genreOfBook = findGenre(genreName);
    if (genreOfBook == NULL) {
        cout << "Genre " << genreName << " does not exist in collection." << endl;
    }
    else {
        genreOfBook->g.addAuthorToBook(bookName, authorName, authorID);
    }
}

void BookCollection::removeAuthor(string genreName, string bookName, int authorID) {
    GenreNode *genreOfBook = findGenre(genreName);
    if (genreOfBook == NULL) {
        cout << "Genre " << genreName << " does not exist in collection." << endl;
    }
    else {
        genreOfBook->g.removeAuthorFromBook(bookName, authorID);
    }
}

void BookCollection::displayGenre(string genreName) {
    GenreNode *genre = findGenre(genreName);
    if (genre == NULL) {
        cout << "--EMPTY--" << endl;
    }
    else {
        cout << genre->g.getGenreName() << endl;
        genre->g.displayBooks();
    }
}
void BookCollection::displayAuthor(int authorID) {
    string authorName = "";
    string bookName = "";
    bool hasBooks = false;
    for (GenreNode *currGenre = head; currGenre != NULL; currGenre = currGenre->next) {
        if (currGenre->g.helperMethod(currGenre->g.getGenreName(),bookName, authorName, authorID)) {
            hasBooks = true;
        }
        else {
            hasBooks = false;
        }
    }
    if (!hasBooks) {
        cout << "--EMPTY--" << endl;
    }
}

BookCollection::GenreNode* BookCollection::findGenre(string genreName) {
    string genreToFind = genreName;
    string currentGenreName = "";
    string temp = "";
    transform(genreToFind.begin(), genreToFind.end(), genreToFind.begin(), ::tolower);
    for (GenreNode *curr = head; curr != NULL; curr = curr->next) {
        currentGenreName = curr->g.getGenreName();
        transform(currentGenreName.begin(), currentGenreName.end(), currentGenreName.begin(), ::tolower);
        if (currentGenreName == genreToFind) {
            return curr;
        }
    }
    return NULL;
}