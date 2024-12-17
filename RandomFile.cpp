#include "RandomFile.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <random> 
#include <cstring>
#include <numeric>
#include <cmath> 
using namespace std;


    // Метод создания и заполнения бинарного файла случайными числами
    void RandomFile::createAndFillBinaryFile(const string& filename, int numValues, int minValue, int maxValue) {
        ofstream outFile(filename, ios::binary);

        if (!outFile) {
            cerr << "Ошибка при открытии файла для записи: " << filename << endl;
            return;
        }

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(minValue, maxValue);

        for (int i = 0; i < numValues; ++i) {
            int value = dist(gen);
            outFile.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }

        outFile.close();
        cout << "Файл \"" << filename << "\" успешно создан и заполнен." << endl;
    }

    // Метод вывода содержимого файла и подсчёта произведения нечётных чисел
    void RandomFile::printAndCalculateOddProduct(const string& filename) {
        ifstream inFile(filename, ios::binary);

        if (!inFile) {
            cerr << "Ошибка при открытии файла для чтения: " << filename << endl;
            return;
        }

        cout << "Содержимое файла \"" << filename << "\":" << endl;

        int value;
        long long oddProduct = 1;
        bool hasOdd = false;

        while (inFile.read(reinterpret_cast<char*>(&value), sizeof(value))) {
            cout << value << " ";
            if (value % 2 != 0) {
                oddProduct *= value;
                hasOdd = true;
            }
        }
        cout << endl;

        if (hasOdd) {
            cout << "Произведение всех нечётных чисел: " << oddProduct << endl;
        }
        else {
            cout << "Нечётные числа отсутствуют в файле." << endl;
        }

        inFile.close();
    }

    // Метод преобразования данных в матрицу и сохранения в другой файл
    void RandomFile::transformToMatrixAndSave(const string& inputFilename, const string& outputFilename, int n) {
        ifstream inFile(inputFilename, ios::binary);
        ofstream outFile(outputFilename, ios::binary);

        if (!inFile) {
            cerr << "Ошибка при открытии входного файла: " << inputFilename << endl;
            return;
        }
        if (!outFile) {
            cerr << "Ошибка при открытии выходного файла: " << outputFilename << endl;
            return;
        }

        vector<int> data; // Сохраняем элементы из входного файла
        int value;

        // Чтение данных из входного файла
        while (inFile.read(reinterpret_cast<char*>(&value), sizeof(value))) {
            data.push_back(value);
        }

        // Создание квадратной матрицы n x n
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        size_t index = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (index < data.size()) {
                    matrix[i][j] = data[index++];
                }
            }
        }

        // Вывод матрицы до замены
        cout << "Матрица до замены:" << endl;
        for (const auto& row : matrix) {
            for (int elem : row) {
                cout << setw(5) << elem;
            }
            cout << endl;
        }

        // Обработка: поменять местами минимальный и максимальный элементы в каждом столбце
        for (int j = 0; j < n; ++j) {
            int minVal = matrix[0][j], maxVal = matrix[0][j];
            int minIdx = 0, maxIdx = 0;

            for (int i = 1; i < n; ++i) {
                if (matrix[i][j] < minVal) {
                    minVal = matrix[i][j];
                    minIdx = i;
                }
                // Если вы обратили внимание на эту строку, то хочу пожелать хорошего дня :)
                if (matrix[i][j] > maxVal) {
                    maxVal = matrix[i][j];
                    maxIdx = i;
                }
            }

            // Меняем местами минимальный и максимальный элементы
            swap(matrix[minIdx][j], matrix[maxIdx][j]);
        }

        // Вывод матрицы после замены
        cout << "Матрица после замены:" << endl;
        for (const auto& row : matrix) {
            for (int elem : row) {
                cout << setw(5) << elem;
            }
            cout << endl;
        }

        // Сохраняем матрицу в выходной файл
        for (const auto& row : matrix) {
            for (int elem : row) {
                outFile.write(reinterpret_cast<const char*>(&elem), sizeof(elem));
            }
        }

        cout << "Матрица сохранена в файл \"" << outputFilename << "\"." << endl;

        inFile.close();
        outFile.close();
    }
    // Метод заполнения бинарного файла информацией о багаже
    void RandomFile::fillBaggageFile(const string& filename) {
        ofstream outFile(filename, ios::binary);

        if (!outFile) {
            cerr << "Ошибка при открытии файла для записи: " << filename << endl;
            return;
        }

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> passengerDist(1, 20);   // Случайное количество пассажиров
        uniform_int_distribution<> bagCountDist(1, 5);     // Количество единиц багажа
        uniform_int_distribution<> weightDist(1, 30);      // Вес единицы багажа
        vector<string> baggageNames = { "чемодан", "сумка", "коробка", "рюкзак", "пакет" };

        int numPassengers = passengerDist(gen); // Генерация случайного числа пассажиров
        cout << "Случайное количество пассажиров: " << numPassengers << endl;

        for (int i = 0; i < numPassengers; ++i) {
            int numBaggage = bagCountDist(gen); // Случайное количество единиц багажа

            for (int j = 0; j < numBaggage; ++j) {
                Baggage baggage;
                // Генерация названия багажа
                strcpy_s(baggage.name, baggageNames[bagCountDist(gen) % baggageNames.size()].c_str()); // Используем strcpy_s
                // Генерация веса багажа
                baggage.weight = static_cast<float>(weightDist(gen));
                // Запись в файл
                outFile.write(reinterpret_cast<const char*>(&baggage), sizeof(Baggage));
            }

            // Добавляем пустую запись для разделения пассажиров
            Baggage separator = { "", 0.0f };
            outFile.write(reinterpret_cast<const char*>(&separator), sizeof(Baggage));
        }

        outFile.close();
        cout << "Файл \"" << filename << "\" успешно заполнен информацией о багаже." << endl;
    }

    // Метод анализа данных в файле о багаже, включая подсчёт суммы квадратов весов
    void RandomFile::analyzeBaggageFile(const string& filename) {
        ifstream inFile(filename, ios::binary);

        if (!inFile) {
            cerr << "Ошибка при открытии файла для чтения: " << filename << endl;
            return;
        }

        vector<int> baggageCounts;  // Массив для хранения количества багажа у каждого пассажира
        int currentCount = 0;

        Baggage baggage;

        cout << "Содержимое файла:\n";
        while (inFile.read(reinterpret_cast<char*>(&baggage), sizeof(Baggage))) {
            // Выводим каждую запись
            if (baggage.weight == 0.0f && strlen(baggage.name) == 0) {
                cout << "Пассажир " << baggageCounts.size() + 1 << ": " << endl;
                cout << "Количество единиц багажа: " << currentCount << endl;
                baggageCounts.push_back(currentCount);
                currentCount = 0;
            }
            else {
                cout << "Багаж: " << baggage.name << ", вес: " << baggage.weight << " кг" << endl;
                ++currentCount;
            }
        }

        inFile.close();

        // Подсчёт пассажиров с более чем двумя единицами багажа
        int moreThanTwo = count_if(baggageCounts.begin(), baggageCounts.end(), [](int count) {
            return count > 2;
            });

        // Подсчёт пассажиров с количеством багажа больше среднего
        double avg = accumulate(baggageCounts.begin(), baggageCounts.end(), 0.0) / baggageCounts.size();
        int moreThanAvg = count_if(baggageCounts.begin(), baggageCounts.end(), [avg](int count) {
            return count > avg;
            });

        cout << "\nЧисло пассажиров с более чем двумя единицами багажа: " << moreThanTwo << endl;
        cout << "Число пассажиров с количеством багажа больше среднего: " << moreThanAvg << endl;

    }


    void RandomFile::createRandomTextFile(const string& filename) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> numValuesDist(1, 20);  // Генерация случайного количества чисел в файле
    uniform_int_distribution<> valueDist(-50, 50); // Случайные целые числа от -1000 до 1000

    int numValues = numValuesDist(gen);  // Генерация случайного числа значений в файле
    cout << "Заполняем файл \"" << filename << "\" " << numValues << " случайными числами." << endl;

    ofstream outFile(filename);

    if (!outFile) {
        cerr << "Ошибка при открытии файла для записи: " << filename << endl;
        return;
    }

    // Записываем случайные значения в файл
    for (int i = 0; i < numValues; ++i) {
        int randomValue = valueDist(gen);  // Генерация случайного числа
        outFile << randomValue << endl;    // Запись числа в файл
    }

    outFile.close();
    cout << "Файл \"" << filename << "\" успешно создан." << endl;
}




