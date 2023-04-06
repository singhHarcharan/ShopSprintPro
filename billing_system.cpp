// Error when we try to add second product as administrator login

#include <iostream>
#include<fstream>       // for file handling operations
using namespace std;

class shopping{
    private:
        int pcode;      // product code
        float price;
        float dis;      // discount
        string pname;   // product name
    public:
        void menu();
        void administrator();
        void buyer();
        void add();
        void edit();
        void rem();     // Remove function
        void list();
        void receipt();
};

void shopping :: menu(){        // (::) denotes scope resolution function.
    m:
    int choice;
    string email;
    string password;
    
    cout << "\t\t\t\t ______________________________ \n";
    cout << "\t\t\t\t                                \n";
    cout << "\t\t\t\t     Supermarket Main Menu      \n";
    cout << "\t\t\t\t                                \n";
    cout << "\t\t\t\t ______________________________ \n";

    cout << "\t\t\t\t |  1) Administrator    |\n";
    cout << "\t\t\t\t |                      |\n";
    cout << "\t\t\t\t |  2) Buyer            |\n";
    cout << "\t\t\t\t |                      |\n";
    cout << "\t\t\t\t |  3) Exit             |\n";  

    cout << "\n\t\t\t    Please select! ";
    cin >> choice;

    switch (choice)
    {
        case 1:
        {
            cout << "\t\t\t Please Login   \n";
            cout << "\t\t\t Enter Email: ";
            cin >> email;
            cout << "\n\t\t\t Password: ";
            cin >> password;

            if(email == "harcharan@gmail.com" && password == "harcharan"){
                administrator();
            }
            else{
                cout << "Invalid email / password";
            }
            break;
        }
        case 2:
        {
            buyer();
        }
        case 3:
        {
            exit(0);
        }
        default:
        {
            cout << "Please select from the given options ";
        }
    }
    goto m;     // m is label
}         

void shopping :: administrator(){

    m:
    int choice;
    cout << "\n\n\n\t\t\t Administrator Menu ";
    cout << "\n\t\t\t |_____1) Add the Product_____|";
    cout << "\n\t\t\t |                            |";
    cout << "\n\t\t\t |_____2) Modify the Product__|";
    cout << "\n\t\t\t |                            |";
    cout << "\n\t\t\t |_____3) Delete the Product__|";
    cout << "\n\t\t\t |                            |";
    cout << "\n\t\t\t |_____4) Back to main menu___|";

    cout << "\n\n\t Please enter your choice ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        add();
        break;
    }
    case 2:
    {
        edit();
        break;
    }
    case 3:
    {
        rem();
        break;
    }
    case 4:
    {
        menu();
        break;
    }
    
    default:
        cout << "Invalid Choice! ";
    }
    goto m;
}

void shopping :: buyer()
{
    m:
    int choice;
    cout << "\t\t\t  Buyer \n";
    cout << "\t\t\t________________\n";
    cout << "                      \n";
    cout << "\t\t\t 1) Buy Product \n";
    cout << "                      \n";
    cout << "\t\t\t 2) Go Back     \n";
    cout << "\t\t\t  Enter your choice : ";

    cin >> choice;

    switch (choice)
    {
    case 1:
        receipt();
        break;
    case 2:
        menu();
    default:
        cout << "Invalid choice !";
    }
    goto m;
}

void shopping :: add()
{
    m:
    fstream data;           // creating object of fstream class
    int c;
    int token = 0;
    float p;
    float d;
    string n;

    cout << "\n\n\t\t\t Add new product";
    cout << "\n\n\t Product code of the product: ";
    cin >> pcode;
    cout << "\n\n\t Name of the product: ";
    cin >> pname;
    cout << "\n\n\t Price of the product: ";
    cin >> price;
    cout << "\n\n\t Discount on the product: ";
    cin >> dis;

    data.open("database.text", ios::in);    // ios::in will open file in reading mode.
    
    // If this data does not exit
    if(!data){
        // Writing Inside the file
        data.open("database.text", ios::app|ios::out);      // ios::app stands for append mode
                                                            // ios::out stands for writing mode
        data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
        data.close();                                
    }
    else{
        data >> c >> n >> p >> d;       // Initializing file

        while(!data.eof()){             // eof() --> end of file function
            if(c == pcode){             // If we wrote duplicate productCode
                token++;                // Increment duplicacy
            }
            data >> c >> n >> p >> d;
        }
        data.close(); 
    }
    
    if(token == 1){     // If there is duplicacy 
        goto m;
    }
    else{
        // Writing Inside the file
        data.open("database.text", ios::app|ios::out);      // ios::app stands for append mode
                                                            // ios::out stands for writing mode
        data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
        data.close(); 
    }
    cout << "\n\n\t\t Record Inserted ! ";
}

