//Here's the listing for the PIPES.CPP file, which contains the definitions of the class member functions. Like
//PIPES.H, it's supplied by the class vendor.
// pipes.cpp
// function definitions for pipes

#include "pipes.h" //class declarations

//--------------------------------------------------------------
//'flows into' operator: c1 >= c2

void operator >= (Component& c1, Component& c2)
{
	c2.inpress = c1.outpress;
	c1.inbackp = c2.outbackp;
	c2.inflow = c1.outflow;
}

//--------------------------------------------------------------
//'tee' divides flow into two

void Tee(Component& src, Component& c1, Component& c2)
{
	//avoid division by 0
	if( (c1.outbackp==0 && c2.outbackp==0) || (c1.outbackp==0 && c2.outbackp==0) )
	{
		c1.inpress = c2.inpress = 0;
		src.inbackp = 0;
		c1.inflow = c2.inflow = 0;
		return;
	} 

	//proportion for each output
	float f1 = (float)c1.outbackp / (c1.outbackp + 	c2.outbackp);
	float f2 = (float)c2.outbackp / (c1.outbackp + c2.outbackp);

	//pressures for two outputs
	c1.inpress = src.outpress * f1;
	c2.inpress = src.outpress * f2;

	//back pressure for single input
	src.inbackp = c1.outbackp + c2.outbackp;

	//flow for two outputs
	c1.inflow = src.outflow * f1;
	c2.inflow = src.outflow * f2;
}

//--------------------------------------------------------------

void Source::Tick() //update source
{ 
	//output pressure fixed
	outbackp = inbackp;
	outflow = (outpress < outbackp) ? outpress : outbackp;
	inflow = outflow;
}

//--------------------------------------------------------------

void Sink::Tick() //update sink
{ 
	//output back pressure fixed
	outpress = inpress;
	outflow = (outbackp < outpress) ? outbackp : outpress;
	inflow = outflow;
}

//--------------------------------------------------------------

void Pipe::Tick(void) //update pipes
{
	outpress = (inpress < resist) ? inpress : resist;
	outbackp = (inbackp < resist) ? inbackp : resist;

	//outflow is the lesser of outpress, outbackp, and resist
	if(outpress < outbackp && outpress < resist)
		outflow = outpress;
	else if(outbackp < outpress && outbackp < resist)
		outflow = outbackp;
	else
		outflow = resist;
}

//--------------------------------------------------------------

void Valve::Tick(void) //update valves
{
	if(status==on) //if valve open
	{
		outpress = inpress;
		outbackp = inbackp;
		outflow = (outpress < outbackp) ? outpress : outbackp;
	}
	else //if valve closed
	{
		outpress = 0;
		outbackp = 0;
		outflow = 0;
	}
}

//--------------------------------------------------------------

void Tank::Tick(void) //update tanks
{
	outbackp = infinity; //will take all the flow

	// you can give it
	if( contents > 0 ) //if not empty
	{
		outpress = (maxoutpress<inbackp) ? maxoutpress : inbackp;
		outflow = outpress;
	}
	else //if empty
	{
		outpress = 0; //no out pressure,
		outflow = 0; //no flow
	}
	contents += inflow - outflow; //always true
}
