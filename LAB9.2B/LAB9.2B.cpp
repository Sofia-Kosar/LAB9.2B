#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum Major { KI, INF, MATH, PHYSICS, ART };
string majorStr[] = { "Комп’ютерні науки", "Інформатика", "Математика та економіка", "Фізика та інформатика", "Трудове навчання" };

struct Student
{
    string prizv;
    unsigned int kurs;
    Major major;
    union
    {
        int program;
        int nummeth;
        int pedagog;
    };
    int physics;
    int math;
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
void CountGoodGrades(Student* p, const int N);
double CalculatePercentGoodPhysicsMath(Student* p, const int N);
void Sort1(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string prizv, const unsigned int kurs, const double avgGrade);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть N: ";
    cin >> N;

    Student* p = new Student[N];
    int menuItem;
    double percent;

    do {
        cout << endl
            << endl
            << endl;
        cout << "Виберіть дію:" << endl
            << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - вивід прізвищ та проценту студентів,"
            << " які мають оцінку 5 з фізики і математики" << endl
            << endl;
        cout << " [4] - вивід предметів та кількість оцінок добре " << endl
            << endl;
        cout << " [5] - сортування студентів" << endl;
        cout << " [6] - індексне впорядкування та вивід даних" << endl;
        cout << " [7] - бінарний пошук" << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl
            << endl;
        cout << "Введіть значення: ";
        cin >> menuItem;
        cout << endl
            << endl
            << endl;

        switch (menuItem)
        {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            percent = CalculatePercentGoodPhysicsMath(p, N);
            cout << "Процент студентів, які отримали '5' і з фізики і з математики: "
                << fixed << setprecision(2) << percent << "%" << endl;
            break;
        case 4:
            CountGoodGrades(p, N);
            break;
        case 5:
            Sort1(p, N);
            Print(p, N);
            break;
        case 6:
            PrintIndexSorted(p, IndexSort(p, N), N);
            break;
        case 7:
        {
            string searchPrizv;
            unsigned int searchKurs;
            double searchAvgGrade;

            cout << "Введіть прізвище студента: ";
            cin.ignore();
            getline(cin, searchPrizv);

            cout << "Введіть номер курсу: ";
            cin >> searchKurs;

            cout << "Введіть середній бал: ";
            cin >> searchAvgGrade;

            int foundIndex = BinSearch(p, N, searchPrizv, searchKurs, searchAvgGrade);
            if (foundIndex != -1)
            {
                cout << "Знайдено студента з порядковим номером " << foundIndex + 1 << endl;
            }
            else
            {
                cout << "Шуканого студента не знайдено" << endl;
            }
        }
        break;
        case 0:
            break;
        default:
            cout << "Ви ввели помилкове значення! "
                << "Слід ввести число - номер вибраного пункту меню" << endl;
            break;
        }
    } while (menuItem != 0);

    delete[] p;
    return 0;
}

void Create(Student* p, const int N)
{
    int major;

    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
        cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

        cout << " прізвище: "; getline(cin, p[i].prizv);
        cout << " курс: "; cin >> p[i].kurs;
        cout << " спеціальність (0 - Комп’ютерні науки, 1 -Інформатика , 2 -Математика та економіка , 3 -Фізика та інформатика, 4 -Трудове навчання): ";
        cin >> major;
        p[i].major = static_cast<Major>(major);
        p[i].major = (Major)major;
        cout << " фізика "; cin >> p[i].physics;
        cout << " математика "; cin >> p[i].math;
        switch (p[i].major)
        {
        case KI:
            cout << " програмування : "; cin >> p[i].program;
            break;
        case INF:
            cout << " чисельні методи : "; cin >> p[i].nummeth;
            break;
        case MATH:
        case PHYSICS:
        case ART:
            cout << " педагогіка : "; cin >> p[i].pedagog;
            break;
        }
        cout << endl;
    }
}

