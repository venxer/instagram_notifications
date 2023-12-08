#ifndef USER_H
#define USER_H

#include "notification.h"

#include <queue>
#include <stack>
#include <fstream>
#include <unordered_map>

class User
{
    private:
        std::string username;
        bool likes;
        bool tags;
        bool comments;
        bool newFollowers;
        bool messageRequests;
        std::queue<Notification*> notifications;
        std::stack<std::string> notificationStack;

    public:
        User();
        User(std::string username,
             bool likes,
             bool tags,
             bool comments,
             bool newFollowers,
             bool messageRequests);

        void noticationQueue(Notification *notification);
        void addNotifcation(const std::string &notificationMessages);
        void printNotifications(std::ofstream &outputFile);

        friend bool parseEvents(std::ifstream &eventFile, const std::unordered_map<std::string, std::string> &postIDToAuthorMap, 
                                User &recievingUser);
};

bool parseEvents(std::ifstream &eventFile, const std::unordered_map<std::string, std::string> &postIDToAuthorMap, 
                 User &recievingUser);

#endif