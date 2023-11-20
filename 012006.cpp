#include <iostream>
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#elif __linux
#include <termios.h>
#endif

using namespace std;

#ifdef _WIN32
string typein_WIN(char qt, string text, string choice)
{
    bool run = true;
    string test;
    text + "\n";
    system("CLS");
    cout << "Для закінчення введення даних натисніть клавішу esc\n";
    while (run) {
        if (_kbhit()) {
            qt = _getch();
            for (int i = 0; i < choice.length(); i++) {
                if (qt == choice[i]) {
                    qt = ' ';
                }
                else if (qt == 13) {
                    qt = '\n';
                }
                else if (qt == 27) {
                    run = false;
                    qt = ' ';
                    break;
                }
            }
            text += qt;
            cout << qt;
        }
    }
    cout << endl << "Ви ввели текст:\n";
    cout << text << endl;
    run = true;
    return text + "\n";
}

#elif __linux
string typein(string validChars) {
    string input;
    system("clear");
    cout << "Для закінчення введення даних натисніть клавішу esc\n";
    struct termios Old, New;
    tcgetattr(0, &Old);
    New = Old;
    New.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &New);
    char ch;
    while ((ch = getchar()) != 27) {
        if (validChars.find(ch) == string::npos) {
            ch = ' ';
        }
        input += ch;
        cout << ch;
    }

    tcsetattr(0, TCSANOW, &Old);
    cout << endl << "Вы ввели текст:\n" << input << endl;
    return input;
}
#endif

int main()
// спільний розділ для обох систем
{
    string Ukr = "йцукенгшщзхждлорпавфячсмитьбюЙЦУКЕНГШЩЗХЖДЛОРПАВФЯЧСМИТЬБЮґҐІіЄєЇї";
    string Eng = "qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM";
    string Num = "0123456789";
    string Symb = "`~!@#$%^&*()_+}{|\":<>?/.,\\';][=-№";
    int    choice = 0;
    char   qt = ' ';   // при потребі цю змінну можна ініціалізувати пробілом
    string text;
#ifdef __linux

    bool menu_run = true;
    while (menu_run)
    {
        cout << "Натисніть 1 для заміни цифр пробілами\n";
        cout << "Натисніть 2 для заміни розділових знаків пробілами\n";
        cout << "Натисніть 3 для заміни англійських букв пробілами\n";
        cout << "Натисніть 4 для заміни українських букв пробілами\n";
        cin >> choice;
        switch (choice) {
        case 1:
            text = typein(Num);
            break;
        case 2:
            text = typein(Symb);
            break;
        case 3:
            text = typein(Eng);
            break;
        case 4:
            text = typein(Ukr);
            break;
        default:
            menu_run = false;
            break;
        }
    }

#elif _WIN32
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    bool menu_run = true;
    while (menu_run)
    {
        cout << "Натисніть 1 для заміни цифр пробілами\n";
        cout << "Натисніть 2 для заміни розділових знаків пробілами\n";
        cout << "Натисніть 3 для заміни англійських букв пробілами\n";
        cout << "Натисніть 4 для заміни українських букв пробілами\n";
        cin >> choice;
        switch (choice) {
        case 1:
            text += typein_WIN(qt, text, Num);
            break;
        case 2:
            text = typein_WIN(qt, text, Symb);
            break;
        case 3:
            text = typein_WIN(qt, text, Eng);
            break;
        case 4:
            text = typein_WIN(qt, text, Ukr);
            break;
        default:
            menu_run = false;
            break;
        }
    }
#endif
}