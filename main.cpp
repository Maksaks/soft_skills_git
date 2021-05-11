#include <iostream>
#include <Windows.h>
#include <fstream>
#include <iomanip>
// 495 // 89 // 242
using namespace std;

class String {
private:
    char* str;
    int maxsize = 65535;
public:
    String() { this->str = new char[1]; }
    String(String& obj);
    String(String& other, int to, int size);
    ~String() { delete[]this->str; };

    void input();
    void init(char* str1);
    void show();

    int strSize();
    void strConcat(String& x);
    int strFind(String& x);
    friend void strFindReplace(String& main, String& from, String& to);

    void fromFile();
    void toFile();
};

//_____________________________Манипуляторы_________________________________
istream &insetup (istream &ifs)
{
    ifs.unsetf(ios::dec);
    ifs.setf(ios::hex);
    return ifs;
}

ostream &outsetup (ostream &ofs)
{
    ofs.setf(ios::left);
    ofs.fill('$');
    ofs<<setw(40);
    return ofs;
}
//_____________________________Манипуляторы_________________________________

//_____________________________Конструкторы_________________________________
String::String(String& obj)
{
    this->str = new char[obj.strSize() + 1];
    for (int i = 0; i < obj.strSize(); i++)
        this->str[i] = obj.str[i];
    this->str[obj.strSize()] = '\0';
}

String::String(String& other, int to, int size)
{
    this->str = new char[size];
    for (int i = 0; i < to; i++)
    {
        this->str[i] = other.str[i];
        if (i == to - 1) { this->str[i] = '\0'; }
    }
}
//_____________________________Конструкторы_________________________________

//_________________________________Методы___________________________________
void String::input()
{
    cin.getline(str, maxsize);
}

void String::init(char* str1)
{
    int i = 0;
    this->str = new char[strlen(str1)];
    while (str1[i] != '\0')
    {
        this->str[i] = str1[i];
        i++;
        if (str1[i] == '\0') { this->str[i] = '\0'; }
    }
}

void String::show()
{
    //cout << this->str;
    cout << outsetup <<this->str;
    cout << endl;
}

int String::strSize()
{
    int res = 0;
    while (str[res] != '\0')
    {res++;}
    return res;
}

void String::strConcat(String& x)
{
    String res;
    res.str = new char[this->strSize() + x.strSize() + 1];
    int size = this->strSize();
    int i = 0;

    while (this->str[i] != '\0')
    {
        res.str[i] = this->str[i];
        i++;
    }
    i = 0;
    while (x.str[i] != '\0')
    {
        res.str[i + size] = x.str[i];
        i++;
        if (x.str[i] == '\0') { res.str[i + size] = '\0'; }
    }
    i = 0;
    delete[] this->str;

    this->str = new char[size + x.strSize() + 1];
    while (res.str[i] != '\0')
    {
        this->str[i] = res.str[i];
        i++;
        if (res.str[i] == '\0') { this->str[i] = '\0'; }
    }
}

int String::strFind(String& x)
{
    int pos = 0, check = 0;
    for (int i = 0; i < this->strSize(); i++)
    {
        for (int j = 0; j < x.strSize(); j++)
        {
            if (this->str[i] == x.str[j])
            {
                if (pos == 0) { pos = i; }
                check++;
                i++;
            }
            else
            {
                pos = 0;
                check = 0;
                j = 0;
                break;
            }
        }
        if (check == x.strSize())
            return pos + 1;
    }
    if (pos == 0)
        return -1;
}

void strFindReplace(String& main, String& from, String& to)
{
    int n = main.strFind(from);     // начало подстроки
    int size = main.strSize() - from.strSize() + to.strSize() + 1;

    String res(main, n, size);      // конечная строка / копируем в нее все до начала построки

    int i = 0;
    while (to.str[i] != '\0')
    {
        res.str[i + n - 1] = to.str[i];
        i++;
        if (to.str[i] == '\0')
        {res.str[i - 1 + n] = '\0';}
    }
    i = 0;

    int s = res.strSize();

    while (main.str[i + n + from.strSize() - 1] != '\0')
    {
        res.str[s + i] = main.str[i + n + from.strSize() - 1];
        i++;
        if (main.str[i + n + from.strSize() - 1] == '\0')
        {res.str[s + i] = '\0';}
    }
    i = 0;

    delete[] main.str;
    main.str = new char[res.strSize() + 1];
    while (i != res.strSize())
    {
        main.str[i] = res.str[i];
        if (i == res.strSize() - 1)
        {main.str[i + 1] = '\0';}
        i++;
    }
}


