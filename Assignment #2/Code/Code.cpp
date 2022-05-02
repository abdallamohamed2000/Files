#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
class FixedLengthRecord
{

public:

    int InsertValue(char* indexfile, int iToken, int iKey)
    {

        vector<pair<int, int>> Rec;
        vector<int> locate_ind;
        int num_Blocks = 1;
        ifstream RecFile;
        ofstream TheIndexedFile;
        RecFile.open(indexfile);
        TheIndexedFile.open("NewFile.txt");
        string NumOfRecord, NumOfBlock, k, v;
        getline(RecFile, NumOfRecord);
        getline(RecFile, NumOfBlock);
        getline(RecFile, k);
        getline(RecFile, v);
        vector<string> Ikey;
        vector<string> Itok;
        Ikey = Extract_values(k, '|', stoi(NumOfBlock), stoi(NumOfRecord));
        Itok = Extract_values(v, '|', stoi(NumOfBlock), stoi(NumOfRecord));

        int count = 1;
        for (int j = 2; j < Ikey.size(); j++)
        {
            if (Ikey[j] != " " && Ikey[j] != "#")
            {
                if (count == 1)
                    num_Blocks++;
                Rec.push_back(make_pair(stoi(Ikey[j]), stoi(Itok[j])));
                locate_ind.push_back(count);
                count++;
            }
            if (Ikey[j] == " ")
                count++;
            if (count > stoi(NumOfBlock))
                count = 1;
        }
        int ind = 0;
        if (locate_ind.size() > 0)
            ind = locate_ind[locate_ind.size() - 1];

        Rec.push_back(make_pair(iKey, iToken));
        if ((ind + 1) % (stoi(NumOfRecord) - 1) == 1 && ind > 0)
        {
            num_Blocks++;
            locate_ind[locate_ind.size() - 1] = 1;
            locate_ind.push_back(2);
        }
        else
            locate_ind.push_back(ind + 1);

        sort(Rec.begin(), Rec.end());
        if (num_Blocks == 1)  num_Blocks++;
        TheIndexedFile << NumOfRecord << "\n";
        TheIndexedFile << NumOfBlock << "\n";

        int index_ = 0;
        vector<int> Last_Blocks;
        int E = 0, EB = 0;
        bool F = 0;
        bool enough = false;
        if (ind == 0) ind++;
        TheIndexedFile << 1 << "|";
        for (int w = 2; w <= stoi(NumOfBlock); w++)
        {
            if (num_Blocks > w)
                TheIndexedFile << w;
            else
                TheIndexedFile << -1;
            for (int j = 1; j < stoi(NumOfRecord); j++)
            {
                if (!enough)
                {
                    if (j == locate_ind[index_])
                    {
                        TheIndexedFile << "|" << Rec[index_].first;
                        index_++;
                        if (index_ == locate_ind.size()) enough = true;
                    }
                    else
                    {
                        TheIndexedFile << "|" << " ";
                    }
                }
                else
                {
                    if (!F)  E++;
                    TheIndexedFile << "|" << " ";
                }
                if (j == stoi(NumOfRecord) - 1)
                {
                    TheIndexedFile << "|";
                    if (num_Blocks >= w)
                        Last_Blocks.push_back(Rec[index_ - 1].first);
                }
            }
            if (!F)
            {
                if (E == stoi(NumOfRecord) - 1)
                {
                    EB = w;
                    F = 1;
                }
            }
            E = 0;
        }
        TheIndexedFile << "\n";
        index_ = 0;
        enough = 0;
        if (EB != 0)
            TheIndexedFile << EB - 1 << "|";
        else
            TheIndexedFile << -1 << "|";
        for (int i = 2; i <= stoi(NumOfBlock); i++)
        {
            if (Last_Blocks.size() >= i - 1)
                TheIndexedFile << Last_Blocks[i - 2];
            else if (i == stoi(NumOfBlock))
                TheIndexedFile << -1;
            else
                TheIndexedFile << i;
            for (int j = 1; j < stoi(NumOfRecord); j++)
            {
                if (!enough)
                {
                    if (locate_ind[index_] == j)
                    {
                        TheIndexedFile << "|" << Rec[index_].second;
                        index_++;
                        if (locate_ind.size() == index_) enough = 1;
                    }
                    else
                    {
                        TheIndexedFile << "|" << " ";
                    }
                }
                else
                    TheIndexedFile << "|" << " ";
                if (j == stoi(NumOfRecord) - 1)
                {
                    TheIndexedFile << "|";
                }
            }
        }
        TheIndexedFile.close();
        RecFile.close();
        remove(indexfile);
        rename("NewFile.txt", indexfile);
        return num_Blocks;
    }
    int GetKey(char* indexfile, int iBlock, int iRecord)
    {
        ifstream RecFile;
        RecFile.open(indexfile);
        string NumOfRecord, NumOfBlock, k, v;
        vector<string> Ikey;
        getline(RecFile, NumOfRecord);
        getline(RecFile, NumOfBlock);
        getline(RecFile, k);
        getline(RecFile, v);
        Ikey = Extract_values(k, '|', stoi(NumOfBlock), stoi(NumOfRecord));
        RecFile.close();
        int i = stoi(NumOfRecord) * (iBlock)+iRecord - 2 * stoi(NumOfRecord);
        return stoi(Ikey[i]);
    }
    int GetVal(char* indexfile, int iBlock, int iRecord)
    {
        ifstream RecFile;
        RecFile.open(indexfile);
        string NumOfRecord, NumOfBlock, k, v;
        vector<string> Ikey;
        vector<string> Itok;
        getline(RecFile, NumOfRecord);
        getline(RecFile, NumOfBlock);
        getline(RecFile, k);
        getline(RecFile, v);
        Itok = Extract_values(v, '|', stoi(NumOfBlock), stoi(NumOfRecord));
        int i = stoi(NumOfRecord) * (iBlock)+iRecord - 2 * stoi(NumOfRecord);
        return stoi(Itok[i]);
    }
    int GetBlockIndex(char* indexfile, int iToken)
    {
        ifstream RecFile;
        RecFile.open(indexfile);
        string NumOfRecord, NumOfBlock, k, v;
        vector<string> Ikey;
        vector<string> Itok;
        getline(RecFile, NumOfRecord);
        getline(RecFile, NumOfBlock);
        getline(RecFile, k);
        getline(RecFile, v);
        Itok = Extract_values(v, '|', stoi(NumOfBlock), stoi(NumOfRecord));
        int i = 0;
        for (; i < Itok.size(); i++)
        {
            if (Itok[i] != " " && Itok[i] != "#")
            {
                if (stoi(Itok[i]) == iToken)
                    break;
            }
        }
        return (i / stoi(NumOfRecord)) + 2;
    }
    int GetRecordIndex(char* indexfile, int iToken)
    {
        ifstream RecFile;
        RecFile.open(indexfile);

        string NumOfRecord, NumOfBlock, k, v;
        vector<string> Ikey;
        vector<string> Itok;
        getline(RecFile, NumOfRecord);
        getline(RecFile, NumOfBlock);
        getline(RecFile, k);
        getline(RecFile, v);
        Itok = Extract_values(v, '|', stoi(NumOfBlock), stoi(NumOfRecord));
        int i = 0;
        for (; i < Itok.size(); i++)
        {
            if (Itok[i] != " " && Itok[i] != "#")
            {
                if (stoi(Itok[i]) == iToken)
                    break;
            }
        }

        return  (i % stoi(NumOfRecord));
    }
    void DeleteKey(char* indexfile, int iToken)
    {
        ifstream RecFile;
        ofstream TheIndexedFile;
        bool Flag = false;
        int j;
        vector<pair<int, int>> Rec;
        vector<int> locate_ind;
        int num_Blocks = 1;
        RecFile.open(indexfile);
        TheIndexedFile.open("NewFile.txt");
        string NumOfRecord, NumOfBlock, k, v;
        vector<string> Ikey;
        vector<string> Itok;
        getline(RecFile, NumOfRecord);
        getline(RecFile, NumOfBlock);
        getline(RecFile, k);
        getline(RecFile, v);
        Ikey = Extract_values(k, '|', stoi(NumOfBlock), stoi(NumOfRecord));
        Itok = Extract_values(v, '|', stoi(NumOfBlock), stoi(NumOfRecord));

        int count = 1;
        int index_d = -1;
        for (j = 2; j < Ikey.size(); j++)
        {
            if (Ikey[j] != " " && Ikey[j] != "#")
            {
                if (stoi(Itok[j]) == iToken)
                {
                    if (locate_ind.size() > 0)
                    {
                        index_d = locate_ind.size() - 1;

                    }
                }
                else
                {
                    Rec.push_back(make_pair(stoi(Ikey[j]), stoi(Itok[j])));
                    locate_ind.push_back(count);
                }

                if (count == 1)
                    num_Blocks++;
                count++;
            }
            if (Ikey[j] == " ")
                count++;
            if (count > stoi(NumOfBlock))
                count = 1;
        }
        int R = GetRecordIndex(indexfile, iToken);
        if (locate_ind[index_d + 1] == R)
            locate_ind[index_d + 1] = R - 1;
        int B = -1;
        if (locate_ind[index_d] < stoi(NumOfRecord) - 2 && R == 2)
        {
            locate_ind[index_d + 1] = locate_ind[index_d] + 1;
            B = GetBlockIndex(indexfile, iToken);
            num_Blocks--;
        }


        TheIndexedFile << NumOfRecord << "\n";
        TheIndexedFile << NumOfBlock << "\n";
        int index_ = 0;
        vector<int> Last;
        int E = 0;
        int EB = 0;
        bool enough = 0, F = 0;
        if (num_Blocks <= 0)
            TheIndexedFile << -1 << "|";
        else
            TheIndexedFile << 1 << "|";
        for (int i = 2; i <= stoi(NumOfBlock); i++)
        {
            if (B == i)
                TheIndexedFile << -1;
            else if (B - 1 == i)
                TheIndexedFile << i + 1;
            else if (num_Blocks > i && i != stoi(NumOfRecord))
                TheIndexedFile << i;
            else
                TheIndexedFile << -1;
            for (int j = 1; j < stoi(NumOfRecord); j++)
            {
                if (B != i && !enough)
                {
                    if (locate_ind[index_] == j)
                    {
                        TheIndexedFile << "|" << Rec[index_].first;
                        index_++;
                        if (index_ == locate_ind.size()) enough = true;
                    }
                    else
                        TheIndexedFile << "|" << " ";
                }
                else
                {
                    if (!F) E++;
                    TheIndexedFile << "|" << " ";
                }
                if (j == stoi(NumOfRecord) - 1)
                {
                    if (B != i)
                    {
                        if (num_Blocks >= i - 1)
                            Last.push_back(Rec[index_ - 1].first);
                    }

                    TheIndexedFile << "|";
                }
            }
            if (!F)
            {
                if (E == stoi(NumOfRecord) - 1)
                {
                    F = true;
                    EB = i;

                }
            }
            E = 0;
        }
        TheIndexedFile << "\n";

        if (EB != 0)
            TheIndexedFile << EB - 1 << "|";
        else
            TheIndexedFile << -1 << "|";
        index_ = 0;
        enough = 0;
        int ii = -1;
        for (int i = 2; i <= stoi(NumOfBlock); i++)
        {
            if (B == i)
            {
                TheIndexedFile << -1;
            }
            else if (Last.size() >= i - 2)
            {
                ii++;
                TheIndexedFile << Last[ii];
            }
            else if (i == stoi(NumOfBlock))
                TheIndexedFile << -1;
            else
                TheIndexedFile << i;
            for (int j = 1; j < stoi(NumOfRecord); j++)
            {
                if (B != i && !enough)
                {
                    if (locate_ind[index_] == j)
                    {
                        TheIndexedFile << "|" << Rec[index_].second;
                        index_++;
                        if (index_ == locate_ind.size()) enough = 1;
                    }
                    else
                        TheIndexedFile << "|" << " ";
                }
                else
                    TheIndexedFile << "|" << " ";
                if (j == stoi(NumOfRecord) - 1)
                {
                    TheIndexedFile << "|";
                }
            }
        }
        TheIndexedFile.close();
        RecFile.close();
        remove(indexfile);
        rename("NewFile.txt", indexfile);
    }
    int FirstEmptyBlock(const char* indexfile)
    {
        ifstream RecFile;
        RecFile.open(indexfile);
        string NumOfRecord, NumOfBlock, k, v;
        vector<string> Ikey;
        vector<string> Itok;
        getline(RecFile, NumOfRecord);
        getline(RecFile, NumOfBlock);
        getline(RecFile, k);
        getline(RecFile, v);
        Itok = Extract_values(v, '|', stoi(NumOfBlock), stoi(NumOfRecord));
        int count = 1;
        int i = 0;
        int empty = 0;
        for (int j = 2; j < Itok.size(); j++)
        {
            if (Itok[j] != " " && Itok[j] != "#")
                count++;
            if (Itok[j] == " ")
            {
                empty++;
                count++;
            }
            if (count > stoi(NumOfBlock))
            {
                count = 1;
                if (empty == stoi(NumOfRecord) - 1)  break;
                i++;
            }
        }

        return i;

    }

