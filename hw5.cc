/*
Name: Lydia Shiffler
date: 4/3/19
Description: Homework5 -- using MPI -- password encoder. Uses salts and encrypted passwords to solve passwords
*/



#include <string>
#include <vector>
#include <fstream>
#include <sstream> 
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>
#include <iostream>


using namespace std;

vector <string> passwords; //encoded passwords
vector <string> salts; //salts 
vector <string> words; //dictionary of words 
int maxdig = 3; // only 3 digits allowed in password 

//hint from juedes:
//take word - dictionary and make a big string - put a hash symbol in between- send whole thing 
//then split it up at the end -- not sure if this is how i want to do it or not?


//read file in
vector <string> load(string &filename) //loading files in 
{
    vector <string> x;
    ifstream file(filename.c_str());
    if(file.is_open())
    {
        string temp;
        while(getline(file, temp))
        {
            x.push_back(temp); 
        }
        file.close();
    }
    return x;
}


//class for solving passwords;
class solve
{
    public:
    /*
    cracking_the_code(vector <string> &salts,vector <string> &passwords, vector <string> &words, int thread_size, int thread_rank, int maxdig = 3)
    {

    }
*/

    //need function to solve the passwords using the hash funciton in the private section of the solve class
    void crack_code(vector <string> &salts,vector <string> &passwords, vector <string> &words, int thread_size, int thread_rank, int maxdig = 3)
    {
        vector <bool> found(passwords.size()); //vector to store the found passwords 
        for(int i = thread_rank; i < words.size(); i += thread_size) //goes from thread rank to thread size
        {
            string word = words[i]; //stores word
            for(int j = 0; j <= maxnumbers; j++)
            {
                stringstream ss;
                ss << j;
                string number = ss.str();

                string pass1 = number + word;
                string pass2 = word + number;

                hash(found, salts, passwords, pass1);
                hash(found, salts, passwords, pass2);
            }
        }
    }
    private:
        vector <string> passwords; //encoded passwords
        vector <string> salts;
        vector <string> words; //dictionary of words 
        int maxnumbers; //there are only a certain amount of numbers allowed 
        int max_pass; //maximum amount of passwords
        int thread_size;
        int thread_rank;

        //hash function that takes a bool vector, vector of salts, passwords, and words
       
        void hash(vector <bool> &found, vector <string> &salts,vector <string> &passwords, vector <string> &words)
        {
            if(int i = 0; i < salts.size(); i++) //needs for loop to go through all the salts
            {
                if(!found[i]) //if the address at the bool vecotr is not there
                {
                    string encoded_words;
                    encoded_words = crypt(words.str(), salts[i].str());
                    if(encoded_words.compare(passwords[i]) == 0)
                    {
                        cout << "password " << i+1 << "found and is " << words << endl;
                        found[i] = 1;
                       
                    }
                }
            } 
        }

};





int main(int argc, char* argv[])
{
    
    
    solve solver;

    solver.crackcode();
    
    MPI_Init(&argc, &argv); //initialized MPI
    
    int thread_size;
    MPI_Comm_size(MPI_COMM_WORLD, &thread_size); //number of processes

    int thread_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &thread_rank); //where the process is (rank)

    if(thread_rank == 0) //checks if the rank starts at 0, and prints out how many threadsd there are
    {
        cout << thread_size << "threads" << endl;
    }

    string file_of_passwords; //string of filename for encoded passwords
    string file_of_salts; //string of filename for salts
    string file_of_words; //string of filename for words(dictionary)

    if(argc < 3) //checking the number of arguments and asking the user to enter which files
    {
        cout << "enter file name for encrypted passwords: " << endl; //needs to be enc_passwords, not passwords
        cin >> file_of_passwords;
        cout << "enter file name for salts: " << endl;
        cin >> file_of_salts;
        cout << "enter file name for dictionary: " << endl;
        cin >> file_of_words;
    }
    else //loads in arguments -- put arguments in make file :)
    {
        {
            file_of_passwords = argv[1];
            file_of_salts = argv[2];
            file_of_words = argv[3];
        }
    }
 //vector of strings for each file
    vector <string> passwords = load(file_of_passwords);
    vector <string> salts = load(file_of_salts);
    vector <string> words = load(file_of_words); 

    vector <string> possible_pass(); //max two dictionary words and max 3 digits 
   


}
