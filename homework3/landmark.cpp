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
	    if(m_cap >= 40) return "large knife/fork";
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
