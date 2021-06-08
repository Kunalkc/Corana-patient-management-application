/*
PROJECT NAME- COVID 19 PATIENT MANAGEMENT SYSTEM

STUDENTS INVOLVED- NAME-KUNAL CHANDEL  ROLL NO - 195004
                   NAME-SHAURYA SHARMA ROLL NO -195014

OBJECTIVE- TO RECORD NEW PATIENT ENTRIES CONTAINING INFORMATION
           ABOUT PATIENT AND SEVERITY OF DISEASE TO A FILE  AND FURTHER DISPLAY ACCORDING
           TO THE NEEDS OF USER BY UNIQUE ID OR SORTED AS REC OR DEAD PATIENTS OR FURTHER SORTED
           ON THE BASIS OF SEVERITY OF THE DISEASE, AND TO MAINTAIN RECORD OF TOTAL DEAD AND RECOVERED PATIENTS

INPUT - ON START OF THE PROGRAM U SEE A MENU , WITH OPTIONS TO MAKE NEW ENTRY , DISPLAY DATA (VARIOUS OPTIONS FURTHER),AND MODIFY
        OUTCOME OF A PATIENT
        1. TO MAKE NEW ENTRY CHOOSE NEW PATIENT AND U WILL BE ASKED TO ENTER PATIENT DETAILS
        3 MODIFY- TO REPORT A DEATH OR RECOVERY (AGAIN ENTRY NEEDED TO BE MADE BEFORE)

OUTPUT-
        2. DISPLAY - AS ONLY CPP FILE IS TO BE SUBMITTED THEREFORE THEIR WILL BE NO RECORD TO DISPLAY OR SORT BEFORE U MAKE AN ENTRY
        AFTER THEIR IS RECORD TO BE DISPLAYED USER CAN CHOOSE ON HOW TO DISPLAY THAT DATA(SORTED ACC TO SEVERITY , OUTCOME OF A CASES ETC
*/
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
using namespace std;

//      WE HAVE USED A PATIENT CLASS CONTAINING ALL THE DETAILS AND FUNCTIONALITY WE ARE GOING TO USE IN OUR PROGRAM FOR PATIENTS    //
class patient {
    int age;
    char name[30];
    char gender[8];
    int bp;
    int rectemp;
    void condition();



    static int inf;


public:
    char status;
    char cond;
    int patientid;//SUPPOSSED TO BE UNIQUE
    // VARIOUS STATIC MEMBERS AND METHODS TO MANIPULATE AND STORE IN A FILE TOTAL NO OF DEAD AND RECOVERED PATIENTS
    static void setid(int o)
    {
        inf = o;
    }
    static int retid()
    {
        return inf;
    }
    static int retdead()
    {
        return dead;
    }
    static int retrec()
    {
        return rec;
    }
    static int dead;
    static void setdead(int o)
    {
        dead = o;
    }
    static int rec;
    static void setrec(int o)
    {
        rec = o;
    }
    static void incdead()
    {
        dead++;
    }
    static void increc()
    {
        rec++;
    }
    //CONSTRUCTORS AS EVERY PATIENT ENTRY WILL BE OF ALIVE PATIENTS AT FIRST
    patient()
    {
        status = 'L';
    }
    void statusded()
    {
        status = 'D';
    }
    void statusrec()
    {
        status = 'R';
    }
    void newentry(void);//FUNCTION TO RECORD THE DETAILS OF A NEW PATIENT
    void displaydata();//TO DISPLAY
    void modifydata();//TO CHANGE STATUS OF A PATIENT IN CASE OF THEIR DEMISE OR RECOVERY
    void tabulardisplay();
};
int patient::dead = 0;
int patient::rec = 0;
int patient::inf = 190000;

//       DECLARATION OF MEMBER FUNCTIONS OF PATIENT CLASS    
void patient::newentry(void)
{
    cout << "Enter Patient's Name" << endl;
    cin.ignore();
    cin.getline(name, 30);
    //stringstream id;
    //id << inf;
    //string s;
    //id >> s;
    //patientid = "cv" + s;
    patientid = inf;
    cout << "Enter gender" << endl;
    cin.getline(gender, 8);
    cout << "Enter age" << endl;
    cin >> age;
    cout << "Enter recorded blood pressure" << endl;
    cin >> bp;
    cout << "Enter recorded temperature" << endl;
    cin >> rectemp;
    inf++;
    condition();
    cout <<endl<<endl<< "Patient id(note down for further ref)---" << patientid << endl;
}

