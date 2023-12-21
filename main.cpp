#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

struct UserInfo {
    string username;
    string password;
    string name;
    double balance;
    string address;
};

// Function to read user information from a file into a map
map<string, UserInfo> readUserDatabase(const string& filename) {
    map<string, UserInfo> userDatabase;
    ifstream file(filename);

    if (file.is_open()) {
        string username, password, name,address;
        double balance;
        // Read data from the file line by line until the end of the file is reached
        while (file >> username >> password >> name>>balance>>address) {
            // Create a UserInfo object with the read data
            UserInfo userInfo{username, password,name,balance,address};
            // Add the UserInfo object to the map using the username as the key
            userDatabase[username] = userInfo;
        }
        file.close();
    }

    return userDatabase;
}

// Function to write user information to a file
void writeUserDatabase(const string& filename, const map<string, UserInfo>& userDatabase) {
    ofstream file(filename);

    if (file.is_open()) {
        // Iterate through each entry in the userDatabase map
        for (const auto& entry : userDatabase) {
            file << entry.second.username << " " << entry.second.password << " " << entry.second.name <<" "<<entry.second.balance<<" "<<entry.second.address<<"\n";
        }
        file.close();
    } else {
        cerr << "Error opening file: " << filename << endl;
    }
}

// Function to check if a user name and password are correct
bool checkCredentials(const map<string, UserInfo>& userDatabase, const string& username, const string& password) {
     // Find the iterator corresponding to the provided username in the userDatabase map
    auto it = userDatabase.find(username);
    // Check if the iterator points to the end of the map, indicating that the username was not found
    // Also, check if the password associated with the found username matches the provided password
    return (it != userDatabase.end() && it->second.password == password);
}
// Function to check if a user name exists in the user database
bool usernameExists(const map<string, UserInfo>& userDatabase, const string& username) {
    return userDatabase.find(username) != userDatabase.end();
}

