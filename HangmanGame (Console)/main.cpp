#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <cstring>

using namespace std;

const int MAX = 300;

void disegna_hangman( int conta )
{

        if(conta==1)
       cout <<" +---+\n"
            <<" |   |\n"
            <<"     |\n"
            <<"     |\n"
            <<"     |\n"
            <<"     |\n"
            <<"=========";

        if(conta==2)
       cout <<" +---+\n"
            <<" |   |\n"
            <<" O   |\n"
            <<"     |\n"
            <<"     |\n"
            <<"     |\n"
            <<"=========";

        if(conta==3)
        cout <<" +---+\n"
             <<" |   |\n"
             <<" O   |\n"
             <<" |   |\n"
             <<"     |\n"
             <<"     |\n"
             <<"=========";

        if(conta==4)
        cout <<" +---+\n"
             <<" |   |\n"
             <<" O   |\n"
             <<"/|   |\n"
             <<"     |\n"
             <<"     |\n"
             <<"=========";

        if(conta==5)
        cout <<" +---+\n"
             <<" |   |\n"
             <<" O   |\n"
             <<"/|¶  |\n"
             <<"     |\n"
             <<"     |\n"
             <<"=========";

        if(conta==6)
        cout <<" +---+\n"
             <<" |   |\n"
             <<" O   |\n"
             <<"/|¶  |\n"
             <<"/    |\n"
             <<"     |\n"
             <<"=========";
        if(conta==7)
        cout <<" +---+\n"
             <<" |   |\n"
             <<" O   |\n"
             <<"/|¶  |\n"
             <<"/ ¶  |\n"
             <<"     |\n"
             <<"=========";

    cout << endl;

}

int controlla_situazione(char s[], int r, int DIM, char found[], int moves)
{
    int k = 0;
    cout << "-----------------------------------------" << endl;

    for(int i=0; i<DIM; i++)
        if(s[i] == r)
          found[i] = s[i];
        else
            k++;

    if(k == DIM)
        cout << "wrong" << endl;

        cout << "PHRASE: ";
    for(int i=0; i<DIM; i++)
        if(s[i] == found[i])
            cout << found[i] << " ";
        else
            cout << "_ ";

    cout << endl;
    if(k == DIM)
    {
        moves++;
        disegna_hangman(moves);
        return moves;
    }
    else
    return moves;

}

int main()
{
    char s[MAX], r;
    int DIM = 0;
    int moves=0, win=0;
    char found[DIM],guess[26];

    cout << "*** HANGMAN GAME ***" << endl << endl;
    cout << "INSERT HIDDEN WORD..." << endl;
    cin >> s;

    DIM = strlen(s);

    cout << "WORD: ";

    for(int i=0; i<DIM; i++)
        cout << "_ ";
        cout << endl;

    int i=0;

    while ( moves <= 6)
    {

        win = 0;
        cout << "GUESS: ";
        cin >> r;
        guess[i] = r;
        for(int j=0; j<i; j++)
        {
            if(r == guess[j])
            {
                cout << " already guesd" << endl;
                cin >> r;
            }
        }
        moves = controlla_situazione(s, r, DIM, found, moves);
        for(int i=0; i<DIM; i++)
            if(s[i] == found[i])
                win++;
        if (win == DIM)
            moves = 7;
        i++;
    }

    if(win == DIM)
        cout << " YOU WIN" <<  endl;
    else
    {
        cout << "\t\t\t  X!! YOU DIE !!X " << endl;
        cout << "\t\t\t  X!! GAME OVER !!X " << endl;
        cout << endl << endl;

    }
     return 0;
}
