#include "Book.h"
#include <iostream>

Book::Book() {
    name = "";
    head = NULL;
}

Book::Book(const string name) {
    Book::name = name;
    head = NULL;
}

Book::~Book() {
    if (head != NULL) {
        AuthorNode *current = head;
        AuthorNode *next;
        while (current != NULL) {
            next = current->next;
            delete current;
            current = next;
        }
    }
}

Book::Book(const Book& bookToCopy) {
    name = bookToCopy.name;
    if (bookToCopy.head == NULL) {
        head = NULL;
    }
    else {
        head = new AuthorNode;
        head->a.setName(bookToCopy.head->a.getName());
        head->a.setID(bookToCopy.head->a.getID());
        AuthorNode *newPtr = head;
        for (AuthorNode *origPtr = bookToCopy.head->next; origPtr != NULL; origPtr = origPtr->next) {
            newPtr->next = new AuthorNode;
            newPtr = newPtr->next;
            newPtr->a.setName(origPtr->a.getName());
            newPtr->a.setID(origPtr->a.getID());
        }
        newPtr->next = NULL;
    }
}

void Book::operator=(const Book& right) {
    name = right.name;
    if (right.head == NULL) {
        head = NULL;
    }
    else {
        head = new AuthorNode;
        head->a.setName(right.head->a.getName());
        head->a.setID(right.head->a.getID());
        AuthorNode *newPtr = head;
        for (AuthorNode *origPtr = right.head->next; origPtr != NULL; origPtr = origPtr->next) {
            newPtr->next = new AuthorNode;
            newPtr = newPtr->next;
            newPtr->a.setName(origPtr->a.getName());
            newPtr->a.setID(origPtr->a.getID());
        }
        newPtr->next = NULL;
    }
}

string Book::getName() const {
    return name;
}

void Book::setName(const string bookName) {
    name = bookName;
}

bool Book::addAuthor(const int id, const string name) {
    if (findAuthor(id) != NULL) {
        cout << "Author with id " << id << " already exists." << endl;
        return false;
    }

    if (head == NULL){
        head = new AuthorNode;
        head->a.setName(name);
        head->a.setID(id);
        head->next = NULL;
        return true;
    }
    else {
        AuthorNode *curr = head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = new AuthorNode;
        curr = curr->next;
        curr->a.setName(name);
        curr->a.setID(id);
        curr->next = NULL;
        return true;
    }
}

bool Book::removeAuthor (const int id) {
    AuthorNode *authorToRemove = findAuthor(id);
    if (authorToRemove == NULL) {
        cout << "Author " << id << " does not exist." << endl;
        return false;
    }

    AuthorNode *prev = head;
    if ((prev->next == NULL) && (prev == authorToRemove)) {
        delete prev;
        head = NULL;
        return true;
    }

    for (AuthorNode *curr = head->next; curr != NULL; curr = curr->next) {
        if (curr == authorToRemove) {
            prev->next = curr->next;
            delete curr;
            return true;
        }
        else if (prev == authorToRemove) {
            head = prev->next;
            delete prev;
            return true;
        }
        prev = prev->next;
    }
}
void Book::displayAuthors() const {
    if (head == NULL) {
        cout << "--EMPTY--" << endl;
        return;
    }
    for (AuthorNode *curr = head; curr != NULL; curr = curr->next) {
        cout << "\t" << curr->a.getID() << ", " << curr->a.getName() << endl;
    }
}

Book::AuthorNode* Book::findAuthor(int id) {
    for (AuthorNode *curr = head; curr != NULL; curr = curr->next) {
        if (curr->a.getID() == id) {
            return curr;
        }
    }
    return NULL;
}

bool Book::authorPresentInBook(string &authorName, int authorID) {
    AuthorNode *ptrOfAuthor = findAuthor(authorID);
    if (ptrOfAuthor == NULL) {
        return false;
    }
    else {
        authorName = ptrOfAuthor->a.getName();
        return true;
    }
}