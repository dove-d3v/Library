#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class Book {
private:
  int id;
  std::string title;
  std::string author;
  bool isIssued;

public:
  Book(std::string title, std::string author, int id)
      : title(title), author(author), id(id), isIssued(false) {}

  std::string getTitle() { return title; }
  std::string getAuthor() { return author; }
  int getId() { return id; }
  bool isAvailable() { return !isIssued; }

  void issueBook() {
    if (isAvailable()) {
      isIssued = true;
    }
  }

  void returnBook() { isIssued = false; }
};

class Student {
public:
  Student(std::string name, int id) : name(name), id(id) {}

  void issueBook(Book book) {
    if (book.isAvailable()) {
      book.issueBook();
      issuedBooks.push_back(book); // Keep track of the issued book
      std::cout << "Book issued: " << book.getTitle() << " to " << name
                << std::endl;
    } else {
      std::cout << "No copies available for: " << book.getTitle() << std::endl;
    }
  }

  void returnBook() {
    viewIssuedBook();
    if (!issuedBooks.empty()) {
      std::cout << "Enter book Id to return :";
      int bId;
      std::cin >> bId;
      issuedBooks[bId].returnBook();
    } else {
      std::cout << "No book issued to return." << std::endl;
    }
  }

  void viewIssuedBook() {
    if (!issuedBooks.empty()) {
      std::cout << std::setw(5) << std::left << "ID" << std::setw(30)
                << std::left << "Title" << std::setw(25) << std::left
                << "Author" << std::setw(15) << std::endl;
      for (auto &book : issuedBooks) {
        std::cout << std::setw(5) << book.getId() << std::setw(30)
                  << book.getTitle() << std::setw(25) << book.getAuthor()
                  << std::endl;
      }
    } else {
      std::cout << "No book currently issued." << std::endl;
    }
  }

private:
  std::string name;
  int id;
  std::vector<Book> issuedBooks; // Pointer to the issued book
};

class Library {
public:
  void addBook(Book book) { books.push_back(book); }

  void displayBooks() {
    std::cout << "\nAvailable Books:\n";
    std::cout << std::setw(5) << std::left << "ID" << std::setw(30) << std::left
              << "Title" << std::setw(25) << std::left << "Author"
              << std::setw(15) << std::left << "Available" << std::endl;
    std::cout << std::string(75, '-') << std::endl;

    for (auto &book : books) {
      std::cout << std::setw(5) << book.getId() << std::setw(30)
                << book.getTitle() << std::setw(25) << book.getAuthor()
                << std::setw(15) << (book.isAvailable() ? "Yes" : "No")
                << std::endl;
    }
  }

  Book findBookById(int id) {
    for (auto &book : books) {
      if (book.getId() == id) {
        return book;
      }
    }
    return books[0];
  }

private:
  std::vector<Book> books;
};

void showMenu() {
  std::cout << "\nLibrary Management System\n";
  std::cout << "1. Add Book\n";
  std::cout << "2. View Books\n";
  std::cout << "3. Issue Book\n";
  std::cout << "4. Return Book\n";
  std::cout << "5. View Issued Book\n";
  std::cout << "6. Exit\n";
}

int main() {
  Library library;
  Student student("Soumitra Yadav", 101);

  // Adding initial books to the library
  library.addBook(Book("Harry Potter & the Sorcerer", "J.K. Rowling", 1));
  library.addBook(Book("The Hobbit", "J.R.R. Tolkien", 2));
  library.addBook(Book("Charlotte's Web", "E.B. White", 3));
  library.addBook(Book("Matilda", "Roald Dahl", 4));
  library.addBook(Book("The Cat in the Hat", "Dr. Seuss", 5));
  library.addBook(Book("Where the Red Fern Grows", "Wilson Rawls", 6));
  library.addBook(Book("The Secret Garden", "Frances Hodgson Burnett", 7));
  library.addBook(Book("Pippi Longstocking", "Astrid Lindgren", 8));
  library.addBook(Book("Anne of Green Gables", "L.M. Montgomery", 9));
  library.addBook(Book("The Chronicles of Narnia", "C.S. Lewis", 10));

  int choice;
  do {
    std::cin.get();
    showMenu();
    std::cout << "Select an action: ";
    std::cin >> choice;

    switch (choice) {
    case 1: {
      std::string title, author;
      int id;
      std::cout << "Enter Book Title: ";
      std::cin.ignore(); // Clear input buffer
      std::getline(std::cin, title);
      std::cout << "Enter Book Author: ";
      std::getline(std::cin, author);
      std::cout << "Enter Book ID: ";
      std::cin >> id;
      library.addBook(Book(title, author, id));
      break;
    }
    case 2:
      library.displayBooks();
      break;
    case 3: {
      int bookId;
      std::cout << "Enter Book ID to issue: ";
      std::cin >> bookId;
      Book book = library.findBookById(bookId);
      if (book.isAvailable()) {
        student.issueBook(book);
      } else {
        std::cout << "Book not found.\n";
      }
      break;
    }
    case 4:
      student.returnBook();
      break;
    case 5:
      student.viewIssuedBook();
      break;
    case 6:
      std::cout << "Exiting the program.\n";
      break;
    default:
      std::cout << "Invalid choice. Please try again.\n";
    }
  } while (choice != 6);

  return 0;
}

