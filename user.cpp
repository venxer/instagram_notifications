#include "user.h"

User::User()
{
    username = "";
    likes = false;
    tags = false;
    comments = false;
    newFollowers = false;
    messageRequests = false;
}
User::User(std::string username,
           bool likes,
           bool tags,
           bool comments,
           bool newFollowers,
           bool messageRequests)
{
    this->username = username;
    this->likes = likes;
    this->tags = tags;
    this->comments = comments;
    this->newFollowers = newFollowers;
    this->messageRequests = messageRequests;
}
void User::noticationQueue(std::shared_ptr<Notification> notification)
{   
    if(notification->getType() == "Like" && !likes)                     return;
    if(notification->getType() == "Tag" && !tags)                       return;
    if(notification->getType() == "Comment" && !comments)               return;
    if(notification->getType() == "Follow" && !newFollowers)            return;
    if(notification->getType() == "MessageRequest" && !messageRequests) return;
    // If empty notifications
    if(notifications.empty())
    {
        notifications.push(notification);
    }
    else // If not empty
    {
        // Check if current is same as prev
        if(notification->getType() == notifications.front()->getType())
        {
            notifications.push(notification);
        }
        else // Curr and Prev diff types
        {
            if(notifications.size() > 3)
            {
                int size = notifications.size();
                while(notifications.size() != 2)
                {
                    notifications.pop();
                }
                std::string second = notifications.front()->getTriggeringUser();
                notifications.pop();
                std::string first = notifications.front()->getTriggeringUser();
                addNotifcation(notifications.front()->aggregateNotificationMessage(first, second, size - 2));
                notifications.pop();

                notifications.push(notification);
            }
            else
            {
                while(!notifications.empty())
                {
                    addNotifcation(notifications.front()->singeNotificationMessage());
                    notifications.pop();
                }

                notifications.push(notification);
            }
        }
    }    
}
void User::addNotifcation(const std::string &notificationMessages)
{
    notificationStack.push(notificationMessages);
}
bool parseEvents(std::ifstream &eventFile, const std::unordered_map<std::string, std::string> &postIDToAuthorMap, 
                User &recievingUser)
{
    std::string triggerUsername, mode, query;
    while(eventFile >> triggerUsername >> mode >> query)
    {
        // like + comment
        if(mode == "likes" || mode == "comments_on")
        {
            // If postID is not found
            if(postIDToAuthorMap.find(query) == postIDToAuthorMap.end()) continue;
            // If postID does not belong to recieving username
            if(postIDToAuthorMap.at(query) != recievingUser.username) continue;
        }
        else
        {
            // If recieving user is not in query
            if(query != recievingUser.username) continue;
        }
        
        if(mode == "likes")
        {
            recievingUser.noticationQueue(std::make_shared<Like>(triggerUsername));
        }
        else if(mode == "tags")
        {
            recievingUser.noticationQueue(std::make_shared<Tag>(triggerUsername));


        }
        else if(mode == "comments_on")
        {
            recievingUser.noticationQueue(std::make_shared<Comment>(triggerUsername));


        }
        else if(mode == "follows")
        {
            recievingUser.noticationQueue(std::make_shared<Follow>(triggerUsername));


        }
        else if(mode == "messageRequests")
        {
            recievingUser.noticationQueue(std::make_shared<MessageRequest>(triggerUsername));
        }
    }
    return true;
}
void User::printNotifications(std::ofstream &outputFile)
{
    while(!notifications.empty())
    {
        if(notifications.size() > 3)
        {
            int size = notifications.size();
            while(notifications.size() != 2)
            {
                notifications.pop();
            }
            std::string second = notifications.front()->getTriggeringUser();
            notifications.pop();
            std::string first = notifications.front()->getTriggeringUser();
            addNotifcation(notifications.front()->aggregateNotificationMessage(first, second, size - 2));
            notifications.pop();
        }
        else
        {
            notificationStack.push(notifications.front()->singeNotificationMessage());
            notifications.pop();
        }

    }
    int outputCount = 0;
    while(!notificationStack.empty() && outputCount < 100)
    {
        outputFile << notificationStack.top() << "\n";
        notificationStack.pop();
        outputCount++;
    }
}

