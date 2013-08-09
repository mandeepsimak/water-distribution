// pipes.h
// header file for pipes

#include <iostream> //for cout, etc.
#include <iomanip> //for setw
//#include <conio.h> //for getch()

using namespace std;

const int infinity = 32767; //infinite back pressure

enum offon { off, on }; //status of valves and switches

class Tank; //for using Tank in Switch

////////////////////////////////////////////////////////////////

class Component //components (Pipe, Valve, etc.)
{
	protected:
	
	int inpress, outpress; //pressures in and out
	int inbackp, outbackp; //back pressures in and out
	int inflow, outflow; //flow in and out
	
	public:

	Component() : inpress(0), outpress(0), inbackp(0),
	outbackp(0), inflow(0), outflow(0)
	{ }
	
	virtual ~Component() //virtual destructor
	{ }

	int Flow() const
	{ return inflow; }

	friend void operator >= (Component&, Component&);

	friend void Tee(Component&, Component&, Component&);
};

////////////////////////////////////////////////////////////////

class Source : public Component //flow begins here
{
	public:

	Source(int outp)
	{ outpress = inpress = outp; }
	
	void Tick(); //update
};

////////////////////////////////////////////////////////////////

class Sink : public Component //flow ends here
{
	public:

	Sink(const int obp) //initialize backpressure
	{ outbackp = inbackp = obp; }

	void Tick(); //update
};

////////////////////////////////////////////////////////////////

class Pipe : public Component //connects other components,
{ 
	//has resistance to flow
	private:

	int resist;

	public:

	Pipe(const int r) //initialize
	{ inbackp = resist = r; }

	void Tick(); //update
};

////////////////////////////////////////////////////////////////

class Valve : public Component //turns flow on or off
{
	
	private:
			
	offon status; //on (open) or off (closed)
	
	public:

	Valve(const offon s) //initialize status
	{ status = s; }

	offon& Status() //get and set status
	{ return status; }

	void Tick(); //update
};

////////////////////////////////////////////////////////////////

class Tank : public Component //stores water
{
	private:

	int contents; //water in tank (gals)
	int maxoutpress; //max output pressure

	public:
	
	Tank(const int mop) //initialize to empty tank
	{ maxoutpress = mop; contents = 0; }

	int Contents() const //get contents
	{ return(contents); }

	void Tick();
};

////////////////////////////////////////////////////////////////

class Switch //activated by tank level
{ //can operate valves
	private:

	offon status; //'on' if contents > triggercap
	int cap; //capacity where switch turns on
	Tank* tankptr; //pointer to owner tank

	public:

	Switch(Tank *tptr, const int tcap) //initialize
	{ tankptr = tptr; cap = tcap; status = off; }

	int Status() const //get status
	{ return(status); }
	
	void Tick() //update status
	{ status = (tankptr->Contents() > cap) ? on : off; }
};
