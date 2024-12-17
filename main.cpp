#include "RandomFile.h"
#include <iostream>
#include <locale>

using namespace std;

// funkcia proverka - ona proveraet na polzovatelya durachka
int proverka() {
    int value;
    while (true) {
        cin >> value;

        // �������� �� ������ �����
        if (cin.fail()) {
            // ���� ���� �� �������� ������
            cin.clear(); // ������� ���� ������
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���������� ������������ ����
            cout << "������! ����������, ������� ����� �����." << endl;
        }
        else if (value <= 0) {
            // ���� ����� �� �������������
            cout << "������! ����� ������ ���� �������������." << endl;
        }
        else {
            // ������� ���������� ������������� �����
            break;
        }
    }
    return value;
}

int main() {
    setlocale(LC_ALL, "Russian");

    // ����� ������
    int n;
    int m;
    string binfile = "random_numbers.bin";
    string matrixfile = "matrix.bin";
    string baggagefile = "baggage.bin";
    string txtfile = "txtfile.txt";  
    string randomtxtfile = "ochenrandomfile.txt";
    string textfile = "textfile.txt";
    string new_textfile = "new_textfile.txt";
    // �������� ������� ������
    RandomFile randomFile;
    cout << "������� 1" << endl;
    cout << "������� ���������� �����: ";
    n = proverka();

    // ���������� �������� ����� ���������� �������
    randomFile.createAndFillBinaryFile(binfile, n, -100, 100);

    
    randomFile.printAndCalculateOddProduct(binfile);
    
    cout << "������� 2" << endl;
    cout << "������� ������ �������:";
    n = proverka();

    // �������������� ������ � ������� 4x4 � ���������� � ������ ����
    randomFile.transformToMatrixAndSave(binfile, matrixfile, n);
    
    cout << "������� 3" << endl;

    // ���������� ����� �������
    randomFile.fillBaggageFile(baggagefile);

    // ������ ����� ������
    randomFile.analyzeBaggageFile(baggagefile);

    cout << "������� 4" << endl;

    // �������� ���������� �����
    randomFile.createRandomTextFile(txtfile);
    
    // ������� ����� ���������
    randomFile.printFileAndSumSquares(txtfile);

    cout << "������� 5" << endl;

    // ��������� ���������� ����� ��������� �����
    randomFile.fillFileWithRandomNumbers(randomtxtfile);

    // ������������ ��������� �����
    randomFile.readFileAndComputeProduct(randomtxtfile);
    
    cout << "������� 6" << endl;
    cout << "������� ����� ������� �����: ";
    m = proverka();
    // ���������� ����� ������ m
    randomFile.processFileByLineLength(textfile, new_textfile, m);



    return 0;
}
