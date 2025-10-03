#include "Book.h"

Book::Book(int id, const std::string& title, const std::string& author,
           const std::string& isbn, int year)
    : id_(id), title_(title), author_(author), isbn_(isbn), year_(year) {}

int Book::id() const { return id_; }
const std::string& Book::title() const { return title_; }
const std::string& Book::author() const { return author_; }
const std::string& Book::isbn() const { return isbn_; }
int Book::year() const { return year_; }

bool Book::operator==(const Book& other) const {
    return id_ == other.id_;
}
