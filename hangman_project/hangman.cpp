#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

class Hangman {
    
    public:
        int words_guessed_correctly;
        void open_category(std::vector <std::string> word_list) {
            //Function to begin playing and open the chosen word list for picking words
            bool category_open = true;
            int category_menu_input;
            while (category_open){
                std::cout << "Get ready to play!\n";
                std::cout << "1. Begin round\n";
                std::cout << "2. Return to main menu\n";
                std::cout << ">>>";
                //Get the user's input to either start the round or go back to the category menu
                std::cin >> category_menu_input;

                std::string new_word; //Variable for storing the random word itself
                std::string new_word_blank; //Variable for storing and keeping track of the blank spaces and letters already guessed correctly
                bool playing;
                int new_word_index;
                //Start the user off with 5 lives
                int lives = 5;
                std::vector <char> bad_guesses; //Vector for storing all the guesses that weren't in the word
                char new_guess;
                bool letter_in_word = false; //Vector for each loop to check if the guess was in the word
                switch(category_menu_input) {
                    case 1 :
                        playing = true;
                        new_word_index = rand() % word_list.size();
                        new_word = word_list[new_word_index];
                        new_word_blank = "";
                        for (int i = 0;i<new_word.length();i++){
                            new_word_blank += "_";
                        }
                        while (playing) {
                            letter_in_word = false;
                            std::cout << new_word_blank << "\n";
                            std::cout << "Lives: " << lives << "\n";
                            std::cout << "Letters guessed: ";
                            for(int i=0;i<bad_guesses.size();i++){
                                std::cout << bad_guesses[i];
                                std::cout << " ";
                            }
                            std::cout << "\n";
                            
                            std::cout << "Next guess >>> ";
                            std::cin >> new_guess;
                            for(int i = 0;i<new_word.length();i++){
                                if(new_word[i] == new_guess){
                                    new_word_blank[i] = new_guess;
                                    letter_in_word = true;
                                }
                            }

                            if(!letter_in_word){
                                bad_guesses.push_back(new_guess);
                                lives -= 1;
                                std::cout << "Sorry, " << new_guess << " isn't in the word! Try again!\n\n";
                            } else {
                                std::cout << "You got it! The word does have '" << new_guess << "' in it! \n\n";
                            }

                        if (lives == 0) {
                            bool asking = true;
                            while (asking){
                                std::cout << "Sorry, you ran out of lives! \n The word was: " << new_word << "\n";
                                std::cout << "Would you like to play again in this category? y/n\n";
                                std::cout << ">>>";
                                std::string play_again;
                                std::cin >> play_again;
                                if (play_again == "y") {
                                    //Remove the word already used from the list to ensure it's not pulled again for the next round
                                    word_list.erase(word_list.begin() + new_word_index); 
                                    playing = false;
                                    asking = false;
                                } else if (play_again == "n") {
                                    category_open = false;
                                    playing = false;
                                    asking = false;
                                } else {
                                    std::cout << "Sorry, try typing either 'y' or 'n' \n";
                                }
                            }
                        }
                        if (new_word_blank == new_word) {
                            bool asking = true;
                            while(asking) {
                                words_guessed_correctly += 1;
                                std::cout << "You got the whole word! It was " << new_word << " \n";
                                std::cout << "Would you like to play again in this category? y/n\n";
                                std::cout << ">>> ";
                                std::string play_again;
                                std::cin >> play_again;
                                if (play_again == "y") {
                                    //Remove the word already used from the list to ensure it's not pulled again for the next round
                                    word_list.erase(word_list.begin() + new_word_index); 
                                    playing = false;
                                    asking = false;
                                } else if (play_again == "n") {
                                    playing = false;
                                    category_open = false;
                                    asking = false;
                                } else {
                                    std::cout << "Sorry, try typing either 'y' or 'n'\n";
                                }
                            }
                        }
                        }

                        break;
                    case 2 :
                        category_open = false;
                        break;
                }
            }
        }

