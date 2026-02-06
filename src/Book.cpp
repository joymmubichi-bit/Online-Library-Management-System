#include "Book.h"
#include <iostream>
#include <cctype>

Book::Book(std::string isbn, std::string title, std::string author,
           std::string genre, int year)
    : ISBN(isbn), title(title), author(author),
      genre(genre), publicationYear(year),
      isAvailable(true), borrowedBy("") {}

std::string Book::getISBN() const { return ISBN; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
std::string Book::getGenre() const { return genre; }
int Book::getPublicationYear() const { return publicationYear; }
bool Book::getAvailability() const { return isAvailable; }
std::string Book::getBorrowedBy() const { return borrowedBy; }

void Book::setAvailability(bool available) { isAvailable = available; }
void Book::setBorrowedBy(std::string userId) { borrowedBy = userId; }

void Book::displayInfo() const
{
    std::cout << "ISBN: " << ISBN << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "Genre: " << genre << std::endl;
    std::cout << "Year: " << publicationYear << std::endl;
    std::cout << "Status: " << (isAvailable ? "Available" : "Borrowed by User ID: " + borrowedBy) << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

bool Book::matchesSearch(const std::string &keyword) const
{
    std::string lowerKeyword = "";
    for (char c : keyword)
        lowerKeyword += tolower(c);

    std::string lowerTitle = "";
    for (char c : title)
        lowerTitle += tolower(c);

    std::string lowerAuthor = "";
    for (char c : author)
        lowerAuthor += tolower(c);

    std::string lowerGenre = "";
    for (char c : genre)
        lowerGenre += tolower(c);

    std::string lowerISBN = "";
    for (char c : ISBN)
        lowerISBN += tolower(c);

    return (lowerTitle.find(lowerKeyword) != std::string::npos ||
            lowerAuthor.find(lowerKeyword) != std::string::npos ||
            lowerGenre.find(lowerKeyword) != std::string::npos ||
            lowerISBN.find(lowerKeyword) != std::string::npos);
}
