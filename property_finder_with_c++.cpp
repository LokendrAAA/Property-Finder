#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<windows.h>
#include<ctime>
#include<conio.h>
#include<ctype.h>
#include <sstream>
#include<iomanip>


using namespace std;
char type[][15]={"FLAT","PG","PENTHOUSE","VILLA","FARM HOUSE","PERSONAL SPACE"};
void addproperty(void);
void deleteproperty(void);
void editproperty(void);
void searchproperty(void);
void rentproperty(void);
void viewproperty(void);
void returntomenu(void);
void mainmenu(void);
void closeapplication(void);
int  getdata();
int  checkid(int);
int t(void);
void Password();
FILE *fp,*ft,*fs;
COORD coord = {0, 0};
int s;
char findprop;
char password[10]={"h"};
int phone2;


struct DMY {
    int dd, mm, yy;
};

struct property {
    int id;
    char stname[30];
    char stlocation[30];
    char name[30];
    char location[30];
    int rooms;
    int moor;
    float Price;
    int Count;
    int streetno;
    char* cat;
};
struct property a;


void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void addproperty() {

    system("cls");
    int i;
    gotoxy(2, 1);
    t(); // (for showing time and date)
    gotoxy(2, 3);
    cout << "SELECT CATEGORY" << endl;
    gotoxy(2, 5);
    cout << "1. FLAT" << endl;
    gotoxy(2, 7);
    cout << "2. PG" << endl;
    gotoxy(2, 9);
    cout << "3. PENTHOUSE" << endl;
    gotoxy(2, 11);
    cout << "4. VILLA" << endl;
    gotoxy(2, 13);
    cout << "5. FARM HOUSE" << endl;
    gotoxy(2, 15);
    cout << "6. PERSONAL SPACE" << endl;
    gotoxy(2, 17);
    cout << "7. Back to main menu" << endl;
    gotoxy(2, 19);
    cout << "Enter your choice: ";
    cin >> s;

    if (s == 7) {
        mainmenu();
    }

    system("cls");
   fstream file("prop.txt", ios::binary | ios::in | ios::app);
    if (getdata() == 1) {
        a.cat = type[s - 1];
        file.seekp(0, ios::end);
        file.write(reinterpret_cast<char*>(&a), sizeof(a));
       file.close();
        gotoxy(2, 25);
        cout << "The record is successfully saved" << endl;
        gotoxy(2, 27);
        cout << "Save any more? (Y/N): ";
        char choice = getch();
        if (choice == 'n' || choice == 'N') {
            mainmenu();
        }
        else if (choice == 'y' || choice == 'Y') {
            system("cls");
            addproperty();
        }
    }
}

void deleteproperty()
{
    system("cls");
    int d;
    char another = 'y';
    gotoxy(2, 1);
    t(); // (for showing time and date)

    while (another == 'y')
    {
        // system("cls");
        gotoxy(2, 3);
        cout << "Enter the property ID to delete: ";
        cin >> d;

        fstream file("prop.txt", ios::binary | ios::in | ios::out);
        if (!file)
        {
            cout << "Error opening file." << endl;
            return;
        }

        fstream tempFile("temp.dat", ios::binary | ios::in | ios::out | ios::trunc);
        if (!tempFile)
        {
            cout << "Error creating temporary file." << endl;
            file.close();
            return;
        }

        bool found = false;
        while (file.read(reinterpret_cast<char*>(&a), sizeof(a)))
        {
            if (a.id != d)
            {
                tempFile.write(reinterpret_cast<char*>(&a), sizeof(a));
            }
            else
            {
                found = true;
            }
        }

        file.close();
        tempFile.close();

        if (found)
        {
            remove("prop.txt");
            rename("temp.dat", "prop.txt");

            cout << "The record is successfully deleted." << endl;

             cout << "press enter to return to main menu." << endl;
        gotoxy(10, 13);
         getch();
        gotoxy(10, 15);
        mainmenu();
        }
        else
        {
            cout << "No such property found." << endl;
        }
        cout << "press enter to return to main menu." << endl;
        gotoxy(10, 13);
         getch();
        gotoxy(10, 15);
        mainmenu();
    }
}



