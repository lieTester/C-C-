
//Ques1: Snake and ladder game.

#include <iostream>
#include <utility>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
using namespace std;

// global variables of game

fstream newfile;
string message;
int countLS,rolldice=1,p1Position=1,p2Position=1,diceValue=0;//position=1
int lineWork[]={3,7,11,15,19,23,27,31,35,39};
int inlinePos[]={13,25,37,49,61,73,85,97,109,121};
pair<int, int> ladders[]={
                        make_pair(3,38),make_pair(4,14),make_pair(9,31),make_pair(21,42),
                        make_pair(28,84),make_pair(51,67),make_pair(72,91),make_pair(80,99)
                        };
pair<int, int> snakes[]={
                        make_pair(17,7),make_pair(62,18),make_pair(54,34),make_pair(87,36),
                        make_pair(64,60),make_pair(93,73),make_pair(95,75),make_pair(98,79)
                        };



// functions used in game
void layoutLadderSnake(pair<pair<int,int>, string> &, pair<pair<int,int>, string> &);
int accurateVal( int, int);
int ladderOrSnake( int &, int );
int diceRoll( int,int);

int main(){

    pair<pair<int,int>, string> p1 = make_pair(make_pair(39,13), "P1");
    pair<pair<int,int>, string> p2 = make_pair(make_pair(39,13), "P2");
    
    while(1){
        layoutLadderSnake(p1,p2);
    }
    // cout << p1.first.first<<"\t"<< p1.first.second<<"\n";
    // cout << p2.first.first<<"\t"<< p2.first.second<<"\n";
    // cout << message<<"\t"<<"\n";
    
    
    return 0;
}

int accurateVal(int layerToptoBotm,int posInLine){

    for (int i = sizeof(lineWork)/sizeof(lineWork[0])-1; i >=0 ; i--)
    {
        if (lineWork[i] == layerToptoBotm && (i%2==0) && posInLine > inlinePos[9])
        {
            // why we are doing this is because of maxmin may be from 0 or 9th index in linework
            posInLine -= inlinePos[9];
            posInLine = inlinePos[9] - posInLine+12;
            break;
        }
        else if (lineWork[i] == layerToptoBotm && (i%2!=0) && posInLine < inlinePos[0]){
            posInLine *= -1;
            posInLine += inlinePos[0]+1;
        }
    }
    // cout <<posInLine<<"\t";
    return posInLine;
}

int ladderOrSnake(int &layerToptoBotm,int posInLine,int &position){

    int oddeven = 0;
    countLS = 0;
    countLS = lineWork[9] - layerToptoBotm;//check in which line
    countLS /= 4;//to get value to minus from line position index
    oddeven = ++countLS;
    countLS = oddeven%2 == 0 ? ((inlinePos[9]-posInLine)/12+((10*(countLS-1)+1))):((10*countLS)-(inlinePos[9]-posInLine)/12);//it give the value which match with either of snake head or ladder tail
    // cout << countLS<<"\t";
    if (countLS <= 100)
    {
        position = countLS;
        if (position == 100)
        {
            // system("clear");
            cout << "\t\t\t\t\t     #################################################################\n";
            cout << "\t\t\t\t\t     #################################################################\n";
            if (p2Position == 100)
            {
                cout <<"\t\t\t\t\t     ################# Congrats Player2 you won game #################\n" ;
                cout <<"\t\t\t\t\t     ################# Your Last dice value was "<<diceValue<<" ####################\n" ;
            }else{
                cout <<"\t\t\t\t\t     ################# Congrats Player1 you won game #################\n" ;
                cout <<"\t\t\t\t\t     ################# Your Last dice value was "<<diceValue<<" ####################\n" ;
            }
            cout << "\t\t\t\t\t     #################################################################\n";
            cout << "\t\t\t\t\t     #################################################################\n";
            exit(0);
        }
    }
    else{
        layerToptoBotm += 4;
    }
    // below we are checking that countls value in snake or ladder pair
    for (int i = 0; i < sizeof(snakes)/sizeof(snakes[0])-1; i++)
    {
        if (snakes[i].first == countLS)
        {
            position = snakes[i].second;
            layerToptoBotm = snakes[i].second /10 ;
            posInLine = snakes[i].second % 10;
            posInLine = (layerToptoBotm+1) % 2 == 0 ? 10-posInLine : posInLine-1;
            // cout << posInLine<<"\t"<<layerToptoBotm<<"\t";
            // posInLine = (13 + (12 * posInLine));
            posInLine = inlinePos[posInLine];
            layerToptoBotm = lineWork[9 - layerToptoBotm];
            // cout<<"Bite by a snake your position is deacrease";        
            message = "Bite by a snake your position is deacrease";
            break;
        }
        else if(ladders[i].first == countLS)
        {
            position = ladders[i].second;
            layerToptoBotm = ladders[i].second /10 ;
            posInLine = ladders[i].second % 10;
            posInLine = (layerToptoBotm+1) % 2 == 0 ? 10-posInLine : posInLine-1;
            // cout << posInLine<<"\t"<<layerToptoBotm<<"\t";
            // posInLine = (13 + (12 * posInLine));
            posInLine = inlinePos[posInLine];
            layerToptoBotm = lineWork[9 - layerToptoBotm];
            // cout<<"You get ladder and your position is increase";
            message = "You get ladder and your position is increase";
            break;
        }
        else
            message = "";
        
    }

    return posInLine;
}