void patient::condition() {
error:
    cout <<endl<< "Choose patient condition" << endl << "1.Asymptomatic(A)" << endl << "2.Mild Symptoms(m)" << endl << "3.Moderate Symptoms(M)" << endl << "4.Critical(S)" << endl;
    int i;
    cin >> i;
    switch (i) {
    case 1: cond = 'A';
        break;
    case 2: cond = 'm';
        break;
    case 3: cond = 'M';
        break;
    case 4: cond = 'S';
        break;
    default:cout << "invalid input";
        goto error;
    }
}
void patient::modifydata() {
    int r;
    cout <<endl<< "To change patient status from alive to dead press 1" << endl;
    cin >> r;
    if (r == 1)
    {
        status = 'D';
    }

}
void patient::displaydata()
{
    cout << "NAME - " << name << endl;
    cout << "GENDER- " << gender << endl;
    cout << "PATIENT ID- " << patientid << endl;
    cout << "AGE - " << age << endl;
    cout << "INITIAL TEMP- " << rectemp << endl;
    cout << "BLOOD PRESSURE- " << bp << endl;
    cout << "OUTCOME- " << status << endl;
    cout << "CONDITION - " << cond << endl;
    cout << "\n========================================\n";

}


// VARIOUS PROGRAM FUNCTIONS TO MANIPULATE OR DISPLAY DATA AT RUNTIME
void newpatient()//NEW PATIENT ENTRY
{
    patient p;
    p.newentry();
    ofstream outfile;
    outfile.open("patient.txt", ios::app);
    if (!outfile)
    {
        cout << "error" << endl;
    }
    outfile.write((char*)&p, sizeof(p));
    outfile.close();
    cout << "patient record created" << endl;
}
//MODIFY FUNC TO CHANGE STATUS FROM ALIVE TO RECOVERED OR DEAD
void modifymenu()
{
    int q;
    
    cout << "Press 1 to report death\nPress 2 to report recovery" << endl;
    cin >> q;
    switch (q)
    {
    case 1:patient::incdead();
        break;
    case 2:patient::increc();
        break;
    }
    bool found = false;
    patient p;
    int pi;
    cout <<endl<< "Enter patient id" << endl;
    cin >> pi;
    ifstream inFile;
    inFile.open("patient.txt", ios::in);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream outFile;
    outFile.open("Temp.txt", ios::out);
    inFile.seekg(0, ios::beg);
    while (inFile.read((char*)&p, sizeof(p)))
    {
        if (p.patientid != pi)
        {
            outFile.write((char*)&p, sizeof(p));
        }
        if (p.patientid == pi && q == 1)
        {
            p.statusded();
            p.displaydata();
            outFile.write((char*)&p, sizeof(p));
        }
        if (p.patientid == pi && q == 2)
        {
            p.statusrec();
            p.displaydata();
            outFile.write((char*)&p, sizeof(p));
        }
    }
    outFile.close();
    inFile.close();
    remove("patient.txt");
    rename("Temp.txt", "patient.txt");
    cout << "\n\n\tRecord updated";
    cin.ignore();
    cin.get();

 

}

//TO READ VALUES TO STATIC VARIABLES OF PATIENT CLASS FROM PRE EXISTING FILE
void set()
{

    ifstream infile;
    int q;
    infile.open("deadcount.txt", ios::in);
    if (!infile)
    {
        cout << "Press any Key...";
        cin.ignore();
        cin.get();
        q = 0;
        return;
    }
    else
    {
        infile >> q;
    }
    patient::setdead(q);
    infile.close();
    ifstream ifile;
    ifile.open("reccount.txt", ios::in);
    if (!ifile)
    {
        cout << "Press any Key...";
        cin.ignore();
        cin.get();
        q = 0;
        return;
    }
    else
    {
        ifile >> q;
    }
    patient::setrec(q);
    ifile.close();

    ifstream id;
    id.open("id.txt", ios::in);
    id >> q;
    patient::setid(q);
    id.close();

}

