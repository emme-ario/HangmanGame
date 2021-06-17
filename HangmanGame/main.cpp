#include <iostream>
#include <ctime>
#include <cstring>
#include <string>
#include <fstream>
#include <process.h>
#include "../../vsgl2.h"

using namespace std;
using namespace vsgl2;
using namespace vsgl2::general;
using namespace vsgl2::video;
using namespace vsgl2::utils;
using namespace vsgl2::io;
using namespace vsgl2::audio;
using namespace vsgl2::ttf_fonts;

const int DIM = 100; //title dimension
const int DIM2 = 40; //subtitle dimension
const int x_select_player = 95; //'select players' x
const int y_select_player = 320; //'select players' y
const int select_player_width = 207; //'select players' width
int click = 0; //'select players' clicks stop
int click2 = 0; //'select difficulty' clicks stop
int red = 0;
int green = 0;
int error = 6;
string parole[120000];
int state_game;
    /**
    * 0 = home
    * 1 = 1 player selected
    * 2 = 2 player selected
    * 3 = select difficulty
    * 4 = game
    * 5 = YOU WON / YOU LOST
    */
void home() //home page graphics
{
    draw_image("images/sfondo_lavagna.jpg", 0, 0, get_window_width(), get_window_height());
    draw_text("vt323.ttf", DIM, "HANGMAN GAME", 85, 190, Color(255, 255, 255, 255));
    draw_text("vt323.ttf", DIM2, "1 PLAYER GAME", x_select_player, y_select_player, Color(255, 255, 255, 255));
    draw_text("vt323.ttf", DIM2, "2 PLAYER GAME", x_select_player + 240, y_select_player, Color(255, 255, 255, 255));
    draw_image("images/hangman00.png", 265, 353, 119, 299, 255);
}

int chosen_player_select(int x, int y) //choose 1 or 2 players
{
    if (x > x_select_player && x < x_select_player + select_player_width &&
        y > y_select_player && y < y_select_player + DIM2)
        return 1;
    if (x > x_select_player + 240 && x < x_select_player + 240 + select_player_width &&
        y > y_select_player && y < y_select_player + DIM2)
        return 2;
}

void click_check(int x, int y)
{
    if ((x > x_select_player && x < x_select_player + select_player_width &&
        y > y_select_player && y < y_select_player + DIM2) ||
        (x > x_select_player + 240 && x < x_select_player + 240 + select_player_width &&
        y > y_select_player && y < y_select_player + DIM2))
        click++;
}

void select_difficulty() //difficulty select page graphics
{
    draw_image("images/sfondo_lavagna.jpg", 0, 0, get_window_width(), get_window_height());
    draw_text("vt323.ttf", DIM - 20, "SELECT DIFFICULTY", 50, 150, Color(255, 255, 255, 255));
    draw_text("vt323.ttf", DIM2, "EASY", x_select_player + 55, y_select_player - 50, Color(255, 255, 255, 255));
    draw_text("vt323.ttf", DIM2, "MEDIUM", x_select_player +175, y_select_player - 50, Color(255, 255, 255, 255));
    draw_text("vt323.ttf", DIM2, "INSANE", x_select_player + 325, y_select_player - 50, Color(255, 255, 255, 255));
    draw_image("images/hangman00.png", 265, 353, 119, 299);
}

int chosen_difficulty(int x, int y) //choose difficulty
{
    if (x > x_select_player + 55 && x < x_select_player + 55 + select_player_width - 142 &&
        y > y_select_player - 50 && y < y_select_player - 50 + DIM2)
        return 1;
    if (x > x_select_player + 175 && x < x_select_player + 175 + select_player_width - 110 &&
        y > y_select_player - 50 && y < y_select_player - 50 + DIM2)
        return 2;
    if (x > x_select_player + 325 && x < x_select_player + 325 + select_player_width - 110 &&
        y > y_select_player - 50 && y < y_select_player - 50 + DIM2)
        return 3;
}

