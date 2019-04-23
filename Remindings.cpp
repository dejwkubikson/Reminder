#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdio>
#include <windows.h>
#include <vector>
#include <algorithm>
using namespace std;

int *ActualTime( int ActTime[5] )
{
	time_t tmptime;
	struct tm * date;
	char hour[9];
	char mnthday[6];
				       
	time( & tmptime );
	date = localtime( & tmptime );
	
	strftime( mnthday, 6, "%m-%d", date ); // actual month - day		    
	strftime( hour, 9, "%H:%M:%S", date ); // actual hour:minute:second
	
	short actMNT, actD, actH, actMIN, actS;
		
	for( int i = 0; i < 9; i +=3 )
	{
		short changeSH1 = ( short )hour[i] - 48;  
		short changeSH2 = ( short )hour[i+1] - 48;
			
		if( i == 0 )
			actH = changeSH1 * 10 + changeSH2; // hours
		
		if( i == 3 )
			actMIN = changeSH1 * 10 + changeSH2; // minutes
				
		if( i == 6 )
			actS = changeSH1 * 10 + changeSH2; // seconds
	} // for
				
	for( int i = 0; i < 6; i+=3 )
	{
		short changeSH1 = ( short )mnthday[i] - 48;  
		short changeSH2 = ( short )mnthday[i+1] - 48;
	
		if( i == 0 )
			actMNT = changeSH1 * 10 + changeSH2; // months
		
		if (i == 3 )
			actD = changeSH1 * 10 + changeSH2; // days
	}	
		
	ActTime[0] = actD;
	ActTime[1] = actMNT;
	ActTime[2] = actH;
	ActTime[3] = actMIN;
	ActTime[4] = actS;
	
	return ActTime;
} // function ActualTime

int MonthToDays( int month )
{
	int days = 0;
	
	for( int i=1; i < month; i++ )
	{
		if( i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12 ) 
			days += 31;
		
		if( i == 2 )
			days += 28;
		
		if( i == 4 || i == 6 || i == 9 || i == 11 )
			days += 30;
	}
	
	return days;
	
}// function MonthToDays

bool LeftTime( short SetTime[], char parameter)
{
	short setD = SetTime[0];
	short setMNT = SetTime[1];
	short setH = SetTime[2];
	short setMIN = SetTime[3];
	short setS = SetTime[4];
	
	int ActTime[5];
	
	do
	{
		system("cls");
		short actH, actMIN, actS, actMNT, actD;
				
		ActualTime( ActTime );
				
		actD = ActTime[0];
		actMNT = ActTime[1];
		actH = ActTime[2];
		actMIN = ActTime[3];
		actS = ActTime[4];


		actD += MonthToDays( actMNT );
		setD += MonthToDays( setMNT );
										
		long act = actD * 86400 + actH * 3600 + actMIN * 60 + actS; // actual time to seconds conversion
		long set = setD * 86400 + setH * 3600 + setMIN * 60 + setS; // set time to seconds conversion

		long div1, div2, div3;
		short leftD, leftH, leftM, leftS;
				
		long difference = set - act;


		leftD = difference / 86400; // amount of days
	    div1 = difference % 86400; // reminder from dividing days
	    leftH = div1 / 3600; // amount of hours
	    div2 = div1 % 3600; // reminder from dividing hours
	    leftM = div2 / 60; // amount of minutes
	    div3 = div2 % 60; // reminder from dividing minutes
	    leftS = div3; // amount of seconds
						
		if( parameter == 'P' )
		{		  	
		  	if( actMNT == setMNT && actD == setD )
		  		printf( "Reminder within: %d:%d:%d ", leftH, leftM, leftS );
		  	else	  		
			printf( "Reminder within: %d days and %d:%d:%d hours", leftD, leftH, leftM, leftS );
		}
		
		if( parameter == 'S' )	  	
	  		printf( "Computer will shut down in: %d:%d:%d ", leftH, leftM, leftS );
		
		if( parameter == 'R')
	  		printf( "Computer will restart in: %d:%d:%d ", leftH, leftM, leftS );
		
		if( parameter == 'H' )
	  		printf( "Computer will hibernate in: %d:%d:%d ", leftH, leftM, leftS );
		
		if( leftD == 0 && leftH == 0 && leftM == 0 && leftS == 0 )
			break;
				
		Sleep(1000);
	}while( true );
	
	return false;
	
};// function LeftTime

