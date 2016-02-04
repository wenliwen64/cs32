#include <iostream>
#include <string>
using namespace std;

//Your declarations and implementations would go here
class Landmark{
    public:
       Landmark(const string& nm): m_name(nm) {}
       virtual ~Landmark() {} 
       inline virtual string name() const { return m_name; }
       virtual string color() const=0;
       virtual string icon() const=0;
    private:// Can we have interface class without constructor? Yes we can but the compiler synthesized one will be taking no parameters.
       string m_name;
};

class Hotel: public Landmark{
    public:
	Hotel(const string& nm): Landmark(nm){}
	inline virtual ~Hotel(){ cout << "Destroying the hotel " << this->name() << "." << endl; }
	inline virtual string color() const {return "yellow";}
	inline virtual string icon() const {return "bed";}
};


class Restaurant: public Landmark{
    public:
	Restaurant(const string& nm, const int& cap): Landmark(nm), m_cap(cap){}
	inline  virtual ~Restaurant(){ cout << "Destroying the restaurant " << this->name() << "." << endl; }
	virtual string color() const { return "yellow"; }
	inline virtual string icon() const {
	    if(m_cap >= 40) return "big knife/fork";
	    else if(m_cap < 40 && m_cap >0) return "small knife/fork";
	    else return "bad";
	}
    private:
	int m_cap;
};

class Hospital: public Landmark{
    public:
	Hospital(const string& nm): Landmark(nm){}
	inline virtual ~Hospital(){ cout << "Destroying the hospital " << this->name() << "." << endl; }
	inline virtual string color() const { return "blue"; }
	inline virtual string icon() const { return "H";}
};

void display(const Landmark* lm)
{
    cout << "Display a " << lm->color() << " " << lm->icon() << " icon for "
	<< lm->name() << "." << endl;
}

int main()
{
    Landmark* landmarks[4];
    landmarks[0] = new Hotel("Westwood Rest Good");
    // Restaurants have a name and seating capacity.  Restaurants with a
    // capacity under 40 have a small knife/fork icon; those with a capacity
    // 40 or over have a large knife/fork icon.
    landmarks[1] = new Restaurant("Bruin Bite", 30);
    landmarks[2] = new Restaurant("La Morsure de l'Ours", 100);
    landmarks[3] = new Hospital("UCLA Medical Center");

    cout << "Here are the landmarks." << endl;
    for (int k = 0; k < 4; k++)
	display(landmarks[k]);
    // Clean up the landmarks before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
	delete landmarks[k];
}
