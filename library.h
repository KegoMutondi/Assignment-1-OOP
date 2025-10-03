#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "User.h"
#include <map>
#include <vector>
#include <optional>
#include <string>

class Library {
private:
    // store book metadata
    std::map<int, Book> books_;      // id -> Book
    std::map<int, int> inventory_;   // id -> copies available (total currently available)
    std::map<int, int> total_copies_; // id -> total copies originally added

    // users
    std::map<int, User> users_;      // userId -> User

public:
    Library() = default;

    // Book management
    bool addBook(const Book& book, int copies = 1); // adds or increments
    bool removeBook(int bookId); // only if no outstanding borrows and exists
    std::optional<Book> getBook(int bookId) const;

    // Search
    std::vector<Book> searchByTitle(const std::string& titlePart) const;
    std::vector<Book> searchByAuthor(const std::string& authorPart) const;
    std::optional<Book> searchByISBN(const std::string& isbn) const;

    // User management
    bool addUser(const User& user);
    bool removeUser(int userId); // only if user has no borrowed books

    // Borrow/Return
    enum class BorrowResult { SUCCESS, NO_COPIES, USER_NOT_FOUND, BOOK_NOT_FOUND, USER_LIMIT_REACHED, ALREADY_BORROWED };
    BorrowResult borrowBook(int userId, int bookId);
    enum class ReturnResult { SUCCESS, USER_NOT_FOUND, BOOK_NOT_FOUND, NOT_BORROWED };
    ReturnResult returnBook(int userId, int bookId);

    // Utilities
    int availableCopies(int bookId) const;
    std::vector<Book> listAllBooks() const;
    std::vector<User> listAllUsers() const;
};

#endif // LIBRARY_H