void Print(Student* p, const int N)
{
    cout << "========================================================================================================================"
        << endl;
    cout << "|  № |   Прізвище   | Курс | Спеціальність          | Фізика | Математика | Програмування | Чисельні методи | Педагогіка"
        << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------"
        << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(2) << right << i + 1 << " ";
        cout << "| " << setw(13) << left << p[i].prizv
            << "| " << setw(4) << right << p[i].kurs << " "
            << "| " << setw(23) << left << majorStr[p[i].major];
        cout << "| " << setw(7) << right << p[i].physics
            << "| " << setw(11) << right << p[i].math;
        switch (p[i].major)
        {
        case KI:
            cout << "| " << setw(14) << right << p[i].program << "| " << setw(17) << "|" << setw(11) << "|" << endl;
            break;
        case INF:
            cout << "| " << setw(15) << "|" << setw(17) << right << p[i].nummeth << "| " << setw(10) << "|" << endl;
            break;
        case MATH:
        case PHYSICS:
        case ART:
            cout << "| " << setw(15) << "|" << setw(18) << "|" << setw(10) << right << p[i].pedagog << "| ";
            break;
        }
        cout << endl;
    }
    cout << "========================================================================================================================"
        << endl;
    cout << endl;
}

void CountGoodGrades(Student* p, const int N)
{
    int countPhysics = 0;
    int countMath = 0;
    int countProgram = 0;
    int countNummeth = 0;
    int countPedagog = 0;

    for (int i = 0; i < N; i++)
    {
        if (p[i].physics == 4) {
            countPhysics++;
        }

        if (p[i].math == 4) {
            countMath++;
        }

        if (p[i].program == 4) {
            countProgram++;
        }
        if (p[i].nummeth == 4) {
            countNummeth++;
        }
        if (p[i].pedagog == 4) {
            countPedagog++;
        }
    }

    cout << "=============================================================================================================" << endl;
    cout << "Кількість оцінок 'Добре' з кожного предмету:" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Фізика: " << countPhysics << " | Математика: " << countMath << " | Програмування: " << countProgram << " | Чисельні методи: " << countNummeth << " | Педагогіка: " << countPedagog << endl;
    cout << "=============================================================================================================" << endl;
}

double CalculatePercentGoodPhysicsMath(Student* p, const int N)
{
    int k = 0;

    for (int i = 0; i < N; i++)
    {
        if (p[i].physics == 5 && p[i].math == 5) {
            k++;
        }
    }

    return 100.0 * k / N;
}


void Sort1(Student* p, const int N)
{
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
    {
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
        {
            int sum1, sum2;

            switch (p[i1].major)
            {
            case KI:
                sum1 = p[i1].physics + p[i1].math + p[i1].program;
                break;
            case INF:
                sum1 = p[i1].physics + p[i1].math + p[i1].nummeth;
                break;
            case MATH:
            case PHYSICS:
            case ART:
                sum1 = p[i1].physics + p[i1].math + p[i1].pedagog;
                break;
            }

            switch (p[i1 + 1].major)
            {
            case KI:
                sum2 = p[i1 + 1].physics + p[i1 + 1].math + p[i1 + 1].program;
                break;
            case INF:
                sum2 = p[i1 + 1].physics + p[i1 + 1].math + p[i1 + 1].nummeth;
                break;
            case MATH:
            case PHYSICS:
            case ART:
                sum2 = p[i1 + 1].physics + p[i1 + 1].math + p[i1 + 1].pedagog;
                break;
            }

            if (sum1 > sum2 ||
                (sum1 == sum2 && p[i1].kurs > p[i1 + 1].kurs) ||
                (sum1 == sum2 && p[i1].kurs == p[i1 + 1].kurs && p[i1].prizv < p[i1 + 1].prizv))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
        }
    }
}


