#ifndef USER_H
#define USER_H

#include "notification.h"

#include <queue>
#include <stack>
#include <fstream>
#include <unordered_map>
#include <memory>

class User
{
    private:
        std::string username;
        bool likes;
        bool tags;
        bool comments;
        bool newFollowers;
        bool messageRequests;
        std::queue<std::shared_ptr<Notification> > notifications;
        std::stack<std::string> notificationStack;

    public:
        User();
        User(std::string username,
             bool likes,
             bool tags,
             bool comments,
             bool newFollowers,
             bool messageRequests);

        void aggregateNotification();
        void notificationQueue(const std::shared_ptr<Notification> &notification);
        void printNotifications(std::ofstream &outputFile);

        friend void parseEvents(std::ifstream &eventFile, const std::unordered_map<std::string, std::string> &postIDToAuthorMap, 
                                User &receivingUser);
};
void parseEvents(std::ifstream &eventFile, const std::unordered_map<std::string, std::string> &postIDToAuthorMap, 
                 User &receivingUser);

#endif