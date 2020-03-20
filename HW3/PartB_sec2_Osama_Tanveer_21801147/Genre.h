#ifndef __SIMPLE_GENRE_H
#define __SIMPLE_GENRE_H

#include <string>
#include "Book.h"

using namespace std;

class Genre {
public:    
    Genre(const string gname = "");
    ~Genre ();
    Genre (const Genre &genreToCopy);
    void operator=(const Genre &right);
    bool addBook(const string bName);
    bool removeBook(const string bName);
    void displayBooks() const;
    string getGenreName() const;
    void setGenreName(const string gName);
    
    // my own 
    void addAuthorToBook(string bName, string authorName, int authorID);
    void removeAuthorFromBook(string bName, int authorID);
    bool helperMethod(string genreName, string &bName, string &authorName, int authorID);

private:
    struct BookNode {
        Book b;
        BookNode* next;
    };
    BookNode* head;
    string genreName;
    BookNode* findBook(const string bName);
};
#endif