    vector<string> Extract_values(string sentence, char delimiter, int NumOfBlock, int NumOfRecord)
    {
        string character_ = "";
        vector<string> Word;
        int i = 0;

        while (i < sentence.length())
        {
            if (sentence[i] == delimiter)
            {
                Word.push_back(character_);
                character_ = "";
            }
            else
                character_ += sentence[i];
            i++;
        }
        Word[0] = '#';
        for (i = 1; i < ((NumOfBlock - 1) * NumOfRecord + 1); i += NumOfRecord)
        {
            Word[i] = '#';
        }
        return Word;
    }
    bool CreateFileRec(char* indexfile, int NumOfBlock, int NumOfRecord)
    {
        ofstream outfile;
        outfile.open(indexfile);
        if (!outfile)
        {
            cout << "Faling open file" << endl;
            return false;
        }

        int empty_value = -1;
        outfile << NumOfRecord << '\n';
        outfile << NumOfBlock << '\n';
        for (int i = 0; i < NumOfBlock; i++)
        {
            outfile << empty_value;
            if (i == 0)
            {
                outfile << '|';
                continue;
            }
            for (int j = 0; j < NumOfRecord; j++)
            {
                outfile << '|' << " ";
            }
        }
        outfile << endl;

        for (int i = 1; i <= NumOfBlock; i++)
        {
            if (i == NumOfBlock)
                outfile << empty_value;
            else
                outfile << i;
            if (i == 1)
            {
                outfile << '|';
                continue;
            }
            for (int j = 0; j < NumOfRecord; j++)
            {
                outfile << '|' << " ";
            }
        }
        return true;
    }

};
int main()
{
    char* indexfile;
    char filename[] = "file.txt";
    indexfile = filename;
    FixedLengthRecord NewRecord;
    NewRecord.CreateFileRec(indexfile, 4, 5);
    NewRecord.InsertValue(indexfile, 5, 1);
    NewRecord.InsertValue(indexfile, 18, 4);
    NewRecord.InsertValue(indexfile, 27, 5);
    NewRecord.InsertValue(indexfile, 88, 2);
    NewRecord.InsertValue(indexfile, 20, 3);
    NewRecord.InsertValue(indexfile, 4, 8);
    NewRecord.InsertValue(indexfile, 11, 9);
    NewRecord.InsertValue(indexfile, 15, 7);
    NewRecord.DeleteKey(indexfile, 15);
    NewRecord.DeleteKey(indexfile, 88);
    NewRecord.DeleteKey(indexfile, 18);
    cout << "finish";
    return 0;
}

