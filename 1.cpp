#include <iostream>
#include <fstream>
#include <set>
using namespace std;

struct CustomerAddress
{
	string Country;
	string City;
	string ZipCode;
};
struct CustomerInformation
{
	string Name;
	string MobileNumber;
	CustomerAddress Address;
	string Username;
	string Password;
}Customer;
//Global Variables
string filename;
int numCars = 0;
int numAllCars = 0;
const int MAX_CARS = 100;
struct car {
    string brand;
    string model;
    string color;
    double distanceTraveled;
    bool available = true;
};
car cars[MAX_CARS];
car fullcars[MAX_CARS];
set<string> existingEntries; // Set to store existing entries in allCars.txt

bool Login() {
    string Username, Password, CustomerUsername, CustomerPassword;

    cout << "Username: ";
    cin.ignore(1, '\n');
    getline(cin, Username);
    filename = Username;

    cout << "Password: ";
    getline(cin, Password);

    ifstream Read(Username + ".txt");
    getline(Read, CustomerUsername);
    getline(Read, CustomerPassword);
    Read.close();

    return (Username == CustomerUsername && Password == CustomerPassword);
}

void save() {
    // Save individual car data
    ofstream savecars(filename + "cars.txt");
    for (int i = 0; i < numCars; i++)
        savecars << cars[i].brand << " " << cars[i].model << " " << cars[i].color << " " << cars[i].distanceTraveled << " ";
    savecars.close();  

    //save dara in allcars.txt
    ofstream allcars("allCars.txt");
        for (int i = 0; i < numAllCars; ++i) {
            allcars << fullcars[i].brand << " " << fullcars[i].model << " " << fullcars[i].color << " " << fullcars[i].distanceTraveled << " " << fullcars[i].available << " ";
        }
        allcars.close();
 
}

void load() {
    ifstream infile(filename + "cars.txt");
    if (infile) {
        while (infile >> cars[numCars].brand >> cars[numCars].model >> cars[numCars].color >> cars[numCars].distanceTraveled) {
            numCars++;
            if (numCars >= MAX_CARS)
                break;
        }
        infile.close();
    }

    ifstream allcars("allCars.txt");
    if (!allcars) {
        cout << "Error: Cannot open file for reading!" << endl;
        return;
    }

    while (allcars >> fullcars[numAllCars].brand >> fullcars[numAllCars].model >> fullcars[numAllCars].color >> fullcars[numAllCars].distanceTraveled >> cars[numAllCars].available) {
        numAllCars++;
        if (numAllCars >= MAX_CARS)
            break;
    }
    allcars.close();
}
void list() {
    cout << "List of cars:" << endl;
    for (int i = 0; i < numCars; ++i) {
        cout << "Car " << i + 1 << ":" << endl;
        cout << "Brand: " << cars[i].brand << endl;
        cout << "Model: " << cars[i].model << endl;
        cout << "Color: " << cars[i].color << endl;
        cout << "Distance Traveled: " << cars[i].distanceTraveled << " miles" << endl;
        cout << endl;
    }
}

