#include "User.h"
#include <algorithm>

User::User(int id, const std::string& name)
    : id_(id), name_(name) {}

int User::id() const { return id_; }
const std::string& User::name() const { return name_; }

bool User::borrowBook(int bookId) {
    if (borrowed_book_ids_.size() >= borrow_limit_) return false;
    if (hasBorrowed(bookId)) return false;
    borrowed_book_ids_.push_back(bookId);
    return true;
}

bool User::returnBook(int bookId) {
    auto it = std::find(borrowed_book_ids_.begin(), borrowed_book_ids_.end(), bookId);
    if (it == borrowed_book_ids_.end()) return false;
    borrowed_book_ids_.erase(it);
    return true;
}

bool User::hasBorrowed(int bookId) const {
    return std::find(borrowed_book_ids_.begin(), borrowed_book_ids_.end(), bookId) != borrowed_book_ids_.end();
}

const std::vector<int>& User::borrowedBooks() const { return borrowed_book_ids_; }
size_t User::borrowLimit() const { return borrow_limit_; }
