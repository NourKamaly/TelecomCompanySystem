// Telecom company System (SP).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include<stdlib.h>
#include <Windows.h>
using namespace std;
struct date {
    int day = 0, month = 0, year = 0;
};
struct packages {
    string name;
    float numberofminutes, numberofGegas, package_price;
    date start_date, renewal_date;
}pkgs[3];
struct lines {
    long long number = 0;
    float balance = 0;
    int package_number;
    packages package_type;

};
struct user_information {
    string name, e_mail, address;
    long long ID, visa_number, password;
    int amount_of_lines;
    float bank_balance;
    lines no_of_lines[3];
}client[10000];

void menu();
user_information creating_account();
void renew_subscription(int index, long long& serial);
void callingXmessaging(int index, long long& serial);
void recharging_balance(int index, long long& serial);
void transferring_balance(int index, long long& serial);
void showing_packages();
void updating_packages_date(int tempi, int tempm);
void finding_contact(int index, int& tempi, int& tempm);

// main function 
int main()
{
    long long serial = 120596872469;
    char answer;
    int result, index_of_client = 2, feedback;

    pkgs[0] = { "mini package",85,4,50 };
    pkgs[1] = { "Normal package",150,20,135 };
    pkgs[2] = { "EXTRA LARGE package",950,256,950 };

    client[0] = { "Elizabeth Bennet","lizzy@gmail.com","Cairo,Egypt",987654321,88888888,77777777,2,1000 };
    client[0].no_of_lines[0] = { 999900009,0,1 };
    client[0].no_of_lines[0].package_type = { "mini package",85,4,50 };
    client[0].no_of_lines[1] = { 888807777,500,2 };
    client[0].no_of_lines[1].package_type = { "Normal package",150,20,135 };

    client[1] = { "Charollette Bronte","cherry@gmail.com","Sheikh Zayed,Egypt",123456789,66666666,55555555,1,500 };
    client[1].no_of_lines[0] = { 666605555 ,100,2 };
    client[1].no_of_lines[0].package_type = { "Normal package",150,20,135 };

    client[2] = { "Darcy","darcy@gmail.com","5th settelment",987123654,44444444,33333333,1,100 };
    client[2].no_of_lines[0] = { 444403333,1000,3 };
    client[2].no_of_lines[0].package_type = { "EXTRA LARGE package",950,256,950 };

    do {

        system("color F0");
        system("cls");
        menu();

        cin >> result;
        switch (result) {

        case 1:index_of_client += 1; client[index_of_client] = creating_account(); break;

        case 2: renew_subscription(index_of_client, serial);  break;

        case 3: callingXmessaging(index_of_client, serial); break;

        case 4: recharging_balance(index_of_client, serial); break;

        case 5: transferring_balance(index_of_client, serial); break;

        default: cout << "You have entered an invalid number" << endl; break;

        }

        cout << "\nWould you like to continue ? Press 'y' for yes and 'n' for no : ";
        cin >> answer;

    } while (answer != 'n');

    cout << "\nThank you so much sir for using conMnEect services ! ";
    cout << "\nPlease take the time to rate the system\n(very bad) 1 2 3 4 5 (excellent)\n";
    cin >> feedback;

    if ((feedback > 0) && (feedback < 4)) {
        cout << "\nWe will try to improve our performance next time, please email conMnEect@gmail.com\n";
    }
    else {
        cout << "\nWe hope to keep up with this quality, for more info email conMnEect@gmail.com\n";
    }
    return 0;
}

