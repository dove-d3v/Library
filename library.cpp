#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// Class representing a book
class Book {
private:
  // Unique identifier for the book
  int id;
  // Title of the book
  std::string title;
  // Author of the book
  std::string author;
  // Status of whether the book is issued
  bool isIssued;

public:
  // Constructor to initialize book details
  Book(std::string title, std::string author, int id)
      : title(title), author(author), id(id), isIssued(false) {}

  // Getter methods to retrieve book information
  std::string getTitle() { return title; }
  std::string getAuthor() { return author; }
  int getId() { return id; }

  // Check if the book is available
  bool isAvailable() { return !isIssued; }

  // Mark the book as issued
  void issueBook() {
    if (isAvailable()) {
      isIssued = true;
    }
  }

  // Mark the book as returned
  void returnBook() { isIssued = false; }
};

// Class representing a student
class Student {
public:
  // Constructor to initialize student details
  Student(std::string name, int id) : name(name), id(id) {}

  // Method to issue a book to the student
  void issueBook(Book book) {
    if (book.isAvailable()) {
      book.issueBook();            // Issue the book if available
      issuedBooks.push_back(book); // Keep track of the issued book
      std::cout << "Book issued: " << book.getTitle() << " to " << name
                << std::endl;
    } else {
      std::cout << "No copies available for: " << book.getTitle() << std::endl;
    }
  }

  // Method to return a book
  void returnBook() {
    viewIssuedBook(); // Display currently issued books
    if (!issuedBooks.empty()) {
      std::cout << "Enter book Id to return: ";
      int bId;
      std::cin >> bId;
      issuedBooks[bId].returnBook(); // Return the selected book
    } else {
      std::cout << "No book issued to return." << std::endl;
    }
  }

  // Method to view all issued books
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
  // Name of the student
  std::string name;
  // Unique identifier for the student
  int id;
  // List of books issued to the student
  std::vector<Book> issuedBooks;
};

// Class representing the library
class Library {
public:
  // Method to add a book to the library
  void addBook(Book book) { books.push_back(book); }

  // Method to display all available books in the library
  void displayBooks() {
    std::cout << "\nAvailable Books:\n";
    std::cout << std::setw(5) << std::left << "ID" << std::setw(30) << std::left
              << "Title" << std::setw(25) << std::left << "Author"
              << std::setw(15) << std::left << "Available" << std::endl;
    std::cout << std::string(75, '-') << std::endl;

    // Loop through books to display their details
    for (auto &book : books) {
      std::cout << std::setw(5) << book.getId() << std::setw(30)
                << book.getTitle() << std::setw(25) << book.getAuthor()
                << std::setw(15) << (book.isAvailable() ? "Yes" : "No")
                << std::endl;
    }
  }

  // Method to find a book by its ID
  Book findBookById(int id) {
    for (auto &book : books) {
      if (book.getId() == id) {
        return book; // Return the found book
      }
    }
    return books[0]; // Return the first book if not found (could be improved)
  }

private:
  // List of books in the library
  std::vector<Book> books;
};

// Function to display the menu options
void showMenu() {
  std::cout << "\nLibrary Management System\n";
  std::cout << "1. Add Book\n";
  std::cout << "2. View Books\n";
  std::cout << "3. Issue Book\n";
  std::cout << "4. Return Book\n";
  std::cout << "5. View Issued Book\n";
  std::cout << "6. Exit\n";
}

// Main function
int main() {
  // Create a library object
  Library library;
  // Create a student object
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

  // Variable to store user choice
  int choice;
  do {
    showMenu(); // Display the menu
    std::cout << "Select an action: ";
    std::cin >> choice; // Get user choice

    // Switch case for handling user actions
    switch (choice) {
    case 1: {
      std::string title, author;
      int id;
      std::cout << "Enter Book Title: ";
      std::cin.ignore();             // Clear input buffer
      std::getline(std::cin, title); // Get book title
      std::cout << "Enter Book Author: ";
      std::getline(std::cin, author); // Get book author
      std::cout << "Enter Book ID: ";
      std::cin >> id;                           // Get book ID
      library.addBook(Book(title, author, id)); // Add book to library
      break;
    }
    case 2:
      library.displayBooks(); // Display all books
      break;
    case 3: {
      int bookId;
      std::cout << "Enter Book ID to issue: ";
      std::cin >> bookId;                       // Get book ID to issue
      Book book = library.findBookById(bookId); // Find book by ID
      if (book.isAvailable()) {
        student.issueBook(book); // Issue book to student
      } else {
        std::cout << "Book not found.\n"; // Handle book not found
      }
      break;
    }
    case 4:
      student.returnBook(); // Return a book
      break;
    case 5:
      student.viewIssuedBook(); // View issued books
      break;
    case 6:
      std::cout << "Exiting the program.\n"; // Exit message
      break;
    default:
      std::cout
          << "Invalid choice. Please try again.\n"; // Handle invalid choice
    }
  } while (choice != 6); // Repeat until exit is chosen

  return 0; // End of program
}
