#include <iostream>
#include <vector>
#include <stdint.h>
#include <string>

using namespace std;

class Card{
    public:
        uint16_t mNr_carte;
        string mstema;
    public:
        Card(){
            mNr_carte=0;
            mstema="";
        }
        Card(uint16_t nr_carte,string stema){
            mNr_carte=nr_carte;
            mstema=stema;
        }
        Card(const Card&other){
            this->mNr_carte=other.mNr_carte;
            this->mstema=other.mstema;
        }
        bool operator==(const Card&other)const{
            if(mNr_carte!=other.mNr_carte)return 0;
            else if(mstema!=other.mstema)return 0;
            return 1;
        }
        uint16_t getNr_carte(){
            return mNr_carte;
        }
        string getStema(){
            return mstema;
        }
        void setNr_carte(uint8_t nr_carte){
            mNr_carte=nr_carte;
        }
        void setStema(string stema){
            mstema=stema;
        }
};

class Deck{
    private:
        string mtype;
    public:
        vector<Card> mCards;
        Deck(){
            mtype="";
            mCards.clear();
        }
        int getSize(){
            return mCards.size();
        }
        void addCard(const Card&card){
            mCards.push_back(card);
        }
        void tipPachet(){
            for(int i=0;i<mCards.size();i++){
                if((mCards[i].mNr_carte<2||mCards[i].mNr_carte>14)||(mCards[i].mstema!="rosu"&&mCards[i].mstema!="negru"&&mCards[i].mstema!="romb"&&mCards[i].mstema!="trefla")){
                    mtype="Pachet masluit";
                    break;
                }
            }
            if(mtype!="Pachet masluit"){
                if(mCards.size()==52)
                    mtype="Pachet OK";
                else mtype="Pregatit pentru Blackjack";
            }
            cout<<mtype<<endl;
        }
        void shuffle_cards(int&a1,int&c1,int&x1,int&a2,int&c2,int&x2){
            Card card;
            x1=(a1*x1+c1)%mCards.size();
            x2=(a2*x2+c2)%mCards.size();
            card=mCards[x1];
            mCards[x1]=mCards[x2];
            mCards[x2]=card;
        }
        void fullPack(){
            vector<string>culori;
            culori.push_back("rosu");
            culori.push_back("negru");
            culori.push_back("romb");
            culori.push_back("trefla");
            for(int j=0;j<4;j++){
                for(int i=2;i<11;i++){
                    Card card(i,culori[j]);
                    mCards.push_back(card);
                }
                for(int i=12;i<15;i++){
                    Card card(i,culori[j]);
                    mCards.push_back(card);
                }
            }
        }
};

class Player{
    private:
        string mName;
        int mhandValue;
        float mMoney;
    public:
        vector<Card>mHand;
        Player(){
            mName="";
            mMoney=0;
            mhandValue=0;
        }
        Player(string name,float money){
            mName=name;
            mMoney=money;
            mHand.clear();
            mhandValue=0;
        }
        string getName(){
            return mName;
        }
        float getMoney(){
            return mMoney;
        }
        void setName(string name){
            mName=name;
        }
        void drawCard(const Card&card){
            mHand.push_back(card);
            if(card.mNr_carte>10)
                mhandValue+=10;
            else mhandValue+=card.mNr_carte;
        }
        int gethandValue(){
            return mhandValue;
        }
        void castig(){
            mMoney=mMoney+10;
        }
        void pierdere(){
            mMoney=mMoney-10;
        }
        void discardCards(){
            mHand.clear();
            mhandValue=0;
        }
        bool verificarePortofel(){
            if(mMoney<10)return 0;
            return 1;
        }

};

int main(){
    string comanda,stema,nume;
    int a1,c1,x1,a2,x2,c2,nr_jucatori,indice;
    char buffer[30];
    float bani;
    uint16_t nr_carte;
    Deck deck;
    vector<Player>players;
    cin>>comanda;
    if(comanda=="shuffle_cards"){
        cin>>a1>>c1>>x1>>a2>>c2>>x2;
        while(scanf("%hu,%s",&nr_carte,buffer)!=EOF){
            stema=buffer;
            Card card(nr_carte,stema);
            deck.addCard(card);
        }
        for(int i=0;i<50;i++)
            deck.shuffle_cards(a1,c1,x1,a2,c2,x2);
        for(int i=0;i<deck.getSize();i++){
            cout<<deck.mCards[i].getNr_carte()<<","<<deck.mCards[i].getStema()<<endl;
        }
    }
    if(comanda=="check_cards"){
        while(scanf("%hu,%s",&nr_carte,buffer)!=EOF){
            stema=buffer;
            Card card(nr_carte,stema);
            deck.addCard(card);
        }
        deck.tipPachet();
    }
    if(comanda=="play_game"){
        deck.fullPack();
        cin>>nr_jucatori;
        for(int i=0;i<nr_jucatori;i++){
            cin>>nume>>bani;
            Player player(nume,bani);
            if(bani>=10)players.push_back(player);
        }
        Player Dealer("Dealer",0);
        while(scanf("%d %d %d %d %d %d\n",&a1,&c1,&x1,&a2,&c2,&x2)!=EOF){
            for(int i=0;i<50;i++)
                deck.shuffle_cards(a1,c1,x1,a2,c2,x2);
            for(int j=0;j<players.size();j++){
                if(!players[j].verificarePortofel()){
                    players.erase(players.begin()+j);
                    j--;
                }
            }
            for(int j=0;j<players.size();j++){
                players[j].drawCard(deck.mCards[j*2]);
                players[j].drawCard(deck.mCards[j*2+1]);
            }
            Dealer.drawCard(deck.mCards[players.size()*2]);
            Dealer.drawCard(deck.mCards[players.size()*2+1]);
            indice=players.size()*2+2;
            for(int j=0;j<players.size();j++){
                while(players[j].gethandValue()<17){
                    players[j].drawCard(deck.mCards[indice]);
                    indice++;
                }
                if(players[j].gethandValue()>21)
                    players[j].pierdere();
            }
            while(Dealer.gethandValue()<17){
                Dealer.drawCard(deck.mCards[indice]);
                indice++;
            }
            if(Dealer.gethandValue()>21){
                for(int i=0;i<players.size();i++){
                    if(players[i].gethandValue()<=21)
                        players[i].castig();
                }
            }
            else{
                for(int i=0;i<players.size();i++){
                    if(players[i].gethandValue()<=21){
                        if(players[i].gethandValue()>Dealer.gethandValue())
                            players[i].castig();
                        else if(players[i].gethandValue()<Dealer.gethandValue())players[i].pierdere();
                    }
                }
            }
            for(int i=0;i<players.size();i++){
                players[i].discardCards();
            }
            Dealer.discardCards();
        }
        for(int i=0;i<players.size();i++){
            cout<<players[i].getName()<<": "<<players[i].getMoney()<<endl;
        }
    }
    return 0;
}