int main() {
    string filename = "user_data.txt";
    map<string, UserInfo> userDatabase;
    //declares a map called userDatabase to store user information;
    string user,password;
    double newBalance;
    start_loop:
    // Read user information from the file
    userDatabase = readUserDatabase(filename);
    int choice, balance;
    cout<<"+------------------------------------------------------------+" <<endl;
    cout<<"|        * Welcome to ASTU Students Bank *                   |" <<endl;
    cout<<"| Select one of the following option below                   |" <<endl;
    cout<<"|  1.Login                                                   |" <<endl;
    cout<<"|  2.Sign up                                                 |" <<endl;
    cout<<"+------------------------------------------------------------+" <<endl;
    cin>>choice;
    switch(choice){
        case 1:
            // log2 in
            sign_in_loop:
            cout<<"+------------------------------------------------------------+" <<endl;
            cout<<"|        * ASTU students bank Login *                        |" <<endl;
            cout<<"| Enter user name:                                           |" <<endl;
            cout<<"+------------------------------------------------------------+" <<endl;
            cin>>user;
            cout<<"+------------------------------------------------------------+" <<endl;
            cout<<"|        * ASTU students bank Login *                        |" <<endl;
            cout<<"| Enter user password:                                       |" <<endl;
            cout<<"+------------------------------------------------------------+" <<endl;
            cin>>password;
             if (checkCredentials(userDatabase, user, password)) {
            cout << "Login successful!\n";
            // Display the name of the user and continue
                   signin_display_loop:
                   cout<<"+------------------------------------------------------------+" <<endl;
                   cout<<"|          "<<setw(10)<<userDatabase[user].name<<", Welcome                               |" <<endl;
                   cout<<"| Select one of the following option below                   |" <<endl;
                   cout<<"|  1. My account                                             |" <<endl;
                   cout<<"|  2. Transfer                                               |" <<endl;
                   cout<<"|  3. Deposit                                                |" <<endl;
                   cout<<"|  4. Withdrawal                                             |" <<endl;
                   cout<<"|  5. Service payment                                        |" <<endl;
                   cout<<"|  6. Exit                                                   |" <<endl;
                   cout<<"+------------------------------------------------------------+" <<endl;
                   cin>>choice;
                   if(choice==1){
                           //My account

                            cout<<"+------------------------------------------------------------+" <<endl;
                            cout<<"|        * My account *                                      |" <<endl;
                            cout<<"|  Dear"<<setw(10)<<userDatabase[user].name<<", your current balace is  "<<setw(10)<<userDatabase[user].balance<<"        |"<<endl;;
                            cout<<"|  1. Back                                                   |" <<endl;
                            cout<<"|  2. Back to main menu                                      |" <<endl;
                            cout<<"| press other key except (1 & 2) to terminate the program    |" <<endl;
                            cout<<"+------------------------------------------------------------+" <<endl;
                           cin>>choice;
                           if (choice==1){
                                goto signin_display_loop;
                           }
                           else if (choice==2){
                            goto start_loop;
                           }
                   }
                   else if(choice==2){
                           // transfer
                           transfer_loop:
                           cout<<"Enter the user you want to transfer: ";
                           string str_choice;
                           cin>>str_choice;

                            if (usernameExists(userDatabase, str_choice)) {
                                  transfer_amount_loop:
                                  cout<<"Enter the amount you want to transfer: ";
                                  double amount;
                                  cin>>amount;
                                  newBalance=userDatabase[user].balance;
                                  if (amount>newBalance){
                                        cout<<"+------------------------------------------------------------+" <<endl
                                            <<"|        * Transfer *                                        |" <<endl
                                            <<"| Your account have no sufficient balance to transfer.       |" <<endl
                                            <<"| your current balance is"<<setw(10)<<newBalance<<"                          |" <<endl
                                            <<"+------------------------------------------------------------+" <<endl;
                                      goto transfer_amount_loop;
                                      }
                                  newBalance-=amount;
                                  // Directly update the balance using the subscript operator
                                  userDatabase[user].balance = newBalance;
                                  // Update the #file with the new user information
                                  writeUserDatabase(filename,userDatabase);
                                  double newuserbalance=userDatabase[str_choice].balance;
                                  newuserbalance+=amount;
                                  userDatabase[str_choice].balance=newuserbalance;
                                  writeUserDatabase(filename,userDatabase);
                                  cout<<"+--------------------------------------------------------------------+" <<endl
                                      <<"|        * Transfer *                                                | " <<endl
                                      <<"| completed!, your account user name \""<<setw(7)<<user<<" \" has been transfered  |"<<endl
                                      <<"|"<<setw(10)<<amount <<" birr to "<<setw(7)<<str_choice<<"                                          | "<<endl
                                      <<"| your current balance is  "<<setw(10)<<userDatabase[user].balance<<"                                |"<<endl
                                      <<"|  1. Back                                                           |" <<endl
                                      <<"|  2. Back to main menu                                              |" <<endl
                                      <<"| press other key except (1 & 2) to terminate the program            |" <<endl
                                      <<"+--------------------------------------------------------------------+" <<endl;
                                  cin>>choice;
                                  if (choice==1){
                                       goto signin_display_loop;
                                   }
                                  else if (choice==2){
                                     goto start_loop;
                                    }

                            } else {
                                cout<<"+------------------------------------------------------------+" <<endl
                                    <<"|        * Transfer *                                        |" <<endl
                                    <<"| User name \""<<setw(6)<<str_choice<<"\" does not exist in the database. |" <<endl
                                    <<"| Please select one of the following option below            |" <<endl
                                    <<"|  1. Try again                                              |" <<endl
                                    <<"|  2. Main menu                                              |" <<endl
                                    <<"+------------------------------------------------------------+" <<endl;
                                 cin>>choice;
                                 switch (choice){
                                  case 1:
                                    goto transfer_loop;
                                    break;
                                  case 2:
                                    goto start_loop;
                                    break;
                                  default:
                                    cout<<"\n invalid input ";
                                     goto transfer_loop;
                                 }

                             }


                   }

                    else if(choice==3){
                           // Deposit
                           cout<<"Enter the amount of money you  want to deposit: ";
                           cin>>choice;

                           newBalance=userDatabase[user].balance;
                           newBalance+=choice;
                           // Directly update the balance using the subscript operator
                          userDatabase[user].balance = newBalance;
                           // Update the #file with the new user information
                           writeUserDatabase(filename,userDatabase);

                           cout <<"+----------------------------------------------------------------+" <<endl
                                <<"|        * Deposit   *                                           |" <<endl
                                <<"| completed!, your account user name \""<<setw(7)<<user<<"\" has been          |"
                                <<"\n| credited "<<setw(10)<<choice <<" birr. Your current balance is  "<<setw(10)<<userDatabase[user].balance<<"  |"<<endl
                                <<"|  1. Back                                                       |" <<endl
                                <<"|  2. Back to main menu                                          |" <<endl
                                <<"| press other key except (1 & 2) to terminate the program        |" <<endl
                                <<"+----------------------------------------------------------------+" <<endl;
                           cin>>choice;
                           if (choice==1){
                                       goto signin_display_loop;
                                   }
                            else if (choice==2){
                                     goto start_loop;
                                    }
                    }
                       else if (choice==4){
                           // withdrawal
                           withdrawal_loop:
                           cout<<"Enter the amount of money you  want to withdrawal: ";
                           cin>>choice;
                           double newBalance=userDatabase[user].balance;
                           if (choice>newBalance){

                                 cout<<"+------------------------------------------------------------+" <<endl
                                     <<"|        * withdrawal *                                      |" <<endl
                                     <<"| Your account have no sufficient balance to withdraw.       |" <<endl
                                     <<"| your current balance is"<<setw(10)<<newBalance<<"                          |" <<endl
                                     <<"+------------------------------------------------------------+" <<endl;
                                     cout<<endl;
                                     goto withdrawal_loop;
                           }
                            else{
                            newBalance-=choice;
                           // Directly update the balance using the subscript operator
                          userDatabase[user].balance = newBalance;
                           // Update the #file with the new user information
                           writeUserDatabase(filename,userDatabase);
                           cout <<"+---------------------------------------------------------------+" <<endl
                                <<"|        * Withdrawal *                                         |" <<endl
                                <<"| completed!, your account user name \""<<setw(7)<<user<<"\" has been         |"
                                <<"\n| debited "<<setw(10)<<choice <<" birr. Your current balance is  "<<setw(10)<<userDatabase[user].balance<<"  |"<<endl
                                <<"|  1. Back                                                      |" <<endl
                                <<"|  2. Back to main menu                                         |" <<endl
                                <<"| press other key except (1 & 2) to terminate the program       |" <<endl
                                <<"+---------------------------------------------------------------+" <<endl;
                            cin>>choice;
                            if (choice==1){
                                       goto signin_display_loop;
                                   }
                            else if (choice==2){
                                     goto start_loop;
                                    }
                            }

                       }
                       else if (choice==5){
                           //service payment

                            cout<<"+------------------------------------------------------------+" <<endl
                                <<"|     * Service payment *                                    |" <<endl
                                <<"| This option is not currently available.                    |" <<endl
                                <<"|  1. Back                                                   |" <<endl
                                <<"|  2. Back to main menu                                      |" <<endl
                                <<"+------------------------------------------------------------+" <<endl;
                           cin>>choice;
                             switch (choice){
                                  case 1:
                                      goto signin_display_loop;
                                  case 2:
                                     goto start_loop;

                                }

                       }
                       else if (choice==6){
                            //exit
                            cout<<"+------------------------------------------------------------+" <<endl
                                <<"|     * Exit *                                               |" <<endl
                                <<"|  1. Back to main menu                                      |" <<endl
                                <<"|  2. Exit from the program                                  |" <<endl
                                <<"+------------------------------------------------------------+" <<endl;
                            cin>>choice;
                            switch(choice){
                                case 1:
                                   goto start_loop;
                                case 2:
                                    cout<<"+------------------------------------------------------------+" <<endl
                                        <<"|     Thank you! for using our bank.                         |" <<endl
                                        <<"+------------------------------------------------------------+" <<endl;
                              }
                       }
                            else {
                             cout<<"Invalid choice ";
                             goto sign_in_loop;

                   }

        } else {
                cout<<"+------------------------------------------------------------+" <<endl;
                cout<<"|     Login failed. Invalid username or password.          |" <<endl;
                cout<<"| Select one of the following option below                   |" <<endl;
                cout<<"|  1. Try again                                              |" <<endl;
                cout<<"|  2. Main menu                                              |" <<endl;
                cout<<"+------------------------------------------------------------+" <<endl;
                cin>>choice;
                switch (choice){
                case 1:
                    goto sign_in_loop;
                case 2:
                    goto start_loop;

                }

        }

        break;
        case 2:
            // Sign Up
           string newUsername, newPassword,newPassword2, name,address;
           double balance;
           user_loop:
           cout << "Enter a new username (user name must be 6 character alphabet) : ";
           cin >> newUsername;
           if (usernameExists(userDatabase, newUsername)) {
                cout<<"The user name already exist.\n ";
                goto user_loop;
           }
           password_loop:
           cout << "Enter a new password (password must be 4 character number : ";
           cin >> newPassword;
           cout<<"Enter the password again ";
           cin>>newPassword2;
           if (newPassword!=newPassword2){
            cout<<"\n The password doesn't match. \n please enter again: ";
            goto password_loop;
           }
           cout << "Enter your name: ";
           cin>> name;
           cout<<"Enter the initial balance: ";
           cin>>balance;
           cout<<"Enter your address: ";
           cin>>address;

           UserInfo newUser{newUsername, newPassword,name, balance,address};
           userDatabase[newUsername] = newUser;

           // Update the file with the new user
           writeUserDatabase(filename, userDatabase);
            cout<<"+------------------------------------------------------------+" <<endl;
            cout<<"|     * Sign Up successful! *                                |" <<endl;
            cout<<"| press any key except \"1\" to terminate the program          |" <<endl;
            cout<<"|  1. Main menu                                              |" <<endl;
            cout<<"+------------------------------------------------------------+" <<endl;
            cin>>choice;
            if (choice==1){
                goto start_loop;
                }
            else{
             cout<<"+------------------------------------------------------------+" <<endl
                 <<"|     Thank you! for using our bank.                         |" <<endl
                 <<"+------------------------------------------------------------+" <<endl;
            }

              }

return 0;
}