void addcar() {
    string brand, model, color;
    double distanceTraveled;
    char ans;
    do {
        cout << "Enter the brand: ";
        cin >> brand;
        cout << "Enter the model: ";
        cin >> model;
        cout << "Enter the color: ";
        cin >> color;
        cout << "Enter the distanceTraveled: ";
        cin >> distanceTraveled;

        cars[numCars] = { brand, model, color, distanceTraveled };
        numCars++;
        fullcars[numAllCars] = { brand, model, color, distanceTraveled };
        numAllCars++;

        cout << "Car added successfully!" << endl;
    ofstream savecars(filename + "cars.txt" ,std::ios::app);
        savecars << brand << " " << model << " " << color << " " << distanceTraveled << " " << true << " ";
    savecars.close();

        ofstream allcars("allCars.txt", std::ios::app);

        allcars << brand << " " << model << " " << color << " " << distanceTraveled << " " << true << " ";

        allcars.close();

        cout << "Do you want to add another car? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
}


void update() {
    char A;
    int CarNum, detail;
    cout << "Choose a car to update:" << endl;
    list();
    cin >> CarNum;

    // Locate the index of the car to update in the fullcars array
    int carIndex=-1;
    for (int i = 0; i < numAllCars; ++i) {
        if (CarNum > 0 && fullcars[i].brand == cars[CarNum-1].brand && fullcars[i].model == cars[CarNum-1].model && fullcars[i].color == cars[CarNum-1].color && fullcars[i].distanceTraveled == cars[CarNum-1].distanceTraveled) {
            carIndex = i;
            break;
        }
    }
    if (carIndex == -1) {
        cout << "Car not found." << endl;
        return;
    }

    cout << "Which detail do you want to update?" << endl;
    cout << "Enter 1 for brand" << endl;
    cout << "Enter 2 for model" << endl;
    cout << "Enter 3 for color" << endl;
    cout << "Enter 4 for distanceTraveled" << endl;
    cin >> detail;

    switch (detail) {
        case 1:
            cout << "Enter new brand: ";
            cin >> cars[CarNum-1].brand;
            fullcars[carIndex].brand = cars[CarNum-1].brand;
            break;
        case 2:
            cout << "Enter new model: ";
            cin >> cars[CarNum-1].model;
            fullcars[carIndex].model = cars[CarNum-1].model;

            break;
        case 3:
            cout << "Enter new color: ";
            cin >> cars[CarNum-1].color;
            fullcars[carIndex].color = cars[CarNum-1].color;
            break;
        case 4:
            cout << "Enter new distanceTraveled: ";
            cin >> cars[CarNum-1].distanceTraveled;
            fullcars[carIndex].distanceTraveled = cars[CarNum-1].distanceTraveled;
            break;
        default:
            cout << "Invalid number!";
            return;
    }

    cout << "Car " << CarNum << " updated:" << endl;
    cout << "Brand: " << cars[CarNum-1].brand << endl;
    cout << "Model: " << cars[CarNum-1].model << endl;
    cout << "Color: " << cars[CarNum-1].color << endl;
    cout << "Distance Traveled: " << cars[CarNum-1].distanceTraveled << " miles" << endl;

    save();
   

    cout << "Do you want to update another car? (y/n)" << endl;
    cin >> A;

    if (A == 'y' || A == 'Y') {
        update();
    } else if (A == 'n' || A == 'N') {
        cout << "Update successful!\n\n";
        return;
    } else {
        cout << "Invalid answer -- returning to the menu";
    }
}



 void removecar() {
    int pos;
    list();
    cout << "Choose a car to remove (enter car number): ";
    cin >> pos;
    int carIndex=-1;
    for (int i = 0; i < numAllCars; ++i) {
        if (pos > 0 && fullcars[i].brand == cars[pos-1].brand && fullcars[i].model == cars[pos-1].model && fullcars[i].color == cars[pos-1].color && fullcars[i].distanceTraveled == cars[pos-1].distanceTraveled) {
            carIndex = i;
            break;
        }
    }
    if (carIndex == -1) {
        cout << "Car not found." << endl;
        return;
    }
        for (int j = carIndex; j < numAllCars; ++j) {
            fullcars[j] = fullcars[j + 1];
        }
        numAllCars--;
         ofstream allcars("allCars.txt");
        for (int i = 0; i < numAllCars; ++i) {
            allcars << fullcars[i].brand << " " << fullcars[i].model << " " << fullcars[i].color << " " << fullcars[i].distanceTraveled << " " << fullcars[i].available << " ";
        }
        allcars.close();


  for (int p=pos-1 ; p<numCars ; ++p)
    {
        cars[p]=cars[p+1];
    }
    numCars--;
        // Remove car from username.txt
        ofstream savecars(filename + "cars.txt");
        for (int i = 0; i < numCars; ++i) {
                savecars << cars[i].brand << " " << cars[i].model << " " << cars[i].color << " " << cars[i].distanceTraveled << " ";
        savecars.close();
    }
    cout << "Car removed successfully!\n" << endl;
        list(); // Display updated list of cars
    }

void rent() {
       
    
    cout << "List of cars:" << endl;
    for (int i = 0; i < numAllCars  ; ++i) {
        cout << "Car " << i + 1 << ":" << endl;
        cout << "Brand: " << fullcars[i].brand << endl;
        cout << "Model: " << fullcars[i].model << endl;
        cout << "Color: " << fullcars[i].color << endl;
        cout << "Distance Traveled: " << cars[i].distanceTraveled << " miles" << endl;
        cout << endl;
    }
    cout<<"choose a car to rent (enter car number)"<<endl;
    int rchoice;
    cin>>rchoice;
    if (fullcars[rchoice-1].available == false)
 {
    cout<<"\nCar is not available\n";
        return;
 }
    else if (fullcars[rchoice-1].available == true)
    {
    cout<<"\nCar rented successfully\n"<<endl;
    fullcars[rchoice-1].available = false;


   
    }

}

void check() 
{
   cout << "List of cars:" << endl;
    for (int i = 0; i < numAllCars  ; ++i) {
        cout << "Car " << i + 1 << ":" << endl;
        cout << "Brand: " << fullcars[i].brand << endl;
        cout << "Model: " << fullcars[i].model << endl;
        cout << "Color: " << fullcars[i].color << endl;
        cout << "Distance Traveled: " << fullcars[i].distanceTraveled << " miles" << endl;
        cout << endl;
    }
    cout<<"choose a car to check (enter car number)"<<endl;
    int rchoice;
    cin>>rchoice;
    if (fullcars[rchoice-1].available)
    cout<<"\nthe car you choose is availabe for rent\n"<<endl;
    else
    cout<<"\nthe car you choose is unavailabe for rent\n"<<endl;

}




int main() {
    cout << "\t\t\t\t\t\t\t  ---------------------------------" << endl;
	cout << "\t\t\t\t\t\t\t\t     Rent A Car" << endl;
	cout << "\t\t\t\t\t\t\t  ---------------------------------" << endl << endl;
	cout << "Press" << endl;
	cout << "1 to Register" << endl;
	cout << "2 to Login" << endl << endl;
	cout << "Your choice : ";

	string Choice;
	cin >> Choice;

	cout << endl << endl << endl;

	if (Choice == "1")
	{
		cout << "| Registration |" << endl << endl;

		cout << "Full Name : ";
		cin.ignore(1, '\n');
		getline(cin, Customer.Name);
		cout << endl;

		cout << "Mobile Number : ";
		getline(cin, Customer.MobileNumber);
		while ((Customer.MobileNumber).length() < 11)
		{
			cout << "Error!,Mobile Number less than 11 digits" << endl << endl;

			cout << "Mobile Number : ";
			getline(cin, Customer.MobileNumber);

		}
		cout << endl;

		cout << "Country : ";
		getline(cin, Customer.Address.Country);
		cout << endl;

		cout << "City : ";
		getline(cin, Customer.Address.City);
		cout << endl;

		cout << "Zip Code : ";
		getline(cin, Customer.Address.ZipCode);
		cout << endl;

		cout << "Username : ";
		getline(cin, Customer.Username);
		cout << endl;

		cout << "Password : ";
		getline(cin, Customer.Password);
		while ((Customer.Password).length() < 6)
		{
			cout << "Error!,Password less than 6 digits" << endl << endl;

			cout << "Password : ";
			getline(cin, Customer.Password);
		}
		cout << endl << "Regsitration complete!" << endl;

		ofstream File;
		File.open(Customer.Username + ".txt");
		File << Customer.Username << endl;
		File << Customer.Password << endl;
		File << Customer.Name << endl;
		File <<Customer.MobileNumber << endl;
		File << Customer.Address.Country << endl;
		File << Customer.Address.City << endl;
		File << Customer.Address.ZipCode << endl;

		File.close();

		main();

	}
	else if (Choice == "2")
	{
		bool Status;

		Status = Login();

		if (Status)
		{
			cout << "Login successfull" << endl << endl;

		}
		else
		{
			cout << "Wrong username or password!" << endl;
            main();
		}
	}
	else
	{
		cout << "Invalid choice" << endl;
		cout << "Please re-enter correct choice" << endl << endl;
		main();
	}
     load();
    int opt;
    bool leave = false;
    cout << "Welcome\n";
    do
    {
    cout
     << "\nChoose an option:\n"
     << "1. Show list of cars.\n"
     << "2. Add a car.\n"
     << "3. Edit a car.\n"
     << "4. Remove a car.\n"
     << "5. Rent a car.\n"
     << "6. Chek car availablty.\n"
     << "7. Exit\n";
    cin>>opt;
    if (opt <8 && opt > 0)
    {
        switch (opt)
        {
            case 1 : 
            {
            list();
            break;
            }
            case 2 :
            {
            addcar();
            break;
            }
            case 3 :
            {
            update();
            break;
            }
            case 4 : 
            {
            removecar();
             break;
            }
            case 5 :
            {
            rent();
            break;
            }
            case 6 :
            {
                check();
                break;
            }
            case 7 :
            {
            save();
            leave=true;
            return 0;
             break;
            }
        }
    }
    else{
        cout<<"invalid answer please enter a valid number!"<<endl;
    }
    }
    while(!leave);
    cout<<"\nExit succesful!\n";
  return 0;
}