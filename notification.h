#ifndef NOTIFCATION_H
#define NOTIFCATION_H

#include <string>

class Notification
{
    protected:
        std::string username;

    public:
        Notification(/* args */);
};

class Like:public Notification
{
    
};
class Tag:public Notification
{
 
};
class Comment:public Notification
{
 
};
class Follow:public Notification
{
 
};
class MessageRequest:public Notification
{
 
};
#endif