void click_check_2(int x, int y)
{
    if ((x > x_select_player + 55 && x < x_select_player + 55 + select_player_width - 142 &&
        y > y_select_player - 50 && y < y_select_player - 50 + DIM2) ||
        (x > x_select_player + 175 && x < x_select_player + 175 + select_player_width - 110 &&
        y > y_select_player - 50 && y < y_select_player - 50 + DIM2) ||
        (x > x_select_player + 325 && x < x_select_player + 325 + select_player_width - 110 &&
        y > y_select_player - 50 && y < y_select_player - 50 + DIM2))
        click2++;
}

bool right_word(const string &s)
{
    for (int i = 0; i < s.size(); i++)
        if (s.at(i) < 'a' || s.at(i) > 'z')
            return false;
    return true;
}

int upload_words(string filename, string words[])
{
    ifstream in(filename);
    int word_number = 0;
    string temp;
    while (in >> temp)
    {
        if (right_word(temp))
        {
            words[word_number] = temp;
            word_number++;
        }
    }
    return word_number;
}

void enter_word_graphics () //enter word page graphics
{
    draw_filled_rect(0, 0, get_window_width(), get_window_height(), Color(255, 255, 255, 255));
    draw_text("vt323.ttf", DIM, "ENTER THE WORD", 35, 150, Color(0, 0, 0, 255));
    draw_text("vt323.ttf", DIM2 - 10, "KEEP CAPS LOCK DISABLED", 170, 600, Color(255, 0, 0, 255));
    draw_rect(get_window_width()/4 - 5, 300, get_window_width()/2, DIM2, Color(0, 0, 0, 255));
}

string enter_word () //write the word
{
    string entered_word = read_text("vt323.ttf", DIM2, get_window_width()/4, 300, Color(0, 0, 0, 255), 18);
    return entered_word;
}

 void draw_hangman (int error)
 {
    if (error == 6){
        draw_image("images/h1.png", 0, 180, 400, 400, 255);
        //cout << "6" << endl;
    }
    if (error == 5){
        draw_image("images/h2.png", 0, 180, 400, 400, 255);
        //cout << "5" << endl;
    }
    if (error == 4){
        draw_image("images/h3.png", 0, 180, 400, 400, 255);
        //cout << "4" << endl;
    }
    if (error == 3){
        draw_image("images/h4.png", 0, 180, 400, 400, 255);
        //cout << "3" << endl;
    }
    if (error == 2){
        draw_image("images/h5.png", 0, 180, 400, 400, 255);
        //cout << "2" << endl;
    }
    if (error == 1){
        draw_image("images/h6.png", 0, 180, 400, 400, 255);
        //cout << "1" << endl;
    }
    if (error == 0){
        draw_image("images/h7.png", 0, 180, 400, 400, 255);
        //cout << "0" << endl;
        draw_text("vt323.ttf", DIM2, "PRESS ENTER TO CONTINUE", 130, 130, Color(38, 204, 27, 255));
    }
 }

void game (string word, string guess)
{
    draw_filled_rect(0, 0, get_window_width(), get_window_height(), Color(255, 255, 255, 255));
    draw_text("vt323.ttf", DIM2 - 10, "KEEP CAPS LOCK DISABLED", 170, 600, Color(255, 0, 0, 255));
    draw_text("vt323.ttf", DIM - 10, guess, 0, 40, Color(0, 0, 0, 255));
    update();
}

void game_over (string word)
{
    draw_filled_rect(0, 0, get_window_width(), get_window_height(), Color(255, 255, 255, 255));
    for (int i = 0; i < 35; i++){
        if (error == -1){
            draw_text("vt323.ttf", DIM, "YOU LOST", 160, 250, Color(0, 0, 0, i));
            draw_text("vt323.ttf", DIM2, "The right word was... " , 150, 450, Color(0, 0, 0, i));
            draw_text("vt323.ttf", DIM2, word , (get_window_width()/2)-((word.size()/2)*DIM2/2), 500, Color(0, 0, 0, i));
        }
        else
            draw_text("vt323.ttf", DIM, "YOU WON", 180, 250, Color(0, 0, 0, i));
        update();
        delay(150);
    }
}

