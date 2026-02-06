#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book
{
private:
    std::string ISBN;
    std::string title;
    std::string author;
    std::string genre;
    int publicationYear;
    bool isAvailable;
    std::string borrowedBy;

public:
    Book(std::string isbn, std::string title, std::string author,
         std::string genre, int year);

    std::string getISBN() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getGenre() const;
    int getPublicationYear() const;
    bool getAvailability() const;
    std::string getBorrowedBy() const;

    void setAvailability(bool available);
    void setBorrowedBy(std::string userId);

    void displayInfo() const;
    bool matchesSearch(const std::string &keyword) const;
};

#endif
