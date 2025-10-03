#include <cassert>
#include <iostream>
#include "Library.h"
#include "Book.h"
#include "User.h"

void test_add_and_search() {
    Library lib;
    Book b1(1,"The C++ Programming Language","Bjarne Stroustrup","ISBN-1",2013);
    Book b2(2,"Clean Code","Robert Martin","ISBN-2",2008);
    lib.addBook(b1, 3);
    lib.addBook(b2, 1);

    auto byTitle = lib.searchByTitle("C++");
    assert(byTitle.size() == 1);
    auto byAuthor = lib.searchByAuthor("martin");
    assert(byAuthor.size() == 1);
    auto byIsbn = lib.searchByISBN("ISBN-1");
    assert(byIsbn.has_value());
    assert(lib.availableCopies(1) == 3);
}

void test_user_and_borrow_return() {
    Library lib;
    Book b1(1,"Intro to Algorithms","CLRS","ISBN-CLRS",2009);
    lib.addBook(b1, 2);

    lib.addUser(User(10, "Carol"));
    lib.addUser(User(11, "Dave"));

    // borrow success
    auto r = lib.borrowBook(10, 1);
    assert(r == Library::BorrowResult::SUCCESS);
    assert(lib.availableCopies(1) == 1);

    // borrow by same user again should fail (already borrowed)
    auto r2 = lib.borrowBook(10, 1);
    assert(r2 == Library::BorrowResult::ALREADY_BORROWED);

    // another user borrows the last copy
    auto r3 = lib.borrowBook(11, 1);
    assert(r3 == Library::BorrowResult::SUCCESS);
    assert(lib.availableCopies(1) == 0);

    // no copies left
    auto r4 = lib.borrowBook(10, 1); // user10 already has but even if not should be NO_COPIES
    assert(r4 == Library::BorrowResult::ALREADY_BORROWED || r4 == Library::BorrowResult::NO_COPIES);

    // return
    auto ret = lib.returnBook(10, 1);
    assert(ret == Library::ReturnResult::SUCCESS);
    assert(lib.availableCopies(1) == 1);

    // return not borrowed
    auto ret2 = lib.returnBook(10, 1);
    assert(ret2 == Library::ReturnResult::NOT_BORROWED);
}

void test_remove_book_and_user_constraints() {
    Library lib;
    Book b1(1,"Test Book","Author","ISBN-T",2000);
    lib.addBook(b1,1);
    lib.addUser(User(1,"U1"));

    // borrow book
    auto r = lib.borrowBook(1,1);
    assert(r == Library::BorrowResult::SUCCESS);

    // cannot remove book while borrowed
    bool removed = lib.removeBook(1);
    assert(!removed);

    // return then remove
    auto ret = lib.returnBook(1,1);
    assert(ret == Library::ReturnResult::SUCCESS);
    removed = lib.removeBook(1);
    assert(removed);

    // user removal: user has no borrows, can remove
    bool uremoved = lib.removeUser(1);
    assert(uremoved);
}

void test_user_borrow_limit() {
    Library lib;
    // add a user
    lib.addUser(User(50, "LimitUser"));
    // add many books
    for (int i=1;i<=10;i++) {
        lib.addBook(Book(i, "B"+std::to_string(i),"A","ISBN"+std::to_string(i),2000+i), 1);
    }
    // borrow up to limit (default 5)
    for (int i=1;i<=5;i++) {
        auto r = lib.borrowBook(50, i);
        assert(r == Library::BorrowResult::SUCCESS);
    }
    // next borrow should fail due to limit
    auto r = lib.borrowBook(50, 6);
    assert(r == Library::BorrowResult::USER_LIMIT_REACHED);
}

int main() {
    std::cout << "Running tests...\n";
    test_add_and_search();
    test_user_and_borrow_return();
    test_remove_book_and_user_constraints();
    test_user_borrow_limit();
    std::cout << "All tests passed ✅\n";
    return 0;
}