int main(int argc, char* argv[])
{
    init(); //init the library
    set_window(650,650,"Vsgl2 Hangman"); //create the window and show it
    int your_choice = 0; //your choice between 1 or 2 players
    int your_choice2 = 0; //your choice between EASY, MEDIUM or INSANE
    string letter; //selected letter
    state_game = 0;
    string word; //hidden word
    string guess;
    srand(time(NULL));
    while (!done()){
            while (state_game == 0){
                home();
                update();
                if(mouse_left_button_pressed()){
                    click_check(get_mouse_x(), get_mouse_y());
                    your_choice = chosen_player_select(get_mouse_x(), get_mouse_y());
                    if (click == 1){
                        if(your_choice == 1){ //1 player
                            //cout << "1 player " << endl;
                            state_game = 1;
                        }
                        if(your_choice == 2){ //2 player
                            //cout << "2 player " << endl;
                            state_game = 2;
                        }
                    }
                }
            }
            if (state_game == 1){
                state_game = 3;
                int num_parole = upload_words("italian.txt", parole);
                while (state_game == 3){
                    select_difficulty();
                    update();
                    if (mouse_left_button_pressed()){
                        click_check_2(get_mouse_x(), get_mouse_y());
                        your_choice2 = chosen_difficulty(get_mouse_x(), get_mouse_y());
                        if (click2 == 1){
                            if(your_choice2 == 1){ //EASY
                                //cout << "EASY " << endl;
                                word = parole[(rand()*0xFFFF + rand()) % num_parole];
                                while (word.size() > 5)
                                    word = parole[(rand()*0xFFFF + rand()) % num_parole];
                                    //cout << word << endl;
                            }
                            if(your_choice2 == 2){ //MEDIUM
                                //cout << "MEDIUM " << endl;
                                word = parole[(rand()*0xFFFF + rand()) % num_parole];
                                while (word.size() <= 5 && word.size() > 12)
                                    word = parole[(rand()*0xFFFF + rand()) % num_parole];
                                    //cout << word << endl;
                            }
                            if(your_choice2 == 3){ //INSANE
                                //cout << "INSANE " << endl;
                                word = parole[(rand()*0xFFFF + rand()) % num_parole];
                                while (word.size() <= 12)
                                    word = parole[(rand()*0xFFFF + rand()) % num_parole];
                                    //cout << word << endl;
                            }
                            state_game = 4;
                        }
                    }
                }
            }
            if (state_game == 2){
                enter_word_graphics();
                update();
                word = enter_word();
                //cout << word << endl;
                state_game = 4;
            }
            guess = "";
            int win_counter = 0;
            error = 6;
            for (int i= 0; i < word.size(); i++)
                guess += '_';
            draw_filled_rect(0, 0, get_window_width(), get_window_height(), Color(255, 255, 255, 255));
            update();
            while (state_game == 4){
                win_counter = 0;
                game(word, guess);
                draw_hangman(error);
                update();
                letter = read_text("vt323.ttf", DIM2 + 30, 550, 200, Color(0, 0, 0, 255), 1);
                int lose_counter = 0;
                for (int i = 0; i < word.size(); i++){
                    if (letter[0] == word[i]){
                        guess[i] = letter[0];
                        lose_counter++;
                    }
                }
                for (int i = 0; i < word.size(); i++){
                    if (guess[i] == word[i])
                        win_counter++;
                }
                //cout << "win_counter = " << win_counter << endl;
                if (lose_counter == 0)
                    error--;
                update();
                if (error == -1 || win_counter == word.size()){
                    state_game = 5;
                }
            }
            if (state_game == 5)
                game_over(word);
        draw_text("vt323.ttf", DIM2 - 10, "Do you want to play again?", 170, 550, Color(255, 0, 0, 255));
        draw_text("vt323.ttf", DIM2 - 10, "[ y ] - [ n ]", 240, 600, Color(0, 0, 0, 255));
        update();
        string play_again;
        play_again = read_text("vt323.ttf", DIM2 - 10, 700, 700, Color(0, 0, 0, 255), 1);
        if (play_again == "y"){
            state_game = your_choice;
            your_choice2 = 0;
            click2 = 0;
        }
        if (play_again == "n"){
            close();
            return 0;
        }
    }
    close();
    return 0;
}