// function 1
void menu() {
    cout << "Welcome sir to conMnEect services, please choose a number to proceed: " << endl
        << "1. Create a new account." << endl << "2. Renew subscription." << endl
        << "3. Calling or messaging." << endl << "4. Re-charging balance." << endl
        << "5. Transferring balance." << endl;
}
// function 2
user_information creating_account() {
    user_information sample;
    int loop_counter = 0;
    long long password1, password2;
    cin.ignore();
    cout << "Please enter the following data: ";
    cout << "\nName: "; getline(cin, sample.name);
    cout << "\nNational ID: "; cin >> sample.ID; cin.ignore();
    cout << "\nE-mail: "; getline(cin, sample.e_mail);
    cout << "\nPassword: "; cin >> password1; cout << "\nRe-enter your password again : "; cin >> password2;
    if (password1 == password2) {
        sample.password = password1;
    }
    cin.ignore();
    cout << "\nAddress: "; getline(cin, sample.address);
    cout << "\nVisa number : "; cin >> sample.visa_number;
    cout << "\nBank balance : "; cin >> sample.bank_balance;
    cout << "\nHow many lines do you own ? (The maximum number is 3) : "; cin >> sample.amount_of_lines;

    if (sample.amount_of_lines <= 3 && sample.amount_of_lines > 0) {
        for (; loop_counter < sample.amount_of_lines; loop_counter++) {
            cout << "\nThe mobile number is : 01 "; cin >> sample.no_of_lines[loop_counter].number;
            cout << "\nThe balance for this number is : "; cin >> sample.no_of_lines[loop_counter].balance; cin.ignore();
            cout << "\nWhat type of package are you subscribed to ? ";
            showing_packages();
            cout << "\nYour package number is : "; cin >> sample.no_of_lines[loop_counter].package_number;
            sample.no_of_lines[loop_counter].package_type.name = pkgs[(sample.no_of_lines[loop_counter].package_number) - 1].name;
            sample.no_of_lines[loop_counter].package_type.numberofGegas = pkgs[(sample.no_of_lines[loop_counter].package_number) - 1].numberofGegas;
            sample.no_of_lines[loop_counter].package_type.numberofminutes = pkgs[(sample.no_of_lines[loop_counter].package_number) - 1].numberofminutes;
        }
    }

    return sample;
}
//function 3
void renew_subscription(int index, long long& serial) {
    int temp_mobile, temp_index, answer;
    cout << "Enter the following data : ";
    finding_contact(index, temp_index, temp_mobile);
    cout << "Would you like to : \n1.Renew subscription.\n2.Change your package type.\n";
    cin >> answer;
    if (answer == 1) {
        if (client[temp_index].no_of_lines[temp_mobile].balance - client[temp_index].no_of_lines[temp_mobile].package_type.package_price > 2) {
            cout << "\nYour previous balance was : " << client[temp_index].no_of_lines[temp_mobile].balance;
            client[temp_index].no_of_lines[temp_mobile].balance -= client[temp_index].no_of_lines[temp_mobile].package_type.package_price;
            cout << "\nYour package costs : " << client[temp_index].no_of_lines[temp_mobile].package_type.package_price;
            updating_packages_date(temp_index, temp_mobile);
        }
        else {
            cout << "\nYour current balance is : " << client[temp_index].no_of_lines[temp_mobile].balance;
            cout << "\nYour package costs : " << client[temp_index].no_of_lines[temp_mobile].package_type.package_price;
            cout << "\nYou dont have enough balance to renew subscription, you need to have at lease 2 pounds after renewing.";
            char answer; cout << "\nWould you like to re-cahrge your balance ? press 'y' for yes and 'n' for no : ";
            cin >> answer;
            if ((answer == 'y') || (answer == 'Y')) {
                recharging_balance(index, serial);
                if (client[temp_index].no_of_lines[temp_mobile].balance - client[temp_index].no_of_lines[temp_mobile].package_type.package_price > 2) {
                    cout << "\nYour previous balance was : " << client[temp_index].no_of_lines[temp_mobile].balance;
                    client[temp_index].no_of_lines[temp_mobile].balance -= client[temp_index].no_of_lines[temp_mobile].package_type.package_price;
                    cout << "\nYour package costs : " << client[temp_index].no_of_lines[temp_mobile].package_type.package_price;
                    updating_packages_date(temp_index, temp_mobile);
                }
            }
        }
    }
    else if (answer == 2) {
        int desired_p;
        showing_packages();
        cout << "\nYou were subscribed to : " << client[temp_index].no_of_lines[temp_mobile].package_type.name;
        cout << "\nChoose your package number : "; cin >> desired_p;
        if (desired_p == client[temp_index].no_of_lines[temp_mobile].package_number) {
            cout << "\nYou are already subscribed to this package.";
        }
        else if (client[temp_index].no_of_lines[temp_mobile].balance - pkgs[desired_p - 1].package_price > 2) {
            client[temp_index].no_of_lines[temp_mobile].package_number = desired_p;
            client[temp_index].no_of_lines[temp_mobile].balance -= pkgs[desired_p - 1].package_price;
            client[temp_index].no_of_lines[temp_mobile].package_type = { pkgs[desired_p - 1].name,pkgs[desired_p - 1].numberofminutes,pkgs[desired_p - 1].numberofGegas,pkgs[desired_p - 1].package_price };
            updating_packages_date(temp_index, temp_mobile);
            cout << "\nYou are now subscribed to the : " << client[temp_index].no_of_lines[temp_mobile].package_type.name;

        }
        else {
            cout << "\nYour current balance is : " << client[temp_index].no_of_lines[temp_mobile].balance;
            cout << "\nThe package you want to subscribe to costs : " << pkgs[desired_p - 1].package_price;
            cout << "\nYou dont have enough balance to renew subscription, you need to have atlease 2 pounds after changing packages.";
            char answer; cout << "\nWould you like to re-cahrge your balance ? press 'y' for yes and 'n' for no ";
            cin >> answer;
            if ((answer == 'y') || (answer == 'Y')) {
                recharging_balance(index, serial);
            }
        }
    }
    else { cout << "\nYou have entered an invalid number."; }
}
//function 4
void callingXmessaging(int index, long long& serial) {
    cout << "\nCalling or messaging will decrease your balance by 0.25 L.E. ";
    int temp_mobile, temp_index, loop_counter = 0;
    finding_contact(index, temp_index, temp_mobile);
    long long reciever_number;
    if ((client[temp_index].no_of_lines[temp_mobile].balance - 0.25) >= 0) {
        cout << "\nDo you want to call someone or message ? \nPress '1' for calling & '2' for messaging.\n";
        int result;
        cin >> result;
        if (result == 1) {
            cout << "Enter the number you wish to call : 01 "; cin >> reciever_number;
            cout << "\nYour balance was : " << client[temp_index].no_of_lines[temp_mobile].balance;
            client[temp_index].no_of_lines[temp_mobile].balance -= 0.25;
            cout << "\nYour call has been made.\nYour new balance is : " << client[temp_index].no_of_lines[temp_mobile].balance;
        }
        else if (result == 2) {
            cout << "\nEnter the message you want to send and press '.' and then enter to end it : \n";
            cin.ignore();
            string message;
            getline(cin, message, '.');
            cout << "Send this message to :01 "; cin >> reciever_number;
            cout << "\nYour balance was : " << client[temp_index].no_of_lines[temp_mobile].balance;
            client[temp_index].no_of_lines[temp_mobile].balance -= 0.25;
            cout << "\nYour message has been sent and your new balance is : " << client[temp_index].no_of_lines[temp_mobile].balance;
        }
        else {
            cout << "\nYou have entered an invalid number.";
        }
    }
    else {
        cout << "\nYou don't have enough balance to request this service.";
        char answer; cout << "\nWould you like to re-cahrge your balance ? press 'y' for yes and 'n' for no : ";
        cin >> answer;
        if ((answer == 'y') || (answer == 'Y')) {
            recharging_balance(index, serial);
        }
    }
}
// function 5
void recharging_balance(int index, long long& serial) {
    int temp_mobile, temp_index, loop_counter = 0;
    long long user_card_input;
    float balance;

    finding_contact(index, temp_index, temp_mobile);
    // I charge 2.5 pounds for this service 
    cout << "\nHow much do you want the serial card to charge ? "; cin >> balance;
    if (client[temp_index].bank_balance - (balance + 2.5) >= 0) {
        cout << "\nYour bank balance was : " << client[temp_index].bank_balance;
        client[temp_index].bank_balance -= balance + 2.5;
        cout << "\nYour bank account has been demoted by : " << balance + 2.5 << " L.E. as we charge 2.5 pounds for this service.";
        cout << "\nYour new bank balance is : " << client[temp_index].bank_balance;
        cout << "\nYour serial card number is : "; cout << serial;
        cout << "\nPlease enter your serial card number : ";
        cin >> user_card_input;
        if (serial == user_card_input) {
            client[temp_index].no_of_lines[temp_mobile].balance += balance;
            cout << "\nThe balance for this mobile phone has been updated to become : "
                << client[temp_index].no_of_lines[temp_mobile].balance;
        }
        else {
            cout << "\nYou have entered an invalid serial card number\n Enter the serial card again : ";
            cin >> user_card_input;
            if (serial == user_card_input) {
                client[temp_index].no_of_lines[temp_mobile].balance += balance;
                cout << "\nThe balance for this mobile phone has been updated to become : "
                    << client[temp_index].no_of_lines[temp_mobile].balance;
            }
        }
        serial -= rand() % 101;
        serial += rand() % 11;
    }
    else { cout << "\nYou dont have enough money in your bank account to purchase a serial card with this amount, please check your bank account balance."; }
}
//function 6
void transferring_balance(int index, long long& serial) {
    cout << "Fill the following information of the sender :";
    float balance;
    int rindex, sindex, rmobile, smobile, ctr = 0;
    finding_contact(index, sindex, smobile);
    cout << "\nFill the following information for the reciever :";
    finding_contact(index, rindex, rmobile);
    //    cout << "\n The sender balance is : " << client[sindex].no_of_lines[smobile].balance;
    cout << "\nHow much money do you want to transfer ? "; cin >> balance;
    if (client[sindex].no_of_lines[smobile].balance - balance > 2) {
        client[sindex].no_of_lines[smobile].balance -= balance;
        cout << "\nThe reciever balance was : " << client[rindex].no_of_lines[rmobile].balance;
        client[rindex].no_of_lines[rmobile].balance += balance;
        cout << "\nThe sender balance has been updated to : " << client[sindex].no_of_lines[smobile].balance;
        cout << "\nThe reciever balance has been updated to : " << client[rindex].no_of_lines[rmobile].balance;
    }
    else {
        cout << "\nTransferring this amount will make you broke, a safe 2 pounds must always be in the account.";
        char answer; cout << "\nWould you like to re-cahrge your balance ? press 'y' for yes and 'n' for no ";
        cin >> answer;
        if (answer == 'y') {
            recharging_balance(index, serial);
        }
    }
}
// function 7
void showing_packages() {
    cout << "conMnEect offers its clients 3 packages : ";
    for (int ctr = 0; ctr < 3; ctr++) {
        cout << "\nPackage number " << ctr + 1 <<
            " : \nis called the " << pkgs[ctr].name << " & offers " << pkgs[ctr].numberofminutes << " minutes for calling, \n";
        cout << pkgs[ctr].numberofGegas << " gega(s) for using internet, and costs " << pkgs[ctr].package_price << " pounds.";
    }
}
//function 8
void updating_packages_date(int tempi, int tempm) {
    cout << "\nEnter today`s date (DMY) : ";
    cin >> client[tempi].no_of_lines[tempm].package_type.start_date.day;
    cin >> client[tempi].no_of_lines[tempm].package_type.start_date.month;
    cin >> client[tempi].no_of_lines[tempm].package_type.start_date.year;

    if (client[tempi].no_of_lines[tempm].package_type.start_date.day != 30) {
        client[tempi].no_of_lines[tempm].package_type.renewal_date.day = (client[tempi].no_of_lines[tempm].package_type.start_date.day + 30) % 30;
        client[tempi].no_of_lines[tempm].package_type.renewal_date.month = client[tempi].no_of_lines[tempm].package_type.start_date.month += 1;
        if (client[tempi].no_of_lines[tempm].package_type.start_date.month == 13) {
            client[tempi].no_of_lines[tempm].package_type.renewal_date.month = 1;
            client[tempi].no_of_lines[tempm].package_type.renewal_date.year++;
        }
        if (client[tempi].no_of_lines[tempm].package_type.start_date.day == 31) {
            client[tempi].no_of_lines[tempm].package_type.renewal_date.month += 1;
        }
        client[tempi].no_of_lines[tempm].package_type.renewal_date.year = client[tempi].no_of_lines[tempm].package_type.start_date.year;

    }
    else {
        client[tempi].no_of_lines[tempm].package_type.renewal_date.day = 30;
        client[tempi].no_of_lines[tempm].package_type.renewal_date.month = client[tempi].no_of_lines[tempm].package_type.start_date.month += 1;
        client[tempi].no_of_lines[tempm].package_type.renewal_date.year = client[tempi].no_of_lines[tempm].package_type.start_date.year;
        if (client[tempi].no_of_lines[tempm].package_type.start_date.month == 13) {
            client[tempi].no_of_lines[tempm].package_type.renewal_date.month = 1;
            client[tempi].no_of_lines[tempm].package_type.renewal_date.year++;
        }
    }

    cout << "\nYour request is pending.\nYour request has been approved and your new balance : ";
    cout << client[tempi].no_of_lines[tempm].balance;
    cout << "\nYour renewal date is on :\nDay\tMonth\tYear\n";
    cout << client[tempi].no_of_lines[tempm].package_type.renewal_date.day << '\t'
        << client[tempi].no_of_lines[tempm].package_type.renewal_date.month << '\t'
        << client[tempi].no_of_lines[tempm].package_type.renewal_date.year;
}
// function 9
void finding_contact(int index, int& tempi, int& tempm) {
    string temp_name;
    int loop_counter = 0;
    cout << "\nName : ";
    cin.ignore();
    getline(cin, temp_name);
    cout << "\nMobile number : 01 "; cin >> tempm;
    for (; loop_counter <= index; loop_counter++) {
        if (temp_name == client[loop_counter].name) {
            tempi = loop_counter;
            break;
        }
    }
    for (loop_counter = 0; loop_counter < client[tempi].amount_of_lines; loop_counter++) {
        if (client[tempi].no_of_lines[loop_counter].number == tempm) {
            tempm = loop_counter; break;
        }
    }
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
