/**
 * @author Albert Villanueva Kosoy Grup C
*/

#ifndef ARTIST_H
#define ARTIST_H
#include <iostream>

using namespace std;

class Artist{
    private:
        int artistId;
        string name;
        string gender;
        string country;
        string styles;
        int playcount;
    public:
        Artist();
        Artist (int artistId, string &name, string& gender, string& country, string& styles, int placount);
        int getArtistId()const;
        string getName()const;
        string getGender()const;
        string getCountry()const;
        string getStyles()const;
        int getPlaycount()const;

        void setArtistId(int artistId);
        void setName(string name);
        void setGender(string gender);
        void setCountry(string country);
        void setStyles(string styles);
        void setPlaycount(int playcount);
        
        void print();
        string toString()const;
};
/**
 * Constructor sense paràmetres de la classe Artist
*/
Artist::Artist(){}

/**
 * Constructor amb paràmetres de la classe Artist
*/
Artist::Artist (int artistId, string &name, string &gender, string &country, string &styles, int playcount)
        : artistId(artistId), name(name), gender(gender), country(country), styles(styles), playcount(playcount){}


/**
 * Consultors i modificadors
*/
int Artist:: getArtistId()const{
    return artistId;
}
void Artist::setArtistId(int artistId){
    this->artistId = artistId;
}

string Artist::getName()const{
    return name;
}

void Artist::setName(string name){
    this->name = name;
}

string Artist::getGender()const{
    return gender;
}

void Artist::setGender(string gender){
    this->gender = gender;
}

string Artist::getCountry()const{
    return country;
}

void Artist::setCountry(string country){
    this->country = country;
}

string Artist::getStyles()const{
    return styles;
}

void Artist::setStyles(string styles){
    this->styles = styles;
}

int Artist::getPlaycount()const{
    return playcount;
}

void Artist::setPlaycount(int playcount){
    this->playcount = playcount;
}

/**
 * Retorna la informació d'un artista com un string per pantalla
 * @return string info dels artistes
*/
string Artist::toString()const{
            string missatge = getName() + "::" + getGender() + "::" + getCountry() + "::" + getStyles() + "::" + to_string(getPlaycount());
            return missatge;
        }

/**
 * Imprimeix la informació d'un artista per pantalla
*/
void Artist::print(){
    cout << "(Id :: " << artistId << ",  nom :: " << name << ", gènere :: " << gender << ", país :: " << country <<
    ", estil :: " << styles << ", playcount :: " << playcount << ")\n";
}
#endif