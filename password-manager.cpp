#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>

using namespace std;
using namespace CryptoPP;

class PasswordManager {
private:
  string masterPasswordHash; // Stores hashed master password
  vector <string> usernames; // Stores usernames
  vector <string> passwords; // Stored passwords
  const string FILENAME = "passwords.dat"; // File to store credentials

  string hashPassword(const string& password); // Hashes the password
  string generateRandomPassword(const string& username); // Generates a unique password based on the username

public:
  PasswordManager(); //Concstructor to load existing credentials
  bool setMasterPassword(const string& password); // Sets the master password
  bool authenticate(const string& password); // Authenticates the master password
  void addCredentials(const string& username); // Stores a new usernames with a generated password
  string getCredentials(const string& username); // Retrieves the generated password for the username
  void deleteCredentials(const string& username); //Removed stored credentials for the given usename
  void saveToFile(); // Saves cresentials to a file
  void loadFromFile(); // Loads credentials from a file
  void displayMenu(); // Displas the menu for the user
};


//Constructor loads saved credentials
PasswordManager::PasswordManager()
{
  loadFromFile();
}


//Hashing function using SHA-256
string PasswordManager::hashPassword(const string& password)
{
  string hash;
  SHA256 sha256; //Create a SHA-256 hash object
  StringSource(password, true, //Use the SHA-256 hash object to encrypt the inputted password
    new HashFilter(sha256, new HexEncoder(new StringSink(hash))));// Convert hash to hexadecimal
  return hash;
}

//Random Password Generator - Creates a unique password based on a username
string PasswordManager::generateRandomPassword(const string& username)
{
  const string characters = //Password will be generated from these set of charcters
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789"
    "!@#$%^&*()-_=+[]{}|;:,.<>?";

  SHA256 hash; //Create a SHA-256 hash object a hash for a given username
  string digest;

//Hash the username to create a unique output
StringSource(username, true,
  new HashFilter(hash,
  new HexEncoder(new StringSink(digest)))); // Output is encoded in hexadecimal format and stored in digest

string password; // initializes a string to store the generated password

for (size_t i=0; i < 16; i++) //loop 16 times to generate a password with 16 charcters
{
  //Convert hex charcters to an index in the characters array
  size_t index = stoi(digest.substr(i*2,2),nullptr,16) % characters.size();
  password += characters[index];
}
return password; //Return a 16-character password with mixed characters
}

//Establishes the master password
bool PasswordManager::setMasterPassword(const string& password)
{
  if (masterPasswordHash.empty())
  {
    masterPasswordHash = hashPassword(password); // Hash the entered password and save it as the master password
    cout << "Master password set successfully." << endl;
    return true;
  }
  return false;
}

// Verifies if stored master password matches entered master password
bool PasswordManager::authenticate(const string& password)
{
  return hashPassword(password) == masterPasswordHash;
}

//Stores the username with a generated password
void PasswordManager::addCredentials(const string& username)
{
  string newPassword = generateRandomPassword(username); // Generates a random password for a given username
  usernames.push_back(username); //Store the username
  passwords.push_back(hashPassword(newPassword)); // Store the hashed passowrd
  cout << "Generated password: " << newPassword << endl;
  saveToFile(); // Save updates credentials to file
}

//Retrieves a generated password for a given username
string PasswordManager::getCredentials(const string& username)
{
  for (size_t i =0; i < username.size(); i++) //Loop through the stored usernames
  {
    if (usernames[i] == username)
    {
    return generateRandomPassword(username);
    }
  }
  return "User not found"; // Return error message if username is not found
}

// Removes stored credentials for a given username
void PasswordManager:: deleteCredentials(const string& username)
{
  for (size_t i=0; i < usernames.size(); i++) // Loop through the stored usernames
  {
    if (usernames[i] == username)
    {
      // Remove the username and corresponding password from the vectors
      usernames.erase(usernames.begin() + i);
      passwords.erase(passwords.begin() + i);
      cout << "Credentials for " << username << " deleted." << endl;
      saveToFile();
      return;
    }
  }
 cout << "Username not found." << endl;
}

//Saves credentails to a file
void PasswordManager::saveToFile()
{
  ofstream file(FILENAME); //Open file for writing
  if (!file)
  {
    cout << "Error! Could not open file." << endl; //Display error message if file cannot open
    return;
  }

  for (size_t i=0; i < usernames.size(); i++) // Save each username and hashed password to file
  {
    file << usernames [i] << " : " << passwords[i] << endl;
  }

  file.close();
  cout << "Credentials saved successfully to file." << endl; // Display success message after saving is complete and file is closed
}

//Loads credentails from a file
void PasswordManager::loadFromFile()
{
  ifstream file(FILENAME); //Open file to read
  if (!file)
  {
    cout << "Error! No existing credentials found." << endl;
    return;
  }

  usernames.clear(); // Clear existing usernames
  passwords.clear(); // Clear existing passwords

  string username, password;
  while (file >> username >> password)
  {
    usernames.push_back(username);
    passwords.push_back(password);
  }

  file.close();
  cout << "Credentials loaded successfully from file." << endl;
}

// Provides an interactive menu for the user
void PasswordManager::displayMenu()
{
  int option;
  string username, password;

  if(masterPasswordHash.empty()) // Prompt user yo set master password, or check if its already set
  {
    cout << "Set master password: ";
    cin >> password;
    setMasterPassword(password);
  }

  cout << "Enter master password to continue: "; // Prompt user to enter master password again to authenticate the master password
  cin >> password;

  if (!authenticate(password)) // Exit program if authentication fails
  {
    cout << "Incorrect master password. Exiting." << endl;
    return;
  }

do
{
  // Display title and menu options
  cout << endl << endl << "Password Manager" << endl << endl;
  cout << "1. Add Credentials" << endl;
  cout << "2. Get Credentials" << endl;
  cout << "3. Delete Credentials" << endl;
  cout << "4. Save to File" << endl;
  cout << "5. Load from File" << endl;
  cout << "6.Exit" << endl;
  cout << "Enter your option: " << endl;

  switch (option)
  {
    case 1: // Enter a username and add credentials for it
      cout << "Enter username ";
      cin >> username;
      addCredentials(username);
      break;

    case 2: // Enter a username and get the crdentials for that specific username
      cout << "Enter username: ";
      cin >> username;
      cout << "Retrieved password: " << getCredentials(username) << endl;
      break;

    case 3: //Enter a username and delete its credentials
      cin >> username;
      cout << "Enter username: ";
      deleteCredentials(username);
      break;

    case 4: // Save credentials to a file
      saveToFile();
      break;

    case 5: // Load credentials from a file
      loadFromFile();
      break;

    case 6: // Exit the program
      cout << "Exiting Password Manager....." << endl;
      break ;

    default: // Handle invalid option
    cin.clear (); // Clear the error flag
    string temp;
    getline(cin, temp); // Clear the invalid input from the buffer
    cout << "Invalid input. Please enter a valid option from 1 to 6." << endl;
 }

 } while (option !=6);
}

//Main function
int main ()
{
  PasswordManager manager;// Create a PasswordManager object
  manager.displayMenu(); // Call menu function
  return 0; //Exit the program successfully
}
