#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
class Attendence
{
    string date, clsSchRec[10], clsAttRec[10], clsMissRec[10];
    int clsSch, clsAtt;

public:
    Attendence()
    {
        date = "", clsSch = 0, clsAtt = 0;
    }
    void input()
    {
        cout << "Enter the Date : ";
        cin >> date;
        cout << "Enter the no. of Class Scheduled : ";
        cin >> clsSch;
        cout << "Enter the no. of class Attended: ";
        cin >> clsAtt;
        cout << "Enter the complete Record of Today's Classes" << endl;
        for (int i = 0; i < clsSch; i++)
        {
            cin >> clsSchRec[i];
        }
        if (clsAtt != 0)
        {
            cout << "Enter the complete Record (in numbers only) of Today's Classes you were present in" << endl;
            for (int i = 0; i < clsAtt; i++)
            {
                cin >> clsAttRec[i];
            }
        }
        if ((clsSch - clsAtt) != 0)
        {
            cout << "Enter the complete Record (in numbers only) of Today's Classes you were absent in (with reason)" << endl;
            for (int i = 0; i < (clsSch - clsAtt); i++)
            {
                cin >> clsMissRec[i];
            }
        }
    }
    void addData()
    {
        ofstream file("AttendenceTracker.md", ios::app);
        file << "|" << date << "|" << clsSch << "|" << clsAtt << "|";
        for (int i = 0; i < clsSch; i++)
        {
            if (i != clsSch - 1)
            {
                file << clsSchRec[i] << ",";
            }
            else
            {
                file << clsSchRec[i] << "|";
            }
        }
        for (int i = 0; i < clsAtt; i++)
        {
            if (i != clsAtt - 1)
            {
                file << clsAttRec[i] << ",";
            }
            else
            {
                file << clsAttRec[i] << "|";
            }
        }
        for (int i = 0; i < (clsSch - clsAtt); i++)
        {
            if (i != (clsSch - clsAtt) - 1)
            {
                file << clsMissRec[i] << ",";
            }
            else
            {
                file << clsMissRec[i] << "|";
            }
        }
    }
    void updateAvg()
    {
        int totalSch, totalAtt;
        double avgAtt;
        ifstream file("AttendenceAvg.md");
        if (file.is_open())
        {
            file >> totalSch;
            file >> totalAtt;
            file.close();

            totalSch += clsSch;
            totalAtt += clsAtt;

            avgAtt = (static_cast<double>(totalAtt) / totalSch) * 100;

            ofstream fileout("AttendenceAvg.md");
            if (fileout.is_open())
            {
                fileout << totalSch << '\n';
                fileout << totalAtt << '\n';
                fileout << avgAtt << '\n';
                fileout.close();
            }
            else
            {
                cerr << "Unable to open output file" << endl;
                return;
            }
        }
        else
        {
            cerr << "Unable to open input file" << endl;
            return;
        }
    }
};

int main(int argc, char const *argv[])
{
    Attendence tracker;
    tracker.input();
    tracker.addData();
    tracker.updateAvg();
    return 0;
}
