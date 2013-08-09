// pipe_app.cpp
// models a water supply system
//#include <pipes.h> //pipes header file

#include"pipes.cpp"

int main()
{
	char ch = 'a';
	Source src(100); //source(maximum capacity)
	Pipe pipe1(80); //pipe(resistance)
	Valve valve1(on); //valve(initially on)
	Tank tank1(60); //tank1(maximum outflow)
	Switch switch1(&tank1, 300); //tank1 high switch
	Switch switch2(&tank1, 50); //tank1 low switch
	Pipe pipe2(80); //pipe
	Sink sink1(30); //sink(maximum capacity)
	Pipe pipe3(40); //pipe
	Valve valve2(on); //valve
	Tank tank2(80); //tank2
	Switch switch3(&tank2, 250); //tank2 high switch
	Switch switch4(&tank2, 50); //tank2 low switch
	Sink sink2(20); //sink
	//cout << "Press Enter for new time tick, 'x' to exit\n";

	int sno = 1;
	
	cout<<"\"SNo.\"\t\"Src\"\t\"P1\"\t\"V1\"\t\"T1\"\t\"P2\"\t\"Snk1\"\t\"P3\"\t\"V2\"\t\"T2\"\t\"Snk2\"\n";

	//while(ch != 'x') //quit on 'x' key
	for(int l=0; l<500; l++)
	{ 
		//make connections

		src >= pipe1; // source flows into pipe1
		pipe1 >= valve1; // pipe1 flows into valve1
		valve1 >= tank1; // valve1 flows into tank1
		Tee(tank1, pipe2, pipe3); // output of tank1 splits
		pipe2 >= sink1; // pipe2 flows into sink1
		pipe3 >= valve2; // pipe3 flows into valve2
		valve2 >= tank2; // valve2 flows into tank2
		tank2 >= sink2; // tank2 flows into sink2
		src.Tick(); //update all components
		pipe1.Tick(); // and switches
		valve1.Tick();
		tank1.Tick();
		switch1.Tick();
		switch2.Tick();
		pipe2.Tick();
		sink1.Tick();
		pipe3.Tick();
		valve2.Tick();
		tank2.Tick();
		switch3.Tick();
		switch4.Tick();
		sink2.Tick();

		//if tank1 gets too high
	
		if( valve1.Status()==on && switch1.Status()==on )
			valve1.Status() = off;
		
		//if tank1 gets too low

		if( valve1.Status()==off && switch2.Status()==off )
			valve1.Status() = on;

		//if tank2 gets too high

		if( valve2.Status()==on && switch3.Status()==on )
			valve2.Status() = off;
		
		//if tank2 gets too low

		if( valve2.Status()==off && switch4.Status()==off )
			valve2.Status() = on;
		
		//output

		//cout<<"\"Src\"\t\"P1\"\t\"V1\"\t\"T1\"\t\"P2\"\t\"Snk1\"\t\"P3\"\t\"V2\"\t\"T2\"\t\"Snk2\"\n";
		cout<<" "<<sno;
		cout <<"\t"<< setw(2) << src.Flow();   //Src
		cout << "\t" << setw(2) << pipe1.Flow();  //P1
	
		if( valve1.Status()==off )
			cout << "\t\"off\"";  //V1
		else
			cout << "\t\"on\"";  //V1
		cout << "\t" << setw(3) << tank1.Contents();  //T1
		cout << "\t" << setw(2) << pipe2.Flow();  //P2
		cout << "\t" << setw(2) << sink1.Flow();  //Snk1
		cout << "\t" << setw(2) << pipe3.Flow();  //P3

		if( valve2.Status()==off )
			cout << "\t\"off\"";  //V2
		else
			cout << "\t\"on\"";  //V2
		cout << "\t" << setw(3) << tank2.Contents();  //T2
		cout << "\t" << setw(2) << sink2.Flow();  //Snk2
		//ch = cin.get();
		sno++;
		cout << "\n";
	} //end while

	return 0;

} //end main()
