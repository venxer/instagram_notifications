#include "notification.h"

Notification::Notification(std::string triggeringUser)
{
    this->triggeringUser = triggeringUser;
}
Like::Like(std::string triggeringUser):Notification(triggeringUser)
{
    type = "Like";
}
std::string Like::singeNotificationMessage()
{
    return triggeringUser + " liked your post.";
}
std::string Like::aggregateNotificationMessage(const std::string &first, const std::string &second, const int &count)
{
    return first + ", " + second + " and " + std::to_string(count) + " others liked your post.";
}

Tag::Tag(std::string triggeringUser):Notification(triggeringUser)
{
    type = "Tag";
}
std::string Tag::singeNotificationMessage()
{
    return triggeringUser + " tagged you in a post.";
}
std::string Tag::aggregateNotificationMessage(const std::string &first, const std::string &second, const int &count)
{
    return first + ", " + second + " and " + std::to_string(count) + " others tagged you in a post.";
}

Comment::Comment(std::string triggeringUser):Notification(triggeringUser)
{
    type = "Comment";
}
std::string Comment::singeNotificationMessage()
{
    return triggeringUser + " commented on your post.";
}
std::string Comment::aggregateNotificationMessage(const std::string &first, const std::string &second, const int &count)
{
    return first + ", " + second + " and " + std::to_string(count) + " others commented on your post.";
}

Follow::Follow(std::string triggeringUser):Notification(triggeringUser)
{
    type = "Follow";
}
std::string Follow::singeNotificationMessage()
{
    return triggeringUser + " started following you.";
}

std::string Follow::aggregateNotificationMessage(const std::string &first, const std::string &second, const int &count)
{
    return first + ", " + second + " and " + std::to_string(count) + " others started following you.";
}

MessageRequest::MessageRequest(std::string triggeringUser):Notification(triggeringUser)
{
    type = "MessageRequest";
}
std::string MessageRequest::singeNotificationMessage()
{
    return triggeringUser + " wants to send you a message.";
}
std::string MessageRequest::aggregateNotificationMessage(const std::string &first, const std::string &second, const int &count)
{
    return first + ", " + second + " and " + std::to_string(count) + " others wants to send you a message.";
}

