#include <iostream>
using namespace std;
#include <fstream>

char c;
// structures

struct product // product structure
{
    int pid;
    char name[30];
    float balance;
};

struct purchase // purchase structure
{
    int prid;
    int pid;
    float qty;
    float ppu; //price per unit
};

struct sale // sale stucture
{
    int sid;
    int pid;
    float qty;
    float ppu;
};

int count_data(char filename[30])
{
    int count = 0;
    if (filename == "prodcut.bin")
    {
        product p;
        ifstream ifs(filename);
        while (ifs.read(reinterpret_cast<char *>(&p), sizeof(p)))
            count++;
        ifs.close();
        return count;
    }

    else if (filename == "purchase.bin")
    {
        purchase pr;
        ifstream ifs(filename);
        while (ifs.read(reinterpret_cast<char *>(&pr), sizeof(pr)))
            count++;
        ifs.close();
        return count;
    }
    else
    {
        sale s;
        ifstream ifs(filename);
        while (ifs.read(reinterpret_cast<char *>(&s), sizeof(s)))
            count++;
        ifs.close();
        return count;
    }
}

//  product functions

int check_product_id(int id)
{
    char filename[30] = "product.bin";
    // add te entry into array
    int count = count_data(filename);
    product p1[count];
    int i = 0;
    ifstream ifs(filename);
    while (ifs.read(reinterpret_cast<char *>(&p1[i]), sizeof(p1[i])))
        i++;
    ifs.close();
    int check = 0;
    for (i = 0; i < count; i++)
    {
        if (id == p1[i].pid)
            check = 1;
    }
    return check;
}

// move data from temp file product file

void move_temp_product()
{
    product p;
    ifstream ifs("temp.bin");
    ofstream ofs("product.bin");
    while (ifs.read(reinterpret_cast<char *>(&p), sizeof(p)))
    {
        ofs.write(reinterpret_cast<char *>(&p), sizeof(p));
    }
    ifs.close();
    ofs.close();
    system("rm temp.bin");
}

void add_product()
{
    system("cls");
    product p;
    // add data to file
    ofstream ofs("product.bin", ios_base::app);
    cout << "Enter product id, name and balance" << endl;
    cout << "Enter id : ";
    cin >> p.pid;
    cout << "Enter product name : ";
    cin >> p.name;
    cout << "Enter product balance : ";
    cin >> p.balance;
    int check = check_product_id(p.pid);
    if (check)
        cout << "product id already exist. " << endl;
    else
    {
        ofs.write(reinterpret_cast<char *>(&p), sizeof(p));
        cout << "Data enter successfully" << endl;
    }

    ofs.close();

}

void display_product()
{
    system("cls");
    product p;
    // Display all the entry
    cout << "Id\tName\tBalance" << endl;
    ifstream ifs("product.bin");
    while (ifs.read(reinterpret_cast<char *>(&p), sizeof(p)))
        cout << p.pid << "\t" << p.name << "\t" << p.balance << endl;
    ifs.close();
}

void modify_product()
{
    system("cls");
    product p;
    int id;
    cout << "Enter te pid of product whose data to modify : ";
    cin >> id;
    // move data after modify to temp.bin from product.bin
    ifstream ifs2("product.bin");
    ofstream ofs("temp.bin");
    int check = 1;
    int check_2 = 1;
    while (ifs2.read(reinterpret_cast<char *>(&p), sizeof(p)))
    {
        if (id == p.pid)
        {
            while(check_2)
            {
                cout << "Enter product id, name and balance" << endl;
                cout << "Enter id : ";
                cin >> p.pid;
                cout << "Enter product name : ";
                cin >> p.name;
                cout << "Enter product balance : ";
                cin >> p.balance;
                check = 0;
                check_2 = check_product_id(p.pid);
                if (check_2 && p.pid ==id )
                    break;
                cout<<"product id already exist"<<endl;
            }
        }
        ofs.write(reinterpret_cast<char *>(&p), sizeof(p));
    }
    ifs2.close();
    ofs.close();
    // move data back to product.bin file
    move_temp_product();
    if (check)
        cout << "NO, such pid exist" << endl;
    else
        cout << "Entry update successfully" << endl;


}

