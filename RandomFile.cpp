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


    // ����� �������� � ���������� ��������� ����� ���������� �������
    void RandomFile::createAndFillBinaryFile(const string& filename, int numValues, int minValue, int maxValue) {
        ofstream outFile(filename, ios::binary);

        if (!outFile) {
            cerr << "������ ��� �������� ����� ��� ������: " << filename << endl;
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
        cout << "���� \"" << filename << "\" ������� ������ � ��������." << endl;
    }

    // ����� ������ ����������� ����� � �������� ������������ �������� �����
    void RandomFile::printAndCalculateOddProduct(const string& filename) {
        ifstream inFile(filename, ios::binary);

        if (!inFile) {
            cerr << "������ ��� �������� ����� ��� ������: " << filename << endl;
            return;
        }

        cout << "���������� ����� \"" << filename << "\":" << endl;

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
            cout << "������������ ���� �������� �����: " << oddProduct << endl;
        }
        else {
            cout << "�������� ����� ����������� � �����." << endl;
        }

        inFile.close();
    }

    // ����� �������������� ������ � ������� � ���������� � ������ ����
    void RandomFile::transformToMatrixAndSave(const string& inputFilename, const string& outputFilename, int n) {
        ifstream inFile(inputFilename, ios::binary);
        ofstream outFile(outputFilename, ios::binary);

        if (!inFile) {
            cerr << "������ ��� �������� �������� �����: " << inputFilename << endl;
            return;
        }
        if (!outFile) {
            cerr << "������ ��� �������� ��������� �����: " << outputFilename << endl;
            return;
        }

        vector<int> data; // ��������� �������� �� �������� �����
        int value;

        // ������ ������ �� �������� �����
        while (inFile.read(reinterpret_cast<char*>(&value), sizeof(value))) {
            data.push_back(value);
        }

        // �������� ���������� ������� n x n
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        size_t index = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (index < data.size()) {
                    matrix[i][j] = data[index++];
                }
            }
        }

        // ����� ������� �� ������
        cout << "������� �� ������:" << endl;
        for (const auto& row : matrix) {
            for (int elem : row) {
                cout << setw(5) << elem;
            }
            cout << endl;
        }

        // ���������: �������� ������� ����������� � ������������ �������� � ������ �������
        for (int j = 0; j < n; ++j) {
            int minVal = matrix[0][j], maxVal = matrix[0][j];
            int minIdx = 0, maxIdx = 0;

            for (int i = 1; i < n; ++i) {
                if (matrix[i][j] < minVal) {
                    minVal = matrix[i][j];
                    minIdx = i;
                }
                // ���� �� �������� �������� �� ��� ������, �� ���� �������� �������� ��� :)
                if (matrix[i][j] > maxVal) {
                    maxVal = matrix[i][j];
                    maxIdx = i;
                }
            }

            // ������ ������� ����������� � ������������ ��������
            swap(matrix[minIdx][j], matrix[maxIdx][j]);
        }

        // ����� ������� ����� ������
        cout << "������� ����� ������:" << endl;
        for (const auto& row : matrix) {
            for (int elem : row) {
                cout << setw(5) << elem;
            }
            cout << endl;
        }

        // ��������� ������� � �������� ����
        for (const auto& row : matrix) {
            for (int elem : row) {
                outFile.write(reinterpret_cast<const char*>(&elem), sizeof(elem));
            }
        }

        cout << "������� ��������� � ���� \"" << outputFilename << "\"." << endl;

        inFile.close();
        outFile.close();
    }
    // ����� ���������� ��������� ����� ����������� � ������
    void RandomFile::fillBaggageFile(const string& filename) {
        ofstream outFile(filename, ios::binary);

        if (!outFile) {
            cerr << "������ ��� �������� ����� ��� ������: " << filename << endl;
            return;
        }

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> passengerDist(1, 20);   // ��������� ���������� ����������
        uniform_int_distribution<> bagCountDist(1, 5);     // ���������� ������ ������
        uniform_int_distribution<> weightDist(1, 30);      // ��� ������� ������
        vector<string> baggageNames = { "�������", "�����", "�������", "������", "�����" };

        int numPassengers = passengerDist(gen); // ��������� ���������� ����� ����������
        cout << "��������� ���������� ����������: " << numPassengers << endl;

        for (int i = 0; i < numPassengers; ++i) {
            int numBaggage = bagCountDist(gen); // ��������� ���������� ������ ������

            for (int j = 0; j < numBaggage; ++j) {
                Baggage baggage;
                // ��������� �������� ������
                strcpy_s(baggage.name, baggageNames[bagCountDist(gen) % baggageNames.size()].c_str()); // ���������� strcpy_s
                // ��������� ���� ������
                baggage.weight = static_cast<float>(weightDist(gen));
                // ������ � ����
                outFile.write(reinterpret_cast<const char*>(&baggage), sizeof(Baggage));
            }

            // ��������� ������ ������ ��� ���������� ����������
            Baggage separator = { "", 0.0f };
            outFile.write(reinterpret_cast<const char*>(&separator), sizeof(Baggage));
        }

        outFile.close();
        cout << "���� \"" << filename << "\" ������� �������� ����������� � ������." << endl;
    }

    // ����� ������� ������ � ����� � ������, ������� ������� ����� ��������� �����
    void RandomFile::analyzeBaggageFile(const string& filename) {
        ifstream inFile(filename, ios::binary);

        if (!inFile) {
            cerr << "������ ��� �������� ����� ��� ������: " << filename << endl;
            return;
        }

        vector<int> baggageCounts;  // ������ ��� �������� ���������� ������ � ������� ���������
        int currentCount = 0;

        Baggage baggage;

        cout << "���������� �����:\n";
        while (inFile.read(reinterpret_cast<char*>(&baggage), sizeof(Baggage))) {
            // ������� ������ ������
            if (baggage.weight == 0.0f && strlen(baggage.name) == 0) {
                cout << "�������� " << baggageCounts.size() + 1 << ": " << endl;
                cout << "���������� ������ ������: " << currentCount << endl;
                baggageCounts.push_back(currentCount);
                currentCount = 0;
            }
            else {
                cout << "�����: " << baggage.name << ", ���: " << baggage.weight << " ��" << endl;
                ++currentCount;
            }
        }

        inFile.close();

        // ������� ���������� � ����� ��� ����� ��������� ������
        int moreThanTwo = count_if(baggageCounts.begin(), baggageCounts.end(), [](int count) {
            return count > 2;
            });

        // ������� ���������� � ����������� ������ ������ ��������
        double avg = accumulate(baggageCounts.begin(), baggageCounts.end(), 0.0) / baggageCounts.size();
        int moreThanAvg = count_if(baggageCounts.begin(), baggageCounts.end(), [avg](int count) {
            return count > avg;
            });

        cout << "\n����� ���������� � ����� ��� ����� ��������� ������: " << moreThanTwo << endl;
        cout << "����� ���������� � ����������� ������ ������ ��������: " << moreThanAvg << endl;

    }


    void RandomFile::createRandomTextFile(const string& filename) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> numValuesDist(1, 20);  // ��������� ���������� ���������� ����� � �����
    uniform_int_distribution<> valueDist(-50, 50); // ��������� ����� ����� �� -1000 �� 1000

    int numValues = numValuesDist(gen);  // ��������� ���������� ����� �������� � �����
    cout << "��������� ���� \"" << filename << "\" " << numValues << " ���������� �������." << endl;

    ofstream outFile(filename);

    if (!outFile) {
        cerr << "������ ��� �������� ����� ��� ������: " << filename << endl;
        return;
    }

    // ���������� ��������� �������� � ����
    for (int i = 0; i < numValues; ++i) {
        int randomValue = valueDist(gen);  // ��������� ���������� �����
        outFile << randomValue << endl;    // ������ ����� � ����
    }

    outFile.close();
    cout << "���� \"" << filename << "\" ������� ������." << endl;
}