void editproperty()
{
    system("cls");
    int c = 0;
    int d, e;
    gotoxy(2, 3);
    cout << "Edit property Section" << endl;
    char another = 'y';

    while (another == 'y')
    {
        system("cls");
        gotoxy(2, 1);
        t(); // (for showing time and date)
        gotoxy(2, 3);
        cout << "Enter property unique ID whose information to be edited: ";
        cin >> d;

        fstream file("prop.txt", ios::in | ios::out | ios::binary);

        if (!file)
        {
            cout << "Error opening file." << endl;
            return;
        }

        while (file.read(reinterpret_cast<char*>(&a), sizeof(a)))
        {
            if (checkid(d) == 0)
            {
                gotoxy(2, 5);
                cout << "The property is available" << endl;
                gotoxy(2, 7);
                cout << "The property ID: " << a.id << endl;
                gotoxy(2, 9);
                cout << "Enter new owner name: ";
                cin >> a.name;
                gotoxy(2, 11);
                cout << "Enter new location: ";
                cin >> a.location;
                gotoxy(2, 13);
                cout << "Enter no. of rooms: ";
                cin >> a.rooms;
                gotoxy(2, 15);
                cout << "Enter new price: ";
                cin >> a.Price;
                gotoxy(2, 16);
                cout << "Enter street no: ";
                cin >> a.streetno;
                gotoxy(2, 17);
                cout << "The property record is successfully modified" << endl;

                file.seekp(file.tellg() - sizeof(a));
                file.write(reinterpret_cast<char*>(&a), sizeof(a));

                c = 1;
            }
        }
        file.close();

        if (c == 0)
        {
            gotoxy(2, 5);
            cout << "No record found" << endl;
        }

        fflush(stdin);
        another = getch();
    }

    returntomenu();
}


void searchproperty()
{
    system("cls");
    gotoxy(2, 1);
    t(); //(for showing time and date)
    int d;
    gotoxy(2, 3);
    cout << "Search property";
    gotoxy(2, 5);
    cout << "1. Search By ID";
    gotoxy(2, 7);
    cout << "2. Search By owner Name";
    gotoxy(2, 9);
    cout << "3. Search By Location Name";
    gotoxy(2, 11);
    cout << "Enter Your Choice";

    fstream file("prop.txt", ios::binary | ios::in | ios::out);
    file.seekg(0, ios::beg);

    switch (getch())
    {
        case '1':
        {
            system("cls");
            gotoxy(2, 1);
            t();
            gotoxy(2, 3);
            cout << "Search property By Id";
            gotoxy(2, 5);
            cout << "Enter the property unq id:";
            cin >> d;
            while (file.read(reinterpret_cast<char*>(&a), sizeof(a)))
            {
                if (a.id == d)
                {
                    Sleep(2);
                    gotoxy(2, 8);
                    cout << "Property with ID is available";
                    gotoxy(2, 10);
                    cout << "ID: " << a.id;
                    gotoxy(2, 12);
                    cout << "Name: " << a.name;
                    gotoxy(2, 14);
                    cout << "Location: " << a.location;
                    gotoxy(2, 16);
                    cout << "Street No: " << a.streetno;
                    gotoxy(2, 18);
                    cout << "Rooms: " << a.rooms;
                    gotoxy(2, 20);
                    cout << "Price: Rs." << a.Price;
                    findprop = 't';
                }
            }
            if (findprop != 't')
            {
                gotoxy(2, 9);
                cout << "No such property Found";
            }
            break;
        }
        case '2':
        {
            char s[15];
            system("cls");
            gotoxy(2, 1);
            t();
            gotoxy(2, 3);
            cout << "Search By owner Name";
            gotoxy(2, 5);
            cout << "Enter owner Name:";
            cin >> s;
            int d = 0;
            while (file.read(reinterpret_cast<char*>(&a), sizeof(a)))
            {
                if (strcmp(a.name, s) == 0)
                {
                    gotoxy(2, 8);
                    cout << "Property with this owner name is available";
                    gotoxy(2, 10);
                    cout << "ID: " << a.id;
                    gotoxy(2, 12);
                    cout << "Name: " << a.name;
                    gotoxy(2, 14);
                    cout << "Location: " << a.location;
                    gotoxy(2, 16);
                    cout << "Street No: " << a.streetno;
                    gotoxy(2, 18);
                    cout << "Rooms: " << a.rooms;
                    gotoxy(2, 20);
                    cout << "Price: Rs." << a.Price;
                    d++;
                }
            }
            if (d == 0)
            {
                gotoxy(2, 7);
                cout<< "No such property Found";
}
break;
}
case '3':
{
    char s[15];
    system("cls");
    gotoxy(2,1);
    t();
    gotoxy(2,3);
    cout << "Search By LOCATION";
    gotoxy(2,5);
    cout << "Enter LOCATION:";
    cin >> s;
    int d = 0;
    while(file.read(reinterpret_cast<char*>(&a), sizeof(a)))
    {
        if(strcmp(a.location, s) == 0)
        {
            gotoxy(2,7 + (d * 6));
            cout << "Property " << d + 1 << " in this location is available";
            gotoxy(2,9 + (d * 6));
            cout << "ID:" << a.id;
            gotoxy(2,11 + (d * 6));
            cout << "Name:" << a.name;
            gotoxy(2,13 + (d * 6));
            cout << "Location:" << a.location;
            gotoxy(2,15 + (d * 6));
            cout << "Street No:" << a.streetno;
            gotoxy(2,17 + (d * 6));
            cout << "Rooms:" << a.rooms;
            gotoxy(2,19 + (d * 6));
            cout << "Price:Rs." << a.Price;
            d++;
        }
    }
    if(d == 0)
    {
        gotoxy(2,7);
        cout << "No such property Found";
    }
    gotoxy(2,7 + (d * 6) + 3);
    cout << "Try another search?(Y/N)";
    if(getch() == 'y')
        searchproperty();
    else
        mainmenu();
    break;
}
    }
    getch();
    mainmenu();
    }

