#ifndef RANDOMFILE_H
#define RANDOMFILE_H

#include <string>
#include <vector>
struct Baggage {
    char name[20]; // Название багажа
    float weight;  // Вес багажа
};

using namespace std;

    class RandomFile {
    public:
        static void createAndFillBinaryFile(const string& filename, int numValues, int minValue, int maxValue); // Создание и заполнение файла
        static void printAndCalculateOddProduct(const string& filename); // Вывод содержимого и произведение нечётных чисел
        static void transformToMatrixAndSave(const string& inputFilename, const string& outputFilename, int n); // Переписать в матрицу и сохранить
        static void fillBaggageFile(const string& filename); // Метод для заполнения файла багажом
        static void analyzeBaggageFile(const string& filename); // Анализ файла багажа
        static void createRandomTextFile(const string& fileNamePrefix);    // Метод для создания текстовых файлов с случайными числами
        static void printFileAndSumSquares(const string& filename);// Метод для вывода содержимого файла и нахождения суммы квадратов
        static void fillFileWithRandomNumbers(const string& filename);  // Метод для заполнения текстового файла случайными числами
        static void readFileAndComputeProduct(const string& filename);  // Метод для считывания чисел из файла и нахождения произведения
        static void processFileByLineLength(const string& filename, const string& new_filename, int m); // Метод для поиска строк искомой длины
    };



#endif // RANDOMFILE_H
