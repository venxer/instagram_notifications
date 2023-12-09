#ifndef NOTIFCATION_H
#define NOTIFCATION_H

#include <string>

class Notification
{
    protected:
        std::string type;
        std::string triggeringUser;

    public:
        Notification(std::string triggeringUser);
        virtual ~Notification(){};

        virtual std::string singeNotificationMessage() = 0;
        virtual std::string aggregateNotificationMessage(const std::string &first, const std::string &second, const int &count) = 0;

        std::string getTriggeringUser() const {return triggeringUser;};
        std::string getType()           const {return type;          };
};

class Like:public Notification
{
    public:
        Like(std::string triggeringUser);

        std::string singeNotificationMessage(); 
        std::string aggregateNotificationMessage(const std::string &first, const std::string &second, const int &count);
};
class Tag:public Notification
{
    public:
        Tag(std::string triggeringUser);

        std::string singeNotificationMessage();
        std::string aggregateNotificationMessage(const std::string &first, const std::string &second, const int &count);
};
class Comment:public Notification
{
    public:
        Comment(std::string triggeringUser);

        std::string singeNotificationMessage();
        std::string aggregateNotificationMessage(const std::string &first, const std::string &second, const int &count);
};
class Follow:public Notification
{
    public:
        Follow(std::string triggeringUser);

        std::string singeNotificationMessage();
        std::string aggregateNotificationMessage(const std::string &first, const std::string &second, const int &count);

};
class MessageRequest:public Notification
{
    public:
        MessageRequest(std::string triggeringUser);

        std::string singeNotificationMessage();
        std::string aggregateNotificationMessage(const std::string &first, const std::string &second, const int &count);
};
#endif