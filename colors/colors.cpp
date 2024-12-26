#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

// Функция проверки ввода на целое неотрицательное число
int dataCheckInt(int integer) {
    while (cin.fail() || integer < 0) { // Пока ввод некорректен или число отрицательное
        cin.clear(); // Очищаем состояние потока
        cin.ignore(1000, '\n'); // Игнорируем лишние символы
        cout << "Ошибка, вы должны ввести целое неотрицательное число." << endl << "Введите число ещё раз: " << endl;
        cin >> integer; // Ввод нового значения
    }
    return integer; // Возвращаем корректное число
}

// Генерация случайного числа в диапазоне от 1 до maxValue
int randFunction(int maxValue) {
    int x = rand() % (maxValue)+1; // Случайное число от 1 до maxValue
    return x;
}

// Рекурсивная функция для подсчёта "соседей" одинакового цвета
int findColorFunction(vector< vector<int>>& matrix, int i, int j) {
    if (matrix[i][j] == 0) { // Если элемент уже обработан
        return 0; // Возвращаем 0
    }
    int counter = 1; // Счётчик начального элемента
    int columnLength = matrix[0].size(); // Количество столбцов
    int rowLength = matrix.size(); // Количество строк

    // Проверка элемента сверху
    if (i - 1 >= 0 && matrix[i][j] == matrix[i - 1][j]) {
        matrix[i][j] = 0; // Устанавливаем текущий элемент в 0
        counter += findColorFunction(matrix, i - 1, j); // Рекурсивный вызов для верхнего элемента
    }
    // Проверка элемента снизу
    if (i + 1 < rowLength && matrix[i][j] == matrix[i + 1][j]) {
        matrix[i][j] = 0;
        counter += findColorFunction(matrix, i + 1, j); // Рекурсивный вызов для нижнего элемента
    }
    // Проверка элемента справа
    if (j + 1 < columnLength && matrix[i][j] == matrix[i][j + 1]) {
        matrix[i][j] = 0;
        counter += findColorFunction(matrix, i, j + 1); // Рекурсивный вызов для правого элемента
    }
    // Проверка элемента слева
    if (j - 1 >= 0 && matrix[i][j] == matrix[i][j - 1]) {
        matrix[i][j] = 0;
        counter += findColorFunction(matrix, i, j - 1); // Рекурсивный вызов для левого элемента
    }
    return counter; // Возвращаем общий счётчик
}

int main()
{
    srand(time(0)); // Установка случайного сидирования для генерации чисел
    setlocale(LC_ALL, "RU"); // Установка локали для русского языка

    // Ввод количества строк
    cout << "Введите количество строк: " << endl;
    int rows = 0;
    cin >> rows;
    rows = dataCheckInt(rows); // Проверка ввода

    // Ввод количества столбцов
    cout << "Введите количество столбцов: " << endl;
    int colums = 0;
    cin >> colums;
    colums = dataCheckInt(colums); // Проверка ввода

    // Ввод максимального значения
    cout << "Введите максимальное значение: " << endl;
    int maxValue = 0;
    cin >> maxValue;
    maxValue = dataCheckInt(maxValue); // Проверка ввода

    // Создание и заполнение матрицы случайными числами
    vector < vector<int>> matrix;
    for (int i = 0; i < rows; i++) {
        vector <int> row;
        for (int j = 0; j < colums; j++) {
            row.push_back(randFunction(maxValue)); // Генерация случайного числа
        }
        matrix.push_back(row); // Добавление строки в матрицу
    }

    // Создание вектора для хранения максимального количества "соседей" для каждого цвета
    vector <int> maxNum(maxValue + 1, 0);

    // Вывод матрицы на экран
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < colums; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    // Подсчёт максимального количества соседей для каждого цвета
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < colums; j++) {
            if (matrix[i][j] == 0) { // Если элемент уже обработан
                continue;
            }
            int v = matrix[i][j]; // Текущий цвет
            int z = findColorFunction(matrix, i, j); // Количество соседей для текущего элемента
            if (maxNum[v - 1] < z) { // Если найдено большее значение
                maxNum[v - 1] = z; // Обновляем максимум
            }
        }
    }

    // Вывод результатов
    for (int i = 0; i < maxNum.size() - 1; i++) {
        cout << i + 1 << ". " << maxNum[i] << endl; // Вывод максимального количества соседей для каждого цвета
    }

    return 0; // Завершение программы
}
