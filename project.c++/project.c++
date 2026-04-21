#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Book
{
public:
    int id;
    char name[30];
    char author[30];
    int qty;

    void getBook()
    {
        cout<<"\nEnter Book ID : ";
        cin>>id;
        cout<<"Enter Book Name : ";
        cin>>name;
        cout<<"Enter Author Name : ";
        cin>>author;
        cout<<"Enter Quantity : ";
        cin>>qty;
    }

    void showBook()
    {
        cout<<setw(10)<<id<<setw(15)<<name<<setw(15)<<author<<setw(10)<<qty<<endl;
    }
};

void addBook()
{
    Book b;
    fstream file;
    file.open("library.txt", ios::out | ios::app | ios::binary);
    b.getBook();
    file.write((char*)&b, sizeof(b));
    file.close();
    cout<<"\nBook Added Successfully!";
}

void displayBooks()
{
    Book b;
    fstream file("library.txt", ios::in | ios::binary);
    if(!file)
    {
        cout<<"\nFile not found!";
        return;
    }
    cout<<"\n--- BOOK RECORDS ---\n";
    cout<<setw(10)<<"ID"<<setw(15)<<"Name"<<setw(15)<<"Author"<<setw(10)<<"Qty"<<endl;
    while(file.read((char*)&b, sizeof(b)))
    {
        b.showBook();
    }
    file.close();
}

void searchBook()
{
    int sid, flag=0;
    Book b;
    cout<<"\nEnter Book ID to search: ";
    cin>>sid;
    fstream file("library.txt", ios::in | ios::binary);
    while(file.read((char*)&b, sizeof(b)))
    {
        if(b.id==sid)
        {
            cout<<"\nBook Found:\n";
            b.showBook();
            flag=1;
            break;
        }
    }
    file.close();
    if(flag==0) cout<<"\nNo Book Found!";
}

void deleteBook()
{
    int did;
    cout<<"\nEnter Book ID to delete: ";
    cin>>did;

    Book b;
    fstream file("library.txt", ios::in | ios::binary);
    fstream temp("temp.txt", ios::out | ios::binary);

    while(file.read((char*)&b, sizeof(b)))
    {
        if(b.id!=did)
            temp.write((char*)&b, sizeof(b));
    }
    file.close();
    temp.close();

    remove("library.txt");
    rename("temp.txt","library.txt");

    cout<<"\nBook Deleted Successfully!";
}

int main()
{
    int ch;
    while(1)
    {
        cout<<"\n\n===== Library Management System =====";
        cout<<"\n1. Add Book";
        cout<<"\n2. Display Books";
        cout<<"\n3. Search Book";
        cout<<"\n4. Delete Book";
        cout<<"\n5. Exit";
        cout<<"\nEnter choice: ";
        cin>>ch;

        switch(ch)
        {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: return 0;
            default: cout<<"\nInvalid Choice!";
        }
    }
}