// ����� ������ ����������� ����� � ���������� ����� ��������� ���������
    void RandomFile::printFileAndSumSquares(const string& filename) {
        ifstream inFile(filename);

        if (!inFile) {
            cerr << "������ ��� �������� ����� ��� ������: " << filename << endl;
            return;
        }

        int value;
        double sumOfSquares = 0.0;

        cout << "���������� ����� \"" << filename << "\":" << endl;
        while (inFile >> value) {
            cout << value << endl;             // ������� �����
            sumOfSquares += value * value;     // ��������� ������� ����� � �����
        }

        inFile.close();

        cout << "\n����� ��������� ��������� �����: " << sumOfSquares << endl;
    }

    // ����� ��� ���������� ���������� ����� ���������� �������
    void RandomFile::fillFileWithRandomNumbers(const string& filename) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> numLinesDist(1, 5);   // ���������� ����� �� 1 �� 5
        uniform_int_distribution<> numNumbersDist(1, 5);  // ���������� ����� � ������ �� 1 �� 5
        uniform_int_distribution<> valueDist(-50, 50);    

        int numLines = numLinesDist(gen);  // ��������� ���������� ���������� �����

        cout << "��������� ���� \"" << filename << "\" " << numLines << " �������� ��������� �����." << endl;

        ofstream outFile(filename);

        if (!outFile) {
            cerr << "������ ��� �������� ����� ��� ������: " << filename << endl;
            return;
        }

        for (int i = 0; i < numLines; ++i) {
            int numNumbers = numNumbersDist(gen);  // ��������� ���������� ���������� ����� � ������

            for (int j = 0; j < numNumbers; ++j) {
                int randomValue = valueDist(gen);  // ��������� ���������� �����
                outFile << randomValue << " ";     // ������ ����� � ������
            }
            outFile << endl;  // ������� ������ ����� ������� ���� �����
        }

        outFile.close();
        cout << "���� \"" << filename << "\" ������� ��������." << endl;
    }

    // ����� ��� ���������� ����� �� �����, ������ � ���������� ������������
    void RandomFile::readFileAndComputeProduct(const string& filename) {
        ifstream inFile(filename);

        if (!inFile) {
            cerr << "������ ��� �������� ����� ��� ������: " << filename << endl;
            return;
        }

        int value;
        long long product = 1;  // �������� � ������� ��� ������������

        cout << "���������� ����� \"" << filename << "\":" << endl;
        while (inFile >> value) {
            cout << value << " ";  // ������� �����
            product *= value;      // �������� �� �����
        }

        inFile.close();

        cout << "\n������������ ���� ����� � �����: " << product << endl;
    }

    // ����� ��� ������ �����, ������ ����������� � ������ ����� ������ m � ����� ����
    void RandomFile::processFileByLineLength(const string& filename, const string& new_filename, int m) {
        ifstream inFile(filename);
        ofstream outFile(new_filename);

        if (!inFile) {
            cerr << "������ ��� �������� ����� ��� ������: " << filename << endl;
            return;
        }
        if (!outFile) {
            cerr << "������ ��� �������� ����� ��� ������: " << new_filename << endl;
            return;
        }

        string line;
        cout << "���������� ����� \"" << filename << "\":" << endl;

        // ������ ���� ��������� � ��������� ����� ������ ������
        while (getline(inFile, line)) {
            cout << line << endl;  // ������� ������ �� �����
            if (line.length() == m) {
                outFile << line << endl;  // ���������� � ����� ����, ���� ����� ������ == m
                cout << "������������ ������: " << line << endl;  // ������� ������, ������� ���������� � ����� ����
            }
        }

        inFile.close();
        outFile.close();
        cout << "������ � ������ " << m << " ���� �������� � ����� ���� " << new_filename << "." << endl;
    }