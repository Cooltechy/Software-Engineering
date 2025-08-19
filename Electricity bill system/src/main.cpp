#include<bits/stdc++.h>
using namespace std;

void Menu(){
    cout<<"1. Register User\n";
    cout<<"2. Generate Bill\n";
    cout<<"3. Process Payment\n";
    cout<<"4. Report - Bills Not Paid\n";
    cout<<"5. Report - By Service Number\n";
    cout<<"6. Exit\n";
}

int main(){

    cout<<"<===============Electricity Bill Management System===============>\n";

    
    while(1){
        Menu();
        cout<<"Enter your choice: ";
        int choice;
        cin>>choice;

        switch(choice){
            case 1:
                // Call register user function
                break;
            case 2:
                // Call generate bill function
                break;
            case 3:
                // Call process payment function
                break;
            case 4:
                // Call report unpaid bills function
                break;
            case 5:
                // Call report by service number function
                break;
            case 6:
                cout<<"Thank you for using the system!\n";
                exit(0);
            default:
                cout<<"Invalid choice! Please try again.\n";
        }
    }


}