#ifndef NOTIFCATION_H
#define NOTIFCATION_H

#include <string>
#include <iostream>


class Notification
{
    protected:
        std::string type;
        std::string triggeringUser; // User causing effect

    public:
        Notification(std::string triggeringUser);
        virtual ~Notification(){};

        virtual std::string singeNotificationMessage() = 0;
        virtual std::string aggregateNotificationMessage(const std::string &first, const std::string &second, const int &count) = 0;

        std::string getTriggeringUser() const {return triggeringUser;};
        std::string getType()           const {return type;};
};

class Like:public Notification
{
    public:
        Like(std::string triggeringUser);
        // virtual ~Like(){};

        std::string singeNotificationMessage(); 
        std::string aggregateNotificationMessage(const std::string &first, const std::string &second, const int &count);


};
class Tag:public Notification
{
    public:
        Tag(std::string triggeringUser);
        // virtual ~Tag(){};

        std::string singeNotificationMessage();
        std::string aggregateNotificationMessage(const std::string &first, const std::string &second, const int &count);
};
class Comment:public Notification
{
    public:
        Comment(std::string triggeringUser);
        // virtual ~Comment(){};

        std::string singeNotificationMessage();
        std::string aggregateNotificationMessage(const std::string &first, const std::string &second, const int &count);
};
class Follow:public Notification
{
    public:
        Follow(std::string triggeringUser);
        // virtual ~Follow(){};

        std::string singeNotificationMessage();
        std::string aggregateNotificationMessage(const std::string &first, const std::string &second, const int &count);

};
class MessageRequest:public Notification
{
    public:
        MessageRequest(std::string triggeringUser);
        // virtual ~MessageRequest(){};

        std::string singeNotificationMessage();
        std::string aggregateNotificationMessage(const std::string &first, const std::string &second, const int &count);
};
#endif