void Reminder()
{
	short setMNT, setD, setH, setMIN, setS;
	string reminding;
	int ActTime[5];
	
	printf( "Press [0] at any moment to go back. \n" );
	
	do
	{
		cout << "Reminder: ";
		getline( cin, reminding );
		cin.clear();
		cin.sync();
		
		if( reminding == "0" )
		{
			system("cls");
			return;
		}
		
		string approve;
		cout << "Do you want to set this reminder (Y/N)" << endl;
		cin >> approve;
		cin.clear();
		cin.sync();
				
		if( approve == "Y" || approve == "y" )
			break;
			
		if( approve == "0" )
		{
			system("cls");
			return;
		}					 
	}while( true );
	
	string set;
			
	do
	{
		ActualTime(ActTime);
				
		short actMNT, actD, actH, actMIN, actS;
		actD = ActTime[0];
		actMNT = ActTime[1];
		actH = ActTime[2];
		actMIN = ActTime[3];
		actS = ActTime[4];

		do
		{
			cout << "When do you want to set the remind? (DD/MM HH:mm) ";
			getline(cin, set);
			cin.clear();
			cin.sync();
			
			if( set == "0 ")
			{
				system("cls");
				return;
			}
			
			for ( int i = 0; i < 12; i +=3 )
			{
				short changeSH1 = (short)set[i] - 48;
				short changeSH2 = (short)set[i+1] - 48;
						
				if( i == 0 )
					setD = changeSH1 * 10 + changeSH2; // months
						
				if( i == 3 )
					setMNT = changeSH1 * 10 + changeSH2; // days
					
				if( i == 6 )
					setH = changeSH1 * 10 + changeSH2; // hours
					
				if( i == 9 )
					setMIN = changeSH1 * 10 + changeSH2; // minutes
			}// for
		
			if( setMNT >= 0 && setMNT < 13 && setD >= 0 && setD < 32 && setH >= 0 && setH < 24 && setMIN >= 0 && setMIN < 60 )
			{
				if( actMNT > setMNT)
					cout << "Wrong date format! Something is probably wrong with the month. " << endl;
			
				if( actMNT == setMNT)
				{
					if( actD > setD )
						cout << "Wrong date format! Something is probably wrong with the days. " << endl;
					else if( actD < setD )
								break;
						else if( actD == setD && actH < setH )
									break;
							if( actD == setD && actH == setH && actMIN < setMIN )
									break;
								else if( actD == setD && actH > setH )
										cout << "Wrong date format! Something is probably wrong with the hours. " << endl;
								else if( actD == setD && actH == setH && actMIN >= setMIN )
									cout << "Wrong date format! Something is probably wrong with the minutes. " << endl;
				} // if actMNT == setMNT
				if( actMNT < setMNT )
					break;			
			}// if that checks logical date format
			else cout << "Wrong date format!" << endl;
					
		}while( true );		
				
		string approve;
		if( actMNT == setMNT && actD == setD )
		{
			if( setMIN >= 0 && setMIN < 10 ) // if the minutes are only one digit long
				printf( "Reminder set for today on %d:0%d. Do you wish to change the date? (Y/N) ", setH, setMIN );
			else printf( "Reminder set for today on %d:%d. Do you wish to change the date? (Y/N) ", setH, setMIN );
		}else if( actMNT == setMNT && setD - actD == 1 )
			{
				if( setMIN >= 0 && setMIN < 10 ) // if the minutes are only one digit long
					printf( "Reminder set for tomorrow at %d:0%d. Do you wish to change the date? (Y/N) ", setH, setMIN );
				else printf( "Reminder set for tomorrow at %d:%d. Do you wish to change the date? (Y/N) ", setH, setMIN );
			}else if( setMIN >= 0 && setMIN < 10 ) // if the minutes are only one digit long
					printf( "Reminder set on day %d/%d at %d:0%d. Do you wish to change the date? (Y/N) ", setD, setMNT, setH, setMIN );
				else printf( "Reminder set on day %d/%d at %d:%d. Do you wish to change the date? (Y/N) ", setD, setMNT, setH, setMIN );
		
		cin >> approve;
		cin.clear();
		cin.sync();
	
		if( approve == "N" || approve == "n" )
			break;
		
		if( approve == "0" )
		{
			system("cls");
			return;
		}
	
	}while( true );
		
	short SetTime[4];
	SetTime[0] = setD;
	SetTime[1] = setMNT;
	SetTime[2] = setH;
	SetTime[3] = setMIN;
	
	fstream oFile;
	oFile.open("Remindings.txt", ios::out | ios::app);

	oFile << set << endl;
	oFile << reminding << endl;
	oFile << endl;
	
	oFile.close();
	
	fstream oFileHis;
	oFileHis.open("Remindings_History.txt", ios::out | ios::app);

	oFileHis << set << endl;
	oFileHis << reminding << endl;
	oFileHis << endl;
	
	oFileHis.close();
		
	if( false == LeftTime( SetTime, 'P' ) )
	{
		system("cls");
		printf( "%s\n\n", reminding.c_str() );
	}
										
}; // function Reminder