void String::fromFile()
{
    char path[40];                               //E:\\Lab_4_Zaikovskiy_D_knt_130\\main.txt
    cin.ignore();                                //E:\\Lab_4_Zaikovskiy_D_knt_130\\conc.txt
    cout << "Enter file path:  ";                //E:\\Lab_4_Zaikovskiy_D_knt_130\\find.txt
    cin >> path;                                 //E:\\Lab_4_Zaikovskiy_D_knt_130\\rec.txt

    ifstream fin(path);
    if(!fin.is_open())
    {
        cout << "File open error" << endl;
    }
    else
    {
        int size = 0;
        char ch;
        while (fin.get(ch))
        {
            size++;
        }
        this->str = new char[size+1];
        fin.clear();                          // сбросить состояние потока
        fin.seekg(0, ios_base::beg);          // перейти в начало файла
        fin.getline(this->str, size + 1);
    }
    fin.close();
}

void String::toFile()
{
    char path[40];                                //E:\\Lab_4_Zaikovskiy_D_knt_130\\main.txt
    cin.ignore();
    cout << "Enter file path:  ";
    cin >> path;

    ofstream fout(path);
    if(!fout.is_open())
    {
        cout << "File open error" << endl;
    }
    else
    {
        fout << outsetup << this->str;
        //fout << this->str;
        cout << "Data has been successfully written to the file" << endl;
    }
    fout.close();
}

//_________________________________Методы___________________________________