int* IndexSort(Student* p, const int N)
{
    int* I = new int[N];

    for (int i = 0; i < N; i++)
        I[i] = i;

    int i, j, value;

    for (i = 1; i < N; i++)
    {
        value = I[i];

        int sumValue = 0;

        switch (p[value].major)
        {
        case KI:
            sumValue = p[value].physics + p[value].math + p[value].program;
            break;
        case INF:
            sumValue = p[value].physics + p[value].math + p[value].nummeth;
            break;
        case MATH:
        case PHYSICS:
        case ART:
            sumValue = p[value].physics + p[value].math + p[value].pedagog;
            break;
        }

        for (j = i - 1; j >= 0; j--)
        {
            int sumJ = 0;

            switch (p[I[j]].major)
            {
            case KI:
                sumJ = p[I[j]].physics + p[I[j]].math + p[I[j]].program;
                break;
            case INF:
                sumJ = p[I[j]].physics + p[I[j]].math + p[I[j]].nummeth;
                break;
            case MATH:
            case PHYSICS:
            case ART:
                sumJ = p[I[j]].physics + p[I[j]].math + p[I[j]].pedagog;
                break;
            }

            if (sumJ > sumValue ||
                (sumJ == sumValue && p[I[j]].kurs > p[value].kurs) ||
                (sumJ == sumValue && p[I[j]].kurs == p[value].kurs && p[I[j]].prizv > p[value].prizv))
            {
                I[j + 1] = I[j];
            }
            else
            {
                break;
            }
        }

        I[j + 1] = value;
    }

    return I;
}

void PrintIndexSorted(Student* p, int* I, const int N)
{
    cout << "========================================================================================================================"
        << endl;
    cout << "|  № |   Прізвище   | Курс | Спеціальність          | Фізика | Математика | Програмування | Чисельні методи | Педагогіка"
        << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------"
        << endl;

    for (int i = 0; i < N; i++)
    {
        int index = I[i];

        cout << "| " << setw(2) << right << i + 1 << " ";
        cout << "| " << setw(13) << left << p[index].prizv
            << "| " << setw(4) << right << p[index].kurs << " "
            << "| " << setw(23) << left << majorStr[p[index].major];
        cout << "| " << setw(7) << right << p[index].physics
            << "| " << setw(11) << right << p[index].math;

        switch (p[index].major)
        {
        case KI:
            cout << "| " << setw(14) << right << p[index].program << "| " << setw(17) << "|" << setw(11) << "|" << endl;
            break;
        case INF:
            cout << "| " << setw(15) << "|" << setw(17) << right << p[index].nummeth << "| " << setw(10) << "|" << endl;
            break;
        case MATH:
        case PHYSICS:
        case ART:
            cout << "| " << setw(15) << "|" << setw(18) << "|" << setw(10) << right << p[index].pedagog << "| ";
            break;
        }
        cout << endl;
    }

    cout << "========================================================================================================================"
        << endl;
    cout << endl;
}

int BinSearch(Student* p, const int N, const string prizv, const unsigned int kurs, const double avgGrade)
{
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;

        int avgGradeM = 0;

        switch (p[m].major)
        {
        case KI:
            avgGradeM = (p[m].physics + p[m].math + p[m].program) / 3.0;
            break;
        case INF:
            avgGradeM = (p[m].physics + p[m].math + p[m].nummeth) / 3.0;
            break;
        case MATH:
        case PHYSICS:
        case ART:
            avgGradeM = (p[m].physics + p[m].math + p[m].pedagog) / 3.0;
            break;
        }

        if (p[m].prizv == prizv && p[m].kurs == kurs && avgGradeM == avgGrade)
            return m;

        int avgGradeValue = 0;

        switch (p[m].major)
        {
        case KI:
            avgGradeValue = (p[m].physics + p[m].math + p[m].program) / 3.0;
            break;
        case INF:
            avgGradeValue = (p[m].physics + p[m].math + p[m].nummeth) / 3.0;
            break;
        case MATH:
        case PHYSICS:
        case ART:
            avgGradeValue = (p[m].physics + p[m].math + p[m].pedagog) / 3.0;
            break;
        }

        if ((p[m].prizv < prizv) ||
            (p[m].prizv == prizv && p[m].kurs < kurs) ||
            (p[m].prizv == prizv && p[m].kurs == kurs && avgGradeValue < avgGrade))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);

    return -1;
}