void delete_product()
{
    system("cls");
    product p;
    int id;
    cout << "Enter te pid of product whose data to delete : ";
    cin >> id;
    // move data after delete to temp.bin from product.bin
    ifstream ifs("product.bin");
    ofstream ofs("temp.bin");
    int check = 1;
    while (ifs.read(reinterpret_cast<char *>(&p), sizeof(p)))
    {
        if (id != p.pid)
            ofs.write(reinterpret_cast<char *>(&p), sizeof(p));
        else
            check = 0;
    }
    ifs.close();
    ofs.close();
    // move data back to product.bin file
    move_temp_product();
    if (check)
        cout << "NO, such pid exist" << endl;
    else
        cout << "Entry Delete successfully" << endl;

}

void product_menu()
{
    int choice;
    while (1)
    {
        system("cls");
        cout << " 1) Add Product" << endl;
        cout << " 2) Display Product" << endl;
        cout << " 3) Modify Product" << endl;
        cout << " 4) Delete Product" << endl;
        cout << " 5) Back to Main Menu" << endl;
        cout << "Enter your choice : ";
        cin >> choice;
        if (choice == 1)
            add_product();
        else if (choice == 2)
            display_product();
        else if (choice == 3)
            modify_product();
        else if (choice == 4)
            delete_product();
        else if (choice == 5)
            break;
        else
            cout << "invalid choice." << endl;
        cin.ignore();
        cin.get();
    }
}

void update_balance(int id, float balance, int token)
{
    product p;
    ifstream ifs("product.bin");
    ofstream ofs("temp.bin");
    if (token)
    {
        while (ifs.read(reinterpret_cast<char *>(&p), sizeof(p)))
        {
            if (id == p.pid)
                p.balance += balance;
            ofs.write(reinterpret_cast<char *>(&p), sizeof(p));
        }
    }
    else
    {
        while (ifs.read(reinterpret_cast<char *>(&p), sizeof(p)))
        {
            if (id == p.pid)
                p.balance -= balance;
            ofs.write(reinterpret_cast<char *>(&p), sizeof(p));
        }
    }
    ifs.close();
    ofs.close();
    move_temp_product();
}

// purchase funtions

void add_purchase()
{
    system("cls");
    char filename[30] = "purchase.bin";
    purchase pr;
    ofstream ofs(filename, ios_base::app);
    pr.prid = count_data(filename) + 1;
    cout << "Enter product id, name and balance" << endl;
    cout << "Purchase id : " << pr.prid << endl;
    cout << "Enter product id : ";
    cin >> pr.pid;
    cout << "Enter product quantity : ";
    cin >> pr.qty;
    cout << "Enter price per product : ";
    cin >> pr.ppu;
    int check = check_product_id(pr.pid);
    if (check)
    {
        update_balance(pr.pid, pr.qty, 1);
        ofs.write(reinterpret_cast<char *>(&pr), sizeof(pr));
        cout << "Purchase Data Enter succfully." << endl;
    }
    else
        cout << "product id does not exist first add product." << endl;
}

void display_purchase_transaction()
{
    system("cls");
    purchase pr;
    int id;
    cout << "Enter purchase id : ";
    cin >> id;
    cout << "PrId\tId\tquantity\tprice_per_unit" << endl;
    ifstream ifs("purchase.bin");
    while (ifs.read(reinterpret_cast<char *>(&pr), sizeof(pr)))
    {
        if (pr.prid == id)
            cout << pr.prid << "\t" << pr.pid << "\t" << pr.qty << "\t\t" << pr.ppu << endl;
    }
    ifs.close();
}

void display_purchase()
{
    system("cls");
    purchase pr;
    // Display all the entry
    cout << "PrId\tId\tquantity\tprice_per_unit" << endl;
    ifstream ifs("purchase.bin");
    while (ifs.read(reinterpret_cast<char *>(&pr), sizeof(pr)))
        cout << pr.prid << "\t" << pr.pid << "\t" << pr.qty << "\t\t" << pr.ppu << endl;
    ifs.close();
}

void purchase_menu()
{
    int choice;

    while (1)
    {
        system("cls");
        cout << " 1) Purchase a Product" << endl;
        cout << " 2) Display Purchase Transaction" << endl;
        cout << " 3) Dispaly all Purchase" << endl;
        cout << " 4) Back to Main Menu" << endl;
        cout << "Enter your choice : ";
        cin >> choice;
        if (choice == 1)
            add_purchase();
        else if (choice == 2)
            display_purchase_transaction();
        else if (choice == 3)
            display_purchase();
        else if (choice == 4)
            break;
        else
            cout << "invalid choice." << endl;
        cin.ignore();
        cin.get();
    }
}

