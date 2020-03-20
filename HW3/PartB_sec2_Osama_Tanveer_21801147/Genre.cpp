#include "Genre.h"
#include <iostream>
#include<bits/stdc++.h>

Genre::Genre(const string gname) {
    genreName = gname;
    head = NULL;
}

Genre::~Genre () {
    if (head != NULL) {
        BookNode *current = head;
        BookNode *next;
        while (current != NULL) {
            next = current->next;
            delete current;
            current = next;
        }
    }
}

Genre::Genre (const Genre &genreToCopy) {
    genreName = genreToCopy.genreName;
    if (genreToCopy.head == NULL) {
        head = NULL;
    }
    else {
        head = new BookNode;
        head->b = genreToCopy.head->b;
        BookNode *newPtr = head;
        for (BookNode *origPtr = genreToCopy.head->next; origPtr != NULL; origPtr = origPtr->next) {
            newPtr->next = new BookNode;
            newPtr = newPtr->next;
            newPtr->b = origPtr->b;
        }
        newPtr->next = NULL;
    }
}
void Genre::operator=(const Genre &right) {
    genreName = right.genreName;
    if (right.head == NULL) {
        head = NULL;
    }
    else {
        head = new BookNode;
        head->b = right.head->b;
        BookNode *newPtr = head;
        for (BookNode *origPtr = right.head->next; origPtr != NULL; origPtr = origPtr->next) {
            newPtr->next = new BookNode;
            newPtr = newPtr->next;
            newPtr->b = origPtr->b;
        }
        newPtr->next = NULL;
    }
}

bool Genre::addBook(const string bName) {
    if (findBook(bName) != NULL) {
        cout << "Book " << bName << " already exists in this genre." << endl;
        return false;
    }

    if (head == NULL){
        head = new BookNode;
        head->b.setName(bName);
        head->next = NULL;
        return true;
    }
    else {
        BookNode *curr = head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = new BookNode;
        curr = curr->next;
        curr->b.setName(bName);
        curr->next = NULL;
        return true;
    }
}

bool Genre::removeBook(const string bName) {
    BookNode *bookToRemove = findBook(bName);
    if (bookToRemove == NULL) {
        cout << "Book " << bName << " does not exist in this genre." << endl;
        return false;
    }

    BookNode *prev = head;
    for (BookNode *curr = head->next; curr != NULL; curr = curr->next) {
        if (curr == bookToRemove) {
            prev->next = curr->next;
            delete curr;
            return true;
        }
        else if (prev == bookToRemove) {
            head = prev->next;
            delete prev;
            return true;
        }
        prev = prev->next;
    }
    return false;
}

void Genre::displayBooks() const {
    if (head == NULL) {
        cout << "--EMPTY--";
        return;
    }
    for (BookNode *curr = head; curr != NULL; curr = curr->next) {
        cout << curr->b.getName() << endl;
        curr->b.displayAuthors();
        cout << endl;
    }
}

string Genre::getGenreName() const {
    return genreName;
}

void Genre::setGenreName(const string gName) {
    genreName = gName;
}

Genre::BookNode* Genre::findBook(const string bName) {
    string bookToFind = bName;
    string currentBookName = "";
    string temp = "";
    transform(bookToFind.begin(), bookToFind.end(), bookToFind.begin(), ::tolower);
    for (BookNode *curr = head; curr != NULL; curr = curr->next) {
        currentBookName = curr->b.getName();
        transform(currentBookName.begin(), currentBookName.end(), currentBookName.begin(), ::tolower);
        if (currentBookName == bookToFind) {
            return curr;
        }
    }
    return NULL;
}
// my own
void Genre::addAuthorToBook(string bName, string authorName, int authorID) {
    BookNode *bookToAddTo = findBook(bName);
    if (bookToAddTo == NULL) {
        cout << "Book does not exist in genre." << endl;
    }
    else {
        bookToAddTo->b.addAuthor(authorID, authorName);
    }
}

void Genre::removeAuthorFromBook(string bName, int authorID) {
    BookNode *bookToRemoveFrom = findBook(bName);
    if (bookToRemoveFrom == NULL) {
        cout << "Book does not exist in genre." << endl;
    }
    else {
        bookToRemoveFrom->b.removeAuthor(authorID);
    }
}

bool Genre::helperMethod(string genreName, string& bName, string &authorName, int authorID) {
    bool bookPresent = false;
    static int id = 0;
    static bool authorDetailsAdded;
    if (id != authorID) {
        id = authorID;
        authorDetailsAdded = false;
    }
    
    bool genreDetailsAdded = false;
    for (BookNode *currBook = head; currBook != NULL; currBook = currBook->next) {
        if (currBook->b.authorPresentInBook(authorName, authorID)) {
            if (!authorDetailsAdded) {
                cout << authorID << ", " << authorName << endl;
                authorDetailsAdded = true;
            }
            if (!genreDetailsAdded) {
                cout << genreName << endl;
                genreDetailsAdded = true;
            }
            
            cout << "\t" << currBook->b.getName() << endl;
            bookPresent = true;
        }    
    }
    
    return bookPresent;
}