void ComputerControl()
{
	options:
	printf( "What do you want to do? \n" );
	printf( "[1] Shut down the computer \n" );
	printf( "[2] Reset the computer \n" );
	printf( "[3] Hibernate the computer \n" );
	printf( "[0] Get back \n\n" );
	
	char option;
	cin >> option;
	cin.clear();
	cin.sync();
	
	short setD, setH, setMIN, setS;
	short actD, actMNT, actH, actMIN, actS;
	int ActTime[5];
	short SetTime[4];
	
	char choice;

	switch( option )
	{
		case '1':
				
			system("cls");
			printf( "Option: Shut down the computer. \n\n" );
			printf( "Press [0] at any moment to get back to options. \n" );
			printf( "Press [1] if you wish to shut down the computer at a specific time. \n" );
			printf( "Press [2] if you wish to shut down the computer within a specific time. \n" );
			
			cin >> choice;
			cin.clear();
			cin.sync();
						
			if(choice == '0')
			{
					system("cls");
					goto options;	
			}
			
			system("cls");
			
			if(choice == '1')
				printf( "At what time do you wish to shut down the computer? (HH:MM) \n" );
			
			if(choice == '2')
				printf("In what time do you wish to shut down the computer? (HH:MM) \n");
			
			do
			{
				ActualTime( ActTime );
				
				actD = ActTime[0];
				actMNT = ActTime[1];
				actH = ActTime[2];
				actMIN = ActTime[3];
				actS = ActTime[4];
					
				do
				{
					string set;
					getline( cin, set );
					cin.clear();
					cin.sync();
					
					if( set == "0" )
					{
						system("cls");
						goto options;	
					}
						
					for( int i = 0; i < 6; i +=3 )
					{
						short changeSH1 = (short)set[i] - 48;
						short changeSH2 = (short)set[i+1] - 48;
		
						if( i == 0 )
							setH = changeSH1 * 10 + changeSH2; // hours
							
						if( i == 3 )
							setMIN = changeSH1 * 10 + changeSH2; // minutes
					} // for

					if( setH >= 0 && setH < 24 && setMIN >= 0 && setMIN < 60 )
						break;
					else cout << "Wrong date format! Try again: ";
								
				}while( true );	
					
				string approve;
	
				if(choice == '1')
				{
					if(actH < setH || actH == setH && actMIN < setMIN)
						printf( "Computer will shut down today at %d:%d. Do you wish to change the time? (Y/N) ", setH, setMIN );
					else 
						printf( "Computer will shut down tomorrow at %d:%d. Do you wish to change the time? (Y/N) ", setH, setMIN );
						
					setS = 0;
				} // choice = 1			
			
				if(choice == '2')
				{
					ActualTime(ActTime);
					actH = ActTime[2];
					actMIN = ActTime[3];
					actS = ActTime[4];
					
					setH += actH;
					setMIN += actMIN;
					setS = actS;
					
					if( setH < 24 )
						printf( "Computer will shut down today at %d:%d:%d. Do you wish to change the time? (Y/N) ", setH, setMIN, setS );
						
					if( setH > 23 )
						printf( "Computer will shut down tomorrow at %d:%d:%d. Do you wish to change the time? (Y/N) ", setH - 24, setMIN, setS );	
				} // choice = 2
								
				cin >> approve;
				cin.clear();
				cin.sync();
			
				if( approve == "N" || approve == "n" )
					break;
				else printf( "Type time again: " );
								
			}while( true );
				
			if( actH > setH || actH == setH && actMIN > setMIN )
				SetTime[0] = actD + 1;
			else SetTime[0] = actD;
			SetTime[1] = actMNT;
			SetTime[2] = setH;
			SetTime[3] = setMIN;
			SetTime[4] = setS;

			if(false == LeftTime(SetTime, 'S'))
			{
				system("cls");
				system("shutdown /s /f");
			}	
				
		break;
		
		case '2':

			system("cls");
			printf( "Option: Restart the computer. \n\n" );
			printf( "Press [0] at any moment to get back to options. \n" );
			printf( "Press [1] if you wish to restart the computer at a specific time. \n" );
			printf( "Press [2] if you wish to restart the computer within a specific time. \n" );
			
			cin >> choice;
			cin.clear();
			cin.sync();
				
			if(choice == '0')
				{
					system("cls");
					goto options;	
				}
			
			system("cls");
			
			if(choice == '1')
				printf( "At what time do you wish to shut down the computer? (HH:MM) \n" );
			
			if(choice == '2')
				printf("In what time do you wish to shut down the computer? (HH:MM) \n");
						
			do
			{
				ActualTime( ActTime );
				
				actD = ActTime[0];
				actMNT = ActTime[1];
				actH = ActTime[2];
				actMIN = ActTime[3];
				actS = ActTime[4];
					
				do
				{
					string set;
					getline( cin, set );
					cin.clear();
					cin.sync();
					
					if( set == "0" )
					{
						system("cls");
						goto options;	
					}
						
					for( int i = 0; i < 6; i +=3 )
					{
						short changeSH1 = (short)set[i] - 48;
						short changeSH2 = (short)set[i+1] - 48;
		
						if( i == 0 )
							setH = changeSH1 * 10 + changeSH2; // hours
							
						if( i == 3 )
							setMIN = changeSH1 * 10 + changeSH2; // minutes
					} // for

					if( setH >= 0 && setH < 24 && setMIN >= 0 && setMIN < 60 )
						break;
					else cout << "Wrong date format! Try again: ";
								
				}while( true );	
					
				string approve;
	
				if(choice == '1')
				{
					if(actH < setH || actH == setH && actMIN < setMIN)
						printf( "Computer will restart today at %d:%d. Do you wish to change the time? (Y/N) ", setH, setMIN );
					else 
						printf( "Computer will restart tomorrow at %d:%d. Do you wish to change the time? (Y/N) ", setH, setMIN );
						
					setS = 0;
				} // choice = 1			
			
				if(choice == '2')
				{
					ActualTime(ActTime);
					actH = ActTime[2];
					actMIN = ActTime[3];
					actS = ActTime[4];
					
					setH += actH;
					setMIN += actMIN;
					setS = actS;
					
					if( setH < 24 )
						printf( "Computer will restart today at %d:%d:%d. Do you wish to change the time? (Y/N) ", setH, setMIN, setS );
						
					if( setH > 23 )
						printf( "Computer will restart tomorrow at %d:%d:%d. Do you wish to change the time? (Y/N) ", setH - 24, setMIN, setS );	
				} // choice = 2
								
				cin >> approve;
				cin.clear();
				cin.sync();
			
				if( approve == "N" || approve == "n" )
					break;
				else printf( "Type time again: " );
								
			}while( true );
				
			if( actH > setH || actH == setH && actMIN > setMIN )
				SetTime[0] = actD + 1;
			else SetTime[0] = actD;
			SetTime[1] = actMNT;
			SetTime[2] = setH;
			SetTime[3] = setMIN;
			SetTime[4] = setS;
				
			if(false == LeftTime(SetTime, 'R'))
			{
				system("cls");
				system("shutdown /r /f");
			}	
				
		break;
				
		case '3':
			
			system("cls");
			printf( "Option: Hibernate the computer. \n\n" );
			printf( "Press [0] at any moment to get back to options. \n" );
			printf( "Press [1] if you wish to hibernate the computer at a specific time. \n" );
			printf( "Press [2] if you wish to hibernate the computer within a specific time. \n" );
			
			cin >> choice;
			cin.clear();
			cin.sync();
				
			if(choice == '0')
				{
					system("cls");
					goto options;	
				}
			
			system("cls");
			
			if(choice == '1')
				printf( "At what time do you wish to hibernate the computer? (HH:MM) \n" );
			
			if(choice == '2')
				printf("In what time do you wish to hibernate the computer? (HH:MM) \n");
						
			do
			{
				ActualTime( ActTime );
				
				actD = ActTime[0];
				actMNT = ActTime[1];
				actH = ActTime[2];
				actMIN = ActTime[3];
				actS = ActTime[4];
					
				do
				{
					string set;
					getline( cin, set );
					cin.clear();
					cin.sync();
					
					if( set == "0" )
					{
						system("cls");
						goto options;	
					}
						
					for( int i = 0; i < 6; i +=3 )
					{
						short changeSH1 = (short)set[i] - 48;
						short changeSH2 = (short)set[i+1] - 48;
		
						if( i == 0 )
							setH = changeSH1 * 10 + changeSH2; // hours
							
						if( i == 3 )
							setMIN = changeSH1 * 10 + changeSH2; // minutes
					} // for

					if( setH >= 0 && setH < 24 && setMIN >= 0 && setMIN < 60 )
						break;
					else cout << "Wrong date format! Try again: ";
								
				}while( true );	
					
				string approve;
	
				if(choice == '1')
				{
					if(actH < setH || actH == setH && actMIN < setMIN)
						printf( "Computer will hibernate today at %d:%d. Do you wish to change the time? (Y/N) ", setH, setMIN );
					else 
						printf( "Computer will hibernate tomorrow at %d:%d. Do you wish to change the time? (Y/N) ", setH, setMIN );
						
					setS = 0;
				} // choice = 1			
			
				if(choice == '2')
				{
					ActualTime(ActTime);
					actH = ActTime[2];
					actMIN = ActTime[3];
					actS = ActTime[4];
					
					setH += actH;
					setMIN += actMIN;
					setS = actS;
					
					if( setH < 24 )
						printf( "Computer will hibernate today at %d:%d:%d. Do you wish to change the time? (Y/N) ", setH, setMIN, setS );
						
					if( setH > 23 )
						printf( "Computer will hibernate tomorrow at %d:%d:%d. Do you wish to change the time? (Y/N) ", setH - 24, setMIN, setS );	
				} // choice = 2
								
				cin >> approve;
				cin.clear();
				cin.sync();
			
				if( approve == "N" || approve == "n" )
					break;
				else printf( "Type time again: " );
								
			}while( true );
				
			if(actH > setH || actH == setH && actMIN > setMIN)
				SetTime[0] = actD + 1;
			else SetTime[0] = actD;
			SetTime[1] = actMNT;
			SetTime[2] = setH;
			SetTime[3] = setMIN;
			SetTime[4] = setS;
				
			if( false == LeftTime(SetTime, 'H') )
			{
				system("cls");
				system("rundll32.exe PowrProf.dll, SetSuspendState Hibernate");
			}
			
		break;
		
		case '0':
		system("cls");
		
		return;
		
		break;
		
	}// switch

}; // function ComputerControl