//  sale functions

float check_balance(int id)
{
    product p;
    ifstream ifs("product.bin");
    while(ifs.read(reinterpret_cast<char*>(&p),sizeof(p)))
    {
        if(p.pid == id)
            return p.balance;
    }
}

void add_sale()
{
    system("cls");
    char filename[30] = "sale.bin";
    sale s;
    ofstream ofs(filename, ios_base::app);
    s.sid = count_data(filename) + 1;
    cout << "Enter product id, name and balance" << endl;
    cout << "Sale id : " << s.sid << endl;
    cout << "Enter product id : ";
    cin >> s.pid;
    cout << "Enter product quantity : ";
    cin >> s.qty;
    cout << "Enter price per product : ";
    cin >> s.ppu;
    int check = check_product_id(s.pid);
    if (check)
    {
        float balance = check_balance(s.pid);
        if (s.qty <= balance)
        {
            update_balance(s.pid, s.qty, 0);
            ofs.write(reinterpret_cast<char *>(&s), sizeof(s));
            cout << "Sale Data Enter successfully." << endl;
        }
        else
            cout<<"SORRY, balance of that product is "<< balance <<" reduce the quantity"<<endl;
        
    }
    else
        cout << "product id does not exist first add product." << endl;
    ofs.close();
}

void display_sale_transaction()
{
    system("cls");
    sale s;
    int id;
    cout << "Enter Sale id : ";
    cin >> id;
    cout << "PrId\tId\tquantity\tprice_per_unit" << endl;
    ifstream ifs("sale.bin");
    while (ifs.read(reinterpret_cast<char *>(&s), sizeof(s)))
    {
        if (s.sid == id)
            cout << s.sid << "\t" << s.pid << "\t" << s.qty << "\t\t" << s.ppu << endl;

    }
    ifs.close();
}

void display_sale()
{
    system("cls");
    sale s;
    // Display all the entry
    cout << "SId\tId\tquantity\tprice_per_unit" << endl;
    ifstream ifs("sale.bin");
    while (ifs.read(reinterpret_cast<char *>(&s), sizeof(s)))
        cout << s.sid << "\t" << s.pid << "\t" << s.qty << "\t\t" << s.ppu << endl;
    ifs.close();
}

void sales_menu()
{
    int choice;

    while (1)
    {
        system("cls");
        cout << " 1) Sale a product" << endl;
        cout << " 2) Display Sale transaction" << endl;
        cout << " 3) Display all Sales" << endl;
        cout << " 4) Back to Main Menu" << endl;
        cout << "Enter your choice : ";
        cin >> choice;
        if (choice == 1)
            add_sale();
        else if (choice == 2)
            display_sale_transaction();
        else if (choice == 3)
            display_sale();
        else if (choice == 4)
            break;
        else
            cout << "invalid choice." << endl;
        cin.ignore();
        cin.get();
    }
}

//  Revenue function

void revenue()
{
    system("cls");
    purchase pr;
    ifstream ifs("purchase.bin");
    double total_purchase = 0;
    while (ifs.read(reinterpret_cast<char *>(&pr), sizeof(pr)))
    {
        total_purchase += (pr.ppu * pr.qty);
    }
    ifs.close();
    sale s;
    ifstream ifs2("sale.bin");
    double total_sale = 0;
    while (ifs2.read(reinterpret_cast<char *>(&s), sizeof(s)))
    {
        total_sale += (s.ppu * s.qty);
    }
    ifs2.close();
    cout <<"Total Purchase = "<< total_purchase << endl;
    cout<<"Total Sale = "<< total_sale << endl;
    cout << "REVENUE = " << total_sale / total_purchase << endl;
}

int main()
{
    int choice;
    while (1)
    {
        system("cls");
        cout << " 1) Product" << endl;
        cout << " 2) Purchases" << endl;
        cout << " 3) Sales" << endl;
        cout << " 4) Revinu" << endl;
        cout << " 5) Exit" << endl;
        cout << "Enter your choice : ";
        cin >> choice;
        if (choice == 1)
            product_menu();
        else if (choice == 2)
            purchase_menu();
        else if (choice == 3)
            sales_menu();
        else if (choice == 4)
            revenue();
        else if (choice == 5)
            break;
        else
        {
            cout << "invalid choice." << endl;
            cin.ignore();
            cin.get();
        }
    }

    return 0;
}