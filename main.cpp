#include "RandomFile.h"
#include <iostream>
#include <locale>

using namespace std;

// funkcia proverka - ona proveraet na polzovatelya durachka
int proverka() {
    int value;
    while (true) {
        cin >> value;

        // Проверка на ошибку ввода
        if (cin.fail()) {
            // Если ввод не является числом
            cin.clear(); // Очищаем флаг ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Пропускаем некорректный ввод
            cout << "Ошибка! Пожалуйста, введите целое число." << endl;
        }
        else if (value <= 0) {
            // Если число не положительное
            cout << "Ошибка! Число должно быть положительным." << endl;
        }
        else {
            // Введено корректное положительное число
            break;
        }
    }
    return value;
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Имена файлов
    int n;
    int m;
    string binfile = "random_numbers.bin";
    string matrixfile = "matrix.bin";
    string baggagefile = "baggage.bin";
    string txtfile = "txtfile.txt";  
    string randomtxtfile = "ochenrandomfile.txt";
    string textfile = "textfile.txt";
    string new_textfile = "new_textfile.txt";
    // Создание объекта класса
    RandomFile randomFile;
    cout << "Задание 1" << endl;
    cout << "Введите количество чисел: ";
    n = proverka();

    // Заполнение входного файла случайными числами
    randomFile.createAndFillBinaryFile(binfile, n, -100, 100);

    
    randomFile.printAndCalculateOddProduct(binfile);
    
    cout << "Задание 2" << endl;
    cout << "Введите размер матрицы:";
    n = proverka();

    // Преобразование данных в матрицу 4x4 и сохранение в другой файл
    randomFile.transformToMatrixAndSave(binfile, matrixfile, n);
    
    cout << "Задание 3" << endl;

    // Заполнение файла багажом
    randomFile.fillBaggageFile(baggagefile);

    // Анализ файла багажа
    randomFile.analyzeBaggageFile(baggagefile);

    cout << "Задание 4" << endl;

    // Создание текстового файла
    randomFile.createRandomTextFile(txtfile);
    
    // Подсчёт суммы квадратов
    randomFile.printFileAndSumSquares(txtfile);

    cout << "Задание 5" << endl;

    // Генерация случайного файла случайных чисел
    randomFile.fillFileWithRandomNumbers(randomtxtfile);

    // Произведение случайных чисел
    randomFile.readFileAndComputeProduct(randomtxtfile);
    
    cout << "Задание 6" << endl;
    cout << "Введите длину искомых строк: ";
    m = proverka();
    // Нахождение строк равных m
    randomFile.processFileByLineLength(textfile, new_textfile, m);



    return 0;
}