bool Menu()
{
	system("cls");
	printf("[1] Remindings \n");
	printf("[2] Control the computer \n");
	printf("[0] Shut down the program \n");

	char option;

	do
	{
		cin >> option;
		cin.clear();
		cin.sync();
				
		if( option == '0' || option == '1' || option == '2' )
			break;	
		else printf("Wrong choice. Try again. \n");
					
	}while( true );

	switch( option )
	{
		case '1':
			
			system("cls");
			Reminder();
		
		break;
		
		case '2':
			
			system("cls");
			ComputerControl();
		
		break;
		
		case '0':
			
			exit(0);
			return false;
			
		break;
	}// switch
	
} // function Menu

string longToStr( long n )
{
	string tmp, result;
	do
	{
		tmp += n % 10 + 48;
		n -= n % 10;
		
	}while(n /= 10);	
	
	for(int i = tmp.size()-1; i >= 0; i--)
		result += tmp[i];
		
	return result;
	
} // function longToStr

int search( string & text , string searchedFrase)
{
	size_t foundPosition = text.find(searchedFrase);

	if(foundPosition == string::npos)
	{
		return false;
	}
	
	return foundPosition + searchedFrase.size();
	
} // funkcja szukaj

bool StartUp()
{
	ifstream iFile;
	iFile.open("Remindings.txt");
	if( !iFile.good() )
	{
		ofstream oFile;
		oFile.open( "Remindings.txt" );
		oFile.close();
		return false;
	}
		
	int ActTime[5];
	ActualTime(ActTime);
	
	short actMNT, actD, actH, actMIN;
	actD = ActTime[0];
	actMNT = ActTime[1];
	actH = ActTime[2];
	actMIN = ActTime[3]; 
	
	string date, reminding, empty;
	string timeSTR;
	long time;
	short days, mnt, h, min;
	vector < string > vecTab;
	
	actD += MonthToDays( actMNT );
	long actTimeSec = actD * 86400 + actH * 3600 + actMIN * 60;
	
	while( !iFile.eof() )
	{
		getline( iFile, date );
				
		for(int i = 0; i < 12; i +=3)
		{
			short changeSH1 = (short)date[i] - 48;  
			short changeSH2 = (short)date[i+1] - 48;
					
			if(i == 0)
				days = changeSH1 * 10 + changeSH2; // remindings day
				
			if(i == 3)
				mnt = changeSH1 * 10 + changeSH2; // remindings month
				
			if(i == 6)
				h = changeSH1 * 10 + changeSH2; // remindings hour
			
			if(i == 9)
				min = changeSH1 * 10 + changeSH2; // remindings minute
		} // for
		
		days = days + MonthToDays( mnt );
		time = days * 86400 + h * 3600 + min * 60;
		timeSTR = longToStr( time );
		
		getline( iFile, reminding );
		getline( iFile, empty );
		
		string whole = timeSTR + "\n" + date + "\n" + reminding + "\n" + empty + "\n";
		vecTab.push_back( whole );
		
		if( time < actTimeSec - 86400 ) // if older than day then delete
			vecTab.pop_back();
		
	} // while		
	iFile.close();
	
	sort( vecTab.begin(), vecTab.end() ); // sorted remindings by seconds
	
	vector < string > vecTabFile;
	int position = 0;
	string searched;
	string found;
	for( int i = 0; i < vecTab.size(); i++ )
	{
		searched = vecTab[i];
		position = search( searched, "\n" );
		searched.erase( 0, position );		
		vecTabFile.push_back( searched );
	}
	
	fstream oFile;
	oFile.open( "Remindings.txt", ios::out );
	
	for( int i = 0; i < vecTab.size(); i++ )
		oFile << vecTabFile[i];
	
	oFile.close();
	
	iFile.open( "Remindings.txt" );
	if( !iFile.good() )
		{
			ofstream oFile;
			oFile.open( "Remindings.txt" );
			printf( "You don't have any remindings'. \n\n" );
			oFile.close();
			return false;
		}
	printf( "Today's remindings: \n\n" );

	short remMNT, remD, remH, remMIN;
	int amount = 0;
	actD = ActTime[0];
	
	while( !iFile.eof() )
	{
		getline( iFile, date );
		getline( iFile, reminding );
		getline( iFile, empty );
				
		for( int i = 0; i < 12; i +=3 )
		{
			short changeSH1 = (short)date[i] - 48;  
			short changeSH2 = (short)date[i+1] - 48;
				
			if (i == 0 )
				remD = changeSH1 * 10 + changeSH2; // remindings day
			
			if( i == 3 )
				remMNT = changeSH1 * 10 + changeSH2; // remindings month
					
			if (i == 6 )
				remH = changeSH1 * 10 + changeSH2; // remindings hour 
		
			if( i == 9 )
				remMIN = changeSH1 * 10 + changeSH2; // remindings minute 
		} // for
	
		if( remD == actD && remMNT == actMNT )
		{
			if( remMIN >= 0 && remMIN < 10 )
				printf( "Reminding at %d:0%d : ", remH, remMIN );
			else printf( "Reminding at %d:%d : ", remH, remMIN );
			cout << reminding << endl;			
			amount ++;
		} // if
		
	} // while 

	iFile.close();
	
	if( amount == 0 )
		printf( "No remindings for today! \n" );
	
	printf( "\nPress [1] to start the program or anything else to quit. \n" );
	char option;
	cin >> option;
	cin.sync();
	cin.clear();

	if( option == '1' )
		return false;
	else exit(0);

} // function StartUp

int main()
{
	StartUp();
	while( true )
	{
		Menu();
	}
		
	system("pause");
	return 0;	
} 