int diceRoll(int layerToptoBotm,int posInLine){
    srand(time(0));   // Initialize random number generator.
    int val=(rand() % 10);
    val = val > 6 ? val - 6 : val;
    if (val == 0)
    {
        val = 1;
    }
    diceValue = val;
    countLS = 0;
    countLS = lineWork[9] - layerToptoBotm;//check in which line
    countLS /= 4;//to get value to minus from line position index
    ++countLS;
    // cout << "Values role dise  " << lineWork[9] - layerToptoBotm <<"\t"<<(countLS%2 == 0) <<"\t"<< val<<"\n";
    if(countLS == 0)
    {
        posInLine += val*12;
        return posInLine;
    }
    else if (countLS%2 == 0){
        posInLine -= val*12;
    }else if (countLS%2 != 0)
        posInLine += val*12;

    return posInLine;
}
void layoutLadderSnake( pair<pair<int,int>, string>& user1, pair<pair<int,int>, string>& user2){

    int option = 0,acurateline[2]={0};

    newfile.open("snakeAndLadder.txt",ios::in); 
    if (newfile.is_open()){   
        string tp;
        int count = 0,x=0;
        while(getline(newfile, tp)){ 

            if (count==user1.first.first || count==user2.first.first)
            {   
                for (int i = 0, exp=0; i < tp.length(); i++)
                {
                    if ((i==user1.first.second && count==user1.first.first) || (i==user2.first.second && count==user2.first.first))
                    {
                        if (i==user1.first.second && i==user2.first.second && user1.first.first == user2.first.first)
                        {
                            cout <<user1.second <<user2.second;
                            i += 3;
                            continue;
                        }
                        else if (i==user1.first.second && count==user1.first.first)
                        {
                            cout << user1.second;
                        }
                        else if (i==user2.first.second && count==user2.first.first)
                        {
                            cout << user2.second;
                        }
                        
                        i++;
                        continue;
                    }
                    cout << tp[i];
                }
                cout << "\n";
            }
            else
                cout <<tp<<"\n"; 
            
            count++;
        }
        newfile.close(); 
    }

//     cout << user1.first.first<<"\t"<< user1.first.second<<"\n";
//     cout << user2.first.first<<"\t"<< user2.first.second<<"\n";
    cout <<"\t\t\t\t\t     " <<message<<(!message.empty()?((rolldice==1)?" P2":" P1"):"")<<"\n";
    cout <<"\t\t\t\t\t\t     Player1 => "<<p1Position<<"  Player2 => "<<p2Position<<"\n";
    cout <<"\t\t\t\t\t\t        Last Dice value => "<<diceValue<<"\n";
    cout <<"\t\t\t\t\t     Enter option 1 to exit and 2 to continue : ";
    cin >> option;
    if (option == 1)
    {
        exit(0);
    }
    system("clear");
    if (rolldice==1)
    {
        rolldice=2;
        user1.first.second = diceRoll(user1.first.first,user1.first.second);
        if (user1.first.second > inlinePos[9] || user1.first.second < inlinePos[0]  )
            user1.first.first-=4;
        user1.first.second = accurateVal(user1.first.first,user1.first.second);
        user1.first.second=ladderOrSnake(user1.first.first,user1.first.second,p1Position);
    }else if (rolldice==2)
    {
        rolldice=1;
        user2.first.second = diceRoll(user2.first.first,user2.first.second);
        if (user2.first.second > inlinePos[9] || user2.first.second < inlinePos[0]  )
            user2.first.first-=4;
        user2.first.second = accurateVal(user2.first.first,user2.first.second);
        user2.first.second=ladderOrSnake(user2.first.first,user2.first.second,p2Position);
    }

}
