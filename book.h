#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:
    int id_;                // internal unique id
    std::string title_;
    std::string author_;
    std::string isbn_;
    int year_;

public:
    Book() = default;
    Book(int id, const std::string& title, const std::string& author,
         const std::string& isbn, int year);

    int id() const;
    const std::string& title() const;
    const std::string& author() const;
    const std::string& isbn() const;
    int year() const;

    // Equality by id
    bool operator==(const Book& other) const;
};

#endif // BOOK_H
