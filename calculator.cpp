#include <iostream>
#include <string>
using namespace std;
int main ()
{
  int Answer;
  char iInput;
  cout << "Welcome to the calculator! " << endl << endl;
do
{
  cout << endl << "Menu: " << endl;
  cout << "1. Convert seconds to hours" << endl;
  cout << "2. Convert seconds to minutes" << endl;
  cout << "3. Convert minutes to hours" << endl;
  cout << "4. Convert hours to seconds" << endl;
  cout << "5. Exit the program." << endl << endl;
  cout << "Please select an option: " << "	";
  cin >> Answer;

  if (Answer < 0)
  {
    cout << "Inavlid input, please enter a non-negative number from 1 to 5" << endl;
  }

  else if (Answer == 1)
  {
    cout << "Enter time in seconds: ";
    double seconds;
    if (!(cin >> seconds) || ( seconds < 0))
    {
      cout << "Invalid intput, please enter a non - negative number." << endl;
      cin.clear ();
      std::string temp;
      std::getline(cin, temp);
      continue;
    }
    double hours;
    hours = seconds / 3600;
    cout << seconds << " seconds when converted to hours is " << hours << " hours." << endl;
  }

  else if (Answer == 2)
  {
    cout << "Enter time in seconds: ";
    double seconds;
    if (!(cin >> seconds ) || (seconds < 0))
    {
      cout << "Invalid input, please enter a non - negative number." << endl;
      cin.clear ();
      std::string temp;
      std::getline(cin, temp);
      continue;
    }
    double minutes;
    minutes = seconds / 60;
    cout << seconds << " seconds when converted to minutes is " << minutes << " minutes." << endl;
  }

  else if (Answer == 3)
  {
    cout << "Enter time in minutes: ";
    double minutes;
    if (!(cin >> minutes) || (minutes < 0))
    {
      cout << "Invalid input, please enter a non - negative number." << endl;
      cin.clear ();
      std::string temp;
      std::getline(cin, temp);
      continue;
    }
    double hours;
    hours = minutes /60;
    cout << minutes << " minutes when converted to hours is " << hours << " hours." << endl;
  }

  else if ( Answer == 4)
  {
    cout << "Enter time in hours: ";
    double hours;
    if (!(cin >> hours ) || (hours < 0))
    {
      cout << "Invalid input, please enter a non - negative number." << endl;
      cin.clear ();
      std::string temp;
      std::getline(cin, temp);
      continue;
    }
    double seconds;
    seconds = hours * 3600;
    cout << hours << " hours when converted to seconds is " << seconds << " seconds." << endl;
  }

  else if (Answer == 5)
  {
    cout << "Are you sure you want to exit the program? (y/n)" << endl;
    cin >> iInput;
    if (iInput == 'y' || iInput == 'Y')
    {
      cout << "Goodbye!" << endl;
    }
    else if (iInput == 'n' || iInput == 'N')
    {
      cout << "Returning to the menu." << endl;
    }
    else
    {
      cout << "Invalid input, please enter 'y' or 'n'." << endl;
    }
  }

  else
  {
    cout << "Invalid intput, please enter a valid option from 1 to 5." << endl;
    cin.clear ();
    std::string temp;
    std::getline(cin, temp);
    continue;
  }

}

while (true && iInput != 'y');
return 0;
}
