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
/**
 * Aggregates the notifications in the user's notification queue when there are 
 * more than 3 of the same type of notifications and creates a summary notification 
 * message based on the last two (most recent two) notifications in the queue.
 * Notification Queue is also emptied after notifications are aggregated.
 */
void User::aggregateNotification()
{
    int size = notifications.size();

    // Resize queue down to 2
    while(notifications.size() != 2)
    {
        notifications.pop();
    }

    // Store username of second most recent triggerUser
    std::string second = notifications.front()->getTriggeringUser();
    notifications.pop();
    // Store username of most recent triggerUser
    std::string first = notifications.front()->getTriggeringUser();

    // Aggregate message base on 
    notificationStack.push(notifications.front()->aggregateNotificationMessage(first, second, size - 2));
    notifications.pop();
}
/**
 * Adds a notification to the user's notification queue, handling aggregation when necessary.
 * Checks the type of the notification and the user's preferences to determine whether to add 
 * the notification to the queue or not. If the notification type is the same as the previous 
 * one and the queue size exceeds 3, it aggregates the notifications. If the queue size is 3 
 * or less, it pushes each notification into a stack with its type-specific message.
 * 
 * @param  notification : Shared pointer to the notification to be added to the queue.
 */
void User::notificationQueue(const std::shared_ptr<Notification> &notification)
{   
    // Check if notification type is not one of the user's paused notifications
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
    // If not empty
    else
    {
        // Check if current notification type is the same as previous
        if(notification->getType() == notifications.front()->getType())
        {
            notifications.push(notification);
        }
        // Current notification type is different than previous
        else
        {
            // If there is more than 3 notifications in the queue, aggregate the old notifications
            // into the stack and push the new notification into the queue
            if(notifications.size() > 3)
            {
                aggregateNotification();
                notifications.push(notification);
            }
            else
            {
                // If there are 3 or less notifications in the queue, push each notification into
                // stack with it's notification type specific message. 
                while(!notifications.empty())
                {
                    notificationStack.push(notifications.front()->singeNotificationMessage());
                    notifications.pop();
                }
                // Push the new notification into the queue
                notifications.push(notification);
            }
        }
    }    
}
/**
 * Parse events from an input file and update a receiving user's notifications
 * It updates the receiving user's notification queue with relevant events.
 * 
 * @param  eventFile         : Input file containing events to be processed
 * @param  postIDToAuthorMap : Mapping of post IDs to their respective authors
 * @param  receivingUser     : User who will receive notifications
 */
void parseEvents(std::ifstream &eventFile, const std::unordered_map<std::string, std::string> &postIDToAuthorMap, 
                User &receivingUser)
{
    std::string triggerUsername, mode, query;
    while(eventFile >> triggerUsername >> mode >> query)
    {
        // Check whether the line in the event should be skipped or processed.
        
        // Both like and comment_on mode use postID as query
        if(mode == "likes" || mode == "comments_on")
        {
            // If postID is not found
            if(postIDToAuthorMap.find(query) == postIDToAuthorMap.end()) continue;
            // If postID does not belong to recieving username
            if(postIDToAuthorMap.at(query) != receivingUser.username) continue;
        }
        // Other modes
        else
        {
            // If recieving user is not in query
            if(query != receivingUser.username) continue;
        }
        
        if (mode == "likes")
        {
            // Create a Like notification and add it to the receiving user's notification queue
            receivingUser.notificationQueue(std::make_shared<Like>(triggerUsername));
        }
        else if (mode == "tags")
        {
            // Create a Tag notification and add it to the receiving user's notification queue
            receivingUser.notificationQueue(std::make_shared<Tag>(triggerUsername));
        }
        else if (mode == "comments_on")
        {
            // Create a Comment notification and add it to the receiving user's notification queue
            receivingUser.notificationQueue(std::make_shared<Comment>(triggerUsername));
        }
        else if (mode == "follows")
        {
            // Create a Follow notification and add it to the receiving user's notification queue
            receivingUser.notificationQueue(std::make_shared<Follow>(triggerUsername));
        }
        else if (mode == "messageRequests")
        {
            // Create a MessageRequest notification and add it to the receiving user's notification queue
            receivingUser.notificationQueue(std::make_shared<MessageRequest>(triggerUsername));
        }

    }
}
/**
 * Print notifications from the user's notification stack to an output file.
 * Moves remaining notifications from queue into the stack and aggregate them as needed.
 * 
 * @param  outputFile : Output file stream to output the notifcations to
 */
void User::printNotifications(std::ofstream &outputFile)
{
    // Process notifications in the queue
    while(!notifications.empty())
    {
        if(notifications.size() > 3)
        {
            aggregateNotification();
        }
        else
        {
            notificationStack.push(notifications.front()->singeNotificationMessage());
            notifications.pop();
        }
    }
    int outputCount = 0;

    // Print up to the top 100 notifications from the stack to the output file
    for (int x = 0; !notificationStack.empty() && x < 100; x++)
    {
        // Print top of stack
        outputFile << notificationStack.top() << "\n";
        // Remove top of stack
        notificationStack.pop();
    }
}