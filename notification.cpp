#include "notification.h"

// Base class Notification constuctor
Notification::Notification(std::string triggeringUser)
{
    this->triggeringUser = triggeringUser;
}

// Derived from Notification class. Represents Like Notifications
Like::Like(std::string triggeringUser):Notification(triggeringUser)
{
    type = "Like";
}
/**
 * Formats and returns a single like notification
 * 
 * @return {std::string}  : Notification message for a single like notifcation
 */
std::string Like::singeNotificationMessage()
{
    return triggeringUser + " liked your post.";
}
/**
 * Formats and returns aggregated like notification
 * Aggregated notifications occur when there are more than 3 of the same type of notifications
 * 
 * @param  first          : username of the most recent user who triggered the notification
 * @param  second         : username of the second most recent user who triggered the notification
 * @param  count          : number of other users beyond first and second who trigger the notifcation
 * 
 * @return {std::string}  : Notification message for an aggregated like notifcation
 */
std::string Like::aggregateNotificationMessage(const std::string &first, const std::string &second, const int &count)
{
    return first + ", " + second + " and " + std::to_string(count) + " others liked your post.";
}

// Derived from Notification class. Represents Tag Notifications
Tag::Tag(std::string triggeringUser):Notification(triggeringUser)
{
    type = "Tag";
}
/**
 * Formats and returns a single tag notification
 * 
 * @return {std::string}  : Notification message for a single tag notifcation
 */
std::string Tag::singeNotificationMessage()
{
    return triggeringUser + " tagged you in a post.";
}
/**
 * Formats and returns aggregated tag notification
 * Aggregated notifications occur when there are more than 3 of the same type of notifications
 * 
 * @param  first          : username of the most recent user who triggered the notification
 * @param  second         : username of the second most recent user who triggered the notification
 * @param  count          : number of other users beyond first and second who trigger the notifcation
 * 
 * @return {std::string}  : Notification message for an aggregated tag notifcation
 */
std::string Tag::aggregateNotificationMessage(const std::string &first, const std::string &second, const int &count)
{
    return first + ", " + second + " and " + std::to_string(count) + " others tagged you in a post.";
}

// Derived from Notification class. Represents Comment Notifications
Comment::Comment(std::string triggeringUser):Notification(triggeringUser)
{
    type = "Comment";
}
/**
 * Formats and returns a single comment notification
 * 
 * @return {std::string}  : Notification message for a single comment notifcation
 */
std::string Comment::singeNotificationMessage()
{
    return triggeringUser + " commented on your post.";
}
/**
 * Formats and returns aggregated comment notification
 * Aggregated notifications occur when there are more than 3 of the same type of notifications
 * 
 * @param  first          : username of the most recent user who triggered the notification
 * @param  second         : username of the second most recent user who triggered the notification
 * @param  count          : number of other users beyond first and second who trigger the notifcation
 * 
 * @return {std::string}  : Notification message for an aggregated comment notifcation
 */
std::string Comment::aggregateNotificationMessage(const std::string &first, const std::string &second, const int &count)
{
    return first + ", " + second + " and " + std::to_string(count) + " others commented on your post.";
}

// Derived from Notification class. Represents Follow Notifications
Follow::Follow(std::string triggeringUser):Notification(triggeringUser)
{
    type = "Follow";
}
/**
 * Formats and returns a single like notification
 * 
 * @return {std::string}  : Notification message for a single follow notifcation
 */
std::string Follow::singeNotificationMessage()
{
    return triggeringUser + " started following you.";
}
/**
 * Formats and returns aggregated follow notification
 * Aggregated notifications occur when there are more than 3 of the same type of notifications
 * 
 * @param  first          : username of the most recent user who triggered the notification
 * @param  second         : username of the second most recent user who triggered the notification
 * @param  count          : number of other users beyond first and second who trigger the notifcation
 * 
 * @return {std::string}  : Notification message for an aggregated follow notifcation
 */
std::string Follow::aggregateNotificationMessage(const std::string &first, const std::string &second, const int &count)
{
    return first + ", " + second + " and " + std::to_string(count) + " others started following you.";
}

// Derived from Notification class. Represents message request Notifications
MessageRequest::MessageRequest(std::string triggeringUser):Notification(triggeringUser)
{
    type = "MessageRequest";
}
/**
 * Formats and returns a single like notification
 * 
 * @return {std::string}  : Notification message for a single message request notifcation
 */
std::string MessageRequest::singeNotificationMessage()
{
    return triggeringUser + " wants to send you a message.";
}
/**
 * Formats and returns aggregated follow notification
 * Aggregated notifications occur when there are more than 3 of the same type of notifications
 * 
 * @param  first          : username of the most recent user who triggered the notification
 * @param  second         : username of the second most recent user who triggered the notification
 * @param  count          : number of other users beyond first and second who trigger the notifcation
 * 
 * @return {std::string}  : Notification message for an aggregated message request notifcation
 */
std::string MessageRequest::aggregateNotificationMessage(const std::string &first, const std::string &second, const int &count)
{
    return first + ", " + second + " and " + std::to_string(count) + " others wants to send you a message.";
}