// Метод вывода содержимого файла и нахождения суммы квадратов элементов
    void RandomFile::printFileAndSumSquares(const string& filename) {
        ifstream inFile(filename);

        if (!inFile) {
            cerr << "Ошибка при открытии файла для чтения: " << filename << endl;
            return;
        }

        int value;
        double sumOfSquares = 0.0;

        cout << "Содержимое файла \"" << filename << "\":" << endl;
        while (inFile >> value) {
            cout << value << endl;             // Выводим число
            sumOfSquares += value * value;     // Добавляем квадрат числа в сумму
        }

        inFile.close();

        cout << "\nСумма квадратов элементов файла: " << sumOfSquares << endl;
    }

    // Метод для заполнения текстового файла случайными числами
    void RandomFile::fillFileWithRandomNumbers(const string& filename) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> numLinesDist(1, 5);   // Количество строк от 1 до 5
        uniform_int_distribution<> numNumbersDist(1, 5);  // Количество чисел в строке от 1 до 5
        uniform_int_distribution<> valueDist(-50, 50);    

        int numLines = numLinesDist(gen);  // Генерация случайного количества строк

        cout << "Заполняем файл \"" << filename << "\" " << numLines << " строками случайных чисел." << endl;

        ofstream outFile(filename);

        if (!outFile) {
            cerr << "Ошибка при открытии файла для записи: " << filename << endl;
            return;
        }

        for (int i = 0; i < numLines; ++i) {
            int numNumbers = numNumbersDist(gen);  // Генерация случайного количества чисел в строке

            for (int j = 0; j < numNumbers; ++j) {
                int randomValue = valueDist(gen);  // Генерация случайного числа
                outFile << randomValue << " ";     // Запись числа в строку
            }
            outFile << endl;  // Перевод строки после каждого ряда чисел
        }

        outFile.close();
        cout << "Файл \"" << filename << "\" успешно заполнен." << endl;
    }

    // Метод для считывания чисел из файла, вывода и нахождения произведения
    void RandomFile::readFileAndComputeProduct(const string& filename) {
        ifstream inFile(filename);

        if (!inFile) {
            cerr << "Ошибка при открытии файла для чтения: " << filename << endl;
            return;
        }

        int value;
        long long product = 1;  // Начинаем с единицы для произведения

        cout << "Содержимое файла \"" << filename << "\":" << endl;
        while (inFile >> value) {
            cout << value << " ";  // Выводим число
            product *= value;      // Умножаем на число
        }

        inFile.close();

        cout << "\nПроизведение всех чисел в файле: " << product << endl;
    }

    // Метод для чтения файла, вывода содержимого и записи строк длиной m в новый файл
    void RandomFile::processFileByLineLength(const string& filename, const string& new_filename, int m) {
        ifstream inFile(filename);
        ofstream outFile(new_filename);

        if (!inFile) {
            cerr << "Ошибка при открытии файла для чтения: " << filename << endl;
            return;
        }
        if (!outFile) {
            cerr << "Ошибка при открытии файла для записи: " << new_filename << endl;
            return;
        }

        string line;
        cout << "Содержимое файла \"" << filename << "\":" << endl;

        // Читаем файл построчно и проверяем длину каждой строки
        while (getline(inFile, line)) {
            cout << line << endl;  // Выводим строку на экран
            if (line.length() == m) {
                outFile << line << endl;  // Записываем в новый файл, если длина строки == m
                cout << "Переписанная строка: " << line << endl;  // Выводим строку, которая переписана в новый файл
            }
        }

        inFile.close();
        outFile.close();
        cout << "Строки с длиной " << m << " были записаны в новый файл " << new_filename << "." << endl;
    }