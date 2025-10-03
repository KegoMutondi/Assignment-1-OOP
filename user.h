#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
private:
    int id_;
    std::string name_;
    std::vector<int> borrowed_book_ids_;
    size_t borrow_limit_ = 5; // default borrowing limit

public:
    User() = default;
    User(int id, const std::string& name);

    int id() const;
    const std::string& name() const;

    // borrow/return tracking (library will call these)
    bool borrowBook(int bookId);
    bool returnBook(int bookId);
    bool hasBorrowed(int bookId) const;
    const std::vector<int>& borrowedBooks() const;
    size_t borrowLimit() const;
};

#endif // USER_H