void rentproperty()
{
    int w;
    system("cls");
    int c = 0;
    char another = 'y';
    while (another == 'y')
    {
        system("cls");
        gotoxy(2, 1);
        t();
        gotoxy(2, 4);
        cout << "RENT PROPERTY";
        gotoxy(10, 6);
        cout << "Enter the Property Id:";
        cin >> w;
        int u = w;
        fstream file("prop.txt", ios::binary | ios::in | ios::out);
        fstream issuefile("Issue.dat", ios::binary | ios::in | ios::app | ios::trunc);
        if (checkid(w) == 0)
        {
            gotoxy(10, 8);
            cout << "The PROPERTY is available";
            gotoxy(10, 9);
            cout << "There are " << a.rooms << " available rooms in this property ";
            gotoxy(10, 10);
            cout << "owner name is " << a.name;
            gotoxy(10, 11);
            cout << "Enter your name:";
            cin >> a.stname;
            gotoxy(10, 12);
            cout << "Enter your home location:";
            cin >> a.stlocation;
            gotoxy(10, 14);
            cout << "Enter mobile number: ";
            cin >> phone2;
            gotoxy(10, 16);
            cout << "Enter the number of rooms required:";
            int requiredRooms;
            gotoxy(45, 16);
            cin >> requiredRooms;
            if (requiredRooms > a.rooms)
            {
                gotoxy(10, 19);
                cout << "Only " << a.rooms << " rooms available";
                returntomenu();
            }
            if (requiredRooms <= a.rooms)
            {
                a.rooms = a.rooms - requiredRooms;
                gotoxy(10,19);
                cout <<"Rooms left :"<<a.rooms;


                file.close();

                ofstream outfile("prop.txt");

                if (!outfile) {
                    cout << "Error opening file." << endl;
                    return;
                }

                outfile.write(reinterpret_cast<char*>(&a), sizeof(a));

                outfile.close();

                c = 1;
            }
        }
        if (c == 0)
        {
            gotoxy(10, 11);
            cout << "No record found";
        }
        gotoxy(10, 20);
        cout << "RENT any more(Y/N):";
        if (getch() == 'n')
        {
            returntomenu();
        }
        else
        {
            rentproperty();
        }

        cin.ignore();
        another = getch();
    }
}


void viewproperty()
{
    int i = 0, j;
    system("cls");
    gotoxy(1, 1);
    cout << "                                                    PROPERTY LIST                                              ";
    gotoxy(2, 2);
    cout << " CATEGORY           ID           OWNER NAME           LOCATION           ROOMS          PRICE        STREET NO. ";
    j = 4;
    ifstream file("prop.txt", ios::binary);
    while (file.read(reinterpret_cast<char*>(&a), sizeof(a)))
    {
        gotoxy(3, j);
        cout << a.cat;
        gotoxy(21, j);
        cout << a.id;
        gotoxy(36, j);
        cout << a.name;
        gotoxy(57, j);
        cout << a.location;
        gotoxy(76, j);
        cout << a.rooms;
        gotoxy(89, j);
        cout << a.Price;
        gotoxy(105, j);
        cout << a.streetno;
        cout << "\n\n";
        j = j + 2;
        i = i + a.rooms;
    }
    file.close();
    returntomenu();
}


void returntomenu()
{
    {
        gotoxy(2, 25);
        cout << " Press ENTER to return to the main menu";
    }
a:
    if (getch() == 13)
        mainmenu();
    else
        goto a;
}

class Direct {
public:
    string own;
    int pri;
    string typ;


    void directFind() {
        system("cls");
        cout << "Direct finding" << endl;
        cout << "Enter owner name: ";
        cin >> own;

        ifstream inputFile("prop.txt");
        if (inputFile.is_open()) {
            string line;
            bool matchFound = false;
            while (getline(inputFile, line)) {
                if (line.find(own) != string::npos) {
                    cout << "Match found: " << line << endl;
                    matchFound = true;
                    string details = extractDetails(line);
                    cout << "Corresponding details: " << details << endl;
                }
            }
            if (!matchFound) {
                cout << "No matching properties found." << endl;
            }
            inputFile.close();
        } else {
            cout << "Unable to open prop.txt file." << endl;
        }
    }
 string extractDetails(const string& line) {
        stringstream ss;
        for (char c : line) {
            if (isprint(static_cast<unsigned char>(c))) {
                ss << c;
            } else {
                ss << "\\x" << setw(2) << setfill('0') << hex << static_cast<int>(c);
            }
        }
        return ss.str();
    }
};


