#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std; // namespace std 사용

class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {
    }
};

class BookManager {
private:
    vector<Book> books; // 책 목록 저장

    // 찾기
    Book* findBookByTitle(const string& title)
    {
        for (auto& b : books)
        {
            if (b.title == title)
            {
                return &b;
            }
            else
            {                
                return nullptr;
            }
        }
    }

    Book* findBookByAuthor(const string& author)
    {
        for (auto& b : books)
        {
            if (b.author == author)
            {
                return &b;
            }
            else
            {
                return nullptr;
            }
        }
    }
public:
    // 책 추가 메서드
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author)); // push_back 사용
        
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;

    }

    // 모든 책 출력 메서드
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (size_t i = 0; i < books.size(); i++) { // 일반적인 for문 사용
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }

    //// 책 제목 검색 메서드
    //void searchByTitle(const string& title)
    //{
    //    cout << "책 제목으로 검색한 결과 :" << endl;
    //    for (const auto& book : books)
    //    {
    //        if (book.title == title)
    //        {
    //            cout << "- " << book.title << " by " << book.author << endl;
    //            return;
    //        }
    //    }
    //    cout << "검색 결과가 없습니다." << endl;   
    //}
    //
    //// 책 저자 검색 메서드
    //void searchByAuthor(const string& author)
    //{
    //    cout << "책 저자로 검색한 결과 :" << endl;
    //    for (const auto& book : books)
    //    {
    //        if (book.author == author)
    //        {
    //            cout << "- " << book.title << " by " << book.author << endl;
    //            return;
    //        }
    //    }
    //    cout << "검색 결과가 없습니다." << endl;
    //    
    //}

    // 얻기
    Book* getBookByTitle(const string& title)
    {
        Book* book = findBookByTitle(title);

        return book;
    }

    Book* getBookByAuthor(const string& author)
    {
        Book* book = findBookByAuthor(author);

        return book;
    }

   
};

class BorrowManager
{
private:
    unordered_map<string, int> stock;

public:
    void initializeStock(Book book, int quantity = 3)
    {
        stock[book.title] = quantity;
    }

    // 책 빌리기
    void borrowBook(const string& title)
    {
        if(stock.find(title) != stock.end())
        {
            if (stock[title] > 0)
            {
                stock[title]--;
                cout << title << " 책을 빌렸습니다." << endl;
                cout << "현재 책 남은 재고 : " << stock[title] << endl;
            }
            else
            {
                cout << "현재 책 재고가 없습니다." << endl;
            }
        }
    }

    // 책 반납하기
    void returnBook(const string& title)
    {
        if (stock.find(title) != stock.end())
        {
            if (stock[title] < 3)
            {
                stock[title]++;
                cout << title << " 책을 반납했습니다." << endl;
            }
            else
            {
                cout << "반납할 책이 없습니다." << endl;
            }
        }            
        else
        {
            cout << "해당 책은 존재하지 않습니다." << endl;
        }
    }

    // 현재 책 재고 현황
    void displayStock()
    {
        cout << "현재 책 재고 현황:" << endl;
        for (auto s : stock)
        {
            cout << "- " << s.first << " | 재고 : " << s.second << endl;
        }
    }

};

