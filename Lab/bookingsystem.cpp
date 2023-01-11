#include "bookingsystem.h"

#include <iostream>

using namespace std;


int BookingSystem::nextID = 0;

/* ===================================================
    TODO: Complete the type conversion constructor.
          Here we assume to allocate same capacity for tennisball, tenniscourt and person.
          Try to add only one extra line of code!
    HINT: Reuse the general constuctor we define below.
   =================================================== */ 
BookingSystem::BookingSystem(int capacity)
{
    BookingSystem(capacity,capacity,capacity);
    // Finish constructing with printing.
    cout << "By using the conversion constructor!" << endl;
}

/* ===================================================
    TODO: Complete the other constructor
          numTennisBall, numTennisCourt, numPerson should be initialized to be 0
          maxNumTennisBall, maxNumTennisCourt, maxNumPerson should be initialized to their assigned values
   =================================================== */ 
BookingSystem::BookingSystem(int nTennisBall, int nTennisCourt, int capacity) 
{
    SN = nextID++;
    // TODO: Allocate memory for tennisballs, tenniscourts and persons here.
    numTennisBall = numTennisCourt = numPerson = 0;
    maxNumPerson = capacity;
    maxNumTennisBall = nTennisBall;
    maxNumTennisCourt = nTennisCourt;

    persons = new Person* [maxNumPerson];
    tennisballs = new TennisBall* [maxNumTennisBall];
    tenniscourts = new TennisCourt* [maxNumTennisCourt];


    // Finish constructing with printing.
    cout <<"#"<< SN<< " BookingSystem Constructed!" << endl;
}


/* ===================================================
    TODO: Complete the copy constructor
          Deep copy all data members of another restaurant
   =================================================== */ 
BookingSystem::BookingSystem(const BookingSystem &other)
{
    SN = nextID++;
    // TODO: Clone TennisBalls.
    for(int i = 0; i < other.numTennisBall; i++)
    {
        this->tennisballs[i] = new TennisBall(*other.tennisballs[i]);
    }
    this->numTennisBall = other.numTennisBall;
    this->maxNumTennisBall = other.maxNumTennisBall;

    // TODO: Clone TennisCourts.
    for(int i = 0; i < other.numTennisCourt; i++)
    {
        this->tenniscourts[i] = new TennisCourt(*other.tenniscourts[i]);
    }
    this->numTennisCourt = other.numTennisCourt;
    this->maxNumTennisCourt = other.maxNumTennisCourt;
    // TODO: Clone Persons.
    for(int i = 0; i < other.numPerson; i++)
    {
        this->persons[i] = new Person(*other.persons[i]);
    }
    this->numPerson = other.numPerson;
    this->maxNumPerson = other.maxNumPerson;
    // Finish copying with printing.
    cout <<"#"<< SN<< " BookingSystem Copied!" << endl; 
}


/* ===================================================
    TODO: Complete the destructor
   =================================================== */ 
BookingSystem::~BookingSystem()
{
    // TODO: Destruct TennisBalls.
    for(int i = 0; i < numTennisBall; i++)
    {
        delete tennisballs[i];
    }
    cout<<"step 0"<<endl;
    // delete [] tennisballs;
    cout<<"step 0"<<endl;
    tennisballs = nullptr;
    cout<<"step 0"<<endl;
    // numTennisBall = 0;
    cout<<"step 0"<<endl;
    // maxNumTennisBall = 0;

    // TODO: Destruct TennisCourts.
    for(int i = 0; i < numTennisCourt; i++)
    {
        delete tenniscourts[1];
    }
    cout<<"step 0"<<endl;
    // delete [] tenniscourts;
    tenniscourts = nullptr;
    numTennisCourt = 0;
    maxNumTennisCourt = 0;

    // TODO: Destruct Persons.
    for(int i = 0; i < numPerson; i++)
    {
        delete persons[i];
    }
    // delete [] persons;
    persons = nullptr;
    numPerson = 0;
    maxNumPerson = 0;
    
    // Finish destructing with printing.
    cout <<"#"<< SN<< " BookingSystem is Destructed." << endl;
}


void BookingSystem::releaseTennisBall()
{
    if (numTennisBall >= maxNumTennisBall)
    {
        cout << "Error: there is no TennisBall , release failed." << endl;
    }
    else
    {
        // TODO: a tennis ball is available by allocating a TennisBall object.
        tennisballs[numTennisBall] = new TennisBall;
        numTennisBall++;
    }
}

void BookingSystem::releaseTennisCourt()
{
    if (numTennisCourt >= maxNumTennisCourt)
    {
        cout << "Error: there is no TennisCourt , release failed." << endl;
    }
    else
    {
        // TODO: a tennis court is available by allocating a TennisCourt object.
        tenniscourts[numTennisCourt] = new TennisCourt();
        numTennisCourt++;
    }
}

void BookingSystem::makeBooking()
{
    if (numPerson >= maxNumPerson)
    {
        cout << "Error: Capacity Lack" << endl;
    }
    else if (numTennisBall < 1 || numTennisCourt < 1)
    {
        cout << "Error: no enough facilities for booking" << endl;
    } 
    else
    {
        /* ===================================================
           TODO: accept person's booking by allocating a Person object. 
            The person would like to reserve a tennis basll and a tennis court.
            The ownership of the top tennisball and tenniscourt is then transferred to the Person object,
            which means the TennisBall object and the TennisCourt object are now pointed by the new Person object instead.
        =================================================== */ 
        Person* person = new Person(tennisballs[0],tenniscourts[0]);
        for(int i = 0; i < numTennisBall-1; i++)
        {
            tennisballs[i] = tennisballs[i+1];
        }
        tennisballs[numTennisBall] = nullptr;
        numTennisBall--;

        for(int i = 0; i < numTennisCourt-1; i++)
        {
            tenniscourts[i] = tenniscourts[i+1];
        }
        tennisballs[numTennisCourt] = nullptr;
        numTennisCourt--;

        persons[numPerson] = person;
        numPerson++;

        // Finish processing.
        cout <<"Booking is successful!!!" << endl;
    }
}

void BookingSystem::log() const
{
    cout << "----------------------" << endl;
    cout << "| Booking System Log |" << endl;
    cout << "----------------------" << endl;
    cout <<"#"<< SN<< " booking system has..." << endl;
    cout << "TennisBall: " << numTennisBall << "/" << maxNumTennisBall << endl;
    cout << "TennisCourt: " << numTennisCourt << "/" << maxNumTennisCourt << endl;
    cout << "Person: " << numPerson << "/" << maxNumPerson << endl;
}