void mainmenu()
{
    Direct obj;
    system("cls");

    int i;
    gotoxy(2, 1);
    t();
    gotoxy(2, 3);
    cout << "MAIN MENU";
    gotoxy(2, 5);
    cout << "1. Add property";
    gotoxy(2, 7);
    cout << "2. Delete property";
    gotoxy(2, 9);
    cout << "3. Search property";
    gotoxy(2, 11);
    cout << "4. Rent property";
    gotoxy(2, 13);
    cout << "5. View property list";
    gotoxy(2, 15);
    cout << "6. Edit property info";
    gotoxy(2, 17);
    cout << "7. Close Application";
    gotoxy(2, 19);
    cout<<"8.direct finding";
    gotoxy(2, 21);
    cout << "Enter your choice:";
    switch (getch())
    {
    case '1':
        addproperty();
        break;
    case '2':
        deleteproperty();
        break;
    case '3':
        searchproperty();
        break;
    case '4':
        rentproperty();
        break;
    case '5':
        viewproperty();
        break;
    case '6':
        editproperty();
        break;
    case '7':
    {
        system("cls");
        gotoxy(16, 3);
        Sleep(3000);
        exit(0);
    }
    case '8':

       obj.directFind();
        break;

    default:
    {
        gotoxy(10, 23);
        cout << "\a Pls Re-enter correct option";
        if (getch())
            mainmenu();
    }
    }
}



int getdata()
{
    int q;
    gotoxy(2, 1);
    t();
    gotoxy(2, 3);
    cout << "Enter the Information Below";
    gotoxy(2, 5);
    cout << "Category:";
    gotoxy(12, 5);
    cout << type[s - 1];
    gotoxy(2, 7);
    cout << "Property Unique code:\t";
    gotoxy(23, 7);
    cin >> q;
    if (checkid(q) == 0)
    {
        gotoxy(21, 13);
        cout << "The unique code id already exists";
        getch();
        mainmenu();
        return 0;
    }
    a.id = q;
    gotoxy(2, 9);
    cout << "Owner name:";
    gotoxy(13, 9);
    cin >> a.name;
    gotoxy(2, 11);
    cout << "Location:";
    gotoxy(11, 11);
    cin >> a.location;
    gotoxy(2, 13);
    cout << "Rooms:";
    gotoxy(8, 13);
    cin >> a.rooms;
    gotoxy(2, 15);
    cout << "Price:";
    gotoxy(8, 15);
    cin >> a.Price;
    gotoxy(2, 17);
    cout << "Street No:";
    gotoxy(12, 17);
    cin >> a.streetno;
    gotoxy(2, 19);
    return 1;
}


int checkid(int t)
{
    fstream file("prop.txt", ios::binary | ios::in | ios::out);
    file.seekg(0, ios::beg);
    while (file.read(reinterpret_cast<char*>(&a), sizeof(a)))
    {
        if (a.id == t)
            return 0;
    }
    return 1;
}

int t(void)
{
    time_t currentTime;
    time(&currentTime);
    std::cout << "Date and time: " << ctime(&currentTime) << std::endl;

    return 0;
}

void Password()
{
    system("cls");
    char d[25] = "Property RENTING ";
    char ch, pass[10];
    int i = 0, j;
    gotoxy(10, 4);
    /*for (j = 0; j < 40; j++)
    {
        Sleep(50);
        printf("*");
    }*/
    for (j = 0; j < 20; j++)
    {
       // Sleep(50);
        printf("%c", d[j]);
    }
   /* for (j = 0; j < 40; j++)
    {
        Sleep(50);
        printf("*");
    }
    gotoxy(10, 10);*/
    gotoxy(15, 7);
    printf("Enter Password:");

    while (ch != 13)
    {
        ch = getch();

        if (ch != 13 && ch != 8)
        {
            putch('*');
            pass[i] = ch;
            i++;
        }
    }
    pass[i] = '\0';
    if (strcmp(pass, password) == 0)
    {
        gotoxy(15, 9);
        printf("Password match");
        gotoxy(17, 10);
        printf("Press any key to continue.....");
        getch();
        mainmenu();
    }
    else
    {
        gotoxy(15, 16);
        printf("Wrong password");
        getch();
        Password();
    }
}
int main() {
    Password();
    cin.get();
    return 0;
}
