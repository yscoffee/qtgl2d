#ifndef OBJECTS_H
#define OBJECTS_H
#include <string>
class Objects
{
protected:
   std::string name;
public:
    Objects();
    virtual void rendering()=0;
    //Call by Timer. Be used to update state of game object
    //Unit of time is millisecond second
    virtual void update(const long ELAPSED_MS )=0;
};

#endif // OBJECTS_H
