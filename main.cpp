#include "user.h"

#include <iostream>

/**
 * Check if file can successfully be opened
 * 
 * @param fileName name of file to be opened
 *      
 * @return the opened file stream
 */
template<typename T>
T validateFile(const std::string &fileName);
/**
 * Parses a JSON file to extract user notification settings for likes, tags, comments, new followers, 
 * and message requests notifications of a specific username. Also checks if all notifications are paused.
 * Function updates the receivingUser object with these notfication preferences.
 * 
 * @param  userJSON          : Input file stream of JSON file with user information
 * @param  receivingUsername : Username to search for in the JSON file
 * @param  receivingUser     : Reference to a User object where the user's data will be stored
 * @return {bool}            : True if the user is found and their data is successfully parsed and stored in receivingUser
 *                             False if the user is not found in the file, or if the user has paused all notifications
 */
bool parseUser(std::ifstream &userJSON, const std::string &receivingUsername, User &receivingUser);
/**
 * 
 * 
 * @param  postJSON                           : 
 * @return {std::unordered_map<std::string,}  : 
 */
std::unordered_map<std::string, std::string> parsePosts(std::ifstream &postJSON);

int main(int argc, char const *argv[])
{
    try
    {
        if(argc != 6)
        {
            throw std::invalid_argument("Invalid Argument Count");
        }
        std::ifstream postJSON        = validateFile<std::ifstream>(argv[1]);
        std::ifstream userJSON        = validateFile<std::ifstream>(argv[2]);
        std::ifstream eventsFile      = validateFile<std::ifstream>(argv[3]);
        std::ofstream output          = validateFile<std::ofstream>(argv[4]);
        std::string receivingUsername = argv[5];

        User user;
        bool parseSuccess = parseUser(userJSON, receivingUsername, user);
    
        // User not found OR User has all notifications paused
        if(!parseSuccess) return 0;
        
        std::unordered_map<std::string, std::string> postIDToAuthorMap = parsePosts(postJSON);

        parseEvents(eventsFile, postIDToAuthorMap, user);

        user.printNotifications(output);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}

template<typename T>
T validateFile(const std::string &fileName)
{
    T stream(fileName);
    if(!stream.good()) std::cerr << "File Error" << fileName << std::endl;
    return stream;
}
bool parseUser(std::ifstream &userJSON, const std::string &receivingUsername, User &receivingUser)
{   
    //JSON to string
    std::string content((std::istreambuf_iterator<char>(userJSON)), std::istreambuf_iterator<char>());
    
    std::string usernameToFind = "\"username\": \"" + receivingUsername + "\"";
    size_t usernameTagStart = content.find(usernameToFind);

    // User with receivingUsername not found
    if(usernameTagStart == std::string::npos) return false;

    bool pauseAll, likes, tags, comments, newFollowers, messageRequests;

    // User notification has pauseAll notifications on
    size_t pauseAllTagEnd = content.find("\"pauseAll\": ", usernameTagStart) + 13;
    size_t pauseAllStart = content.find_first_not_of("\"", pauseAllTagEnd);
    size_t pauseAllEnd = content.find("\"", pauseAllStart);
    pauseAll = content.substr(pauseAllStart, pauseAllEnd - pauseAllStart) == "true";
    if(pauseAll) return false;

    // Fetch user notication settings
    size_t likesTagEnd = content.find("\"likes\": ", usernameTagStart) + 10;
    size_t likesStart = content.find_first_not_of("\"", likesTagEnd);
    size_t likesEnd = content.find("\"", likesStart);
    likes = content.substr(likesStart, likesEnd - likesStart) == "true";

    size_t tagsTagEnd = content.find("\"tags\": ", usernameTagStart) + 9;
    size_t tagsStart = content.find_first_not_of("\"", tagsTagEnd);
    size_t tagsEnd = content.find("\"", tagsStart);
    tags = content.substr(tagsStart, tagsEnd - tagsStart) == "true";

    size_t commentsTagEnd = content.find("\"comments\": ", usernameTagStart) + 13;
    size_t commentsStart = content.find_first_not_of("\"", commentsTagEnd);
    size_t commentsEnd = content.find("\"", commentsStart);
    comments = content.substr(commentsStart, commentsEnd - commentsStart) == "true";

    size_t newFollowersTagEnd = content.find("\"newFollowers\": ", usernameTagStart) + 17;
    size_t newFollowersStart = content.find_first_not_of("\"", newFollowersTagEnd);
    size_t newFollowersEnd = content.find("\"", newFollowersStart);
    newFollowers = content.substr(newFollowersStart, newFollowersEnd - newFollowersStart) == "true";

    size_t messageRequestsTagEnd = content.find("\"messageRequests\": ", usernameTagStart) + 20;
    size_t messageRequestsStart = content.find_first_not_of("\"", messageRequestsTagEnd);
    size_t messageRequestsEnd = content.find("\"", messageRequestsStart);
    messageRequests = content.substr(messageRequestsStart, messageRequestsEnd - messageRequestsStart) == "true";

    User user(receivingUsername, likes, tags, comments, newFollowers, messageRequests);
    receivingUser = user;

    return true;
}
std::unordered_map<std::string, std::string> parsePosts(std::ifstream &postJSON)
{
    std::unordered_map<std::string, std::string> postIDToAuthorMap;

    std::string line;
    while(std::getline(postJSON, line)) 
    {
        size_t postIDTagStart = line.find("\"id\":\"") + 6;
        size_t postIDStart = line.find_first_not_of("\"", postIDTagStart);
        size_t postIDEnd = line.find("\"", postIDStart);
        std::string postID = line.substr(postIDStart, postIDEnd - postIDStart);

        size_t postAuthorTagStart = line.find("\"ownerUsername\":\"") + 17;
        size_t postAuthorStart = line.find_first_not_of("\"", postAuthorTagStart);
        size_t postAuthorEnd = line.find("\"", postAuthorStart);
        std::string postAuthor = line.substr(postAuthorStart, postAuthorEnd - postAuthorStart);

        postIDToAuthorMap[postID] = postAuthor;
    }
    return postIDToAuthorMap;
}