        void begin_to_play() {
            //Open files to read all the lists of words
            std::ifstream farm_word_file;
            std::ifstream store_word_file;
            std::ifstream countries_word_file;
            std::ifstream fruits_word_file;
            
            farm_word_file.open("farm_words.txt");
            store_word_file.open("store_words.txt");
            countries_word_file.open("countries_words.txt");
            fruits_word_file.open("fruits_words.txt");

            //Create vectors to store all the words in each file
            std::vector <std::string> farm_word_list;
            std::vector <std::string> store_word_list;
            std::vector <std::string> countries_word_list;
            std::vector <std::string> fruits_word_list;

            //Populating word list vectors with the words from the text files
            std::string text;

            while (getline (farm_word_file,text)){
                farm_word_list.push_back(text);
            }
            
            while (getline (store_word_file,text)){
                store_word_list.push_back(text);
            }
            
            while (getline (countries_word_file,text)){
                countries_word_list.push_back(text);
            }

            while (getline (fruits_word_file, text)) {
                fruits_word_list.push_back(text);
            }


            std::cout << "Let's play!\n\n";
            bool playing = true;
            int category_choice;
            while (playing) {
                //List out all the available categories
                std::cout << "Pick a category!\n";
                std::cout << "1. Farm\n";
                std::cout << "2. Store\n";
                std::cout << "3. Countries\n";
                std::cout << "4. Fruits\n";
                std::cout << "5. Exit\n\n";
                std::cout << ">>>";
                //Get the choice of category and open the corresponding category itself
                std::cin >> category_choice;
                switch(category_choice){
                    case 1 :
                        open_category(farm_word_list);
                        break;

                    case 2 :
                        open_category(store_word_list);
                        break;

                    case 3 : 
                        open_category(countries_word_list);
                        break;

                    case 4 :
                        open_category(fruits_word_list);
                        break;

                    case 5 :
                        playing = false;
                        break;
                }
            }
        }

        void add_new_word(std::string new_word,std::vector <std::string> word_list, std::string file_name) {
            //Function for adding words to the file for use in the game
            word_list.push_back(new_word);
            std::fstream word_file_to_edit;
            word_file_to_edit.open(file_name, std::ios_base::app);
            new_word = "\n" + new_word;
            word_file_to_edit << new_word;
            word_file_to_edit.close();
        }

        void open_editing_of_category(std::string file_name,std::string category_name){
            std::vector <std::string> current_word_list;
            std::ifstream word_file;
            word_file.open(file_name);
            std::string text;
            while (getline (word_file,text)){
                current_word_list.push_back(text);
            }
            word_file.close();

            bool editing_category_open = true;

            while(editing_category_open) {
                std::cout << "let's add to the " << category_name << " category\n";
                std::cout << "Just type 'exit' to go back to the previous menu\n";
                std::cout << "What word would you like to add?\n";
                std::cout <<">>> ";
                std::string new_word;
                std::cin >> new_word;

                if (new_word == "exit") {
                    editing_category_open = false;

                } else if (std::count(current_word_list.begin(),current_word_list.end(),new_word)){
                    std::cout << "Sorry, " << new_word << " is already in this file, try another word!\n";

                } else {
                    std::cout << "Ok! " << new_word << " has been added to the list!\n";
                    current_word_list.push_back(new_word);
                    add_new_word(new_word,current_word_list,file_name);
                }
            }
        }

        void open_add_words() {
            //Function for adding words to a words text file
            bool editing_menu = true;
            while (editing_menu) {
                std::cout << "Welcome to the editing menu.\n";
                std::cout << "Which category would you like to add to? \n";
                std::cout << "1. Farm\n";
                std::cout << "2. Store\n";
                std::cout << "3. Countries\n";
                std::cout << "4. Fruits\n";
                std::cout << "5. Exit\n\n";
                std::cout << ">>>";
                int category_edit_choice;
                std::cin >> category_edit_choice;
                switch(category_edit_choice) {
                    case 1 :
                        open_editing_of_category("farm_words.txt","Farm");
                        break;

                    case 2 :
                        open_editing_of_category("store_words.txt","Store");
                        break;

                    case 3 :    
                        open_editing_of_category("countries_words.txt","Countries");
                        break;

                    case 4 :
                        open_editing_of_category("fruits_words.txt","Fruits");
                        break;

                    case 5 :
                        editing_menu = false;
                        break;  
                }
            }
        }

        void main_menu() {
            words_guessed_correctly = 0;
            bool main_menu_open = true;
            while (main_menu_open) {
                int menu_choice;
                std::cout << "Welcome to hangman!\n";
                std::cout << "1. Play\n";
                std::cout << "2.Add Words\n";
                std::cout << "3. Exit\n";
                std::cout << ">>>";
                std::cin >> menu_choice;
                switch (menu_choice) {
                    case 1 :
                        begin_to_play();
                        break;
                    case 2 :
                        open_add_words();
                        break;
                    case 3 :
                        main_menu_open = false;
                        break;
                }
            }
        }
    };




int main() {
    Hangman main_game;
    main_game.main_menu();
    std::cout << "You got " << main_game.words_guessed_correctly << " words this time! \n";
    if (main_game.words_guessed_correctly >= 3){
        std::cout << "Great job!";
    }
    std::cout << "Bye!";
}