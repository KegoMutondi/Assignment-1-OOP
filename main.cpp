#include <iostream>
#include "Library.h"
#include "Book.h"
#include "User.h"

int main() {
    Library lib;
    lib.addBook(Book(1,"C++ Primer","Lippman","9780321714114",2012), 2);
    lib.addBook(Book(2,"Effective Modern C++","Scott Meyers","9781491903995",2014), 1);

    lib.addUser(User(100, "Alice"));
    lib.addUser(User(101, "Bob"));

    auto r = lib.borrowBook(100, 1);
    std::cout << "Borrow attempt for Alice book 1 => " << (r==Library::BorrowResult::SUCCESS ? "OK" : "FAIL") << std::endl;
    std::cout << "Available copies of book1: " << lib.availableCopies(1) << "\n";

    auto s = lib.searchByAuthor("Meyers");
    std::cout << "Search by author 'Meyers' found: " << s.size() << " book(s)\n";

    return 0;
}