void display_all()
{
    patient p;
    ifstream inFile;
    inFile.open("patient.txt", ios::in);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        cin.ignore();
        cin.get();
        return;
    }
    cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    inFile.seekg(0);
    while (inFile.read((char*)&p, sizeof(p)))
    {
        p.displaydata();
        cout << "\n\n====================================\n";
    }
    inFile.close();
}
void conddisplay()
{
    int a;
    char pi;
    cout << "Enter 1 for Severe patients"<<endl<<"Enter 2 for Mild symtom patients"<<endl<<"Enter 3 for Moderate symtom patients"<<endl<<"Enter 4 for Asymptomatic" << endl;
    cout << "\n\n\n========================================================================\n";
    cin >> a;
    switch (a)
    {
    case 1: pi = 'S';
        break;
    case 2: pi = 'm';
        break;
    case 3: pi = 'M';
        break;
    case 4: pi = 'A';
        break;
    }
    patient p;
    ifstream infile;
    infile.open("patient.txt", ios::in);
    if (!infile)
    {
        cout << "File could not be open !! Press any Key...";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag = false;
    while (infile.read((char*)&p, sizeof(p)))
    {
        if (p.cond == pi && p.status == 'L')
        {
            p.displaydata();
            cout << "\n=====================================================\n\n";
            flag = true;
        }
    }
    infile.close();
    if (flag == false)
        cout << "\n\nrecord not exist";
    cin.ignore();
    cin.get();
}
void outcomed()
{
    int a;
    char pi;
    cout <<endl<< "Enter 1 for dead"<<endl<<"Enter 2 for recovered" << endl;
    cout << "\n\n\n========================================================================\n";
    cin >> a;
    switch (a)
    {
    case 1: pi = 'D';
        break;
    case 2: pi = 'R';
        break;
    }
    patient p;
    ifstream infile;
    infile.open("patient.txt", ios::in);
    if (!infile)
    {
        cout << "File could not be open !! Press any Key...";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag = false;
    while (infile.read((char*)&p, sizeof(p)))
    {
        if (p.status == pi)
        {
            p.displaydata();
            flag = true;
        }
    }
    infile.close();
    if (flag == false)
        cout << "\n\nrecord not exist";
    cin.ignore();
    cin.get();
}
void displaymenu();
//MAIN MENU
void mainmenu() {
    int a;
    set();
    cout << "\n\nENTER THE INDEX OF THE OPTION YOU WANT TO CHOOSE" << endl;
    cout << "\n1> NEW PATIENT ENTRY \n2>MODIFY STATUS OF EXISTING PATIENT\n3>DISPLAY RECORDS" << endl;
    cout << "\n\n====================================================\n\n\n" << endl;
    cin >> a;
    switch (a)
    {
    case 1: newpatient();
        break;
    case 2: modifymenu();
        break;
    case 3: displaymenu();
        break;
    default:cout << "INVALID INPUT";
    }
}
//TO MOVE DATA FROM STATIC MEMBERS OF PATIENT BACK INTO FILE
void writetofiles()
{
    ofstream outfile;
    outfile.open("deadcount.txt", ios::out);
    outfile << patient::retdead();
    outfile.close();
    ofstream ofile;
    ofile.open("reccount.txt", ios::out);
    ofile << patient::retrec();
    ofile.close();
    ofstream id;
    id.open("id.txt", ios::out);
    id << patient::retid();
    id.close();

}
//TO DISPLAY THE DATA AS PER REQUIREMENT
void displaymenu() {

    int q;
    cout << "\n\nENTER THE INDEX OF THE OPTION YOU WANT TO CHOOSE" << endl;
    cout << "\n1>TOTAL CAUSUALTIES\n2>TOTAL RECOVERIES\n3>ENTER PATIENT ID FOR DETAILS\n4>DISPLAY EVERY PATIENT DATA\n5>DISPLAY SORTED BASED ON CONDITION\n6>BASED ON OUTCOME" << endl;
    cout << "\n\n\n==============================================================================\n\n\n";
    cin >> q;
    switch (q)
    {
    case 1:cout << patient::retdead() << endl;
        break;
    case 2:cout << patient::retrec() << endl;
        break;
    case 3:
    {
        int pi;
        cout << endl << "Enter patient id" << endl;
        cin >> pi;
        patient p;
        ifstream infile;
        infile.open("patient.txt", ios::in);
        if (!infile)
        {
            cout << "File could not be open !! Press any Key...";
            cin.ignore();
            cin.get();
            return;
        }
        bool flag = false;
        while (infile.read((char*)&p, sizeof(p)))
        {
            if (p.patientid == pi)
            {
                p.displaydata();
                flag = true;
            }
        }
        infile.close();
        if (flag == false)
            cout << "\n\nrecord not exist";
        cin.ignore();
        cin.get();
        break;
    }
    case 4:display_all();
        break;
    case 5:conddisplay();
        break;
    case 6: outcomed();
        break;
    default:"Invalid!!!!";
    };
    int i;
    cout <<endl<< "Enter 1 to go to Main Menu" << endl << "Enter 2 to go to Display Data Menu" << endl << "Enter 3 to Exit";
    cin>> i;
    switch (i) {
    case 1:mainmenu();writetofiles();
        break;

    case 2:writetofiles();displaymenu();
    case 3:writetofiles();exit(0);
    }

}

//OUR ONE AND ONLY MAIN FUNCTION
int main()
{
    cout << setw(50) << "COVID 19 PATIENT MANAGEMENT SYSTEM" << setw(10) << endl;
    cout <<endl<< "Press Enter if u dont see the Menu." << endl;
    set();
    mainmenu();
    writetofiles();
    cout <<endl<< "*************";
    cout <<endl<<endl<< "Press 1 for Main Menu" << endl << "Press 2 to Exit" << endl;
    int j;
    cin >> j;
    switch (j) {
    case 1:mainmenu();writetofiles();
    case 2:return 0;
    }
    
  
}
