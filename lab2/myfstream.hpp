#include "../lab1/CryptoLib.hpp"


vector<int64> make_m();
int put_fileOut(vector<int64> file_bits, const char * filePath);

vector<int64> make_m()
{
    fstream fileIn;
    vector<int64> file_bits;
    fileIn.open("net.txt", ios::in | ios::binary);
    if (!fileIn.is_open())
    {
        cout << "\ncannot open input file" << endl;
        file_bits.push_back(0);
        return file_bits;
    }
    else
    {
        fileIn.seekg(0, ios::end);
        int file_size = fileIn.tellg();
        fileIn.seekg(0, ios::beg);
        char ch;
        for (int i = 0; i < file_size; i++)
        {
            fileIn.read(&ch, sizeof(char));
            file_bits.push_back((int64)ch + 255);
        }

        fileIn.close();

        return file_bits;
    }
}

int put_fileOut(vector<int64> file_bits, const char * filePath)
{
    fstream fileOut;
    fileOut.open(filePath, ios::out | ios::binary);
    if (!fileOut.is_open())
    {
        cout << "\ncannot open output file" << endl;
        return 1;
    }
    else
    {
        for (int i = 0; i < file_bits.size(); i++)
        {
            file_bits[i] = file_bits[i] - 255;
        }

        for (uint i = 0; i < file_bits.size(); i++)
        {
            fileOut.write((char *)&file_bits[i], sizeof(char));
        }
        fileOut.close();
        return 0;
    }

}
