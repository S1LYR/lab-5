#ifndef RANDOMFILE_H
#define RANDOMFILE_H

#include <string>
#include <vector>
struct Baggage {
    char name[20]; // �������� ������
    float weight;  // ��� ������
};

using namespace std;

    class RandomFile {
    public:
        static void createAndFillBinaryFile(const string& filename, int numValues, int minValue, int maxValue); // �������� � ���������� �����
        static void printAndCalculateOddProduct(const string& filename); // ����� ����������� � ������������ �������� �����
        static void transformToMatrixAndSave(const string& inputFilename, const string& outputFilename, int n); // ���������� � ������� � ���������
        static void fillBaggageFile(const string& filename); // ����� ��� ���������� ����� �������
        static void analyzeBaggageFile(const string& filename); // ������ ����� ������
        static void createRandomTextFile(const string& fileNamePrefix);    // ����� ��� �������� ��������� ������ � ���������� �������
        static void printFileAndSumSquares(const string& filename);// ����� ��� ������ ����������� ����� � ���������� ����� ���������
        static void fillFileWithRandomNumbers(const string& filename);  // ����� ��� ���������� ���������� ����� ���������� �������
        static void readFileAndComputeProduct(const string& filename);  // ����� ��� ���������� ����� �� ����� � ���������� ������������
        static void processFileByLineLength(const string& filename, const string& new_filename, int m); // ����� ��� ������ ����� ������� �����
    };



#endif // RANDOMFILE_H