int main() {
    BookManager bookmanager;
    BorrowManager borrowManager;

    // 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
    // 프로그램 종료를 선택하기 전까지 계속 동작합니다.
    while (true) {
        system("cls");

        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
        cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력
        cout << "3. 책 제목으로 검색" << endl; // 검색할 책 제목 검색
        cout << "4. 책 저자로 검색" << endl; // 검색할 책 저자 검색
        cout << "5. 책 대여" << endl; // 책 대여
        cout << "6. 책 반납" << endl; // 책 반납
        cout << "7. 책 대여 현황" << endl; // 책 대여 현황 출력
        cout << "8. 종료" << endl; // 프로그램 종료
        cout << "선택: ";

        int choice; // 사용자의 메뉴 선택을 저장
        cin >> choice;

        if (choice == 1) {
            // 1번 선택: 책 추가
            // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
            string title, author;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            cout << "책 저자: ";
            getline(cin, author); // 저자명 입력 (공백 포함)
            bookmanager.addBook(title, author); // 입력받은 책 정보를 추가
            Book* book = bookmanager.getBookByTitle(title);
            borrowManager.initializeStock(*book);
        }
        else if (choice == 2) {
            // 2번 선택: 모든 책 출력
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
            bookmanager.displayAllBooks();
        }
        else if (choice == 3)
        {
            // 3번 선택 : 책 제목으로 검색
            // 사용자로부터 책 제목을 입력받아 책 정보 검색한다.
            string title;
            cout << "검색할 책 제목 : ";
            cin.ignore();   // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title);    // 제목 입력 (공백 포함)
            //bookmanager.searchByTitle(title);   // 입력받은 책 제목 검색
            Book* book = bookmanager.getBookByTitle(title);
            cout << "책 제목으로 검색한 결과 :" << endl;
            if (book)
            {
                cout << book->title << " by " << book->author << endl;
            }
            else
            {
                cout << "검색 결과가 없습니다." << endl;
            }
            
        }
        else if (choice == 4)
        {
            // 4번 선택 : 책 저자 검색
            // 사용자로부터 책 저자를 입력받아 책 정보 검색한다.
            string author;
            cout << "검색할 책 저자 : ";
            cin.ignore();   // 이전 입력의 잔여 버퍼를 제거
            getline(cin, author);    // 저자 입력 (공백 포함)
            //bookmanager.searchByAuthor(author);   // 입력받은 책 저자 검색
            Book* book = bookmanager.getBookByAuthor(author);
            cout << "책 저자로 검색한 결과 :" << endl;
            if (book)
            {
                cout << book->title << " by " << book->author << endl;
            }
            else
            {
                cout << "검색 결과가 없습니다." << endl;
            }
        }
        else if (choice == 5)
        {
            // 5번 선택 : 책 대여
            // 사용자로부터 대여할 책 제목 또는 저자을 받아 책을 대여한다,
            int num;
            cout << "대여 여부 (1 : 책의 이름, 2 : 책의 저자)" << endl;
            cin.ignore();   // 이전 입력의 잔여 버퍼를 제거
            cin >> num;
            switch (num)
            {
            case 1:
            {
                // 책 제목으로 대여하기
                string title;
                cout << "대여할 책 제목 : ";
                cin.ignore();   // 이전 입력의 잔여 버퍼를 제거
                getline(cin, title);    // 대여할 책 제목 입력 (공백 포함)
                Book* book = bookmanager.getBookByTitle(title);
                if (book)
                {
                    borrowManager.borrowBook(book->title);
                }
                else
                {
                    cout << "존재하지 않는 책입니다." << endl;
                }
                break;
            }                
            case 2:
            {
                // 책 저자로 대여하기
                string author;
                cout << "대여할 책 제목 : ";
                cin.ignore();   // 이전 입력의 잔여 버퍼를 제거
                getline(cin, author);    // 대여할 책 제목 입력 (공백 포함)
                Book* book = bookmanager.getBookByAuthor(author);
                if (book)
                {
                    borrowManager.borrowBook(book->title);
                }
                else
                {
                    cout << "존재하지 않는 책입니다." << endl;
                }
                break;
            }
            default:
                cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
                break;
            }
            
        }
        else if (choice == 6)
        {
            // 6번 선택 : 책 반납
            // 사용자로부터 반납할 책 제목을 받아 책을 반납한다.
            string title;
            cout << "반납할 책 제목 : ";
            cin.ignore();   // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title);    // 대여할 책 제목 입력 (공백 포함)
            borrowManager.returnBook(title);
        }
        else if (choice == 7)
        {
            // 7번 선택 : 현재 책들에 대여 상태
            // 현재 책 대여 상태를 출력한다.
            borrowManager.displayStock();
        }
        else if (choice == 8) {
            // 5번 선택: 종료
            // 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
            cout << "프로그램을 종료합니다." << endl;
            break; // while 루프 종료
        }
        else {
            // 잘못된 입력 처리
            // 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }

        system("pause");

    }

    return 0; // 프로그램 정상 종료
}