int main()
{
    //setlocale(LC_ALL, "rus");
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);

    String a;
    char str1[] = "Default string!";
    bool end = false;

    int main_menu_choose;
    int choose_input = 0;
    int choose_5 = 0;
    int choose_6 = 0;
    int choose_7 = 0;

        cout << "Select operation:\n"
            << "-> 1. String input\n"
            << "-> 2. String output\n"
            << "-> 3. Write string to file\n"
            << "-> 4. Find out the number of characters in a string\n"
            << "-> 5. Concatenate strings\n"
            << "-> 6. Search for a substring\n"
            << "-> 7. Finding and replacing a substring\n"
            << "-> 8. Clear console\n"
            << "-> 9. Try new feature\n"
            << "-> 0. Exit\n\n";

        while (!end)
        {
            cout << "\n> ";
            cin >> main_menu_choose;
            switch (main_menu_choose)
            {
            case 1:
                cout << "-> 1. Console input\n"
                    << "-> 2. Set programmatically\n"
                    << "-> 3. From the file\n\n";
                cout << "> ";
                cin  >>choose_input;
                switch (choose_input)
                {
                case 1:
                    cout << "Enter the string: " << endl;
                    cin.ignore();
                    a.input();
                    break;
                case 2:
                    cout << "String: " << endl;
                    a.init(str1);
                    a.show();
                    break;
                case 3:
                    a.fromFile();                 //E:\\Lab_4_Zaikovskiy_D_knt_130\\main.txt
                    cout << "String: " << endl;
                    a.show();
                    break;
                default:
                    cout << "Error! You have chosen the wrong menu item!" << endl;
                    end = true;
                    break;
                }
                break;

            case 2:
                if (choose_input != 1 && choose_input != 2 && choose_input != 3)
                {
                    cout << "You have not entered a string!" << endl;
                    break;
                }
                cout << "Your string: " << endl;
                a.show();
                break;

            case 3:
                a.toFile();       //E:\\Lab_4_Zaikovskiy_D_knt_130\\main.txt
                break;

            case 4:
                if (choose_input != 1 && choose_input != 2 && choose_input != 3)
                {
                    cout << "You have not entered a string!" << endl;
                    break;
                }

                {int num_of_char = a.strSize();
                cout << "Number of characters per line: " << num_of_char << endl; }
                break;

            case 5:
                if (choose_input != 1 && choose_input != 2 && choose_input != 3)
                {
                    cout << "You have not entered a string!" << endl;
                    break;
                }

                cout << "-> 1. Console input\n"
                    << "-> 2. From the file\n\n";
                cout << "> ";
                cin >> choose_5;
                if(choose_5 == 1)
                {
                    String b;
                    cout << "Enter string you want to attach to the main one: " << endl;
                    cin.ignore();
                    b.input();
                    a.strConcat(b);
                    cout << "New string: " << endl;
                    a.show();
                }
                else if(choose_5 == 2)  //E:\\Lab_4_Zaikovskiy_D_knt_130\\conc.txt
                {
                    String b;
                    cout << "File with string you want to attach to the main one" << endl;
                    b.fromFile();
                    a.strConcat(b);
                    cout << "New string: " << endl;
                    a.show();
                }
                else
                {
                     cout << "Error! You have chosen the wrong menu item!" << endl;
                }
                break;

            case 6:
                if (choose_input != 1 && choose_input != 2 && choose_input != 3)
                {
                    cout << "You have not entered a string!" << endl;
                    break;
                }
                cout << "-> 1. Console input\n"
                    << "-> 2. From the file\n\n";
                cout << "> ";
                cin >> choose_6;
                if(choose_6 == 1)
                {
                    String b;
                    cout << "Enter a substring: " << endl;
                    cin.ignore();
                    b.input();
                    if (a.strFind(b) < 0)
                    {
                        cout << "No substring found!" << endl;
                    }
                    else
                    {
                        cout << "The substring was found! Starts with " << a.strFind(b) << " character!" << endl;
                    }
                }
                else if(choose_6 == 2)    //E:\\Lab_4_Zaikovskiy_D_knt_130\\find.txt
                {
                    String b;
                    cout << "Substring from file" << endl;
                    b.fromFile();
                    if (a.strFind(b) < 0)
                    {
                        cout << "No substring found!" << endl;
                    }
                    else
                    {
                        cout << "The substring was found! Starts with " << a.strFind(b) << " character!" << endl;
                    }
                }
                else
                {
                     cout << "Error! You have chosen the wrong menu item!" << endl;
                }
                break;

            case 7:
                if (choose_input != 1 && choose_input != 2 && choose_input != 3)
                {
                    cout << "You have not entered a string!" << endl;
                    break;
                }

                cout << "-> 1. Console input\n"
                    << "-> 2. From the file\n\n";
                cout << "> ";
                cin >> choose_7;
                if(choose_7 == 1)
                {
                    String b;
                    String c;
                    cout << "Enter the substring you want to replace: " << endl;
                    cin.ignore();
                    b.input();
                    if (a.strFind(b) < 0)
                    {
                        cout << "No substring found!" << endl;
                    }
                    else
                    {
                        cout << "Enter the substring you want to replace the previous one with: " << endl;
                        c.input();
                        strFindReplace(a, b, c);
                        cout << "New string: " << endl;
                        a.show();
                    }
                }
                else if(choose_7 == 2)          //E:\\Lab_4_Zaikovskiy_D_knt_130\\find.txt
                {                               //E:\\Lab_4_Zaikovskiy_D_knt_130\\rec.txt
                    String b;
                    String c;
                    cout << "Substring you want to replace" << endl;
                    b.fromFile();
                    if (a.strFind(b) < 0)
                    {
                        cout << "No substring found!" << endl;
                    }
                    else
                    {
                        cout << "Substring you want to replace the previous one with: " << endl;
                        c.fromFile();
                        strFindReplace(a, b, c);
                        cout << "New string: " << endl;
                        a.show();
                    }
                }
                else
                {
                     cout << "Error! You have chosen the wrong menu item!" << endl;
                }

                break;

            case 8:
                system("cls");
                cout << "Select operation:\n"
                    << "-> 1. String input\n"
                    << "-> 2. String output\n"
                    << "-> 3. Write string to file\n"
                    << "-> 4. Find out the number of characters in a string\n"
                    << "-> 5. Concatenate strings\n"
                    << "-> 6. Search for a substring\n"
                    << "-> 7. Finding and replacing a substring\n"
                    << "-> 8. Clear console\n"
                    << "-> 9. Try new feature\n"
                    << "-> 0. Exit\n\n";
                break;
            case 9:
                {ifstream test("E:\\Lab_4_Zaikovskiy_D_knt_130\\test.txt");
                int a = 0;
                cout << a << endl;
                test >> insetup >> a;
                cout << a;
                test.close();}
                break;
            case 0:
                end = true;
                break;

            default:
                cout << "Error! You have chosen the wrong menu item!" << endl;
                end = true;
                break;
            }
        }

    return 0;
}
