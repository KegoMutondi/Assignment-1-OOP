#include "Library.h"
#include <algorithm>
#include <cctype>

bool Library::addBook(const Book& book, int copies) {
    if (copies <= 0) return false;
    int id = book.id();
    auto it = books_.find(id);
    if (it == books_.end()) {
        books_.emplace(id, book);
        inventory_[id] = copies;
        total_copies_[id] = copies;
    } else {
        inventory_[id] += copies;
        total_copies_[id] += copies;
    }
    return true;
}

bool Library::removeBook(int bookId) {
    // allow removal only if book exists and available copies == total copies (no outstanding borrows)
    auto tIt = total_copies_.find(bookId);
    auto iIt = inventory_.find(bookId);
    if (tIt == total_copies_.end() || iIt == inventory_.end()) return false;
    if (tIt->second != iIt->second) return false; // some copies are borrowed
    // erase
    books_.erase(bookId);
    inventory_.erase(bookId);
    total_copies_.erase(bookId);
    return true;
}

std::optional<Book> Library::getBook(int bookId) const {
    auto it = books_.find(bookId);
    if (it == books_.end()) return std::nullopt;
    return it->second;
}

// helper lowercase
static std::string lower(const std::string& s) {
    std::string out = s;
    for (char &c : out) c = (char)std::tolower(c);
    return out;
}

std::vector<Book> Library::searchByTitle(const std::string& titlePart) const {
    std::vector<Book> res;
    std::string key = lower(titlePart);
    for (const auto& p : books_) {
        if (lower(p.second.title()).find(key) != std::string::npos) res.push_back(p.second);
    }
    return res;
}

std::vector<Book> Library::searchByAuthor(const std::string& authorPart) const {
    std::vector<Book> res;
    std::string key = lower(authorPart);
    for (const auto& p : books_) {
        if (lower(p.second.author()).find(key) != std::string::npos) res.push_back(p.second);
    }
    return res;
}

std::optional<Book> Library::searchByISBN(const std::string& isbn) const {
    std::string key = isbn;
    for (const auto& p : books_) {
        if (p.second.isbn() == key) return p.second;
    }
    return std::nullopt;
}

bool Library::addUser(const User& user) {
    int id = user.id();
    if (users_.find(id) != users_.end()) return false;
    users_.emplace(id, user);
    return true;
}

bool Library::removeUser(int userId) {
    auto it = users_.find(userId);
    if (it == users_.end()) return false;
    if (!it->second.borrowedBooks().empty()) return false;
    users_.erase(it);
    return true;
}

Library::BorrowResult Library::borrowBook(int userId, int bookId) {
    auto uIt = users_.find(userId);
    if (uIt == users_.end()) return BorrowResult::USER_NOT_FOUND;
    auto bIt = books_.find(bookId);
    if (bIt == books_.end()) return BorrowResult::BOOK_NOT_FOUND;
    auto invIt = inventory_.find(bookId);
    if (invIt == inventory_.end() || invIt->second <= 0) return BorrowResult::NO_COPIES;
    // check user constraints
    User& user = uIt->second;
    if (user.hasBorrowed(bookId)) return BorrowResult::ALREADY_BORROWED;
    if (user.borrowedBooks().size() >= user.borrowLimit()) return BorrowResult::USER_LIMIT_REACHED;
    // perform
    bool ok = user.borrowBook(bookId);
    if (!ok) return BorrowResult::USER_LIMIT_REACHED;
    invIt->second -= 1;
    return BorrowResult::SUCCESS;
}

Library::ReturnResult Library::returnBook(int userId, int bookId) {
    auto uIt = users_.find(userId);
    if (uIt == users_.end()) return ReturnResult::USER_NOT_FOUND;
    auto bIt = books_.find(bookId);
    if (bIt == books_.end()) return ReturnResult::BOOK_NOT_FOUND;
    User& user = uIt->second;
    if (!user.hasBorrowed(bookId)) return ReturnResult::NOT_BORROWED;
    bool ok = user.returnBook(bookId);
    if (!ok) return ReturnResult::NOT_BORROWED;
    inventory_[bookId] += 1;
    return ReturnResult::SUCCESS;
}

int Library::availableCopies(int bookId) const {
    auto it = inventory_.find(bookId);
    if (it == inventory_.end()) return 0;
    return it->second;
}

std::vector<Book> Library::listAllBooks() const {
    std::vector<Book> out;
    for (const auto& p : books_) out.push_back(p.second);
    return out;
}

std::vector<User> Library::listAllUsers() const {
    std::vector<User> out;
    for (const auto& p : users_) out.push_back(p.second);
    return out;
}