void shopping :: edit()
{
    fstream data, data1;
    int pkey;
    int token = 0;
    int c;          // code for newProduct
    float p;
    float d;
    string n;       // name of newProduct

    cout << "\n\t\t\t Modify the record ";
    cout << "\n\t\t\t Product Code :";
    cin >> pkey;

    data.open("database.txt", ios::in);

    // If file does not exist in data.
    if(!data){
        cout << "\n\n File doesn't exist !";
    }
    // Note:
    // Now, we'll edit data in database1.txt file, then remove database.text file
    // and at last rename database1.txt file to database.txt
    else{
        // Open file in writing mode.
        data1.open("database1.txt", ios::app|ios::out);
        data >> pcode >> pname >> price >> dis;     // Initialising data
        while(!data.eof())
        {
            // If productCode & productKey entered by admin matches with already present item
            if(pkey == pcode){
                cout << "\n\t\t Product new code : ";
                cin >> c;
                cout << "\n\t\t Name of the product : ";
                cin >> n;
                cout << "\n\t\t Price :";
                cin >> p;
                cout << "\n\t\t Discount : ";
                cin >> d;

                data1 << " " << c << " " << n << " " << p << " " << d << "\n";
                cout << "\n\n\t\t Recorde Edited ";
                token++;
            }
            // If productCode & productKey entered by admin doesn't match with already present item
            else{
                data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();

        // Remove previous file and name the new file as previous one
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if(token == 0)
        {
            cout << "\n\n Record not found, sorry! ";
        }
    }
}

void shopping :: rem()
{
    fstream data, data1;
    int pkey;
    int token = 0;
    cout << "\n\n\t Delete Product ";
    cout << "\n\n\t Product Code : ";
    cin >> pkey;
    data.open("database.txt", ios::in);   // Opening file in reading mode

    if(!data){
        cout << "File doesn't exist";
    }
    else{
        data1.open("database1.txt", ios::app|ios::out); // Open file in append & writing mode
        data >> pcode >> pname >> price >> dis;
        
        while(!data.eof())
        {
            if(pcode == pkey)
            {
                cout << "\n\n\t Product Deleted Successfully ";
                token++;
            }
            // Otherwise, all products will be shown except the product u want to delete
            else
            {
                data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();

        // Remove previous file and name the new file as previous one
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if(token == 0)
        {
            cout << "\n\n Record not found ";
        }
    }
}

void shopping :: list()
{
    fstream data;
    data.open("database.txt", ios::in);     // open file in reading mode
    cout << "\n\n|_______________________________________________________\n";
    cout << "Product Number \t\t Name \t\t Price \n";
    cout << "\n\n|_______________________________________________________\n";
    data >> pcode >> pname >> price >> dis;
    
    while(!data.eof())
    {
        cout << pcode << "\t\t" << pname << "\t\t" << price << "\n";
        data >> pcode >> pname >> price >> dis;
    }
    data.close();
}

void shopping :: receipt()
{
    fstream data;

    int arrc[100];      // array of product code
    int arrq[100];      // array of product quantity
    char choice;
    int c = 0;          // count
    float amount = 0;
    float dis = 0;
    float total = 0;

    cout << "\n\n\t\t\t\t RECEIPT ";
    data.open("database.txt", ios::in);  // open file in reading mode

    // If data doesn't exist
    if(!data)
    {
        cout << "\n\n Empty Database ";
    }
    else{
        data.close();
        
        list();     // show customer all products available by calling list
        cout << "\n___________________________________________\n";
        cout << "\n|                                          \n";
        cout << "\n         Please place the order            \n";
        cout << "\n|                                          \n";
        cout << "\n___________________________________________\n";

        do
        {
            m:
            cout << "\n\n Enter Product Code : ";
            cin >> arrc[c];
            cout << "\n\n Enter the product quantity : ";
            cin >> arrq[c];

            for(int i=0; i<c; i++)
            {
                if(arrc[c] == arrc[i]){
                    cout << "\n\n Duplicate product code.Please try again!";
                    goto m;
                }
                c++;    // If product key if not duplicate, increment count
                cout << "\n\n Do you want to buy another product? If yes then press y else no";
                cin >> choice;
            }

        } while (choice == 'y');

        cout << "\n\n\t\t\t __________________________RECEIPT________________________\n";
        cout << "\n Product No. \t Product name \t Product Quantity \t Price \t Amount \t Amount with discount\n";
        for(int i=0; i<c; i++)
        {
            data.open("database.txt", ios::in);     // open file in reading mode
            data >> pcode >> pname >> price >> dis;

            while(!data.eof())
            {
                if(pcode == arrc[i])
                {
                    amount = price * arrq[i];
                    dis = amount - (amount*dis/100);
                    total = total + dis;
                    cout << "\n" << pcode << "\t\t" << pname << "\t\t" << arrq[i] << "\t\t" << price << "\t\t" << amount << "\t\t" << dis;
                }
                data >> pcode >> pname >> price >> dis;
            }
        }
        data.close();
        
    }
    cout << "\n\n ______________________________________________";
    cout << "\n Total Amount : " << total;
}

int main()
{
    shopping s;
    s.menu();



    return 0;
}